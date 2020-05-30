#include "src/dora_protocol.h"
#include "src/project.h"
#include "src/platform.h"

#include <QMutexLocker>
#include <QSettings>
#include <QByteArray>

DoraProtocol::DoraProtocol(QObject* parent) : QObject(parent)
{
    m_udpServerSocket = new QUdpSocket(this);
    m_udpClientSocket = new QUdpSocket(this);
    m_tcpServer       = new QTcpServer(this);

    m_hello.append(0x01);
    m_hello.append("");
    m_goodbye.append(0x03);
    m_goodbye.append("Bye Bye");

    initializeFromPreferenceIni();
}

QString DoraProtocol::getSystemSignature()
{
    static QString signature;

    if (signature.isEmpty() == false)
        return signature;

    signature = Platform::getSystemUsername();

    return signature;
}

void DoraProtocol::handleDatagrams(const QByteArray& data, QHostAddress& sender)
{
    int type = static_cast<int>(data[0]);

    switch (type)
    {
    case 0x01: /** broadcast */
    {
        break;
    }
    case 0x03: /** goodbye */
    {
        break;
    }
    }
}

void DoraProtocol::sayHello()
{
    m_udpServerSocket->writeDatagram(QByteArray(), QHostAddress::Broadcast, m_udpPort);
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

