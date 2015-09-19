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
    property string clipName: text3.text
    property string clipPath: image1.source

    FontLoader {
        id: fixedFont
        name: "Titillium"
    }

    DropShadow {
        anchors.fill: source
        horizontalOffset: 3
        verticalOffset: 3
        radius: 8
        transparentBorder: true
        samples: 16
        color: "#40000000"
        source: image1
    }

    Image {
        id: image1
        x: 6
        height: 28
        source: "thumbnail_placeholder.png"
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors.bottomMargin: 40
        anchors.bottom: parent.bottom
        enabled: true
        smooth: true
        fillMode: Image.PreserveAspectFit
    }

    Column {
        id: column3
        x: 362
        y: 96
        width: 95
        height: 34

        Text {
            id: text3
            color: "#ffffff"
            text: clipResolution
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            font.family: fixedFont.name
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
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
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
        x: 354
        y: 34
        width: 112
        height: 34
        spacing: 0

        Text {
            id: text1
            color: "#ffffff"
            text: qsTr("14.01.2015")
            anchors.top: parent.top
            anchors.topMargin: 0
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
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
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
