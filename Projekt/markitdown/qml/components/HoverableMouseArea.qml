import QtQuick

MouseArea {
    id: mouseArea
    readonly property alias hovered: hoverHandler.hovered

    HoverHandler {
        id: hoverHandler
        enabled: mouseArea.hoverEnabled
    }
}
