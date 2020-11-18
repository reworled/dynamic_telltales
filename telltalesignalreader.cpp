#include "telltalesignalreader.h"
#include "safeutil.h"

#include <QDataStream>
#include <QNetworkDatagram>
#include <QUdpSocket>

#include <qsafechecksum.h>
#include <qsafeevent.h>
#include <qsafestring.h>


TelltaleSignalReader::TelltaleSignalReader(SafeRenderer::StateManager *stateManager, QObject *parent) : QObject(parent)
  , m_stateMan(stateManager)
{
    m_socket = new QUdpSocket(this);
    m_socket->bind(QHostAddress::LocalHost, (quint16)310865);
    connect(m_socket, &QUdpSocket::readyRead, this, &TelltaleSignalReader::readDatagrams);
    initTelltaleList();
    m_tellTalesDelay.setSingleShot(true);
    connect(&m_tellTalesDelay, &QTimer::timeout, this, &TelltaleSignalReader::switchOnAllTelltales);
}

void TelltaleSignalReader::readDatagrams()
{
    QByteArray data;
    while (m_socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = m_socket->receiveDatagram();
        data = datagram.data();
    }
    QDataStream in(&data, QIODevice::ReadOnly);
    int telltale; bool on; QVariant stateData;
    in >> telltale >> on >> stateData;
    processTellTale(telltale, on, stateData);
}

void TelltaleSignalReader::processTellTale(int telltale, bool on, QVariant stateData)
{
    Q_UNUSED(stateData)
    switchOffAllTelltales();
    Telltale *tt = getTelltale(telltale);
    if (on)
    {
        if (!isActiveCurrently(telltale))
        {
            m_activeTelltales.append(tt);
        }
    }
    else
    {
        int indexOf = m_activeTelltales.indexOf(tt);
        if (-1 != indexOf) {
            m_activeTelltales.removeAt(indexOf);
        }
    }
    scheduleTellTalesOn();
}

bool TelltaleSignalReader::isActiveCurrently(int telltale_ui_id)
{
    for (auto telltale : m_activeTelltales)
    {
        if (telltale_ui_id == telltale->ui_id)
        {
            return true;
        }
    }
    return false;
}

Telltale *TelltaleSignalReader::getTelltale(int telltale_ui_id)
{
    for (int i = 0; i < m_allTelltales.length(); i++)
    {
        if (telltale_ui_id == m_allTelltales[i].ui_id)
        {
            return &m_allTelltales[i];
        }
    }
    return nullptr;
}


void TelltaleSignalReader::initTelltaleList()
{
    m_allTelltales.append({0, getIdNumber("fullBeamTelltale"), 640, 225});
    m_allTelltales.append({0, getIdNumber("lowBeamTelltale"), 700, 225});
    m_allTelltales.append({1, getIdNumber("batteryTelltale"), 580, 225});
    m_allTelltales.append({2, getIdNumber("coolantTelltale"), 760, 225});
    m_allTelltales.append({3, getIdNumber("oilTelltale"), 580, 285});
    m_allTelltales.append({4, getIdNumber("parkingTelltale"), 640, 285});
    m_allTelltales.append({5, getIdNumber("warningTelltale"), 700, 285});
}

void TelltaleSignalReader::switchOffAllTelltales()
{
    for (auto telltale : m_activeTelltales)
    {
        switchTelltale(telltale->qsr_id, false);
        sendTelltaleHome(telltale);
    }
}

void TelltaleSignalReader::switchOnAllTelltales()
{
    static int step = 70;
    int current_x = 195;
    static int the_y = 370;
    for (auto telltale : m_activeTelltales)
    {
        moveTelltale(telltale->qsr_id, current_x, the_y);
        current_x += step;
        switchTelltale(telltale->qsr_id);
    }
}

void TelltaleSignalReader::switchTelltale(quint32 id, bool on)
{
    SafeRenderer::QSafeEventVisibility visible;
    visible.setId(id);
    visible.setValue((on?1U:0U));
    m_stateMan->handleEvent(visible);
}

void TelltaleSignalReader::sendTelltaleHome(Telltale *telltale)
{
    moveTelltale(telltale->qsr_id, telltale->home_x, telltale->home_y);
}

void TelltaleSignalReader::moveTelltale(quint32 id, int x, int y)
{
    SafeRenderer::QSafeEventPosition position;
    position.setId(id);
    position.setX(x);
    position.setY(y);
    if (m_stateMan) {
        m_stateMan->handleEvent(position);
    }
}

void TelltaleSignalReader::scheduleTellTalesOn()
{
    if (m_heartbeat) {
        if (m_tellTalesDelay.isActive()) {
            m_tellTalesDelay.stop();
        }
        m_tellTalesDelay.start(500);
    }
    else {
        switchOnAllTelltales();
    }
}

void TelltaleSignalReader::heartbeat(bool heartbeat)
{
    m_heartbeat = heartbeat;
}
