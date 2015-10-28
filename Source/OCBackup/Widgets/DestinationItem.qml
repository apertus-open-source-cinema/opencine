import QtQuick 2.3
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle
{
    id: row1
    width: 270
    height: 36

    Rectangle
    {
        id: rectangle1
        color: "#2e2e2e"
        anchors.right: rectangle3.left
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0


        property string driveName: model.driveName ? model.driveName : "?";
        property string driveLetter: model.driveLetter ? model.driveLetter : "?";
        property real usedSpace: model.usedSpace ? model.usedSpace : -1;
        property real totalSpace: model.totalSpace ? model.totalSpace : -1;
        property string spaceUnit: model.spaceUnit ? model.spaceUnit : "?";
        property alias backgroundColor: rectangle1.color;
        //height: 49

        Text {
            id: driveInfo
            width: 1
            color: "#ffffff"
            text: driveName + " (" + driveLetter + ")"
            anchors.right: driveSize.left
            anchors.rightMargin: 10
            clip: false
            antialiasing: false
            smooth: false
            styleColor: "#ff0000"
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 5
            font.pixelSize: 12
            elide: Text.ElideRight
        }

        ProgressBar
        {
            value: usedSpace
            maximumValue: totalSpace

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5

            anchors.left: parent.left
            anchors.leftMargin: 5

            anchors.right: parent.right
            anchors.rightMargin: 5

            style: ProgressBarStyle {
                progress: Rectangle {
                    border.width: 1
                    border.color: "#01000000"
                    radius: 2
                    anchors.margins: 1
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "#644624" }
                        GradientStop { position: 1.0; color: "#a27e34" }
                    }
                }

                background: Rectangle {
                    radius: 3
                    color: "transparent"
                    border.color: "#1e1e1e"
                    border.width: 1
                    //implicitWidth: 200
                    implicitHeight: 5
                }
            }
        }

        Text {
            id: driveSize
            color: "#ffffff"
            text: usedSpace + "/" + totalSpace + " " + spaceUnit
            clip: true

            styleColor: "#db0000"
            anchors.right: parent.right
            anchors.rightMargin: 5
            font.pixelSize: 12
            anchors.top: parent.top
            anchors.topMargin: 5
        }
    }


    Rectangle {
        id: rectangle3
        width: 30
        color: "#2e2e2e"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.top: parent.top

        Button {
            id: button1
            text: qsTr("")
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent

            style: ButtonStyle {
                background: Rectangle {
                    //implicitWidth: 100
                    //implicitHeight: 25
                    border.width: control.activeFocus ? 2 : 1
                    border.color: control.pressed? "#f00" : "#888"
                    radius: 3
                    color: "transparent"

                    gradient: Gradient {
                        GradientStop { position: 0 ; color: control.pressed ? "#00000000" : "#eee" }
                        GradientStop { position: 1 ; color: control.pressed ? "#55ff0000" : "#ccc" }
                    }
                }
            }

            Image {
                id: image1
                anchors.rightMargin: 3
                anchors.leftMargin: 3
                anchors.bottomMargin: 3
                anchors.topMargin: 3
                anchors.fill: parent
                sourceSize.height: 0
                sourceSize.width: 0
                fillMode: Image.PreserveAspectFit
                source: "delete_icon.png"
            }


        }
    }
}
