import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3

Rectangle {
    id: root
    width: 640
    height: 480
    color: "#1b1b1b"

    MouseArea {
        id: rootMouseArea
        anchors.rightMargin: -700
        anchors.bottomMargin: -780
        anchors.leftMargin: 700
        anchors.topMargin: 780
        anchors.fill: parent
        hoverEnabled: true

        propagateComposedEvents: true
    }

    Grid {
        id: grid1
        anchors.rightMargin: 3302
        anchors.bottomMargin: 650
        anchors.leftMargin: -3302
        anchors.topMargin: -650
        flow: Grid.LeftToRight
        anchors.fill: parent
        scale: 1
        transformOrigin: Item.TopLeft
        smooth: true
        antialiasing: false
        spacing: 6
        layoutDirection: Qt.LeftToRight
        rows: 0
        columns: 3

        ThumbnailItem {
        }

        ThumbnailItem {
        }

        ThumbnailItem {
        }

        ThumbnailItem {
        }

        ThumbnailItem {
        }

        ThumbnailItem {
        }

        ThumbnailItem {
        }

        ThumbnailItem {
        }

        ThumbnailItem {
        }

        ThumbnailItem {
        }
    }

    GridLayout {
        anchors.rightMargin: -1390
        anchors.bottomMargin: 448
        anchors.leftMargin: 1390
        anchors.topMargin: -448
        anchors.fill: parent
        clip: false
        columnSpacing: 5
        columns: 3

        //        scale: scaleSlider.value
        ThumbnailItem {
        }
        ThumbnailItem {
        }
        ThumbnailItem {
        }
        ThumbnailItem {
        }
        ThumbnailItem {
        }
        ThumbnailItem {
        }
        ThumbnailItem {
        }
    }

    GridView {
        id: gridView1
        anchors.fill: parent
        boundsBehavior: Flickable.StopAtBounds
        cellWidth: 276
        scale: 1
        cellHeight: 223
        highlightRangeMode: GridView.NoHighlightRange
        snapMode: GridView.NoSnap

        //keyNavigationWraps: false
        model: ListModel {
            ListElement {
                clipResolution: "1920x1080"
            }
            ListElement {
                clipResolution: "1280x720"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
            ListElement {
                name: "Test3"
            }
        }

        delegate: ThumbnailItem
        {
            id: thumbnailItem
            clipResolution: model.clipResolution
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
        color: "#00000000"
        anchors.topMargin: 447
        anchors.fill: parent
        visible: rootMouseArea.containsMouse
        opacity: controlMouseArea.containsMouse ? 1.0 : 0.3

        MouseArea {
            id: controlMouseArea
            anchors.fill: parent
            hoverEnabled: true

            propagateComposedEvents: true
        }

        Slider {
            id: scaleSlider
            width: 250
            stepSize: 0.1
            tickmarksEnabled: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 6
            anchors.horizontalCenter: parent.horizontalCenter
            value: 0.5
        }
    }
}
