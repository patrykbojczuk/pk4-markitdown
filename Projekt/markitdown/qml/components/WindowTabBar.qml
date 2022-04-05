import QtQuick
import QtQuick.Controls
import "qrc:/"

Rectangle {
    height: 40
    border.color: "transparent"

    property bool isMaximized: false

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

        WindowButton {
            id: closeButton
            width: 12
            height: 12
            color: "#00000000"
            borderColor: Constants.backgroundColor
            iconUrl: Constants.closeIcon
        }
        WindowButton {
            id: minimizeButton
            width: 12
            height: 12
            color: "#00000000"
            borderColor: Constants.backgroundColor
            iconUrl: Constants.minimizeIcon
        }
        WindowButton {
            id: resizeButton
            width: 12
            height: 12
            color: "#00000000"
            borderColor: Constants.backgroundColor
            iconUrl: isMaximized ? Constants.demaximizeIcon : Constants.maximizeIcon
        }
    }
}


