#ifndef SAFESWITCHSIGNALLER_H
#define SAFESWITCHSIGNALLER_H

#include <QObject>
#include <QVariant>

class SafeSwitchSignaller : public QObject
{
    Q_OBJECT
public:
    explicit SafeSwitchSignaller(QObject *parent = nullptr);

public slots:
    void setTelltale(int telltale, bool on, QVariant stateData = QVariant());
    void sendMultiGaugeValye(qreal mgv);
    void sendHeartBeat(int interval = 1500);

signals:

};

#endif // SAFESWITCHSIGNALLER_H
