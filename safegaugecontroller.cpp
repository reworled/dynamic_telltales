#include "safegaugecontroller.h"
#include "safeutil.h"

#include <QDataStream>
#include <QNetworkDatagram>
#include <QUdpSocket>

#include <qsafeevent.h>
#include <qsafestring.h>


SafeGaugeController::SafeGaugeController(SafeRenderer::StateManager *stateMan, QObject *parent) : QObject(parent)
  , m_stateMan(stateMan)
{
    m_socket = new QUdpSocket(this);
    m_socket->bind(QHostAddress::LocalHost, (quint16)310866);
    connect(m_socket, &QUdpSocket::readyRead, this, &SafeGaugeController::readDatagrams);
}

SafeGaugeController::~SafeGaugeController()
{
    m_socket->close();
}

void SafeGaugeController::heartbeat(bool heartbeat)
{
    m_heartbeat = heartbeat;
    setGaugeBGVisibility();
}

void SafeGaugeController::readDatagrams()
{
    QByteArray data;
    while (m_socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = m_socket->receiveDatagram();
        data = datagram.data();
    }
    QDataStream in(&data, QIODevice::ReadOnly);
    qreal mgv;
    in >> mgv;
    processMultiGaugeValue(mgv);
}

void SafeGaugeController::processMultiGaugeValue(qreal mgv)
{
    m_lastMgv = mgv;
    if (!m_heartbeat) {
        pushRpm(mgv);
        pushSpeed(mgv);
        pushFuel(mgv);
    }
}

void SafeGaugeController::pushRpm(qreal val)
{
    val *= 8000;
    int plainRpms = (int)val;
    QString str = QString::number(plainRpms);
    str += " rpm";
    setTextField("safeText1", str.toLatin1().data());
}
void SafeGaugeController::pushSpeed(qreal val)
{
    val *= 210;
    int plainSpeed = (int)val;
    QString str = QString::number(plainSpeed);
    str += " km/h";
    setTextField("safeText2", str.toLatin1().data());
}
void SafeGaugeController::pushFuel(qreal val)
{
    val *= 100;
    int plainLevel = (int)val;
    QString str = QString::number(plainLevel);
    str += "%";
    setTextField("safeText3", str.toLatin1().data());
}

void SafeGaugeController::setTextField(const char* fieldName, const char* text) {
    SafeRenderer::QSafeEventSetText setText;
    SafeRenderer::QSafeEventSetColor setColor;
    setText.setId(getIdNumber(fieldName));
    setText.setValue(text, SafeRenderer::safe_strlen(text));
    setColor.setId(getIdNumber(fieldName));
    setColor.setColor(255,255,255);
    if (m_stateMan) {
        m_stateMan->handleEvent(setText);
        m_stateMan->handleEvent(setColor);
    }
}


void SafeGaugeController::setGaugeBGVisibility()
{
    SafeRenderer::QSafeEventChangeState stateChangeCircle1;
    SafeRenderer::QSafeEventChangeState stateChangeCircle2;
    SafeRenderer::QSafeEventChangeState stateChangeCircle3;
    quint32 stateToGoTo = m_heartbeat ? getIdNumber("hidden") : getIdNumber("shown");
    quint32 circle1 = getIdNumber("circle1");
    quint32 circle2 = getIdNumber("circle2");
    quint32 circle3 = getIdNumber("circle3");
    stateChangeCircle1.setId(circle1);
    stateChangeCircle2.setId(circle2);
    stateChangeCircle3.setId(circle3);
    stateChangeCircle1.setName(stateToGoTo);
    stateChangeCircle2.setName(stateToGoTo);
    stateChangeCircle3.setName(stateToGoTo);
    if (m_stateMan) {
        m_stateMan->handleEvent(stateChangeCircle1);
        m_stateMan->handleEvent(stateChangeCircle2);
        m_stateMan->handleEvent(stateChangeCircle3);
    }

    if (m_heartbeat) {
        setTextField("safeText3", "");
        setTextField("safeText1", "");
        setTextField("safeText2", "");
    }
    else {
        pushRpm(m_lastMgv);
        pushSpeed(m_lastMgv);
        pushFuel(m_lastMgv);
    }

}
