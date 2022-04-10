import QtQuick
import QtQuick.Controls
import "qrc:/"
import "qrc:/components"

Item {
    id: mainItem
    readonly property int maxHeight: cheatsheetHeader.height + cheatsheetContents.height

    Item {
        id: cheatsheetHeader
        anchors.horizontalCenter: parent.horizontalCenter
        width: 700
        height: 100

        Text {
            id: cheatsheetHeaderText
            text: "markdown cheatsheet"
            font.pixelSize: 48
            verticalAlignment: Text.AlignVCenter
            font.family: "Poppins"
            font.weight: Font.Thin
            color: Constants.fontColor
        }

        MouseArea {
            id: authorMouseArea
            cursorShape: Qt.PointingHandCursor
            anchors.right: cheatsheetHeaderText.right
            anchors.top: cheatsheetHeaderText.bottom
            anchors.topMargin: -5
            height: authorLink.implicitHeight
            width: authorLink.implicitWidth

            Text {
                id: authorLink
                text: "by <u>Adam Pritchard</u>"
                font.pixelSize: 24
                horizontalAlignment: Text.AlignRight
                font.family: "Poppins"
                font.weight: Font.Light
                color: Constants.fontColor
            }

            onClicked: {
                Qt.openUrlExternally("https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet")
            }
        }

        MouseArea {
            id: licenseMouseArea
            cursorShape: Qt.PointingHandCursor
            anchors.left: authorMouseArea.right
            anchors.leftMargin: 5
            anchors.bottom: authorMouseArea.bottom
            anchors.bottomMargin: 2
            height: licenseLink.implicitHeight
            width: licenseLink.implicitWidth

            Text {
                id: licenseLink
                text: "(<u>CC-BY license</u>)"
                font.pixelSize: 18
                horizontalAlignment: Text.AlignRight
                font.family: "Poppins"
                textFormat: Text.RichText
                font.weight: Font.Light
                font.underline: false
                color: Constants.fontColor
            }

            onClicked: {
                Qt.openUrlExternally("https://creativecommons.org/licenses/by/3.0/")
            }
        }

        states: [
            State {
                name:"smWidthHeader"
                when: width < 700

                AnchorChanges {
                    target: cheatsheetHeader

                    anchors.horizontalCenter: undefined

                    anchors.left: mainItem.left
                    anchors.right: mainItem.right
                }
                PropertyChanges {
                    target: cheatsheetHeaderText
                    restoreEntryValues: true

                    fontSizeMode: Text.HorizontalFit
                    width: cheatsheetHeader.width
                }
                AnchorChanges {
                    target: licenseMouseArea

                    anchors.left: undefined
                    anchors.right: cheatsheetHeaderText.right
                }
                AnchorChanges {
                    target: authorMouseArea

                    anchors.right: licenseMouseArea.left
                }
                PropertyChanges {
                    target: authorMouseArea
                    restoreEntryValues: true

                    anchors.rightMargin: 5
                }
            }
        ]
    }

    Flickable {
        id: cheatsheetFlickable
        interactive: true
        clip: true
        flickableDirection: Flickable.VerticalFlick
        anchors.top: cheatsheetHeader.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        contentHeight: cheatsheetContents.implicitHeight

        Column {
            id: cheatsheetContents
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top

            Rectangle {
                width: 680
                height: 900
                color: "darkgreen"
            }

            Item {
                height: 25
                anchors.left: parent.left
                anchors.right: parent.right
            }
        }

        ScrollBar.vertical: CustomScrollBar {
            id: vScrollBar
            wheelEnabled: true
            enabled: true
            active: true
            transform: Scale { yScale: (cheatsheetContents.implicitHeight - 45) / cheatsheetContents.implicitHeight }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:910;width:700}
}
##^##*/
