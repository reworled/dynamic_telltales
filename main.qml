import QtQuick 2.12
import QtQuick.Window 2.12
import QtQml.Models 2.12
import Qt.SafeRenderer 1.2

Rectangle {

    visible: true
    width: 880
    height: 480
    color: "black"

    Loader {
        id: lowda
        width: 800
        height: 480
        sourceComponent: gaugeCompo
    }

    Component {
        id: gaugeCompo
        GaugePanel {
            valye: slid.value
            ttm: tom
            Image {
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                anchors.margins: 5
                source: "car-logo.png"
                width: 150
                fillMode: Image.PreserveAspectFit
            }
        }
    }

    Component {
        id: nothing
        Item {

        }
    }


    // TTM will use a proprietary internal message format
    // to send telltale signals to the C++ safeui
    TelltaleManager {
        id: tom
    }

    Column {
        id: col
        anchors.top: parent.top
        anchors.right: parent.right
        width: 70
        KwikSwitch {
            id: ks1
            iconSrc: "telltales/beam-green.png"
            onPoweredChanged: {
                tom.setTelltale(0, powered, false)
                if (!powered) {
                    ks2.powered = powered
                }
            }
        }
        KwikSwitch {
            id: ks2
            iconSrc: "telltales/beam-blue.png"
            onPoweredChanged: {
                if (powered) {
                    ks1.powered = powered
                    tom.setTelltale(0, powered, true)
                }
                else {
                    if (ks1.powered)
                        tom.setTelltale(0, true, false)
                }
            }
        }
        KwikSwitch {
            iconSrc: "telltales/battery.svg"
            onPoweredChanged: {
                tom.setTelltale(1, powered, "")
            }
        }
        KwikSwitch {
            iconSrc: "telltales/engine-coolant.svg"
            onPoweredChanged: {
                tom.setTelltale(2, powered, "")
            }
        }
        KwikSwitch {
            iconSrc: "telltales/oil.svg"
            onPoweredChanged: {
                tom.setTelltale(3, powered, "")
            }
        }
        KwikSwitch {
            iconSrc: "telltales/parking-lights.svg"
            onPoweredChanged: {
                tom.setTelltale(4, powered, "")
            }
        }
        KwikSwitch {
            iconSrc: "telltales/warning.svg"
            onPoweredChanged: {
                tom.setTelltale(5, powered, "")
            }
        }
    }

    Rectangle {
        id: crashButton
        width: 70
        height: 70
        radius: 30
        anchors.margins: 10
        color: ma.pressed ? Qt.darker("red") : "red"
        anchors.top: col.bottom
        anchors.horizontalCenter: col.horizontalCenter
        Text {
            anchors.centerIn: parent
            text: lowda.sourceComponent === gaugeCompo ? qsTr("CRASH") : qsTr("reload")
        }
        MouseArea {
            id: ma
            anchors.fill: parent
            onClicked: {
                if (lowda.sourceComponent === gaugeCompo) {
                    lowda.sourceComponent = nothing
                } else {
                    lowda.sourceComponent = gaugeCompo
                }
            }
        }
    }
    Rectangle {
        color: Qt.darker("#c0c0c0")
        width: 60
        border.width: 4
        border.color: Qt.darker(color)
        anchors.bottom: parent.bottom
        anchors.top: crashButton.bottom
        anchors.horizontalCenter: crashButton.horizontalCenter
        Rectangle {
            anchors.centerIn: parent
            height: parent.height * 0.9
            width: 6
            color: Qt.darker(parent.color)
        }

        MouseArea {
            id: slid
            anchors.fill: parent
            property real value: 1 - pip.y/slid.height
            Component.onCompleted: safeconnect.sendMultiGaugeValye(value)
            onValueChanged: safeconnect.sendMultiGaugeValye(value)
            onClicked: {
                pip.y = mouse.y
            }
            Rectangle {
                id: pip
                y: 20
                width: parent.width * 0.8; height: 15
                color: "#c0c0c0"
                border.color: Qt.darker("#c0c0c0")
                anchors.horizontalCenter: parent.horizontalCenter
                MouseArea {
                    anchors.fill: parent
                    drag.target: parent
                    drag.axis: Drag.YAxis
                    drag.maximumY: slid.height - 20
                    drag.minimumY: 2
                }
            }
        }
    }

    SafeCode {

    }
}

