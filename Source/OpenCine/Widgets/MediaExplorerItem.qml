import QtQuick 2.3
import QtGraphicalEffects 1.0

Rectangle {
    id: rectangle1
    width: 378
    height: 120
    color: index % 2 == 0 ? "#222222" : "#333333"
    //color: "#302f2f"
    border.width: 0
    anchors.left: parent.left
    anchors.right: parent.right

    //Clip properties
    property string clipName: ""
    property int clipFPS: -1
    property int clipWidth: -1
    property int clipHeight: -1

    property bool loaded: false

    Row {
        id: row1
        anchors.fill: parent


        Rectangle {
            id: rectangle2
            width: 143.64
            color: "#000000"
            anchors.topMargin: 6
            anchors.bottomMargin: 6
            anchors.leftMargin: 6
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.top: parent.top
            border.width: 0
            clip: false

            Image
            {
                id: image1
                width: 182
                clip: true
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.top: parent.top
                fillMode: Image.PreserveAspectFit
                //source: "qrc:/qtquickplugin/images/template_image.png"
            }
        }

        Image {
            id: image2
            antialiasing: true
            clip: false
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            fillMode: Image.PreserveAspectFit
            anchors.right: parent.right
            anchors.rightMargin: 0
            source: "marker.svg"
            mipmap: true

            visible: (loaded ? true : false)

            ColorOverlay
            {
                    anchors.fill: source
                    source: image2
                    color: "#A27E34"
                    cached: false
                    antialiasing: true
            }
            //color: (loaded ? "#00FF00" : "#000000")
        }
        Column {
            id: column1
            anchors.left: rectangle2.right
            anchors.leftMargin: 6
            spacing: 6
            anchors.top: parent.top
            anchors.topMargin: 6
            anchors.right: parent.right
            anchors.rightMargin: 6
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 6

            Text {
                id: text1
                color: "#dedddd"
                text: clipName
                smooth: true
                clip: true
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                antialiasing: false
                font.bold: true
                font.pixelSize: 12
            }

            Text {
                id: text2
                color: "#dedddd"
                text: "JP46"
                clip: true
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                antialiasing: false
                font.bold: true
                font.pixelSize: 12
            }

            Text {
                id: text3
                color: "#dedddd"
                text: clipFPS + " FPS"
                styleColor: "#000000"
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                clip: true
                antialiasing: false
                font.bold: true
                font.pixelSize: 12
            }

            Text {
                id: text4
                color: "#dedddd"
                text: clipWidth + " x " + clipHeight
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                clip: true
                antialiasing: false
                font.bold: true
                font.pixelSize: 12
            }

            RatingControl {
                id: ratingControl1
                width: 107
                height: 24
                radius: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                clip: true
                antialiasing: false
                border.width: 0
            }
        }
    }
}
