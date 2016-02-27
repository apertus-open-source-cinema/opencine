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

    //property alias clipResolution: text3.text
    //property string clipName: "" //text3.text
    //property string clipPath: "" //image1.source

    FontLoader {
        id: fixedFont
        name: "Titillium"
    }

    Rectangle {
        id: rectangle1
        color: "#00000000"
        border.color: "#c40000"
        anchors.rightMargin: 6
        anchors.leftMargin: 6
        anchors.bottomMargin: 6
        anchors.topMargin: 6
        anchors.fill: parent

        Image {
            id: image1
            anchors.fill: parent
            source: "image://colors/yellow" //"thumbnail_placeholder.png"
            anchors.bottom: column2.top
            enabled: true
            smooth: true
            fillMode: Image.PreserveAspectFit
        }

        DropShadow {
            anchors.fill: parent
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8
            transparentBorder: true
            samples: 16
            color: "#40000000"
            source: image1
        }
    }

}
