import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    width: 190
    height: 62
    color: "#00000000"
    border.width: 0

    Row
    {
        id: row1
        anchors.fill: parent

        Image
        {
            id: image2
            width: parent.width / 5
            height: parent.height
            fillMode: Image.PreserveAspectFit
            anchors.left: parent.left
            anchors.leftMargin: 0
            source: "star.svg"
        }        

        Image
        {
            id: image3
            width: parent.width / 5
            height: parent.height
            fillMode: Image.PreserveAspectFit
            anchors.left: image2.right
            anchors.leftMargin: 0
            source: "star.svg"
        }

        Image
        {
            id: image4
            width: parent.width / 5
            height: parent.height
            antialiasing: true
            fillMode: Image.PreserveAspectFit
            anchors.left: image3.right
            anchors.leftMargin: 0
            source: "star.svg"
        }

        Image
        {
            id: image5
            width: parent.width / 5
            height: parent.height
            antialiasing: true
            fillMode: Image.PreserveAspectFit
            anchors.left: image4.right
            anchors.leftMargin: 0
            source: "star.svg"
        }

        Image
        {
            id: image6
            width: parent.width / 5
            height: parent.height
            antialiasing: true
            fillMode: Image.PreserveAspectFit
            anchors.left: image5.right
            anchors.leftMargin: 0
            source: "star.svg"
        }
    }
}
