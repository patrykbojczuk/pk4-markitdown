import QtQuick
import "qrc:/"

Column {
    id: textBox

    property alias text: input.text
    property string inputName
    property string inputDescription

    anchors.left: parent.left
    anchors.right: parent.right
    spacing: 3
    anchors.rightMargin: 0
    anchors.leftMargin: 0
    padding: 0

    Row {
        id: row
        height: row.implicitHeight
        anchors.left: parent.left
        anchors.right: parent.right
        rightPadding: 10
        leftPadding: 10
        anchors.topMargin: 0
        anchors.rightMargin: 0
        anchors.leftMargin: 0

        Text {
            id: inputNameText
            text: textBox.inputName
            color: Constants.fontColor
            font.pixelSize: 18
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: 10
        }

        Text {
            id: inputDescriptionText
            color: Constants.fontColor25
            text: textBox.inputDescription
            elide: Text.ElideMiddle
            font.pixelSize: 18
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            fontSizeMode: Text.HorizontalFit
            anchors.rightMargin: 10
            width: row.width - inputNameText.width - (5 + 10 + 10)
        }
    }

    Rectangle {
        id: rectangle
        radius: 6
        border.width: 1
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        border.color: Constants.fontColor50
        height: 42
        color: "transparent"

        TextInput {
            id: input
            visible: true
            color: Constants.fontColor

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            verticalAlignment: Text.AlignVCenter
            bottomPadding: 0
            topPadding: 0
            activeFocusOnPress: true
            cursorVisible: true
            selectByMouse: true
            persistentSelection: true
            rightPadding: 10
            leftPadding: 10
            anchors.topMargin: 0
            anchors.bottomMargin: 0
            font.pointSize: 20
            anchors.rightMargin: 0
            anchors.leftMargin: 0
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:3}
}
##^##*/

