#include "safeswitchsignaller.h"

#include <QDataStream>
#include <QUdpSocket>

SafeSwitchSignaller::SafeSwitchSignaller(QObject *parent) : QObject(parent)
{

}

void SafeSwitchSignaller::setTelltale(int telltale, bool on, QVariant stateData)
{
    QByteArray data;
    QDataStream ds(&data, QIODevice::WriteOnly);
    ds << telltale << on << stateData;

    QUdpSocket outSock;
    outSock.writeDatagram(data.data(), data.length(), QHostAddress::LocalHost, (quint16)310865);
    outSock.close();
}

void SafeSwitchSignaller::sendMultiGaugeValye(qreal mgv)
{
    QByteArray data;
    QDataStream ds(&data, QIODevice::WriteOnly);
    ds << mgv;

    QUdpSocket outSock;
    outSock.writeDatagram(data.data(), data.length(), QHostAddress::LocalHost, (quint16)310866);
    outSock.close();
}

void SafeSwitchSignaller::sendHeartBeat(int interval)
{
    QByteArray data;
    QDataStream ds(&data, QIODevice::WriteOnly);
    ds << interval;

    QUdpSocket outSock;
    outSock.writeDatagram(data.data(), data.length(), QHostAddress::LocalHost, (quint16)310867);
    outSock.close();
}
