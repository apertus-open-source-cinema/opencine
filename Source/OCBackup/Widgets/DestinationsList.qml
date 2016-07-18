import QtQuick 2.4
import QtGraphicalEffects 1.0

import "OCWidgets"

Rectangle
{
    id: driveList
    width: 276
    height: 300
    color: "#191919"

    border.width: 1
    border.color: "#555555"

    signal itemSelectionChanged(int currentItem)

    ListModel {
        id: testList
        ListElement { clipWidth: 1920
                clipHeight: 1080
                driveName: "TestDrive"
                            driveLetter: "E:"
                            usedSpace: "1.2"
                            totalSpace: "1.5"
                            spaceUnit: "GB"
                            }
        ListElement { clipName: "44" }
        ListElement { clipName: "78" }
        ListElement { }
    }

    Component
    {
        id: listDelegate

        DestinationItem
        {
            height: 36
            width: parent.width

//            MouseArea
//            {
//                id: itemMouseArea
//                anchors.fill: parent

//                onClicked:
//                {
//                    listView.currentIndex = index
//                    driveList.itemSelectionChanged(index)
//                }
//            }
        }
    }

    OCListView
    {
        id: listView

        model: testList
        delegate: listDelegate

        highlight: null
    }
}
