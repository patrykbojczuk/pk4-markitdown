import QtQuick
import Qt5Compat.GraphicalEffects
import "qrc:/"
import "qrc:/components"

HoverableMouseArea {
    id: mouseArea
    width: 40
    height: 40
    cursorShape: Qt.PointingHandCursor
    property color color
    property color hoveredColor
    property int iconPadding
    property int radius
    property url iconSource
    property string toolTipText
    property int toolTipPosition: CustomToolTip.Position.Left
    property int toolTipEnterDirection: CustomToolTip.EnterDirection.FromRight

    DropShadow {
        color: "#000"
        radius: background.radius * 2
        source: background
        spread: 0.5
        cached: true
        transparentBorder: true
        anchors.fill: background
    }

    Rectangle {
        id: background
        anchors.fill: parent
        radius: mouseArea.radius
        border.width: 0
        color: mouseArea.hovered
               ? mouseArea.hoveredColor
               : mouseArea.color


        Image {
            source: iconSource
            fillMode: Image.PreserveAspectFit
            anchors.fill: parent
            anchors.topMargin: mouseArea.iconPadding
            anchors.bottomMargin: mouseArea.iconPadding
            anchors.leftMargin: mouseArea.iconPadding
            anchors.rightMargin: mouseArea.iconPadding
        }

        Behavior on color {
            ColorAnimation {
                duration: 200
                easing.type: Easing.OutQuad
            }
        }
    }

    CustomToolTip {
        id: buttonToolTip
        visible: toolTipText.length && mouseArea.hovered
        text: toolTipText
        transitionDirection: toolTipEnterDirection
    }

    states: [
        State {
            name: 'toolTipOnTop'
            when: toolTipPosition === CustomToolTip.Position.Top

            PropertyChanges {
                target: buttonToolTip

                x: background.x + 0.5 * background.width - 0.5 * buttonToolTip.width
                y: -(buttonToolTip.height + 10)

            }
        },
        State {
            name: 'toolTipOnRight'
            when: toolTipPosition === CustomToolTip.Position.Right

            PropertyChanges {
                target: buttonToolTip

                x: buttonToolTip.width + 10
                y: background.y + 0.5 * background.height - 0.5 * buttonToolTip.height
            }
        },
        State {
            name: 'toolTipOnBottom'
            when: toolTipPosition === CustomToolTip.Position.Bottom

            PropertyChanges {
                target: buttonToolTip

                x: background.x + 0.5 * background.width - 0.5 * buttonToolTip.width
                y: buttonToolTip.height + 10

            }
        },
        State {
            name: 'toolTipOnLeft'
            when: toolTipPosition === CustomToolTip.Position.Left

            PropertyChanges {
                target: buttonToolTip

                x: -(buttonToolTip.width + 10)
                y: background.y + 0.5 * background.height - 0.5 * buttonToolTip.height
            }
        }
    ]
}
