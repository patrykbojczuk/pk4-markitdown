import QtQuick
import "qrc:/"

MouseArea{
    id: mouseArea
    width: 12
    height: mouseArea.width
    preventStealing: true

    property bool hovered: false

    HoverHandler{
        onHoveredChanged: {
            mouseArea.hovered = hovered
        }
    }

    Rectangle {
        color: mouseArea.color
        radius: (mouseArea.width / 2)
        border.color: mouseArea.borderColor
        border.width: 1
        anchors.fill: parent

        Image {
           id: icon
           source: mouseArea.iconUrl
           fillMode: Image.PreserveAspectFit
           sourceSize.height: 24
           sourceSize.width: 24
           anchors.fill: parent
           visible: false
        }
    }

    onHoveredChanged: {
        if (hovered) {
            icon.visible = true
        } else {
            icon.visible = false
        }
    }

    property color color: Constants.closeButtonColor
    property color borderColor: Constants.closeButtonBorderColor
    property url iconUrl: Constants.closeIcon
}
