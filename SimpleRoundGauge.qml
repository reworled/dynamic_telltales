import QtQuick 2.0
import QtQuick.Shapes 1.12

Item {

    id: root

    property color needleColor: Qt.darker("red")
    property int needleLength: height * 2/6
    property int needleWidth: width * 1/20
    property alias backgroundImage: gaugeDial.source
    property alias centerCapSource: needleCap.source
    property alias needleImage: needleImage.source

    property real value

    property real minimumRotation
    property real maximumRotation
    property real minimumValue
    property real maximumValue

    property PropertyAnimation needleAnimation

    // This is no longer API, and should not be tinkered with

    property real cleanValue: {
        var val = Math.max(minimumValue, value)
        val = Math.min(maximumValue, val)
        return val
    }

    property real range: maximumValue-minimumValue
    property real progress: cleanValue/range
    property real rotationRange: maximumRotation-minimumRotation
    property real rotaionalProgress: progress * rotationRange

    property real angle: minimumRotation + rotaionalProgress

    property point center: Qt.point(width/2, height/2)

    Image {
        id: gaugeDial
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: needleImage
        height: root.needleLength
        width: root.needleWidth
        x: center.x - (width/2)
        y: center.y

        transform: Rotation {
            id: rotator
            origin.x: needleImage.width/2
            origin.y: 0
            angle: root.angle
            Behavior on angle {
                RotationAnimation {
                    duration: 200; easing.type: Easing.InOutCirc
                }
            }
        }
    }

    Image  {
        id: needleCap
        x: center.x - width/2
        y: center.y - height/2
    }
}
