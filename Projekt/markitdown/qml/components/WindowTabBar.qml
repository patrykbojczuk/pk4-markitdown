import QtQuick
import QtQuick.Controls
import "qrc:/"

Rectangle {
    height: 40
    border.color: "transparent"

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
    }
}


