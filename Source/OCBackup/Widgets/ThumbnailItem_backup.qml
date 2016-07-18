import QtQuick 2.4
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.1

Rectangle {
    id: thumbnail
    width: 200
    height: (width / 4) * 3
    color: "#00000000"
    scale: 1
    transformOrigin: Item.Center

    property alias clipResolution: text3.text
    property string clipName: "" //text3.text
    property string clipPath: "" //image1.source

    FontLoader {
        id: fixedFont
        name: "Titillium"
    }

    Rectangle {
        id: rectangle1
        color: "#ffffff"
        anchors.bottom: column2.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 6
        anchors.leftMargin: 6
        anchors.bottomMargin: 47
        anchors.topMargin: 6

        Image {
            id: image1
            anchors.fill: parent
            source: "image://colors/yellow" //"thumbnail_placeholder.png"
            enabled: true
            smooth: true
            fillMode: Image.PreserveAspectFit
        }
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

    Column {
        id: column3
        width: 95
        anchors.leftMargin: -image1.paintedWidth / 2
        anchors.left: image1.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        Text {
            id: text3
            color: "#ffffff"
            text: "0x0"
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            horizontalAlignment: Text.AlignLeft
            font.family: fixedFont.name
            font.bold: true
            font.pixelSize: 16
        }

        Text {
            id: text4
            color: "#ffffff"
            text: clipName;
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            horizontalAlignment: Text.AlignLeft
            font.family: fixedFont.name
            font.bold: true
            font.pixelSize: 16
        }
    }


    Column {
        id: column2
        width: 112
        anchors.rightMargin: -image1.paintedWidth / 2
        anchors.right: image1.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        spacing: 0

        Text {
            id: text1
            color: "#ffffff"
            text: "14.01.2015"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            font.family: fixedFont.name
            horizontalAlignment: Text.AlignRight
            font.bold: true
            font.pixelSize: 16
        }

        Text {
            id: text2
            color: "#ffffff"
            text: "00:00:05.02"
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            style: Text.Normal
            font.family: fixedFont.name
            horizontalAlignment: Text.AlignRight
            font.bold: true
            font.pixelSize: 16
        }
    }

}
