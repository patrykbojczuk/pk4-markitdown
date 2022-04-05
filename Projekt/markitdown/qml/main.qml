import QtQuick
import "qrc:/"
import "qrc:/components"

Window {
    id: window
    width: 1280
    height: 720
    visible: true
    title: "Mark It Down"
    color: "transparent"
    flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground

    Rectangle {
        id: contentWrapper
        color: Constants.backgroundColor
        radius: Constants.windowRadius
        anchors.fill: parent

        WindowTabBar {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 0
            anchors.rightMargin: 0
            anchors.leftMargin: 0

            isMaximized: window.visibility === 4
        }
    }
}
