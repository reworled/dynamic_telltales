import QtQuick 2.0

Telltale {

    id: root
    property real lightAngle: showHighBeams ? 0 : -14
    Behavior on lightAngle {
        NumberAnimation { duration: animationSpeed; easing.type: Easing.InOutCubic }
    }

    property int animationSpeed: 1000

    doSetState: function(state) {
        showHighBeams = state
    }

    Column {
        x: 5
        y: 13
        spacing: 4
        Repeater {
            model: 5
            delegate: Rectangle {
                height: 4
                radius: height/2
                width: 20
                color: showHighBeams? "#00519a" : "#00935f"
                Behavior on color {
                    ColorAnimation {
                        duration: animationSpeed
                    }
                }
                transform: Rotation {
                    origin.x: 20
                    origin.y: 0
                    angle: lightAngle
                }
            }
        }
    }

    property bool showHighBeams: false
    Image {
        anchors.centerIn: parent
        width: 60; height: 60
        source: "telltales/beam-green.png"
    }
    Image {
        anchors.centerIn: parent
        width: 60; height: 60
        source: "telltales/beam-blue.png"
        opacity: showHighBeams ? 1 : 0
        Behavior on opacity {
            NumberAnimation { duration: animationSpeed }
        }
    }
}
