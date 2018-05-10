import QtQuick 2.4

Item {
    width: 400
    height: 400

    Rectangle {
        id: rectangle1
        color: "#424242"
        anchors.fill: parent
    }

    Text {
        id: text1
        x: 92
        y: 126
        width: 177
        height: 50
        color: "#ffffff"
        text: qsTr("Test")
        styleColor: "#ff0d0d"
        font.pixelSize: 12
    }
}

