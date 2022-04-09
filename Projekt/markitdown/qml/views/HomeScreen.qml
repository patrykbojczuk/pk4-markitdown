import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import "qrc:/"
import "qrc:/components"

Rectangle {
    id: homeScreen
    width: 510
    height: 1080
    color: "transparent"
    border.width: 0

    Rectangle {
        id: leftContainer
        color: "transparent"
        width: appNameHeader.implicitWidth
        height: 480
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        anchors.topMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            id: appNameHeader
            color: Constants.fontColor
            text: "Mark It Down"
            verticalAlignment: Text.AlignVCenter
            padding: 0
            rightPadding: 0
            leftPadding: 0
            bottomPadding: 0
            topPadding: 0
            font.kerning: true
            font.weight: Font.DemiBold
            font.pointSize: 64
        }

        Text {
            id: appNameSubheader
            color: Constants.fontColor
            text: "markdown editor"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: appNameHeader.bottom
            anchors.topMargin: -6
            font.pixelSize: 36
            font.kerning: true
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Thin
        }

        Item {
            id: markdownCheatsheetButtonGroup
            anchors.verticalCenter: appNameSubheader.verticalCenter
            anchors.right: leftContainer.right
            anchors.rightMargin: 3
            width: 30
            height: width

            DropShadow {
                color: "#000"
                radius: markdownCheatsheetButton.radius * 2
                source: markdownCheatsheetButton
                spread: 0.5
                cached: true
                transparentBorder: true
                anchors.fill: markdownCheatsheetButton
            }

            IconButton {
                id: markdownCheatsheetButton
                color: Constants.lighterBackgroundColor
                hoveredColor: Constants.lighterLighterBackgroundColor
                iconPadding: 5
                radius: width / 5
                iconSource: "qrc:/assets/icons/HomeScreen/markdown.svg"
                anchors.fill: parent
            }

            CustomToolTip {
                id: markdownCheatsheetButtonToolTip
                visible: markdownCheatsheetButton.hovered
                text: 'Markdown Cheatsheet'
                y: markdownCheatsheetButton.y + 0.5 * markdownCheatsheetButton.height - 0.5 * markdownCheatsheetButtonToolTip.height
                x: -(markdownCheatsheetButtonToolTip.width + 10)
            }
        }

        Text {
            id: startSectionHeader
            color: Constants.fontColor
            text: "Start"
            anchors.left: parent.left
            anchors.top: appNameSubheader.bottom
            font.pixelSize: 24
            font.kerning: true
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 40
            font.weight: Font.Normal
        }

        Column {
            id: startSectionLinks
            height: 40
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: startSectionHeader.bottom
            anchors.rightMargin: 0
            spacing: 5
            anchors.topMargin: 7

            IconLink {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                height: 16
                iconSource: "qrc:/assets/icons/HomeScreen/new-file.svg"
                linkText: "New file"
                tooltipText: "Create and open new markdown file"
            }

            IconLink {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                height: 16
                iconSource: "qrc:/assets/icons/HomeScreen/open-file.svg"
                linkText: "Open"
                tooltipText: "Open existing markdown file"
            }
        }

        Text {
            id: recentFilesSectionHeader
            color: Constants.fontColor
            text: "Recent files"
            anchors.left: parent.left
            anchors.top: startSectionLinks.bottom
            font.pixelSize: 24
            font.kerning: true
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 64
        }

        Column {
            id: recentFilesSectionSectionLinks
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: recentFilesSectionHeader.bottom
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 100
            anchors.leftMargin: 0
            anchors.topMargin: 7
            anchors.rightMargin: 0
            spacing: 5

            IconLink {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                height: 20
                iconSource: "qrc:/assets/icons/HomeScreen/markdown-link.svg"
                linkText: "example.md"
                linkPath: "~/Documents/projects/mid"
                tooltipText: linkPath + '/' + linkText
            }

            IconLink {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                height: 20
                iconSource: "qrc:/assets/icons/HomeScreen/markdown-link.svg"
                linkText: "README.md"
                linkPath: "~/Documents/projects/mid"
                tooltipText: linkPath + '/' + linkText
            }

            IconLink {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                height: 20
                iconSource: "qrc:/assets/icons/HomeScreen/markdown-link.svg"
                linkText: "privacy policy.md"
                linkPath: "~/Documents/projects/mid"
                tooltipText: linkPath + '/' + linkText
            }

            IconLink {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                height: 20
                iconSource: "qrc:/assets/icons/HomeScreen/markdown-link.svg"
                linkText: "example2.md"
                linkPath: "~/Documents/projects/mid"
                tooltipText: linkPath + '/' + linkText
            }
        }
    }

    states: [
        State {
            name: 'twoColumns'
            when: homeScreen.width >= 1400
            PropertyChanges {
                target: markdownCheatsheetButtonGroup
                visible: false
            }
            PropertyChanges {
                target: leftContainer
                anchors.horizontalCenter: undefined
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/
