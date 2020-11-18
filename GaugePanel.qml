import QtQuick 2.0

import Qt.SafeRenderer 1.2

Rectangle {
    color: "#781514"

    property real valye: 0

    SimpleRoundGauge {
        id: speed
        width: 350
        height: width
        backgroundImage: "speedbg.png"
        centerCapSource: "speedcap.png"
        needleImage: "genericneedle.png"
        value: valye * range
        maximumValue: 210
        minimumValue: 0
        minimumRotation: 58
        maximumRotation: (360-58)

        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    }
    SimpleRoundGauge {
        id: tach
        width: 225
        height: width
        backgroundImage: "tachbg.png"
        centerCapSource: "tachcap.png"
        needleImage: "genericneedle.png"
        value: valye * range
        maximumValue: 8000
        minimumValue: 0
        minimumRotation: 58
        maximumRotation: (360-58)
    }
    SimpleRoundGauge {
        id: fuel
        width: 225
        height: width
        backgroundImage: "fulebg.png"
        centerCapSource: "fuelcap.png"
        needleImage: "genericneedle.png"
        value: valye * range
        maximumValue: 1
        minimumValue: 0
        minimumRotation: 58
        maximumRotation: 210
        anchors.right: parent.right
    }

    Rectangle {
        width: (60 + 10) * 6
        height: 60 + 10
        color: "black"
        radius: 9
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: speed.bottom
        anchors.topMargin: 15

        Timer {
            running: true
            interval: 250
            repeat: true
            onTriggered: {
                safeconnect.sendHeartBeat((interval + 500))
            }
        }

        Row {
            anchors.fill: parent
            Repeater {
                anchors.fill: parent
                model: ttm.showingTelltales
            }
        }

    }
    property TelltaleManager ttm: TelltaleManager {}
    property SafeMessage message
}
