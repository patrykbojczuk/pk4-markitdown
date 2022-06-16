import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import pb.pk.markitdown 1.0
import "qrc:/"
import "qrc:/components"
import "qrc:/views"

Item {
    id: homeScreen
    width: 510
    height: 1080

    signal addNewFile
    signal openFile

    Item {
        id: leftContainer
        width: appNameHeader.implicitWidth
        height: 480
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: 100
        anchors.bottomMargin: 100
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

        IconButton {
            id: markdownCheatsheetButton
            anchors.verticalCenter: appNameSubheader.verticalCenter
            anchors.right: leftContainer.right
            anchors.rightMargin: 3
            width: 30
            height: width
            color: Constants.lighterBackgroundColor
            hoveredColor: Constants.lighterLighterBackgroundColor
            iconPadding: 5
            radius: width / 5
            iconSource: "qrc:/assets/icons/HomeScreen/markdown.svg"
            toolTipEnterDirection: CustomToolTip.EnterDirection.FromRight
            toolTipPosition: CustomToolTip.Position.Left
            toolTipText: "Markdown Cheatsheet"

            onClicked: {
                cheatsheetWindow.visible = true
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
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                height: 16
                iconSource: "qrc:/assets/icons/HomeScreen/new-file.svg"
                linkText: "New file"
                tooltipText: "Create and open new markdown file"
                onClicked: addNewFile()
            }

            IconLink {
                anchors.left: parent.left
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                height: 16
                iconSource: "qrc:/assets/icons/HomeScreen/open-file.svg"
                linkText: "Open"
                tooltipText: "Open existing markdown file"
                onClicked: openFile()
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
            visible: ConfigManager.recentFiles.length
        }

        readonly property var iconLinkFactory: Qt.createComponent(
                                                   "qrc:/components/IconLink.qml")

        property Connections connections: Connections {
            target: ConfigManager

            function onRecentFilesChanged() {
                recentFilesSectionSectionLinks.generateList()
                recentFilesSectionHeader.visible = ConfigManager.recentFiles.length
            }
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

            function cleanList() {
                for (const childId in recentFilesSectionSectionLinks.children) {
                    recentFilesSectionSectionLinks.children[childId].destroy()
                }
            }

            function addListItem(name, path) {
                const incubator = leftContainer.iconLinkFactory.incubateObject(
                                    recentFilesSectionSectionLinks, {
                                        "maxWidth": recentFilesSectionSectionLinks.width,
                                        "anchors.left": recentFilesSectionSectionLinks.left,
                                        "anchors.rightMargin": 0,
                                        "anchors.leftMargin": 0,
                                        "height": 20,
                                        "iconSource": "qrc:/assets/icons/HomeScreen/markdown-link.svg",
                                        "linkText": name,
                                        "linkPath": path,
                                        "tooltipText": 'Open ' + path + '/' + name
                                    })
                if (incubator.status !== Component.Ready) {
                    incubator.onStatusChanged = function (status) {
                        if (status === Component.Ready) {
                            incubator.object.clicked.connect(
                                        linkClicked.bind(this, name, path))
                        }
                    }
                } else {
                    incubator.object.clicked.connect(linkClicked.bind(this,
                                                                      name,
                                                                      path))
                }
            }

            function linkClicked(name, path) {
                TabManager.createTab(path + '/' + name)
            }

            function generateList() {
                cleanList()
                for (var i = ConfigManager.recentFiles.length - 1, max = 4; i !== 0
                     && max !== 0; --i & --max) {

                    addListItem(ConfigManager.getFilenameName(
                                    ConfigManager.recentFiles[i]),
                                ConfigManager.getFilenameParent(
                                    ConfigManager.recentFiles[i]))
                }
            }
        }
    }

    Item {
        id: rightContainer
        visible: false
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: 50
        anchors.bottomMargin: 50
        anchors.left: leftContainer.right
        anchors.right: parent.right
        anchors.leftMargin: 150
        anchors.rightMargin: 150

        MarkdownCheatsheet {
            id: rightContainerCheatsheet
            anchors.fill: parent
            anchors.leftMargin: 25
            anchors.rightMargin: 25
            anchors.bottomMargin: 0
            anchors.topMargin: 0
        }
    }

    Window {
        id: cheatsheetWindow
        title: "markdown cheatsheet"
        visible: false
        color: Constants.backgroundColor
        minimumWidth: 420
        width: 700
        height: 620
        maximumHeight: cheatsheetWindowCheatsheet.maxHeight

        MarkdownCheatsheet {
            id: cheatsheetWindowCheatsheet
            anchors.fill: parent
            anchors.leftMargin: 25
            anchors.rightMargin: 25
            anchors.bottomMargin: 0
            anchors.topMargin: 0
        }
    }

    states: [
        State {
            name: 'twoColumns'
            when: homeScreen.width >= 1400
            PropertyChanges {
                target: markdownCheatsheetButton
                restoreEntryValues: true

                visible: false
            }
            AnchorChanges {
                target: leftContainer
                anchors.horizontalCenter: undefined
                anchors.left: parent.left
                anchors.right: parent.horizontalCenter
            }
            PropertyChanges {
                target: leftContainer
                restoreEntryValues: true

                anchors.leftMargin: 200
                anchors.rightMargin: 100
            }
            PropertyChanges {
                target: rightContainer
                restoreEntryValues: true

                visible: true
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/

