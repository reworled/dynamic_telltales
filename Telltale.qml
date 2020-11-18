import QtQuick 2.0

Item {

    id: root

    property int type

    property var doSetState

    function setState(state) {
        if (!!doSetState) {
            doSetState(state)
        }
    }
    scale: 0
    property int animationSpeed: 400

    ParallelAnimation {
        id: creationAnimation

        NumberAnimation {
            target: root
            property: "scale"
            from: 0; to: 1
            duration: animationSpeed
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: rootation
            property: "angle"
            from: 0; to: 720
            duration: animationSpeed
        }
    }
    transform: Rotation {
        id: rootation
        origin.x: 30
        origin.y: 30
    }

    function openAnimation() {
        creationAnimation.start()
    }
}
