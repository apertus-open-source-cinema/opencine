import QtQuick 2.4
import QtGraphicalEffects 1.0

import "OCWidgets"

Rectangle
{
    //id: driveList
    width: 276
    height: 300
    color: "#191919"

    border.width: 1
    border.color: "#555555"

    signal itemSelectionChanged(int currentItem)

    ListModel {
        id: testList
        ListElement {
            driveName: "TestDrive"
        }
        ListElement { driveName: "44" }
        ListElement { driveName: "78" }
        ListElement { }
    }

    Component
    {
        id: listDelegate

        DestinationItem
        {
            height: 36
            width: parent.width
        }
    }

    OCListView
    {
        id: listView

        model: destinationsList
        delegate: listDelegate

        highlight: null
    }
}
