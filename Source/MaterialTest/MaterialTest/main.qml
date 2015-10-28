import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

//import "/home/andi/Source/MaterialTest/MaterialTest/3rdParty/Material/modules" as Material
//import Material 0.1
//import Material.Extras 0.1
ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Material UI")

Component
{
    id: contactDelegate

    FlipCard
    {
        width: 340
        height: 40

        MouseArea {
            hoverEnabled: false
            anchors.fill: parent
            //propagateComposedEvents: true
            //preventStealing: true

            onClicked: {
                listView.currentIndex = index
                gotoIndex(index)
            }
        }
    }



//    Rectangle {
//           id: listItem
//           width: 240
//           height: 80
//           anchors.horizontalCenter: parent.horizontalCenter

//           //transform: Scale { origin.x: 25; origin.y: 25; xScale: 1.3}
//           //opacity: isSelected ? 1.0 : 0.3

//            //antialiasing: true
//            //layer.enabled: true
//            //smooth: true

//           radius: 3

//           //            antialiasing: true
//           //            smooth: true
//           property real scaleFactor: 1.1
//           property bool isSelected: listItem.ListView.isCurrentItem

//           color: "white"

//           Behavior on scale {
//               NumberAnimation {
//                   duration: 200
//               }
//           }

//           Behavior on width {
//               NumberAnimation {
//                   duration: 200
//               }
//           }

//           Behavior on height {
//               NumberAnimation {
//                   duration: 200
//               }
//           }

//           Row {
//               anchors.fill: parent
//               //anchors.fill: parent
//               anchors.margins: 15


//               spacing: 15

//               Rectangle {
//                   id: testRect
//                   //color: "#222222"

//                   border.width: 1
//                   border.color: "gray"

//                   width: 50
//                   height: 50

//                   radius: width / 2

//                   Text {
//                       anchors.centerIn: parent
//                       color: "darkgray"
//                       text: driveName[0]
//                       font.bold: true
//                       //scale: scaleFactor * 2
//                       font.pointSize: parent.width / 2
//                       textFormat: Text.PlainText
//                   }
//               }

//               Column {
//                   //anchors.left: testRect.right
//                   //anchors.right: parent.right
//                   anchors.margins: 10

//                   spacing: 10

//                   Text {
//                       text: driveName
//                   }

//                   ProgressBar {
//                       id: progressBar
//                       property bool isSelected: listItem.isSelected
//                       property color color: isSelected ? "darkturquoise" : "maroon"

//                       maximumValue: 100
//                       value: usedSpace
//                       width: parent.width

//                       style: ProgressBarStyle {
//                           background: Rectangle {
//                               radius: 2
//                               color: "lightgray"
//                               //border.color: "gray"
//                               //border.width: 1
//                               implicitWidth: 200
//                               implicitHeight: 15
//                           }
//                           progress: Rectangle {
//                               id: progressBarChunk
//                               color: control.color

////                                ColorAnimation on color
////                                {
////                                    to: "yellow"
////                                    duration: 500
////                                }

//                               //opacity: 0.6
//                               //border.color: "steelblue"
//                           }
//                       }
//                   }
//               }
//           }
//                       states: State {

//                           //name: "back"
//                           PropertyChanges {
//                               target: listItem
//                               scale: scaleFactor
//                           }
//                           PropertyChanges {
//                               target: listItem
//                               //width: 240 * scaleFactor
//                               //height: 80 * scaleFactor
//                           }
//                           when: isSelected
//                       }

//                       MouseArea {
//                           hoverEnabled: false
//                           anchors.fill: parent

//                           onClicked: {
//                               listView.currentIndex = index
//                               gotoIndex(index)
//                           }
//                       }
//      }
}

//            ColorOverlay {
//                anchors.fill: parent
//                source: parent
//                color: listItem.isSelected ? "transparent" : "#10ff0000"//"#20807000"
//            }


//        }

//    }



    ListModel {
        id: listModel

        ListElement {
            driveName: "Kingston DT-100 G2"
            usedSpace: 43
        }

        ListElement {
            driveName: "TOSHIBA EXT"
            usedSpace: 43
        }

        ListElement {
            driveName: "CANON"
            usedSpace: 43
        }

        ListElement {
            driveName: "Lexar P20"
            usedSpace: 43
        }
    }

    function gotoIndex(idx) {
        anim.running = false
        var pos = listView.contentY
        var destPos
        listView.positionViewAtIndex(idx, ListView.Center)
        destPos = listView.contentY
        anim.from = pos
        anim.to = destPos
        anim.running = true
    }

    Rectangle {
        color: "#193a4e"
        anchors.fill: parent


        //padding:  30
        ListView {
            id: listView

            //width: 180; height: 300
            //anchors.fill: parent
            anchors.fill: parent
            model: listModel
            delegate: contactDelegate
            anchors.margins: 20
            spacing: 25

            topMargin: parent.height / 4
            bottomMargin: parent.height / 4

            pixelAligned: true

            displaced: Transition {
                NumberAnimation {
                    properties: "y"
                    duration: 100
                }
            }

            NumberAnimation {
                id: anim
                target: listView
                property: "contentY"
                duration: 300
            }
        }
    }
}
