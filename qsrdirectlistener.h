#ifndef QSRDIRECTLISTENER_H
#define QSRDIRECTLISTENER_H

#include <QUdpSocket>
#include <QTimer>
#include <QUdpSocket>
#include <QObject>

#include <qsafeevent.h>


class QSRDirectListener : public QObject
{
    Q_OBJECT
public:
    explicit QSRDirectListener(QObject *parent = nullptr);

    bool heartBeating() { return m_heartBeating; }

signals:
    void heartbeatChanged(bool heartBeat);

public slots:
    void heartFailed();
    void readDatagrams();

private:
    QUdpSocket *m_socket;
    QTimer m_hbTimer;
    bool m_heartBeating = false;

    void checkHeartbeat(bool heartBeat);
    void processHeartbeat(int interval);
};

#endif // QSRDIRECTLISTENER_H
