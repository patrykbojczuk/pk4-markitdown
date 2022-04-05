import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import "qrc:/"

TabButton {
    property color backgroundColor: Constants.backgroundColor
    property color textColor: Constants.fontColor
    property int customId: -1
    property int maxTextWidth: 120

    signal closed(int id)

    id: button
    display: AbstractButton.TextOnly
    contentItem: Text {
        id: btnText
        text: parent.text
        elide: Text.ElideMiddle
        anchors.verticalCenter: parent.verticalCenter
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        textFormat: Text.PlainText
        maximumLineCount: 1
        fontSizeMode: Text.HorizontalFit
        font: parent.font
        anchors.right: close.left
        anchors.rightMargin: 13
        anchors.left: parent.left
        anchors.leftMargin: 13
        color: parent.textColor
        antialiasing: true
        onImplicitWidthChanged: {
            if (implicitWidth > maxTextWidth){
                width = maxTextWidth
            }
        }
        width: implicitWidth
    }
    background: Rectangle {
        color: parent.checked ? backgroundColor : "transparent"
        border.width: 0
        width: parent.width
        height: parent.height
    }
    width: (btnText.implicitWidth > maxTextWidth
                ? maxTextWidth
                : btnText.implicitWidth)
                    + 3 * 13 + close.width

    MouseArea {
        id: close
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 13
        anchors.right: parent.right
        width: 14
        height: width
        hoverEnabled: true

        onClicked: {
            closed(customId)
        }

        property bool hovered: false

        HoverHandler {
            onHoveredChanged: {
                close.hovered = hovered
            }
        }

        Image {
            id: closeIcon
            source: "qrc:/assets/icons/tab-close.svg"
            antialiasing: true
            fillMode: Image.PreserveAspectFit
            sourceSize.height: 14
            sourceSize.width: 14
            width: parent.width
            height: width
        }
        Glow {
            anchors.fill: closeIcon
            source: closeIcon
            transparentBorder: true
            spread: 0.75
            radius: 1
            color: close.hovered ? "#FFFFFF" : "transparent"
        }
    }
}

