import QtQuick 2.0

Rectangle {
    id: rectangle1
    width: 350
    height: 120
    //color: "#302f2f"
    color: index % 2 == 0 ? "#2E2E2E" : "#363636"
    border.width: 0
    anchors.left: parent.left
    anchors.right: parent.right

    property string clipName: ""
    property int clipFPS: 0

    Row {
        id: row1
        anchors.fill: parent

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
                text: clipFPS + " FPS"
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
                text: qsTr("24 FPS")
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
                text: qsTr("1920 x 1080")
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

            Image {
                id: image1
                width: 182
                clip: true
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.top: parent.top
                fillMode: Image.PreserveAspectFit
                source: "qrc:/qtquickplugin/images/template_image.png"
            }
        }
    }
}
