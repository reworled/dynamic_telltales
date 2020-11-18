#ifndef SAFEGAUGECONTROLLER_H
#define SAFEGAUGECONTROLLER_H

#include <QObject>
#include <statemanager.h>

class QUdpSocket;

class SafeGaugeController : public QObject
{
    Q_OBJECT
public:
    explicit SafeGaugeController(SafeRenderer::StateManager *stateMan, QObject *parent = nullptr);
    ~SafeGaugeController();

public slots:
    void heartbeat(bool heartbeat);

signals:

private:
    QUdpSocket *m_socket = nullptr;
    SafeRenderer::StateManager *m_stateMan = nullptr;
    qreal m_lastMgv = 0.91565;

    bool m_heartbeat = true;

    void processMultiGaugeValue(qreal mgv);
    void setGaugeBGVisibility();

    void pushRpm(qreal val);
    void pushSpeed(qreal val);
    void pushFuel(qreal val);

    void setTextField(const char *fieldName, const char *text);
private slots:
    void readDatagrams();
};

#endif // SAFEGAUGECONTROLLER_H
