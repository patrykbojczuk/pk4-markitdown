import QtQuick
import QtQuick.Controls
import "qrc:/"

TabButton {
    property color backgroundColor: Constants.backgroundColor
    property int imageSize
    property url imageSource

    display: AbstractButton.IconOnly
    background: Rectangle {
        color: parent.checked ? backgroundColor : "transparent"
        border.width: 0
        width: parent.width
        height: parent.height
    }

    Image {
        width: imageSize
        height: imageSize
        anchors.verticalCenter: parent.verticalCenter
        source: imageSource
        anchors.horizontalCenter: parent.horizontalCenter
        sourceSize.height: imageSize
        sourceSize.width: imageSize
        antialiasing: true
    }
}
