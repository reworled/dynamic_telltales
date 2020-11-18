#include "qsrdirectlistener.h"

#include <QDataStream>
#include <QNetworkDatagram>
#include <QTcpSocket>

QSRDirectListener::QSRDirectListener(QObject *parent) : QObject(parent)
{    
    m_socket = new QUdpSocket(this);
    m_socket->bind(QHostAddress::LocalHost, (quint16)310867);
    connect(m_socket, &QUdpSocket::readyRead, this, &QSRDirectListener::readDatagrams);
    m_hbTimer.setSingleShot(true);
    connect(&m_hbTimer, &QTimer::timeout, this, &QSRDirectListener::heartFailed);
}

void QSRDirectListener::readDatagrams()
{
    QByteArray data;
    while (m_socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = m_socket->receiveDatagram();
        data = datagram.data();
    }
    QDataStream in(&data, QIODevice::ReadOnly);
    int pulse;
    in >> pulse;
    processHeartbeat(pulse);
}


void QSRDirectListener::processHeartbeat(int interval)
{
    checkHeartbeat(true);
    m_hbTimer.stop();
    m_hbTimer.start(interval);
}

void QSRDirectListener::heartFailed()
{
    checkHeartbeat(false);
}

void QSRDirectListener::checkHeartbeat(bool heartBeat)
{
    if (heartBeat != m_heartBeating) {
        m_heartBeating = heartBeat;
        emit heartbeatChanged(m_heartBeating);
    }
}
