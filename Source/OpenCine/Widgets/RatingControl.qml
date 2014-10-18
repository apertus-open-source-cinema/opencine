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
                opacity: 0.5

                scale:  mouseArea.containsMouse ? 1.0 : 0.6

                MouseArea
                {
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
                        PropertyChanges
                        {
                            target: image
                            opacity: 1
                            scale: mouseArea.containsMouse ? 1.0 : 0.8
                        }
                    }
                ]
            }
        }
    }
}
