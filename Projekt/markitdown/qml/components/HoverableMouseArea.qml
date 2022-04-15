import QtQuick

MouseArea {
    id: mouseArea
    hoverEnabled: true
    readonly property alias hovered: hoverHandler.hovered

    HoverHandler {
        id: hoverHandler
        enabled: mouseArea.hoverEnabled
    }
}
