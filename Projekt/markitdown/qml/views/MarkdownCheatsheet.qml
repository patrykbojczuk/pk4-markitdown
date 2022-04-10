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
                when: mainItem.width < 700

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
            spacing: 20

            readonly property bool horizontalFlow:  mainItem.width >= 600

            CheatsheetComparison {
                horizontalFlow: cheatsheetContents.horizontalFlow
                headerText: 'Headers'
                comparisonText: '# H1\n## H2\n### H3\n#### H4\n##### H5\n###### H6\n\nAlternatively, for H1 and H2, an underline-ish style:\n\nAlt-H1\n======\n\nAlt-H2\n------'
            }

            CheatsheetComparison {
                horizontalFlow: cheatsheetContents.horizontalFlow
                headerText: "Emphasis"
                comparisonText: "Emphasis, aka italics, with *asterisks* or _underscores_.\n\nStrong emphasis, aka bold, with **asterisks** or __underscores__.\n\nCombined emphasis with **asterisks and _underscores_**.\n\nStrikethrough uses two tildes. ~~Scratch this.~~"
            }

            CheatsheetComparison {
                horizontalFlow: cheatsheetContents.horizontalFlow
                headerText: "Lists"
                comparisonText: "1. First ordered list item\n2. Another item\n  * Unordered sub-list. \n1. Actual numbers don't matter, just that it's a number\n  1. Ordered sub-list\n2. And another item.\n\n   You can have properly indented paragraphs within list items. Notice the blank line above, and the leading spaces (at least one, but we'll use three here to also align the raw Markdown).\n\n   To have a line break without a paragraph, you will need to use two trailing spaces.  \n   Note that this line is separate, but within the same paragraph.  \n   (This is contrary to the typical GFM line break behaviour, where trailing spaces are not required.)\n\n* Unordered list can use asterisks\n- Or minuses\n+ Or pluses"
            }

            CheatsheetComparison {
                horizontalFlow: cheatsheetContents.horizontalFlow
                headerText: "Links"
                comparisonText: "[I'm an inline-style link](https://www.google.com)\n\n[I'm an inline-style link with title](https://www.google.com \"Google's Homepage\")\n\n[I'm a reference-style link][Arbitrary case-insensitive reference text]\n\n[I'm a relative reference to a repository file](../blob/master/LICENSE)\n\n[You can use numbers for reference-style link definitions][1]\n\nOr leave it empty and use the [link text itself].\n\nURLs and URLs in angle brackets will automatically get turned into links. \nhttp://www.example.com or <http://www.example.com> and sometimes example.com (but not on Github, for example).\n\nSome text to show that the reference links can follow later.\n\n[arbitrary case-insensitive reference text]: https://www.mozilla.org\n[1]: http://slashdot.org\n[link text itself]: http://www.reddit.com"
            }

            CheatsheetComparison {
                horizontalFlow: cheatsheetContents.horizontalFlow
                headerText: "Images"
                comparisonText: "Here's our logo (hover to see the title text):\n\nInline-style: \n![alt text](https://github.com/adam-p/markdown-here/raw/master/src/common/images/icon48.png \"Logo Title Text 1\")\n\nReference-style: \n![alt text][logo]\n\n[logo]: https://github.com/adam-p/markdown-here/raw/master/src/common/images/icon48.png \"Logo Title Text 2\""
            }

            CheatsheetComparison {
                horizontalFlow: cheatsheetContents.horizontalFlow
                headerText: "Code"
                comparisonText: "Inline `code` has `back-ticks around` it.\n\nBlocks of code are either fenced by lines with three back-ticks ` ``` `, or are indented with four spaces. I recommend only using the fenced code blocks.\n\n  \n\n```javascript\nvar s = \"JavaScript syntax highlighting\";\nalert(s);\n```\n \n```python\ns = \"Python syntax highlighting\"\nprint s\n```\n \n```\nNo language indicated, so no syntax highlighting. \nBut let's throw in a <b>tag</b>.\n```"
            }

            CheatsheetComparison {
                horizontalFlow: cheatsheetContents.horizontalFlow
                headerText: "Blockquotes"
                comparisonText: "> Blockquotes are very handy in email to emulate reply text.\n> This line is part of the same quote.\n\nQuote break.\n\n> This is a very long line that will still be quoted properly when it wraps. Oh boy let's keep writing to make sure this is long enough to actually wrap for everyone. Oh, you can *put* **Markdown** into a blockquote."
            }

            CheatsheetComparison {
                horizontalFlow: cheatsheetContents.horizontalFlow
                headerText: "Horizontal Rule"
                comparisonText: "Three or more...\n\n---\n\nHyphens\n\n***\n\nAsterisks\n\n___\n\nUnderscores"
            }

            CheatsheetComparison {
                horizontalFlow: cheatsheetContents.horizontalFlow
                headerText: "Line Breaks"
                comparisonText: "Here's a line for us to start with.\n\nThis line is separated from the one above by two newlines, so it will be a *separate paragraph*.\n\nThis line is also a separate paragraph, but...  \nThis line is only separated by a single newline, so it's a separate line in the *same paragraph*."
            }

            Item {
                height: 10
                anchors.left: parent.left
                anchors.right: parent.right
            }
        }

        ScrollBar.vertical: CustomScrollBar {
            id: vScrollBar
            wheelEnabled: true
            enabled: true
            active: true
            transform: Scale { yScale: (cheatsheetContents.implicitHeight - 65) / cheatsheetContents.implicitHeight }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:910;width:700}
}
##^##*/
