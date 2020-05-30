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

#include "src/dukto_protocol.h"
#include "src/project.h"
#include "src/platform.h"

#include <QMutexLocker>
#include <QSettings>
#include <QByteArray>

DuktoProtocol::DuktoProtocol(QObject* parent) : QObject(parent)
{
    m_udpServerSocket = new QUdpSocket(this);
    m_udpClientSocket = new QUdpSocket(this);
    m_tcpServer       = new QTcpServer(this);

    initializeFromPreferenceIni();
}

QString DuktoProtocol::getSystemSignature()
{
    static QString signature;

    if (signature.isEmpty() == false)
        return signature;

    signature = Platform::getSystemUsername();

    return signature;
}

void DuktoProtocol::handleDatagrams(const QByteArray& data, QHostAddress& sender)
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
    default:
    {
        qDebug() << QString("unknown type 0x%1.").arg(type, 2, 16, QLatin1Char('0'));
    }
    }
}

void DuktoProtocol::initializeFromPreferenceIni()
{
    QSettings setting(Project::getApplicationPreferenceIniPath(), QSettings::IniFormat);

    static bool isFirst = true;
    if (isFirst)
    {
        isFirst = false;

        m_udpPort = setting.value("udp_port").toInt();
        m_tcpPort = setting.value("tcp_port").toInt();

        m_udpServerSocket->bind(static_cast<quint16>(m_udpPort));
        connect(m_udpServerSocket, &QUdpSocket::readyRead, this, &DuktoProtocol::newUdpDatagrams);
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

void DuktoProtocol::newUdpDatagrams()
{
    while (m_udpServerSocket->hasPendingDatagrams())
    {
        QHostAddress sender;
        QByteArray datagram;

        datagram.resize(static_cast<int>(m_udpServerSocket->pendingDatagramSize()));
        int size = static_cast<int>(m_udpServerSocket->readDatagram(datagram.data(),
                                                                    static_cast<qint64>(datagram.size()),
                                                                    &sender));
        datagram.resize(size);

        handleDatagrams(datagram, sender);
     }
}

