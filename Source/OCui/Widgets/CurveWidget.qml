import QtQuick 2.5

Rectangle
{
    width: 256
    height: 256

    border.width: 13
    border.color: '#222222'

    property int posX: 10
    property int posY: 10
    property variant positions: [0, height, 10, 10, 30, 30, 40, 40, 50, 50, 60, 60, width, 0]

    Canvas {
        id: canvas
        width: parent.width
        height: parent.height

        contextType: "2d"

        Path {
            id: myPath
            startX: 0; startY: 100

            PathCurve { x: 0; y: height }
            PathCurve { x: 10; y: 10 }
            PathCurve { x: positions[4]; y: positions[5] }
            PathCurve { x: 40; y: 40 }
            PathCurve { x: 50; y: 50 }
            PathCurve { x: 60; y: 60 }
            PathCurve { x: width; y: 0 }
        }

        onPaint: {

            var ctx = getContext('2d')
            ctx.fillStyle = '#111111'
            ctx.strokeStyle = '#222222'
            //ctx.setLineDash([2,3])
            ctx.fillRect(0, 0, width, height)

//            ctx.path = myPath
//            ctx.stroke();

            var deltaX = width / 10;
            var deltaY = height / 10;

            ctx.beginPath()
            for(var i = 0; i < 10; i++)
            {
                ctx.moveTo(deltaX * i, 0)
                ctx.lineTo(deltaX * i, height)
            }

            for(var i = 0; i < 10; i++)
            {
                ctx.moveTo(0, deltaY * i)
                ctx.lineTo(width, deltaY * i)
            }
            ctx.stroke()

            ctx.strokeStyle = '#666666'

            ctx.beginPath()
            ctx.moveTo(0, height)
            for(var i = 0; i < positions.length; i += 2)
            {
                ctx.quadraticCurveTo(120, 120, positions[i], positions[i + 1])
                ctx.moveTo(positions[i], positions[i + 1])
            }
            //ctx.lineTo(width, 0)
            ctx.stroke()

            /*var left = width * 0.25
        var right = width * 0.75
        var vCenter = height * 0.5
        var vDelta = height / 6

        ctx.lineCap = "square"
        ctx.lineWidth = vDelta * 0.4
        ctx.strokeStyle = 'black'

        ctx.beginPath()
        ctx.moveTo(left, vCenter - vDelta)
        ctx.lineTo(right, vCenter - vDelta)
        ctx.moveTo(left, vCenter)
        ctx.lineTo(right, vCenter)
        ctx.moveTo(left, vCenter + vDelta)
        ctx.lineTo(right, vCenter + vDelta)
        ctx.stroke()*/
        }
    }

    //    DropArea {
    //        x: 75; y: 75
    //        width: 50; height: 50

    //        Rectangle {
    //            anchors.fill: parent
    //            color: "green"

    //            visible: parent.containsDrag
    //        }
    //    }

    Repeater
    {
        model: positions.length / 2
        Rectangle
        {
            id: point
            width: 10
            height: 10
            color: "#111111"
            border.color: "darkred"
            border.width: 2
            radius: 5
            x: positions[index * 2] - width / 2
            y: positions[index * 2 + 1] - height / 2
            //x: posX / 2 - width / 2
            //y: posY / 2 - height / 2

            Drag.active: dragArea.drag.active
            //        Drag.hotSpot.x: posX
            //        Drag.hotSpot.y: posY
            Drag.onDragStarted:
            {
                parent.color = "blue"
                console.log("Drag started..")
                positions[index * 2] = x
                positions[index * 2 + 1] = y
                //posX = x
                //posY = y
            }

            MouseArea {
                id: dragArea
                anchors.fill: parent
                drag.target: parent

                //            onEntered:
                //            {
                //                console.log("Clicked..")
                //                parent.color = "red"

                //            }
                //            onExited:
                //            {
                //                parent.color = "darkred"
                //            }

                onPressed: parent.border.color = "red"
                onReleased: parent.border.color = "darkred"
                onPositionChanged: {
                    var globalCoordinares = point.mapToItem(point.parent, parent.width / 2, parent.height / 2)
                    positions[index * 2] = globalCoordinares.x
                    positions[index * 2 + 1] = globalCoordinares.y

                    canvas.requestPaint()
                }
            }
        }
    }

    Path {
        startX: 20; startY: 0
        PathCubic {
            x: 80; y: 0
            control1X: -10; control1Y: 90
            control2X: 210; control2Y: 90
        }
    }
}

