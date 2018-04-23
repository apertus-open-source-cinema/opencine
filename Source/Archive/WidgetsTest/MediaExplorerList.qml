import QtQuick 2.3
import QtGraphicalEffects 1.0

Rectangle {
    id: mediaExplorerList
    width: 276
    height: 300
    color: "#191919"
//    smooth: false
//    antialiasing: false

//    border.width: 1
//    border.color: "#555555"

    Component {
        id: listDelegate

        DriveItem
        {
            width: parent.width;
            driveName: model.driveName;
            driveLetter: model.driveLetter;
            usedSpace: model.usedSpace;
            totalSpace: model.totalSpace;
            spaceUnit: model.spaceUnit;
            color: ListView.view.currentIndex === index ? "#CC0000" : "#333333";

            anchors.leftMargin: 1
            anchors.rightMargin: 1

            MouseArea
            {
                id: itemMouseArea
                anchors.fill: parent

                onClicked:
                {
                    clipList.currentIndex = index
                }
            }
        }
    }

        Component {
            id: highlightBox
            Rectangle {
                id: highlightBar
                width: clipList.currentItem.width
                height: clipList.currentItem.height
                color: "red"
                radius: 5
                x: clipList.currentItem.x
                y: clipList.currentItem.y

                Behavior on y
                {
                    PropertyAnimation
                    {
                        duration: 50
                    }
                }
            }
        }

        ListView {
            id: clipList
            smooth: false
            boundsBehavior: Flickable.StopAtBounds
            antialiasing: false

            anchors.fill: parent

            clip: true

            model: listModel
            delegate: listDelegate

            focus: true

            highlightFollowsCurrentItem: false
            //highlight: highlightBox

            spacing: 3
        }

//        InnerShadow {
//            id: topLeftShadow
//            anchors.fill: source
//            radius: 8.0
//            smooth: false
//            scale: 1
//            antialiasing: false
//            samples: 16
//            horizontalOffset: 2
//            verticalOffset: 2
//            color: "#b0000000"
//            source: clipList
//        }

//        InnerShadow {
//            anchors.fill: source
//            radius: 8.0
//            smooth: false
//            anchors.rightMargin: 0
//            anchors.bottomMargin: 0
//            anchors.leftMargin: 0
//            anchors.topMargin: 0
//            antialiasing: false
//            samples: 16
//            horizontalOffset: -1
//            verticalOffset: -1
//            color: "#b0000000"
//            source: topLeftShadow
//        }

        ScrollBar {
            smooth: false
            antialiasing: false
            flickable: clipList
        }
    }
