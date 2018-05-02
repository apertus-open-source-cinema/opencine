// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

import QtQuick 2.4

Item
{
  anchors.fill: parent

  property alias delegate: listView.delegate
  property alias model: listView.model
  property alias currentIndex: listView.currentIndex
  property alias highlight: listView.highlight

  Component
  {
    id: highlightBox

    Rectangle
    {
      z: 2 //avoid highlighting hiding behind the items
      id: highlightBar
      width: listView.currentItem.width
      height: listView.currentItem.height

      border.width: 2
      border.color: "#BB0000"

      color: "transparent"

      radius: 3
      x: listView.currentItem.x
      y: listView.currentItem.y

      Behavior on y
      {
        PropertyAnimation
        {
          easing.type: Easing.Linear
          duration: 50
        }
      }
    }
  }

  ListView
  {
    id: listView
    anchors.rightMargin: 2
    anchors.leftMargin: 2
    anchors.bottomMargin: 2
    anchors.topMargin: 2
    boundsBehavior: Flickable.StopAtBounds
    anchors.fill: parent

    clip: true
    focus: true

    highlightFollowsCurrentItem: false
    highlight: highlightBox

    spacing: 3
  }

  ScrollBar
  {
    flickable: listView
  }
}
