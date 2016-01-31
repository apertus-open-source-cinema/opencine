import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4

Item {
    id: frontPanel

    width: 240
    height: 40

    Rectangle
    {
        color: "white"
        radius: 3
        anchors.fill: parent

        Column {
            id: column1
            anchors.fill: parent
            anchors.margins: 10

            Rectangle {
                id: testRect

                border.width: 1
                border.color: "gray"

                width: 50
                height: 50

                radius: width / 2
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

                Text {
                    anchors.centerIn: parent
                    color: "darkgray"
                    text: "?"
                    font.bold: true
                    font.pointSize: parent.width / 2
                    textFormat: Text.PlainText
                }
            }
        }
    }
}

