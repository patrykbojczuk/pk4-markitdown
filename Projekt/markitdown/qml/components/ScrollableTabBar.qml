import QtQuick
import QtQuick.Controls
import "qrc:/"

TabBar {
    id: tabBar

    contentItem: ListView {
        model: tabBar.contentModel
        currentIndex: tabBar.currentIndex

        spacing: tabBar.spacing
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds
        flickableDirection: Flickable.AutoFlickIfNeeded
        snapMode: ListView.SnapToItem

        ScrollBar.horizontal: ScrollBar {
            id: scrollBar
            policy: ScrollBar.AsNeeded

            contentItem: Rectangle {
                color: "transparent"
                implicitHeight: 6
                anchors.bottom: parent.bottom

                Rectangle {
                    color: scrollBar.size > 0.999
                           ? "transparent"
                           : scrollBar.pressed
                             ? Constants.fontColor50
                             : scrollBar.hovered
                               ? Constants.fontColor25
                               : Constants.fontColor10

                    anchors.fill: parent
                    anchors.topMargin: 1
                    anchors.leftMargin: 3
                    anchors.bottomMargin: 2
                    anchors.rightMargin: 3
                    radius: 1.5

                    Behavior on color {
                        ColorAnimation {
                            duration: 150
                            easing.type: Easing.OutQuad
                        }
                    }
                }
            }
            background: Rectangle {
                color: "transparent"
            }
        }

        highlightMoveDuration: 0
        highlightRangeMode: ListView.ApplyRange
        preferredHighlightBegin: 40
        preferredHighlightEnd: tabBar.height - 40
    }
}
