import QtQuick
import QtQuick.Controls
import "qrc:/"
import "qrc:/components"

MouseArea {
    id: iconLink
    cursorShape: Qt.PointingHandCursor
    width: row.implicitWidth < maxWidth ? row.implicitWidth : maxWidth

    property url iconSource
    property string linkText
    property string linkPath
    property string tooltipText
    property int fontSize: 14
    property int maxWidth

    readonly property alias hovered: hoverHandler.hovered

    HoverHandler {
        id: hoverHandler
    }

    Row {
        id: row

        Image {
            id: icon
            width: height
            height: 20
            source: iconSource
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: linkTextEl
            text: linkText
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            leftPadding: 10
            font.underline: iconLink.hovered
            textFormat: Text.PlainText
            color: Constants.linkColor
            font.pointSize: fontSize
        }

        Text {
            id: linkPathEl
            text: linkPath
            elide: Text.ElideMiddle
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            leftPadding: 5
            textFormat: Text.PlainText
            fontSizeMode: Text.HorizontalFit
            font.pointSize: fontSize
            color: Constants.fontColor25
            visible: linkPath.length
        }
    }

    CustomToolTip {
        id: toolTip
        text: tooltipText
        visible: tooltipText.length && hovered
        x: linkTextEl.x + 0.5 * linkTextEl.width - 0.5 * toolTip.width
        y: linkTextEl.height
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:20;width:640}
}
##^##*/
