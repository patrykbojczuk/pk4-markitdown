import QtQuick
import QtQuick.Controls
import "qrc:/"
import "qrc:/components"

Rectangle {
    id: windowTabBar
    width: 720
    height: 40
    color: Constants.lighterBackgroundColor
    radius: Constants.windowRadius
    border.color: "transparent"
    border.width: 0

    property bool isMaximized: false
    property bool supportsSystemMove: false

    signal close
    signal minimize
    signal resize

    signal startSystemMove
    signal addWindowX(real dX)
    signal addWindowY(real dY)

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

    MouseArea {
        // Move window
        anchors.fill: parent
        anchors.rightMargin: 5
        anchors.leftMargin: 5
        anchors.topMargin: 5
        propagateComposedEvents: true
        preventStealing: true

        property real previousX: 0
        property real previousY: 0

        onPressed: function(mouse){
            startSystemMove()
            if (!supportsSystemMove){
                previousX = mouseX
                previousY = mouseY
            }
        }

        onMouseXChanged: {
            if (previousX){
                var dx = mouseX - previousX
                addWindowX(dx)
            }
        }
        onMouseYChanged: {
            if (previousY){
                var dy = mouseY - previousY
                addWindowY(dy)
            }
        }
    }

    ScrollableTabBar {
        id: tabs
        position: TabBar.Header
        anchors.fill: parent
        activeFocusOnTab: false
        spacing: 0
        contentHeight: 40
        anchors.leftMargin: appButtons.width + appButtons.anchors.leftMargin * 2
        anchors.rightMargin: anchors.leftMargin
        background: Rectangle {
            color: "transparent"
        }

        ImageTabButton {
            y: 0
            width: parent.height
            height: parent.height
            text: "Home Screen"
            imageSource: "qrc:/assets/icons/home-screen.svg"
            imageSize: 18
            checked: true
        }
        ClosableTabButton {
            y: 0
            height: parent.height
            text: "test1"
        }
        ClosableTabButton {
            y: 0
            height: parent.height
            text: "test2asdasdasdasdasdasd"
        }
        ClosableTabButton {
            y: 0
            height: parent.height
            text: "test1asdasdasdasdasdasdasdas"
        }
        ClosableTabButton {
            y: 0
            height: parent.height
            text: "test2asdasdasdasdasdsadasd"
        }
        ClosableTabButton {
            y: 0
            height: parent.height
            text: "test1asdasdasdasd"
        }
        ClosableTabButton {
            y: 0
            height: parent.height
            text: "test2asdasdasdasdasd"
        }
        ClosableTabButton {
            y: 0
            height: parent.height
            text: "test1asdasdasdasdasdasdasdasdasdasdasdasdasd"
        }
        ClosableTabButton {
            y: 0
            height: parent.height
            text: "test2asdasdasd"
            onClicked: {}
        }
        ImageTabButton {
            y: 0
            width: parent.height
            height: parent.height
            text: "New tab"
            imageSource: "qrc:/assets/icons/tab-new.svg"
            imageSize: 15
            checkable: false
            onClicked: {

            }
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 80
        color: Constants.lighterBackgroundColor

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
}
