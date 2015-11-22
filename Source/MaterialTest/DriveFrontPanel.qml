import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4

Item {
    id: frontPanel


    //anchors.horizontalCenter: parent.horizontalCenter
    property bool isSelected: parent.isSelected

    Rectangle {
        id: listItem
        anchors.fill: parent

        radius: 3

        color: "white"

        Row {
            anchors.fill: parent
            anchors.margins: 15

            spacing: 15

            Rectangle {
                id: testRect

                border.width: 1
                border.color: "gray"

                width: 50
                height: 50

                radius: width / 2

                Text {
                    anchors.centerIn: parent
                    color: "darkgray"
                    text: driveName[0]
                    font.bold: true
                    font.pointSize: parent.width / 2
                    textFormat: Text.PlainText
                }
            }

            Column {
                anchors.margins: 10
                anchors.left: testRect.right
                anchors.right: parent.right

                spacing: 10

                Text {
                    text: driveName
                }

                ProgressBar {
                    id: progressBar
                    property color color: frontPanel.isSelected ? "darkturquoise" : "maroon"

                    maximumValue: 100
                    value: usedSpace
                    width: parent.width

                    style: ProgressBarStyle {
                        background: Rectangle {
                            radius: 2
                            color: "lightgray"
                            implicitWidth: 200
                            implicitHeight: 15
                        }
                        progress: Rectangle {
                            id: progressBarChunk
                            color: control.color
                        }
                    }
                }
            }
        }
    }
}
