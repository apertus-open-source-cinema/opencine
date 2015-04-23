import QtQuick 2.4
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.1

Rectangle {
    id: thumbnail
    width: 300
    height: (width / 4) * 3
    color: "#00000000"
    scale: 1
    transformOrigin: Item.Center

    property string clipResolution: "0x0"

    FontLoader {
        id: fixedFont
        name: "Titillium"
    }

    DropShadow {
        x: 6
        y: 6
        anchors.fill: image1
        horizontalOffset: 3
        verticalOffset: 3
        radius: 8
        antialiasing: false
        transparentBorder: true
        spread: 0
        cached: true
        fast: false
        samples: 16
        color: "#000000"
        source: image1
    }

    Image {
        id: image1
        x: 6
        height: 28
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors.bottomMargin: 48
        anchors.bottom: parent.bottom
        enabled: true
        smooth: true
        antialiasing: false
        fillMode: Image.PreserveAspectFit
        source: "thumbnail_placeholder.png"
    }

    Column {
        id: column3
        height: 34
        anchors.top: image1.bottom
        anchors.topMargin: 6
        anchors.leftMargin: parent.width / 2 - image1.paintedWidth / 2
        anchors.rightMargin: parent.width / 2
        anchors.right: parent.right
        anchors.left: parent.left

        Text {
            id: text3
            y: 193
            color: "#ffffff"
            text: clipResolution
            font.family: fixedFont.name
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            font.bold: true
            font.pixelSize: 16
        }

        Text {
            id: text4
            y: 193
            color: "#ffffff"
            text: qsTr("24fps")
            font.family: fixedFont.name
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            font.bold: true
            font.pixelSize: 16
        }
    }

    Column {
        id: column2
        height: 34
        anchors.top: image1.bottom
        anchors.topMargin: 6
        anchors.rightMargin: parent.width / 2 - image1.paintedWidth / 2
        spacing: 0
        anchors.leftMargin: parent.width / 2
        anchors.left: parent.left
        anchors.right: parent.right

        Text {
            id: text1
            y: 193
            color: "#ffffff"
            text: qsTr("14.01.2015")
            font.family: fixedFont.name
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            horizontalAlignment: Text.AlignRight
            font.bold: true
            font.pixelSize: 16
        }

        Text {
            id: text2
            y: 193
            color: "#ffffff"
            text: qsTr("00:00:05.02")
            style: Text.Normal
            font.family: fixedFont.name
            horizontalAlignment: Text.AlignRight
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            font.bold: true
            font.pixelSize: 16
        }
    }
}
