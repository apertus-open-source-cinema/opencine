import QtQuick 2.3
import QtGraphicalEffects 1.0

Rectangle
{
    id: mediaExplorerList
    width: 276
    height: 300
    color: "#191919"

    border.width: 1
    border.color: "#555555"

    opacity: 1.0

    //property var listModel: null;
    property int prevItem: 0;
    property int currItem: 0;

    signal loadClip(int clipIndex);

    Component
    {
      id: listDelegate

      MediaExplorerItem
      {
        clipName: model.clipName
        clipFPS: model.clipFPS
        clipWidth: model.clipWidth
        clipHeight: model.clipHeight

        loaded: false
      }
    }

    Component
    {
     id: highlightBox
     Rectangle
     {
        id: highlightBar
        width: clipList.currentItem.width; height: clipList.currentItem.height
        color: "blue"; radius: 5
        y: clipList.currentItem.y
        Behavior on y { PropertyAnimation { duration: 50 }}

        InnerShadow
        {
           id: topLeftShadowHighlight
           anchors.fill: source
           radius: 8.0
           samples: 16
           horizontalOffset: 3
           verticalOffset: 3
           color: "#b0000000"
           source: highlightBar
       }

       InnerShadow
       {
          anchors.fill: source
          radius: 8.0
          samples: 16
          horizontalOffset: -1
          verticalOffset: -1
          color: "#b0000000"
          source: topLeftShadowHighlight
      }
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

        focus: true
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
    }
}
