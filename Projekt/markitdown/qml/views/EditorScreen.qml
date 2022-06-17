import QtQuick
import QtQuick.Controls
import pb.pk.markitdown 1.0
import "qrc:/"
import "qrc:/components"

Item {
    id: editorScreen
    width: 1920
    height: 1080

    property alias text: textEdit.text
    property string htmlText: ""

    signal copy
    signal cut
    signal paste

    signal formatBold
    signal formatItalic
    signal formatStrikethrough
    signal formatHeading(int level)
    signal formatLink
    signal formatUL
    signal formatOL
    signal formatBlockquote
    signal formatInlineCode
    signal formatCodeblock
    signal formatImage

    onCopy: function () {
        textEdit.copy()
    }

    onCut: function () {
        textEdit.cut()
    }

    onPaste: function () {
        textEdit.paste()
    }

    onFormatBold: function () {
        const boldModifiers = ["**", "__"]
        const start = textEdit.selectionStart, end = textEdit.selectionEnd
        textEdit.insert(end, boldModifiers[0])
        textEdit.insert(start, boldModifiers[0])
        textEdit.select(start + boldModifiers[0].length,
                        end + boldModifiers[0].length)

        textEdit.textChanged()
    }

    onFormatItalic: function () {
        const italicModifiers = ["*", "_"]
        const start = textEdit.selectionStart, end = textEdit.selectionEnd
        textEdit.insert(end, italicModifiers[0])
        textEdit.insert(start, italicModifiers[0])
        textEdit.select(start + italicModifiers[0].length,
                        end + italicModifiers[0].length)

        textEdit.textChanged()
    }

    onFormatStrikethrough: function () {
        const strikethroughModifier = '~~'
        const start = textEdit.selectionStart, end = textEdit.selectionEnd
        textEdit.insert(end, strikethroughModifier)
        textEdit.insert(start, strikethroughModifier)
        textEdit.select(start + strikethroughModifier.length,
                        end + strikethroughModifier.length)

        textEdit.textChanged()
    }

    onFormatHeading: function (level) {
        const genLevelStr = () => {
            let str = ""
            for (var i = 0; i < level; ++i) {
                str += "#"
            }
            return str
        }
        const start = textEdit.selectionStart, end = textEdit.selectionEnd
        textEdit.insert(end, "\n")
        textEdit.insert(start, "\n" + genLevelStr() + " ")

        textEdit.textChanged()
    }

    onFormatUL: function () {
        const start = textEdit.selectionStart, end = textEdit.selectionEnd
        let text = textEdit.getText(start, end)
        const lines = text.split("\n")
        lines.forEach(txt => txt = "- " + txt)
        text = lines.join("\n")
        textEdit.remove(start, end)
        textEdit.insert(start, text)

        textEdit.textChanged()
    }

    onFormatOL: function () {
        const start = textEdit.selectionStart, end = textEdit.selectionEnd
        let text = textEdit.getText(start, end)
        const lines = text.split("\n")
        let currentNum = 0
        lines.forEach(txt => txt = ++currentNum + ". " + txt)
        text = lines.join("\n")
        textEdit.remove(start, end)
        textEdit.insert(start, text)

        textEdit.textChanged()
    }

    onFormatBlockquote: function () {
        const start = textEdit.selectionStart, end = textEdit.selectionEnd
        let text = textEdit.getText(start, end)
        const lines = text.split("\n")
        lines.forEach(txt => txt = "> " + txt)
        text = lines.join("\n")
        textEdit.remove(start, end)
        textEdit.insert(start, text)

        textEdit.textChanged()
    }

    onFormatInlineCode: function () {
        const inlineCodeModifiers = ["`", "``"]
        const start = textEdit.selectionStart, end = textEdit.selectionEnd
        textEdit.insert(end, inlineCodeModifiers[0])
        textEdit.insert(start, inlineCodeModifiers[0])
        textEdit.select(start + inlineCodeModifiers[0].length,
                        end + inlineCodeModifiers[0].length)

        textEdit.textChanged()
    }

    onFormatCodeblock: function () {
        const start = textEdit.selectionStart, end = textEdit.selectionEnd
        textEdit.insert(end, "\n```")
        textEdit.insert(start, "```\n")

        textEdit.textChanged()
    }

    onFormatLink: function () {
        if (textEdit.selectedText !== '') {
            linkableElementDialog.textInputText = textEdit.selectedText
        } else {
            linkableElementDialog.textInputText = ''
        }
        linkableElementDialog.urlInputText = ''
        linkableElementDialog.titleInputText = ''

        linkableElementDialog.type = LinkableElementScreen.LinkableType.Link
        linkableElementDialog.open()

        textEdit.textChanged()
    }

    onFormatImage: function () {
        if (textEdit.selectedText !== '') {
            linkableElementDialog.textInputText = textEdit.selectedText
        } else {
            linkableElementDialog.textInputText = ''
        }
        linkableElementDialog.urlInputText = ''
        linkableElementDialog.titleInputText = ''

        linkableElementDialog.type = LinkableElementScreen.LinkableType.Image
        linkableElementDialog.open()

        textEdit.textChanged()
    }

    MarkdownToolBar {
        id: toolBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 50

        onFormatBold: editorScreen.formatBold()
        onFormatItalic: editorScreen.formatItalic()
        onFormatStrikethrough: editorScreen.formatStrikethrough()
        onFormatHeading: id => editorScreen.formatHeading(id)
        onFormatUL: editorScreen.formatUL()
        onFormatOL: editorScreen.formatOL()
        onFormatBlockquote: editorScreen.formatBlockquote()
        onFormatInlineCode: editorScreen.formatInlineCode()
        onFormatCodeblock: editorScreen.formatCodeblock()
        onFormatLink: editorScreen.formatLink()
        onFormatImage: editorScreen.formatImage()
    }

    LinkableElementScreen {
        id: linkableElementDialog

        onAccepted: function () {
            const start = textEdit.selectionStart, end = textEdit.selectionEnd

            textEdit.remove(start, end)
            textEdit.insert(
                        start,
                        `${linkableElementDialog.type === LinkableElementScreen.LinkableType.Image ? '!' : ''}[${linkableElementDialog.textInputText}](${linkableElementDialog.urlInputText}${linkableElementDialog.titleInputText.length ? ' "' + linkableElementDialog.titleInputText + '"' : ''})`)
        }
    }

    Connections {
        target: ConfigManager

        function onFontFamilyChanged() {
            textEdit.font.family = ConfigManager.fontFamily.family
            textDisplay.font.family = ConfigManager.fontFamily.family
        }

        function onFontSizeChanged() {
            textEdit.font.pointSize = ConfigManager.fontSize
            textDisplay.font.pointSize = ConfigManager.fontSize
        }
    }

    Item {
        id: mainEditor
        anchors.top: toolBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 13
        anchors.rightMargin: 13
        anchors.leftMargin: 13

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
                text: ""
                height: implicitHeight
                font.family: ConfigManager.fontFamily.family
                font.pointSize: ConfigManager.fontSize
                wrapMode: Text.WordWrap
                persistentSelection: true
                selectByMouse: true
                cursorVisible: true
                color: Constants.fontColor
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                focus: true

                Component.onCompleted: {
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
                text: editorScreen.htmlText
                textFormat: Text.RichText
                height: implicitHeight
                font.family: ConfigManager.fontFamily.family
                font.pointSize: ConfigManager.fontSize
                wrapMode: Text.WordWrap
                color: Constants.fontColor
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                onLinkActivated: function (link) {
                    Qt.openUrlExternally(link)
                }
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
                        yScale: (textDisplayScrollBar.height - (2 * 26))
                                / textDisplayScrollBar.height
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

