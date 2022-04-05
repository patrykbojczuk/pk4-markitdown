import QtQuick
import QtQuick.Controls
import "qrc:/"

Rectangle {
    id: windowTabBar
    height: 40
    color: Constants.lighterBackgroundColor
    radius: Constants.windowRadius
    border.color: "transparent"

    property bool isMaximized: false

    signal close
    signal minimize
    signal resize

    Rectangle {
        // Hides bottom radius
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        height: Constants.windowRadius
        color: Constants.lighterBackgroundColor
    }

    Row {
        id: appButtons
        width: 54
        height: 14
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 12
        topPadding: 1
        rightPadding: 1
        bottomPadding: 1
        leftPadding: 1
        spacing: 8

        HoverHandler {
            onHoveredChanged: {
                if (hovered) {
                    closeButton.color = Constants.closeButtonColor
                    closeButton.borderColor = Constants.closeButtonBorderColor

                    minimizeButton.color = Constants.minimizeButtonColor
                    minimizeButton.borderColor = Constants.minimizeButtonBorderColor

                    resizeButton.color = Constants.resizeButtonColor
                    resizeButton.borderColor = Constants.resizeButtonBorderColor
                } else if (!closeButton.hovered && !minimizeButton.hovered && !resizeButton.hovered) {
                    closeButton.color = "#00000000"
                    closeButton.borderColor = Constants.backgroundColor

                    minimizeButton.color = "#00000000"
                    minimizeButton.borderColor = Constants.backgroundColor

                    resizeButton.color = "#00000000"
                    resizeButton.borderColor = Constants.backgroundColor
                }
            }
        }

        WindowButton {
            id: closeButton
            width: 12
            height: 12
            color: "#00000000"
            borderColor: Constants.backgroundColor
            iconUrl: Constants.closeIcon
            onClicked: windowTabBar.close()
        }
        WindowButton {
            id: minimizeButton
            width: 12
            height: 12
            color: "#00000000"
            borderColor: Constants.backgroundColor
            iconUrl: Constants.minimizeIcon
            onClicked: windowTabBar.minimize()
        }
        WindowButton {
            id: resizeButton
            width: 12
            height: 12
            color: "#00000000"
            borderColor: Constants.backgroundColor
            iconUrl: isMaximized ? Constants.demaximizeIcon : Constants.maximizeIcon
            onClicked: windowTabBar.resize()
        }
    }
}


