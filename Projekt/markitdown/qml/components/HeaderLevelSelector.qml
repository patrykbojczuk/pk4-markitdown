import QtQuick
import "qrc:/"
import "qrc:/components"

Rectangle {
    id: background
    width: 220
    height: 30
    radius: height
    color: Constants.lighterBackgroundColor
    border.color: Constants.lighterLighterBackgroundColor
    border.width: 2

    signal formatHeader(int level)
    signal closed

    Row {
        id: row
        anchors.fill: parent
        anchors.rightMargin: 0
        rightPadding: 13
        leftPadding: 13
        spacing: 10

        HoverableMouseArea {
            anchors.verticalCenter: parent.verticalCenter
            height: 16
            width: 18
            cursorShape: Qt.PointingHandCursor

            onClicked: formatHeader(1)

            Text {
                text: "H1"
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                color: Constants.fontColor
                font.bold: parent.hovered
            }
        }

        HoverableMouseArea {
            anchors.verticalCenter: parent.verticalCenter
            height: 16
            width: 18
            cursorShape: Qt.PointingHandCursor

            onClicked: formatHeader(2)

            Text {
                text: "H2"
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                color: Constants.fontColor
                font.bold: parent.hovered
            }
        }

        HoverableMouseArea {
            anchors.verticalCenter: parent.verticalCenter
            height: 16
            width: 18
            cursorShape: Qt.PointingHandCursor

            onClicked: formatHeader(3)

            Text {
                text: "H3"
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                color: Constants.fontColor
                font.bold: parent.hovered
            }
        }

        HoverableMouseArea {
            anchors.verticalCenter: parent.verticalCenter
            height: 16
            width: 18
            cursorShape: Qt.PointingHandCursor

            onClicked: formatHeader(4)

            Text {
                text: "H4"
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                color: Constants.fontColor
                font.bold: parent.hovered
            }
        }

        HoverableMouseArea {
            anchors.verticalCenter: parent.verticalCenter
            height: 16
            width: 18
            cursorShape: Qt.PointingHandCursor

            onClicked: formatHeader(5)

            Text {
                text: "H5"
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                color: Constants.fontColor
                font.bold: parent.hovered
            }
        }

        HoverableMouseArea {
            anchors.verticalCenter: parent.verticalCenter
            height: 16
            width: 18
            cursorShape: Qt.PointingHandCursor

            onClicked: formatHeader(6)

            Text {
                text: "H6"
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                color: Constants.fontColor
                font.bold: parent.hovered
            }
        }

        Item {
            id: closeItem
            anchors.verticalCenter: parent.verticalCenter
            width: 28
            height: 18

            HoverableMouseArea {
                id: closeMouseArea
                width: 18
                height: width
                anchors.rightMargin: 0
                anchors.right: parent.right
                cursorShape: Qt.PointingHandCursor

                onClicked: background.closed()

                Image {
                    id: closeIcon
                    anchors.fill: parent
                    source: "qrc:/assets/icons/EditorScreen/MarkdownToolBar/close.svg"
                    opacity: closeMouseArea.hovered ? 0.66 : 0.33

                    Behavior on opacity {
                        NumberAnimation {
                            target: closeIcon
                            property: "opacity"
                            duration: 150
                            easing.type: Easing.OutQuad
                        }
                    }
                }
            }
        }
    }
}
