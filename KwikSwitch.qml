import QtQuick 2.0

Image {

    id: root
    property bool powered: false
    property alias iconSrc: icon.source

    source: "switchon.png"

    Image {
        id: offski
        anchors.fill: parent
        source: "switchoff.png"
        opacity: powered ? 0 : 1
        Behavior on opacity {
            NumberAnimation {
                duration: 200
            }
        }
    }

    Image {
        id: icon
        width: 20//parent.width - parent.sourceSize.width
        anchors.left: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        fillMode: Image.PreserveAspectFit
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.powered = !root.powered
    }
}
