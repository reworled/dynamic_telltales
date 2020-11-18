import QtQuick 2.0

import Qt.SafeRenderer 1.2

Item {
    // Value must be hard-coded #SafetyFirst
    width: 880
    height: 480

    property color yellow: "#c0aa11"
    property color blue: "#00139a"
    property color red: "#B31111"
    property color green: "#00935f"

    SafePicture {
        id: batteryTelltale
        objectName: "batteryTelltale"
        y: 225; x: 580
        width: 60
        height: 60
        visible: false
        source: "dats/battery.dat"
        color: red
    }
    SafePicture {
        id: fullBeamTelltale
        objectName: "fullBeamTelltale"
        y: 225; x: 640
        width: 60
        height: 60
        visible: false
        source: "dats/beam-blue.dat"
        color: blue
    }
    SafePicture {
        id: lowBeamTelltale
        objectName: "lowBeamTelltale"
        y: 225; x: 700
        width: 60
        height: 60
        visible: false
        source: "dats/beam-grrn.dat"
        color: green
    }
    SafePicture {
        id: coolantTelltale
        objectName: "coolantTelltale"
        y: 225; x: 760
        width: 60
        height: 60
        visible: false
        source: "dats/engine-coolant.dat"
        color: red
    }
    SafePicture {
        id: oilTelltale
        objectName: "oilTelltale"
        y: 285; x: 580
        width: 60
        height: 60
        visible: false
        source: "dats/oil.dat"
        color: yellow
    }
    SafePicture {
        id: parkingTelltale
        objectName: "parkingTelltale"
        y: 285; x: 640
        width: 60
        height: 60
        visible: false
        source: "dats/parking-lights.dat"
        color: green
    }
    SafePicture {
        id: warningTelltale
        objectName: "warningTelltale"
        y: 285; x: 700
        width: 60
        height: 60
        visible: false
        source: "dats/warning.dat"
        color: yellow
    }

    SafeImage {
        id: circle1
        objectName: "circle1"
        x: 0
        y: 0
        width: 225
        height: 225
        source: "safe_bg/circle.png"
        opacity: 0
        state: "hidden"
        states: [
            State {
                name: "hidden"
                PropertyChanges {
                    target: circle1
                    opacity: 0
                }
            },
            State {
                name: "shown"
                PropertyChanges {
                    target: circle1
                    opacity: 1
                }
            }
        ]
        transitions: [
            Transition {
                from: "shown"
                to: "hidden"
                NumberAnimation { duration: 1 }
            },
            Transition {
                from: "hidden"
                to: "shown"
                NumberAnimation { duration: 400; easing.type: Easing.InOutQuad }
            }
        ]
    }
    SafeImage {
        id: circle2
        objectName: "circle2"
        x: 225
        y: 0
        width: 350
        height: 350
        source: "safe_bg/circle.png"
        opacity: 0
        state: "hidden"
        states: [
            State {
                name: "hidden"
                PropertyChanges {
                    target: circle2
                    opacity: 0
                }
            },
            State {
                name: "shown"
                PropertyChanges {
                    target: circle2
                    opacity: 1
                }
            }
        ]
        transitions: [
            Transition {
                from: "shown"
                to: "hidden"
                NumberAnimation { duration: 1 }
            },
            Transition {
                from: "hidden"
                to: "shown"
                NumberAnimation { duration: 400; easing.type: Easing.InOutQuad }
            }
        ]
    }
    SafeImage {
        id: circle3
        objectName: "circle3"
        x: 575
        y: 0
        width: 225
        height: 225
        source: "safe_bg/circle.png"
        opacity: 0
        state: "hidden"
        states: [
            State {
                name: "hidden"
                PropertyChanges {
                    target: circle3
                    opacity: 0
                }
            },
            State {
                name: "shown"
                PropertyChanges {
                    target: circle3
                    opacity: 1
                }
            }
        ]
        transitions: [
            Transition {
                from: "shown"
                to: "hidden"
                NumberAnimation { duration: 1 }
            },
            Transition {
                from: "hidden"
                to: "shown"
                NumberAnimation { duration: 400; easing.type: Easing.InOutQuad }
            }
        ]
    }

    SafeText {
        id: safeText1
        objectName: "safeText1"
//        text: "0123456789"
        height: 50
        width: 150
        x: 50
        y: 125
//        color: "white"
        horizontalAlignment: SafeText.AlignHCenter
        runtimeEditable: true
        font.family: "Impact"
        font.pixelSize: 30
    }
    SafeText {
        id: safeText2
        objectName: "safeText2"
        height: 50
        width: 150
        x: 325
        y: 225
        horizontalAlignment: SafeText.AlignHCenter
        runtimeEditable: true
        font.family: "Impact"
        font.pixelSize: 40
    }
    SafeText {
        id: safeText3
        objectName: "safeText3"
        height: 50
        width: 75
        x: 680
        y: 125
        horizontalAlignment: SafeText.AlignHCenter
        runtimeEditable: true
        font.family: "Impact"
        font.pixelSize: 30
    }
}
