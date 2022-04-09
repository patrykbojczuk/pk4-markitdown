import QtQuick
import QtQuick.Controls
import "qrc:/"

MouseArea {
    id: iconLink
    property url iconSource
    property string linkText
    property string linkPath
    property string tooltipText
    property int fontSize: 14

    readonly property alias hovered: hoverHandler.hovered

    HoverHandler {
        id: hoverHandler
    }

    Image {
        id: icon
        width: height
        height: 20
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        source: iconSource
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: linkTextEl
        text: linkText
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: icon.right
        font.underline: iconLink.hovered
        textFormat: Text.PlainText
        anchors.leftMargin: 10
        color: Constants.linkColor
        font.pointSize: fontSize
    }

    Text {
        id: linkPathEl
        text: linkPath
        elide: Text.ElideMiddle
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: linkTextEl.right
        verticalAlignment: Text.AlignVCenter
        textFormat: Text.PlainText
        fontSizeMode: Text.HorizontalFit
        font.pointSize: fontSize
        anchors.leftMargin: 5
        color: Constants.fontColor25
        visible: linkPath.length
    }

    ToolTip {
        id: toolTip
        delay: 250
        text: tooltipText
        horizontalPadding: tooltipTextEl.font.pointSize * 1.2
        visible: tooltipText.length && hovered
        x: linkTextEl.x + 0.5 * linkTextEl.width - 0.5 * toolTip.width
        y: linkTextEl.height
        background: Rectangle {
            color: Constants.lighterBackgroundColor
            border.width: 0
            radius: Constants.windowRadius / 2
        }
        contentItem: Text {
            id: tooltipTextEl
            color: Constants.fontColor
            text: toolTip.text
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:20;width:640}
}
##^##*/
