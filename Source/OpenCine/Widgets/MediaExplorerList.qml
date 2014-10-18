import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    width: 276
    height: 300
    color: "#191919"

    border.width: 1
    border.color: "#555555"

    //property var listModel: null;

    Component {
        id: listDelegate

        MediaExplorerItem
        {
            clipName: name
            clipFPS: fps
        }
    }

    /*ListModel
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
    }*/

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

     InnerShadow
     {
        id: topLeftShadow
        anchors.fill: source
        radius: 8.0
        samples: 16
        horizontalOffset: 3
        verticalOffset: 3
        color: "#b0000000"
        source: clipList
    }

    InnerShadow
    {
       anchors.fill: source
       radius: 8.0
       samples: 16
       horizontalOffset: -1
       verticalOffset: -1
       color: "#b0000000"
       source: topLeftShadow
   }

    ScrollBar
    {
        flickable: clipList
        //vertical: true
    }
}
