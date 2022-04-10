import QtQuick
import QtQuick.Controls
import "qrc:/"

ScrollBar {
    id: scrollBar
    policy: ScrollBar.AsNeeded

    contentItem: Rectangle {
        color: "transparent"
        implicitHeight: 6
        implicitWidth: 6

        Rectangle {
            id: scrollBarThumb
            color: scrollBar.size > 0.999
                   ? "transparent"
                   : scrollBar.pressed
                     ? Constants.fontColor50
                     : scrollBar.hovered
                       ? Constants.fontColor25
                       : Constants.fontColor10

            anchors.fill: parent
            radius: 1.5

            Behavior on color {
                ColorAnimation {
                    duration: 150
                    easing.type: Easing.OutQuad
                }
            }
        }

        states: [
            State {
                name: "horizontal"
                when: scrollBar.horizontal

                AnchorChanges {
                    target: scrollBar.contentItem
                    anchors.right: undefined
                    anchors.bottom: scrollBar.bottom
                }
                PropertyChanges {
                    target: scrollBarThumb
                    anchors.topMargin: 1
                    anchors.leftMargin: 3
                    anchors.bottomMargin: 2
                    anchors.rightMargin: 3
                }
            },
            State {
                name: "vertical"
                when: scrollBar.vertical

                AnchorChanges {
                    target: scrollBar.contentItem
                    anchors.bottom: undefined
                    anchors.right: scrollBar.right
                }
                PropertyChanges {
                    target: scrollBarThumb
                    anchors.topMargin: 3
                    anchors.leftMargin: 2
                    anchors.bottomMargin: 3
                    anchors.rightMargin: 2
                }
            }
        ]
    }
    background: Rectangle {
        color: "transparent"
    }
}
