import QtQuick
import QtQuick.Controls
import "qrc:/"

ToolTip {
    id: toolTip
    delay: 250
    horizontalPadding: tooltipTextEl.font.pointSize * 1.2
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
