import QtQuick
import QtQuick.Layouts
import "qrc:/"
import "qrc:/components"
import "qrc:/views"

Window {
    id: window
    width: 1280
    height: 720
    visible: true
    title: "Mark It Down"
    color: "transparent"
    flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground
    minimumWidth: 510
    minimumHeight: 300

    Rectangle {
        color: Constants.backgroundColor
        radius: Constants.windowRadius
        anchors.fill: parent

        WindowTabBar {
            id: tabBar
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 0
            anchors.rightMargin: 0
            anchors.leftMargin: 0

            isMaximized: window.visibility === 4

            onClose:{
                window.close();
                Qt.quit();
            }
            onMinimize: {
                window.visibility = window.visibility !== 3 ? 3 : 1
            }
            onResize: {
                window.visibility = window.visibility !== 4 ? 4 : 2
            }

            onStartSystemMove: {
                supportsSystemMove = window.startSystemMove()
            }
            onAddWindowX: function(dX) {
                window.setX(window.x + dX)
            }
            onAddWindowY: function(dY) {
                window.setY(window.y + dY)
            }

            onAddNewFile: {
                console.log("Handle file opening")
            }
        }

        StackLayout {
            id: contentWrapper
            anchors.fill: parent
            anchors.topMargin: tabBar.height

            HomeScreen {}
        }

        Rectangle {
            // Subtle frame
            anchors.fill: parent
            color: "#00000000"
            border.width: 1
            border.color: "#40ffffff"
            radius: 8
        }
    }

    ResizeHandler {
        anchors.fill: parent
        onChangeGeometry: function(x, y, w, h) {
            window.setGeometry(x, y, w, h)
        }
    }

    onWidthChanged: {
        if (width < minimumWidth) {
            width = minimumWidth
        }
    }

    onHeightChanged: {
        if (height < minimumHeight) {
            height = minimumHeight
        }
    }
}
