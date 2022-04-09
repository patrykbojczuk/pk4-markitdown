import QtQuick
import "qrc:/"


MouseArea {
    id: mouseArea
    width: 40
    height: 40
    cursorShape: Qt.PointingHandCursor
    property color color
    property color hoveredColor
    property int iconPadding
    property int radius
    property url iconSource

    Rectangle {
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

    readonly property alias hovered: readonlyProperties.hovered

    QtObject {
        id: readonlyProperties
        property bool hovered: hoverHandler.hovered
    }

    HoverHandler {
        id: hoverHandler
    }
}
