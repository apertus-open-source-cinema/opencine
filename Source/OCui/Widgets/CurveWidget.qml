import QtQuick 2.5

Rectangle {
    id: mainPane
    width: 100
    height: 100

    border.width: 13
    border.color: '#222222'

    property int posX: 10
    property int posY: 10
    property variant positions: [0, height, 10, 10, 30, 30, 40, 40, 50, 50, 60, 60, width, 0]

    property real scaleFactorX: width / 100.0
    property real scaleFactorY: height / 100.0

    Canvas {
        id: canvas
        width: parent.width
        height: parent.height

        transformOrigin: Item.TopLeft

        onPaint: {

            var ctx = getContext('2d')
            ctx.save()
            ctx.fillStyle = '#111111'
            ctx.strokeStyle = '#222222'
            ctx.fillRect(0, 0, width, height)

            var deltaX = width / 10
            var deltaY = height / 10

            ctx.beginPath()
            //Vertical lines
            for (var i = 0; i < 10; i++) {
                ctx.moveTo(deltaX * i, 0)
                ctx.lineTo(deltaX * i, height)
            }

            //Horizontal lines
            for (var i = 0; i < 10; i++) {
                ctx.moveTo(0, deltaY * i)
                ctx.lineTo(width, deltaY * i)
            }
            ctx.stroke()

            ctx.strokeStyle = '#666666'

            ctx.beginPath()
            ctx.moveTo(0, positions[1])
            ctx.lineTo(positions[0], positions[1])
            for (var i = 0; i < positions.length; i += 2) {
                ctx.quadraticCurveTo(120, 120, positions[i], positions[i + 1])
                ctx.moveTo(positions[i], positions[i + 1])
            }
            ctx.moveTo(positions[positions.length - 2],
                       positions[positions.length - 1])
            ctx.lineTo(width, positions[positions.length - 1])
            ctx.stroke()

            ctx.restore();
        }
    }

    Repeater {
        model: positions.length / 2
        delegate: DragHandle {
            id: point
            x: positions[index * 2] * scaleFactorX - width / 2
            y: positions[index * 2 + 1] * scaleFactorY - height / 2

            MouseArea {
                id: dragArea
                anchors.fill: parent
                drag.target: parent

                drag.minimumX: -parent.width / 2
                drag.maximumX: mainPane.width - (parent.width / 2)
                drag.minimumY: -parent.height / 2
                drag.maximumY: mainPane.height - (parent.height / 2)

                onPressed: parent.border.color = "red"
                onReleased: parent.border.color = "darkred"
                onPositionChanged: {
                    var globalCoordinares = point.mapToItem(point.parent,
                                                            parent.width / 2,
                                                            parent.height / 2)

                    positions[index * 2] = globalCoordinares.x
                    positions[index * 2 + 1] = globalCoordinares.y

                    canvas.requestPaint()
                }
            }
        }
    }
}
