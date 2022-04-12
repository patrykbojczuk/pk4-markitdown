import QtQuick
import QtQuick.Controls
import "qrc:/"
import "qrc:/components"

Item {
    id: editorScreen
    width: 1920
    height: 1080

    Item {
        id: mainEditor
        anchors.fill: parent
        anchors.bottomMargin: 13
        anchors.rightMargin: 13
        anchors.leftMargin: 13
        anchors.topMargin: 50


        Flickable {
            id: textEditFlickable
            clip: true
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.bottomMargin: 5
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.verticalCenter
            topMargin: 26
            leftMargin: 26
            rightMargin: 26
            bottomMargin: 26
            contentHeight: textEdit.implicitHeight
            boundsBehavior: Flickable.StopAtBounds
            flickableDirection: Flickable.VerticalFlick
            interactive: true

            TextEdit {
                id: textEdit
                text: qsTr("Text Edit")
                height: implicitHeight
                font.pixelSize: 14
                wrapMode: Text.WordWrap
                persistentSelection: true
                selectByMouse: true
                cursorVisible: true
                color: Constants.fontColor
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                focus: true

                Component.onCompleted:{
                    textEdit.selectAll()
                    textEdit.deselect()
                }
            }

            Keys.onDownPressed: textEditScrollBar.increase()
            Keys.onUpPressed: textEditScrollBar.decrease()

            ScrollBar.vertical: CustomScrollBar {
                id: textEditScrollBar
                wheelEnabled: true
                transform: [
                    Translate {
                        x: -13
                    },
                    Scale {
                        origin.y: textEditScrollBar.height / 2
                        yScale: (textEditScrollBar.height - (2 * 26)) / textEditScrollBar.height
                    }
                ]
            }
        }

        Item {
            id: spacerWrapper
            height: 10
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right

            Rectangle {
                id: spacer
                height: 2
                radius: 1
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 13
                anchors.leftMargin: 13
                color: Constants.lighterBackgroundColor
            }
        }

        Flickable {
            id: textDisplayFlickable
            clip: true
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            anchors.bottomMargin: 0
            anchors.topMargin: 5
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.verticalCenter
            anchors.bottom: parent.bottom
            topMargin: 26
            leftMargin: 26
            rightMargin: 26
            bottomMargin: 26
            contentHeight: textDisplay.implicitHeight
            boundsBehavior: Flickable.StopAtBounds
            flickableDirection: Flickable.VerticalFlick
            interactive: true

            Text {
                id: textDisplay
                text: textEdit.text
                height: implicitHeight
                font.pixelSize: 14
                wrapMode: Text.WordWrap
                color: Constants.fontColor
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
            }

            Keys.onDownPressed: textDisplayScrollBar.increase()
            Keys.onUpPressed: textDisplayScrollBar.decrease()

            ScrollBar.vertical: CustomScrollBar {
                id: textDisplayScrollBar
                wheelEnabled: true
                transform: [
                    Translate {
                        x: -13
                    },
                    Scale {
                        origin.y: textDisplayScrollBar / 2
                        yScale: (textDisplayScrollBar.height - (2 * 26)) / textDisplayScrollBar.height
                    }
                ]
            }
        }
    }

    states: [
        State {
            name: "twoColumns"
            when: editorScreen.width >= 1400

            PropertyChanges {
                target: spacerWrapper
                restoreEntryValues: true

                height: undefined
                width: 10
            }
            AnchorChanges {
                target: spacerWrapper

                anchors.verticalCenter: undefined
                anchors.left: undefined
                anchors.right: undefined

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }

            PropertyChanges {
                target: spacer
                restoreEntryValues: true

                height: undefined
                width: 2
                anchors.rightMargin: undefined
                anchors.leftMargin: undefined
                anchors.topMargin: 13
                anchors.bottomMargin: 13
            }
            AnchorChanges {
                target: spacer

                anchors.verticalCenter: undefined
                anchors.left: undefined
                anchors.right: undefined

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }

            PropertyChanges {
                target: textEditFlickable
                restoreEntryValues: true

                anchors.rightMargin: 5
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.bottomMargin: 0
            }
            AnchorChanges {
                target: textEditFlickable
                anchors.left: parent.left
                anchors.right: parent.horizontalCenter
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }

            PropertyChanges {
                target: textDisplayFlickable
                restoreEntryValues: true

                anchors.rightMargin: 0
                anchors.leftMargin: 5
                anchors.topMargin: 0
                anchors.bottomMargin: 0
            }
            AnchorChanges {
                target: textDisplayFlickable
                anchors.left: parent.horizontalCenter
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;height:620;width:510}
}
##^##*/
