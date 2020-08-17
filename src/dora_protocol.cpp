#include "src/dora_protocol.h"
#include "src/project.h"
#include "src/platform.h"

#include <QMutexLocker>
#include <QSettings>
#include <QByteArray>
#include <QStringList>
#include <QTimer>
#include <QDateTime>
#include <QNetworkInterface>

DoraProtocol::DoraProtocol(QObject* parent) :
    QObject(parent),
    kHello("dora hello"),
    kSplitter(",|"),
    kBroadcastInterval(3000),
    kCheckInterval(kBroadcastInterval * 2),
    kDeadSpan(kBroadcastInterval * 2)
{
    m_udpServerSocket = new QUdpSocket(this);
    m_udpClientSocket = new QUdpSocket(this);
    m_tcpServer       = new QTcpServer(this);

    m_hello.append(kHello);
    m_hello.append(kSplitter);
    m_hello.append(Platform::getPlatformName());
    m_hello.append(kSplitter);
    m_hello.append(Platform::getSystemUsername());
    m_hello.append(kSplitter);

    initializeFromPreferenceIni();
}

void DoraProtocol::init()
{
    /** UDP server */
    QTimer* timer1 = new QTimer(this);
    timer1->setInterval(kBroadcastInterval);
    connect(timer1, &QTimer::timeout, this, &DoraProtocol::sayHello);
    timer1->start();

    /** UDP client */
    m_udpClientSocket->bind(static_cast<quint16>(m_udpPort), QUdpSocket::ShareAddress);
    connect(m_udpClientSocket, &QUdpSocket::readyRead, this, &DoraProtocol::newUdpDatagrams);

    /** peers check */
    QTimer* timer2 = new QTimer(this);
    timer2->setInterval(kCheckInterval);
    connect(timer2, &QTimer::timeout, this, &DoraProtocol::peersCheck);
    timer2->start();
}

void DoraProtocol::handleDatagrams(const QByteArray& data, const QHostAddress& sender)
{
    QString privateCode;

    {
        QMutexLocker locker(&m_privateCodeMutex);
        privateCode = m_privateCode;
    }

    quint32 num = sender.toIPv4Address();
    QString peerIP = QString("%1.%2.%3.%4").arg((num >> 24) & 0xFF).arg((num >> 16) & 0xFF).arg((num >> 8) & 0xFF).arg(num & 0xFF);

    QStringList strList = QString(data.data()).split(kSplitter);
    if (strList.size() >= 4)
    {
        if (strList[0] == kHello &&
            strList[3] == privateCode &&
            isInLocalIPAddresses(peerIP) == false)
        {
            Peer peer;
            peer.lastUpdatedTime = QDateTime::currentDateTime().toTime_t();
            peer.platform = strList[1];
            peer.username = strList[2];
            emit peerChanged(peerIP, peer, PeerOperation::add);

#if 1
            qDebug() << "[DoraProtocol::handleDatagrams]" << peerIP << peer.lastUpdatedTime << peer.platform << peer.username;
#endif
        }
    }
}

QList<QHostAddress> DoraProtocol::getAllNICsBroadcastAddresses()
{
    QList<QHostAddress> addrsList;
    QList<QNetworkInterface> interfacesList = QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface interface, interfacesList)
    {
        foreach (QNetworkAddressEntry entry, interface.addressEntries())
        {
            QHostAddress addr = entry.broadcast();
            if (addr != QHostAddress::Null &&
                entry.ip() != QHostAddress::LocalHost &&
                entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                addrsList.push_back(addr);
            }
        }
    }

    return addrsList;
}

QList<QHostAddress> DoraProtocol::getAllNICsIPAddresses()
{
    QList<QHostAddress> ipsList;
    QList<QNetworkInterface> interfacesList = QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface interface, interfacesList)
    {
        foreach (QNetworkAddressEntry entry, interface.addressEntries())
        {
            QHostAddress ip = entry.ip();
            if (ip != QHostAddress::Null &&
                entry.ip() != QHostAddress::LocalHost &&
                entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                ipsList.push_back(ip);
            }
        }
    }

    return ipsList;
}

bool DoraProtocol::isInLocalIPAddresses(const QString &ip)
{
    QList<QHostAddress> ipsList = getAllNICsIPAddresses();
    QHostAddress addr(ip);

    if (ipsList.indexOf(addr) == -1) /** not existed */
        return false;

    return true;
}

void DoraProtocol::sayHello()
{
    QByteArray packet;
    packet.append(m_hello);

    {
        QMutexLocker locker(&m_privateCodeMutex);
        packet.append(m_privateCode);
    }

    /** multi-NIC (NIC is "Network Interface Card") */

    m_udpServerSocket->writeDatagram(packet, QHostAddress::Broadcast, static_cast<quint16>(m_udpPort));
}

void DoraProtocol::initializeFromPreferenceIni()
{
    QSettings setting(Project::getApplicationPreferenceIniFile(), QSettings::IniFormat);

    static bool isFirst = true;
    if (isFirst)
    {
        isFirst = false;

        m_udpPort = setting.value("udp_port").toInt();
        m_tcpPort = setting.value("tcp_port").toInt();

        m_udpClientSocket->bind(static_cast<quint16>(m_udpPort), QUdpSocket::ShareAddress);
        connect(m_udpClientSocket, &QUdpSocket::readyRead, this, &DoraProtocol::newUdpDatagrams);
    }

    {
        QMutexLocker locker(&m_fileStorageDirMutex);
        m_fileStorageDir = setting.value("file_storage_path").toString();
    }

    m_isBalloonMessageEnabled = setting.value("balloon_message_enabled").toInt();

    if (setting.value("private_lan_enabled").toBool())
    {
        QMutexLocker locker(&m_privateCodeMutex);
        m_privateCode = setting.value("private_code").toString();
    }
}

void DoraProtocol::newUdpDatagrams()
{
    while (m_udpClientSocket->hasPendingDatagrams())
    {
        QHostAddress sender;
        QByteArray datagram;

        datagram.resize(static_cast<int>(m_udpClientSocket->pendingDatagramSize()));
        int size = static_cast<int>(m_udpClientSocket->readDatagram(datagram.data(),
                                                                    static_cast<qint64>(datagram.size()),
                                                                    &sender));
        datagram.resize(size);

        handleDatagrams(datagram, sender);
    }
}

void DoraProtocol::peersCheck()
{
    QMap<QString, Peer> temp;

    {
        QMutexLocker locker(&m_peersMapMutex);
        temp = m_peersMap; /** copy */
    }

    uint currentTime = QDateTime::currentDateTime().toTime_t();
    for (auto it = temp.begin(); it != temp.end(); ++it)
    {
        QString ip = it.key();
        Peer peer = it.value();

        if (qAbs(currentTime - peer.lastUpdatedTime) >= kDeadSpan)
            emit peerChanged(ip, peer, PeerOperation::remove);
    }
}

