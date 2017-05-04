import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3

Rectangle {
    id: root
    width: 700
    height: 700
    color: "#1b1b1b"

    signal playClip(int clipIndex);

    //property alias fileList: gridView1.model

    property color highlightColor: "darkred";

    MouseArea {
        id: rootMouseArea
        //        anchors.rightMargin: -700
        //        anchors.bottomMargin: -780
        //        anchors.leftMargin: 700
        //        anchors.topMargin: 780
        anchors.fill: parent
        hoverEnabled: true

        //propagateComposedEvents: true
    }

    Component
    {
        id: thumbHighlight
        Rectangle
        {
            color: highlightColor;
            radius: 3;
            border.color: "white";
            border.width: 2;
            opacity: 0.3;
            //x: gridView1.currentItem.x
            //y: gridView1.currentItem.y;
        }
    }

    GridView {
        id: gridView1
        cacheBuffer: 20
        anchors.fill: parent
        boundsBehavior: Flickable.StopAtBounds
        cellWidth: 210 * (scaleSlider.value / 3)
        scale: 1
        cellHeight: (cellWidth / 4 * 3)
        highlightRangeMode: GridView.NoHighlightRange
        snapMode: GridView.NoSnap

        //highlightFollowsCurrentItem: true;
        highlightMoveDuration: 0
        highlight: thumbHighlight
        focus: true

        //* (scaleSlider.value / 5)
        //keyNavigationWraps: false

        model: fileList

        delegate: ThumbnailItem
        {
            id: thumbnailItem
            //clipResolution: model.clipWidth + "x" + model.clipHeight
            clipName: model.clipName
            clipPath: model.clipPath
            width: 210 * (scaleSlider.value / 3)
            //height: 200


            MouseArea
            {
                anchors.fill: parent
                onClicked: gridView1.currentIndex = index
                onDoubleClicked: root.playClip(gridView1.currentIndex) //highlightColor = "darkorange"
                hoverEnabled: true;
            }
        }

        addDisplaced: Transition {
            NumberAnimation {
                properties: "x,y"
                duration: 1000
            }
        }

        ScrollBar
        {
            flickable: gridView1;
        }
    }

    Rectangle {
        id: rectangle1
        y: 0
        width: 0
        height: 40
        color: "#00000000"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left


        Slider {
            id: scaleSlider
            width: 250
            stepSize: 0.5
            tickmarksEnabled: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 6
            anchors.horizontalCenter: parent.horizontalCenter
            minimumValue: 1
            maximumValue: 7
            value: 3
            opacity: 0.3

            states: State {
                name: "hovered"; when: controlMouseArea.containsMouse
                PropertyChanges { target: scaleSlider; opacity: 1.0 }
            }

            transitions: Transition {
                NumberAnimation { properties: "opacity"; easing.type: Easing.Linear }
            }

            // Reference: http://stackoverflow.com/questions/16183408/mousearea-stole-qml-elements-mouse-events
            MouseArea {
                id: controlMouseArea
                anchors.fill: parent
                hoverEnabled: true

                propagateComposedEvents: true

                onClicked: mouse.accepted = false;
                onPressed: mouse.accepted = false;
                onReleased: mouse.accepted = false;
                onDoubleClicked: mouse.accepted = false;
                onPositionChanged: mouse.accepted = false;
                onPressAndHold: mouse.accepted = false;
            }
        }
    }
}

