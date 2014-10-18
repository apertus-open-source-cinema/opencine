import QtQuick 2.0

import QtQuick 2.0
Rectangle {
    width: 276
    height: 300
    color: "#191919"

    border.width: 1
    border.color: "red"

    Component {
        id: listDelegate

        ListViewItem
        {
            clipName: name
            clipFPS: fps
        }
    }

    ListModel
    {
        id: listModel

        ListElement
        {
            name: "Test1"
            fps: 30
        }

        ListElement
        {
            name: "Test2"
            fps: 24
        }

        ListElement
        {
            name: "Test3"
            fps: 30
        }

        ListElement
        {
            name: "Test4"
            fps: 24
        }
    }

    ListView
    {
        id: clipList

        anchors.fill: parent
        anchors.margins: 1

        clip: true

        boundsBehavior: Flickable.StopAtBounds

        model: listModel
        delegate: listDelegate
    }

    ScrollBar
    {
        flickable: clipList
        //vertical: true
    }
}
