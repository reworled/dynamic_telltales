#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


#include <QtSafeRenderer/qsafelayoutresourcereader.h>
#include <QtSafeRenderer/qsafewindow.h>
#include <QtSafeRenderer/statemanager.h>
#include <eventhandler.h>
#include <safewindow.h>

#include <QQuickView>
#include <QWindow>

#include "safeswitchsignaller.h"
#include "safegaugecontroller.h"
#include "telltalesignalreader.h"
#include "qsrdirectlistener.h"

using namespace SafeRenderer;

StateManager *stateMan;
SafeSwitchSignaller *signaller;

// This could be further refactored down into a separate class.
void openTheSafeRenderer(QWindow *parent) {
    static QSafeLayoutResourceReader layout("/layoutdata/SafeCode/SafeCode.srl");
    static SafeWindow telltaleWindow(layout.size(), parent);
    try {
        stateMan = new StateManager(telltaleWindow, layout);
        for (quint32 i=0U;i<layout.count(); i++) {
            QSafeEventVisibility visible;
            visible.setId(layout.item(i).id());
            visible.setValue(0U);
            stateMan->handleEvent(visible);
        }
        QSRDirectListener *qsrdl = new QSRDirectListener();
        TelltaleSignalReader *ttsr = new TelltaleSignalReader(stateMan);
        SafeGaugeController *sgc = new SafeGaugeController(stateMan);
        QObject::connect(qsrdl, &QSRDirectListener::heartbeatChanged, ttsr, &TelltaleSignalReader::heartbeat);
        QObject::connect(qsrdl, &QSRDirectListener::heartbeatChanged, sgc, &SafeGaugeController::heartbeat);
        EventHandler eventHandler(stateMan);
        eventHandler.handleEvents();
    } catch(QSafeRenderer::RendererException rendererError) {
        printf("Failed to initialize renderer: %d\n", rendererError);
        fflush(stdout);
    } catch(...) {
        printf("Error occurred in event handler.\n");
        fflush(stdout);
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    const char *ipaddressLiteral = "QT_SAFERENDER_IPADDRESS";
    const char *portLiteral = "QT_SAFERENDER_PORT";
    QString ipaddressStr = qgetenv(ipaddressLiteral);
    QString portStr = qgetenv(portLiteral);
    if (ipaddressStr.isEmpty())
        qputenv(ipaddressLiteral, "127.0.0.1");
    if (portStr.isEmpty())
        qputenv(portLiteral, "32112");


    QQuickView *view = new QQuickView;
    signaller = new SafeSwitchSignaller();
    view->engine()->rootContext()->setContextProperty("safeconnect", signaller);
    view->setSource(QStringLiteral("qrc:/main.qml"));
    view->show();
    openTheSafeRenderer(view);
    return 0;
}
