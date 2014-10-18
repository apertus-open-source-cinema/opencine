import QtQuick 2.3
import QtGraphicalEffects 1.0

Rectangle {
    id: ratingControl
    width: 190
    height: 62
    color: "#00000000"
    border.width: 0

    property int rating: 2

    Row
    {
        anchors.fill: parent

        Repeater
        {
            model: 5

            Image
            {
                id: image
                width: parent.width / 5
                height: parent.height
                smooth: true
                antialiasing: true
                fillMode: Image.PreserveAspectFit
                //anchors.left: parent.left
                //anchors.leftMargin: 0
                source: "star.svg"
                mipmap: true
                cache: true

                scale:  mouseArea.containsMouse ? 1.0 : 0.8
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    hoverEnabled: true         //this line will enable mouseArea.containsMouse

                    onClicked:
                    {
                        ratingControl.rating = index
                    }
                }

                states: [
                    State
                    {
                        name: "star"
                        when: ratingControl.rating >= index
                        PropertyChanges {
                            target: image
                            opacity: 1
                            scale: 1
                        }
                    }
                ]
            }
        }
    }
    /*    Row
    {
        id: row1
        anchors.fill: parent

        Image
        {
            id: image2
            width: parent.width / 5
            height: parent.height
            smooth: true
            antialiasing: true
            fillMode: Image.PreserveAspectFit
            anchors.left: parent.left
            anchors.leftMargin: 0
            source: "star.svg"
            mipmap: true
            cache: true

            scale:  mouseArea.containsMouse ? 1.0 : 0.8
            MouseArea {
                   id: mouseArea
                   anchors.fill: parent
                   hoverEnabled: true         //this line will enable mouseArea.containsMouse
               }
        }

        Image
        {
            id: image3
            width: parent.width / 5
            height: parent.height
            antialiasing: true
            fillMode: Image.PreserveAspectFit
            anchors.left: image2.right
            anchors.leftMargin: 0
            source: "star.svg"
            mipmap: true
            cache: true
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
            mipmap: true
            cache: true
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
            mipmap: true
            cache: true
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
            mipmap: true
            cache: true
        }
    }*/
}
