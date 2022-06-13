import QtQuick
import QtQuick.Controls
import "qrc:/"

Button {
    id: button
    enum IconPosition {
        Left,
        Right
    }
    property url iconSource
    property int iconPosition
    property int iconWidth
    property string buttonText

    width: 2 * iconLeft.width + 20 + buttonContentText.implicitWidth + 2 * 20
    height: 38
    background: Rectangle {
        color: hoverHandler.hovered ? Constants.lighterLighterBackgroundColor : Constants.backgroundColor
        radius: 6
    }

    HoverHandler {
        id: hoverHandler
        cursorShape: Qt.PointingHandCursor
        enabled: true
    }

    contentItem: Item {
        id: buttonContent
        anchors.fill: parent

        Image {
            id: iconLeft
            width: iconWidth
            height: width
            source: iconSource
            fillMode: Image.PreserveAspectFit
            visible: iconPosition === DialogButton.IconPosition.Left ? true : false
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: buttonContentText.left
            anchors.rightMargin: 20
        }

        Text {
            id: buttonContentText
            color: Constants.fontColor
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: iconPosition
                                            === DialogButton.IconPosition.Left ? 15 : -15
            text: parent.parent.text
        }

        Image {
            id: iconRight
            width: iconWidth
            height: width
            source: iconSource
            fillMode: Image.PreserveAspectFit
            visible: iconPosition === DialogButton.IconPosition.Right ? true : false
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: buttonContentText.right
            anchors.leftMargin: 20
        }
    }
}
