#ifndef TelltaleSignalReader_H
#define TelltaleSignalReader_H

#include <QObject>
#include <QVariant>
#include <QTimer>
#include <statemanager.h>

class QUdpSocket;

struct Telltale {
    int ui_id;
    quint32 qsr_id;
    int home_x;
    int home_y;
};

class TelltaleSignalReader : public QObject
{
    Q_OBJECT
public:
    explicit TelltaleSignalReader(SafeRenderer::StateManager *stateManager, QObject *parent = nullptr);

public slots:
    void heartbeat(bool heartBeat);
    void processTellTale(int telltale, bool on, QVariant stateData);

signals:


private:
    QUdpSocket *m_socket = nullptr;
    SafeRenderer::StateManager * m_stateMan = nullptr;

    QVector<Telltale> m_allTelltales;
    QList<Telltale*> m_activeTelltales;

    QTimer m_tellTalesDelay;

    bool m_heartbeat = true;


    void initTelltaleList();

    bool isActiveCurrently(int telltale_ui_id);
    Telltale *getTelltale(int telltale_ui_id);

    void scheduleTellTalesOn();
    void switchTelltale(quint32 telltale, bool on = true);
    void sendTelltaleHome(Telltale *telltale);
    void moveTelltale(quint32 id, int x, int y);

private slots:
    void readDatagrams();
    void switchOnAllTelltales();
    void switchOffAllTelltales();
};

#endif // TelltaleSignalReader_H
