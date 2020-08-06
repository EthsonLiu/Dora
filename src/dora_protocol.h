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
#include <QMap>

struct Peer
{
    QString username;
    QString platform;
    uint64_t lastUpdatedTime;
};

enum class PeerOperation
{
    remove,
    add
};

class DoraProtocol : public QObject
{
    Q_OBJECT

public:

    explicit DoraProtocol(QObject* parent = nullptr);
    void init();

signals:

    void peerChanged(QString& peerIP, const Peer& peer, PeerOperation);

private:

    void handleDatagrams(const QByteArray& data, const QHostAddress& sender);

public slots:

    void initializeFromPreferenceIni();

private slots:

    void sayHello();
    void newUdpDatagrams();
    void peersCheck();

private:

    const QString        kHello;
    const QString        kSplitter;
    const int            kBroadcastInterval;
    const int            kCheckInterval;

    int                  m_udpPort;
    int                  m_tcpPort;

    QByteArray           m_hello;

    QAtomicInteger<int>  m_isBalloonMessageEnabled;

    QMutex               m_privateCodeMutex;
    QString              m_privateCode;

    QMutex               m_fileStorageDirMutex;
    QString              m_fileStorageDir;

    QUdpSocket*          m_udpServerSocket;
    QUdpSocket*          m_udpClientSocket;
    QTcpServer*          m_tcpServer;

    QMutex               m_peersMapMutex;
    QMap<QString, Peer>  m_peersMap;

};

#endif /** SRC_DORA_PROTOCOL_H */
