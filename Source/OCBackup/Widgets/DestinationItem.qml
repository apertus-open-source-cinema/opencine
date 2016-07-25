import QtQuick 2.3
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item
{
    id: row1
    width: 270
    height: 36

    Rectangle
    {
        id: rectangle1
        color: "#2e2e2e"
        anchors.fill: parent
        anchors.right: rectangle3.left


        property string driveName: model.driveName ? model.driveName : "?";

        Text {
            id: pathInfo
            color: "#ffffff"
            text: driveName
            anchors.fill: parent
            anchors.right: driveSize.left
            clip: false
            antialiasing: false
            smooth: false
            styleColor: "#ff0000"
            font.pixelSize: 12
            elide: Text.ElideRight
        }
    }
}
