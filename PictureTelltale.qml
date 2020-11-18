import QtQuick 2.0

Telltale {

    property alias source: image.source

    Image {
        id: image
        width: 60; height: 60
        anchors.centerIn: parent
    }
}
