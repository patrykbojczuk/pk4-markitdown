import QtQuick
import QtQuick.Controls
import "qrc:/"
import "qrc:/components"

MouseArea {
    id: iconLink
    cursorShape: Qt.PointingHandCursor
    width: maxWidth && (row.implicitWidth > maxWidth)
           ? maxWidth
           : row.implicitWidth;

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
            elide: Text.ElideMiddle
            width: iconLink.maxWidth && linkTextEl.implicitWidth > (iconLink.maxWidth - icon.width)
                   ? iconLink.maxWidth - icon.width
                   : linkTextEl.implicitWidth
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
            width: iconLink.maxWidth && linkPathEl.implicitWidth > (iconLink.maxWidth - icon.width - linkTextEl.width)
                   ? iconLink.maxWidth - icon.width - linkTextEl.width
                   : linkPathEl.implicitWidth
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            leftPadding: 5
            textFormat: Text.PlainText
            font.pointSize: fontSize
            color: Constants.fontColor25
            visible: linkPath.length && linkPathEl.width > 150
        }
    }

    CustomToolTip {
        id: toolTip
        text: tooltipText
        visible: tooltipText.length && hovered
        x: linkTextEl.x + 0.5 * linkTextEl.width - 0.5 * toolTip.width
        y: linkTextEl.height
        transitionDirection: CustomToolTip.EnterDirection.FromTop
    }
}


