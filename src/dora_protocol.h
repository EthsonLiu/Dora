#ifndef SRC_DORA_PROTOCOL_H
#define SRC_DORA_PROTOCOL_H

#include "src/config.h"
#include "src/platform.h"

#include <QObject>
#include <QString>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAtomicInteger>
#include <QMutex>

class DoraProtocol : public QObject
{
    Q_OBJECT

public:

    explicit DoraProtocol(QObject* parent = nullptr);

private:

    void handleDatagrams(const QByteArray& data, const QHostAddress& sender);
    void sayHello();

public slots:

    void initializeFromPreferenceIni();

private slots:

    void newUdpDatagrams();

private:

    const QString        kHello;
    const QString        kSplitter;
    const int            kBroadcastInterval;
    const int            kCheckInteval;

    int                  m_udpPort;
    int                  m_tcpPort;

    QByteArray           m_hello;

    QAtomicInteger<bool> m_isBalloonMessageEnabled;

    QMutex               m_privateCodeMutex;
    QString              m_privateCode;

    QMutex               m_fileStorageDirMutex;
    QString              m_fileStorageDir;

    QUdpSocket*          m_udpServerSocket;
    QUdpSocket*          m_udpClientSocket;
    QTcpServer*          m_tcpServer;

};

#endif /** SRC_DORA_PROTOCOL_H */
