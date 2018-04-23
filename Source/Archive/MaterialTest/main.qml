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
            MouseArea {
                anchors.fill: parent
                propagateComposedEvents: true
                enabled: listView.currentIndex != index

                onClicked: {
                    listView.currentIndex = index
                    gotoIndex(index)
                }
            }
        }
    }
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
        anim.running = false;
        var pos = listView.contentY;
        //var destPos;
        listView.positionViewAtIndex(idx, ListView.Center);
        var destPos = listView.contentY;
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

//            highlight: Rectangle {
//                        color: "lightsteelblue";
//                        radius: 5
//                    }
                    focus: true
                    //clip: true

//            displaced: Transition {
//                NumberAnimation {
//                    properties: "y"
//                    duration: 300
//                }
//            }

            NumberAnimation {
                id: anim
                target: listView
                property: "contentY"
                duration: 300
            }
        }
    }
}

