/**
 * DUKTO - A simple, fast and multi-platform file transfer tool for LAN users
 * Copyright (C) 2011 Emanuele Colombo
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef SRC_DUKTO_PROTOCOL_H
#define SRC_DUKTO_PROTOCOL_H

#include "src/config.h"
#include "src/platform.h"

#include <QObject>
#include <QString>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAtomicInteger>
#include <QMutex>

class DuktoProtocol : public QObject
{
    Q_OBJECT

public:

    explicit DuktoProtocol(QObject* parent = nullptr);
    QString getSystemSignature();

private:

    void handleDatagrams(const QByteArray& data, QHostAddress& sender);

public slots:

    void initializeFromPreferenceIni();

private slots:

    void newUdpDatagrams();

private:

    int                  m_udpPort;
    int                  m_tcpPort;

    QAtomicInteger<bool> m_isBalloonMessageEnabled;

    QMutex               m_privateCodeMutex;
    QString              m_privateCode;

    QMutex               m_fileStorageDirMutex;
    QString              m_fileStorageDir;

    QUdpSocket*          m_udpServerSocket;
    QUdpSocket*          m_udpClientSocket;
    QTcpServer*          m_tcpServer;

};

#endif /** SRC_DUKTO_PROTOCOL_H */
