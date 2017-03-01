import QtQuick 2.3
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle
{
    id: rectangle1
    color: "#2e2e2e"

    height: 36
    width: 220

    property string driveName: model.driveName ? model.driveName : "?";
    property string drive: model.drive ? model.drive : "?";
    property real usedSpace: model.usedSpace ? model.usedSpace : -1;
    property real totalSpace: model.totalSpace ? model.totalSpace : -1;
    property string spaceUnit: model.spaceUnit ? model.spaceUnit : "?";
    property alias backgroundColor: rectangle1.color;

	ExclusiveGroup { id: tabPositionGroup }

    Text {
        id: pathInfo
        y: 3
        color: "#ffffff"
        text: driveName + " (" + drive + ")"
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
