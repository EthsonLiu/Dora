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
#include <QList>
#include <QHostAddress>

/**
 * Peer infomation.
 */
struct Peer
{
    QString username;
    QString platform;
    uint    lastUpdatedTime;
};

/**
 * The operation of Peer.
 *
 * PeerOperation::remove is meaning the Peer is levaing,
 * and PeerOperation::add is meaning the Peer is coming。
 */
enum class PeerOperation
{
    remove,
    add
};

/**
 * Dora protocol, including UDP and TCP.
 */
class DoraProtocol : public QObject
{
    Q_OBJECT

public:

    explicit DoraProtocol(QObject* parent = nullptr);

    /**
     * Init UDP and TCP objects, and start their timers to process.
     */
    void init();

signals:

    /**
     * To emit a signal of some Peer is leaving or coming.
     *
     * @param peerIP
     *        The IP of peer.
     *
     * @param peer
     *        Which Peer is leaving or coming.
     *
     * @param opt
     *        Is leaving or coming?
     */
    void peerChanged(const QString& peerIP, const Peer& peer, PeerOperation opt);

private:

    /**
     * Handle the UDP message. Parse and check it, and then emit peerChanged.
     *
     * @param data
     *        The UDP message.
     *
     * @param sender
     *        The sender.
     */
    void handleDatagrams(const QByteArray& data, const QHostAddress& sender);

    /**
     * Get the broadcast addresses of all the NICs.
     */
    QList<QHostAddress> getAllNICsBroadcastAddresses();

    /**
     * Get the IP addresses of all the NICs.
     */
    QList<QHostAddress> getAllNICsIPAddresses();

    /**
     * Whether or not ip is existed in local NIC ips(returned by getAllNICsIPAddresses()).
     */
    bool isInLocalIPAddresses(const QString& ip);

public slots:

    /**
     * Read preference file and re-initialize.
     */
    void initializeFromPreferenceIni();

private slots:

    /**
     * To broadcast.
     */
    void sayHello();

    /**
     * Receive UDP messages.
     */
    void newUdpDatagrams();

    /**
     * Check all peers to judge if some had left. If so, remove them.
     */
    void peersCheck();

private:

    const QString        kHello;
    const QString        kSplitter;
    const int            kBroadcastInterval;

    /**
     * The interval of function peersCheck called
     */
    const int            kCheckInterval;

    /**
     * If currentTime - Peer.lastUpdatedTime >= kDeadSpan,
     * that is to say, the peer has dead, we should remove it
     * form list.
     */
    const int            kDeadSpan;

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

    /**
     * The key of m_peersMap is the IP of the Peer,
     * for example, "192.168.70.1".
     */
    QMutex               m_peersMapMutex;
    QMap<QString, Peer>  m_peersMap;

};

#endif /** SRC_DORA_PROTOCOL_H */
