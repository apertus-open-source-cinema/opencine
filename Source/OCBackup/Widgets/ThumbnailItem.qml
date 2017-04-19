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
    property string clipName: "" //text3.text
    property string clipPath: "" //thumbnailImage.source
    property string altSource: "thumbnail_placeholder.png"

    FontLoader {
        id: fixedFont
        name: "Titillium"
    }

    Rectangle {
        id: rectangle1
        x: 6
        y: 6
        color: "#00000000"
        anchors.bottom: text1.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        //border.color: "#c40000"
        anchors.rightMargin: 6
        anchors.leftMargin: 6
        anchors.bottomMargin: 5
        anchors.topMargin: 6

        Image {
            id: thumbnailImage
            anchors.fill: parent
            source: "image://OCthumb/" + clipPath + clipName
            sourceSize.width: 200
            sourceSize.height: 150
            enabled: true
            smooth: true
            fillMode: Image.PreserveAspectFit
            asynchronous: true
            onStatusChanged:
            {
                //console.log("Image state: " + status)

                if (thumbnailImage.status == Image.Error || thumbnailImage.status == Image.Null)
                {
                    thumbnailImage.source = "";
                    thumbnailImage.source = altSource;
                }
            }
        }

        DropShadow {
            anchors.fill: thumbnailImage
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8
            transparentBorder: true
            samples: 16
            color: "#40000000"
            source: thumbnailImage
        }
    }


    Text {
        id: text1
        y: 65
        width: 0
        color: "#ffffff"
        text:{
            console.log("Clip name: " + clipName)
            clipName ? clipName : "N/A"
        }
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        font.pixelSize: 12
    }
}
