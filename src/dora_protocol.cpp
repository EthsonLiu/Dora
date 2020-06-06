#include "src/dora_protocol.h"
#include "src/project.h"
#include "src/platform.h"

#include <QMutexLocker>
#include <QSettings>
#include <QByteArray>
#include <QStringList>

DoraProtocol::DoraProtocol(QObject* parent) :
    QObject(parent),
    kHello("dora hello"),
    kSplitter(",|"),
    kBroadcastInterval(1500),
    kCheckInteval(kBroadcastInterval * 3)
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

void DoraProtocol::handleDatagrams(const QByteArray& data, const QHostAddress& sender)
{
    QStringList strList = QString(data.data()).split(kSplitter);
    if (strList.size() >= 4)
    {
        if (strList[0] == kHello)
        {

        }
    }
}

void DoraProtocol::sayHello()
{
    QByteArray packet;
    packet.append(m_hello);

    {
        QMutexLocker locker(&m_privateCodeMutex);
        packet.append(m_privateCode);
    }

    m_udpServerSocket->writeDatagram(packet, QHostAddress::Broadcast, static_cast<quint16>(m_udpPort));
}

void DoraProtocol::initializeFromPreferenceIni()
{
    QSettings setting(Project::getApplicationPreferenceIniPath(), QSettings::IniFormat);

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

    m_isBalloonMessageEnabled = setting.value("balloon_message_enabled").toBool();

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

