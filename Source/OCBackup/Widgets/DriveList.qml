import QtQuick 2.3
import QtGraphicalEffects 1.0

Rectangle {
    id: mediaExplorerList
    width: 276
    height: 300
    color: "#191919"

    border.width: 1
    border.color: "#555555"

    signal itemSelectionChanged(int currentItem)
    property alias listDelegate: clipList.delegate

    Component {
        id: listDelegate

        DriveItem {
            width: parent.width

            MouseArea {
                id: itemMouseArea
                anchors.fill: parent

                onClicked: {
                    clipList.currentIndex = index;
                    mediaExplorerList.itemSelectionChanged(index);
                }
            }
        }
    }

    Component {
        id: highlightBox

        Rectangle {
            z: 1
            id: highlightBar
            width: clipList.currentItem.width
            height: clipList.currentItem.height

            border.width: 2
            border.color: "#BB0000"

            color: "transparent"

            radius: 3
            x: clipList.currentItem.x
            y: clipList.currentItem.y

            Behavior on y {
                PropertyAnimation {
                    easing.type: Easing.Linear
                    duration: 150
                }
            }
        }
    }

    ListView {
        id: clipList
        anchors.rightMargin: 2
        anchors.leftMargin: 2
        anchors.bottomMargin: 2
        anchors.topMargin: 2
        boundsBehavior: Flickable.StopAtBounds
        anchors.fill: parent

        clip: true

        model: listModel
        delegate: listDelegate

        focus: true

        highlightFollowsCurrentItem: false
        highlight: highlightBox

        spacing: 3
    }

    ScrollBar
    {
        flickable: clipList
    }
}
