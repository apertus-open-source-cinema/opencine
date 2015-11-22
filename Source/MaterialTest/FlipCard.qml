import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Flipable {
    id: flipable
    width: 240
    height: 80

    property bool flipped: false
    property bool isSelected: flipable.ListView.isCurrentItem

    property real scaleFactor: 1.1

    anchors.horizontalCenter: parent.horizontalCenter

    opacity: isSelected ? 1.0 : 0.6

    front: DriveFrontPanel {
        width: parent.width
        height: parent.height

        Image {
            anchors.right: parent.right
            source: "settings.svg"
            width: 20
            height: 20
            visible: !flipped && isSelected

            MouseArea {
                anchors.fill: parent
                onClicked: flipped = !flipped
                //preventStealing: true
            }
        }
    }

    back: DriveBackPanel {
        width: parent.width
        height: parent.height

        Image {
            anchors.right: parent.right
            source: "settings.svg"
            width: 20
            height: 20
            visible: flipped && isSelected

            MouseArea {
                anchors.fill: parent
                onClicked: flipped = !flipped
                //preventStealing: true
            }
        }
    }

    transform: Rotation {
        id: rotation
        origin.x: flipable.width / 2
        origin.y: flipable.height / 2
        axis.x: 1
        axis.y: 0
        axis.z: 0
        angle: 0
    }

    states: [
        State {
            PropertyChanges {
                target: rotation
                angle: 180
            }
            when: flipped
        },
        State {
            PropertyChanges {
                target: flipable
                scale: scaleFactor
            }
            when: isSelected
        }
    ]

    transitions: Transition {
        NumberAnimation {
            target: rotation
            property: "angle"
            duration: 300
        }
    }

    Behavior on scale {
        NumberAnimation {
            duration: 200
        }
    }

//        Behavior on width {
//            NumberAnimation {
//                duration: 100
//            }
//        }

//        Behavior on height {
//            NumberAnimation {
//                duration: 100
//            }
//        }
}
