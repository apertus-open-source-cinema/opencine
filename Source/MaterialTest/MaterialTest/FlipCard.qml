import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Flipable {
    id: flipable
    width: 240
    height: 240

    property bool flipped: false
    property bool isSelected: flipable.ListView.isCurrentItem

    property real scaleFactor: 1.1

    anchors.horizontalCenter: parent.horizontalCenter

    Item {
        id: frontPanel

        width: 240
        height: 40

        Rectangle {
            width: parent.width
            height: parent.height
            color: "green"
        }
        Text {
            text: "Test"
        }

        Button {
            anchors.right: parent.right
            text: "Set"
            visible: !flipable.flipped

            MouseArea {
                anchors.fill: parent
                //enabled: !flipable.flipped
                onClicked: flipable.flipped = !flipable.flipped
                propagateComposedEvents: true
            }
        }
    }

    Item {
        id: backPanel

        width: 240
        height: 40

        Rectangle {
            width: parent.width
            height: parent.height
            color: "red"
        }
        Text {
            text: "Test2"
        }

        Button {
            anchors.right: parent.right
            text: "Set"
            visible: flipable.flipped

            MouseArea {
                anchors.fill: parent
                //enabled: flipable.flipped
                onClicked: flipable.flipped = !flipable.flipped
                propagateComposedEvents: true
            }
        }
    }

//    front: Rectangle {
//        width: 100
//        height: 100
//        color: "red"
//    }

    front: frontPanel
    back: backPanel

    transform: Rotation {
        id: rotation
        origin.x: flipable.width / 2
        origin.y: flipable.height / 2
        axis.x: 0
        axis.y: -1
        axis.z: 0 // set axis.y to 1 to rotate around y-axis
        angle: 0 // the default angle
    }

    states: [
        State {
            //name: "back"
            PropertyChanges {
                target: rotation
                angle: 180
            }
            when: flipable.flipped
        },
        State {
            //name: "back"
            PropertyChanges {
                target: flipable
                scale: scaleFactor
            }
//            PropertyChanges {
//                target: flipable
//                //width: 240 * scaleFactor
//                //height: 80 * scaleFactor
//            }
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

    Behavior on width {
        NumberAnimation {
            duration: 200
        }
    }

    Behavior on height {
        NumberAnimation {
            duration: 200
        }
    }
}
