import QtQuick
import QtQuick.Layouts
import Qt.labs.platform 1.1
import pb.pk.markitdown 1.0
import "qrc:/"
import "qrc:/components"
import "qrc:/views"

Window {
    id: window
    width: 1280
    height: 720
    visible: true
    title: "Mark It Down"
    color: "transparent"
    flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground
    minimumWidth: 510
    minimumHeight: 300

    MenuBar {
        id: menuBar

        Menu {
            id: fileMenu
            title: "File"
            enabled: true

            MenuItem {
                text: "New file"
                onTriggered: fileHandler.createNewFileOrOverwrite()
            }

            MenuItem {
                text: "Open file"
                onTriggered: fileHandler.openFile()
            }

            MenuSeparator {
                visible: tabBar.currentId !== -1
            }

            MenuItem {
                visible: tabBar.currentId !== -1
                text: "Save file"
                onTriggered: {
                    TabManager.getTabById(tabBar.currentId).save()
                }
            }

            MenuItem {
                visible: tabBar.currentId !== -1
                text: "Save as"
                onTriggered: {
                    fileHandler.saveFileAs()
                }
            }

            MenuSeparator {
                visible: tabBar.currentId !== -1
            }

            Menu {
                visible: tabBar.currentId !== -1
                title: "Export"

                MenuItem {
                    text: "HTML"
                    onTriggered: {
                        fileHandler.exportToFile(FileHandler.ExportFormats.Html)
                    }
                }

                MenuItem {
                    text: "PDF"
                    onTriggered: {
                        fileHandler.exportToFile(FileHandler.ExportFormats.Pdf)
                    }
                }
            }
        }

        Menu {
            id: editMenu
            title: "Edit"
            visible: tabBar.currentId !== -1
            enabled: true

            MenuItem {
                text: "Copy"
                onTriggered: {
                    contentWrapper.itemAt(contentWrapper.currentIndex).copy()
                }
            }

            MenuItem {
                text: "Cut"
                onTriggered: {
                    contentWrapper.itemAt(contentWrapper.currentIndex).cut()
                }
            }

            MenuItem {
                text: "Paste"
                onTriggered: {
                    contentWrapper.itemAt(contentWrapper.currentIndex).paste()
                }
            }

            MenuSeparator {}

            MenuItem {
                text: "Bold"
                onTriggered: {
                    contentWrapper.itemAt(
                                contentWrapper.currentIndex).formatBold()
                }
            }

            MenuItem {
                text: "Italic"
                onTriggered: {
                    contentWrapper.itemAt(
                                contentWrapper.currentIndex).formatItalic()
                }
            }

            MenuItem {
                text: "Strikethrough"
                onTriggered: {
                    contentWrapper.itemAt(
                                contentWrapper.currentIndex).formatStrikethrough()
                }
            }

            Menu {
                title: "Header"

                MenuItem {
                    text: "Level 1"
                    onTriggered: {
                        contentWrapper.itemAt(
                                    contentWrapper.currentIndex).formatHeading(
                                    1)
                    }
                }

                MenuItem {
                    text: "Level 2"
                    onTriggered: {
                        contentWrapper.itemAt(
                                    contentWrapper.currentIndex).formatHeading(
                                    2)
                    }
                }

                MenuItem {
                    text: "Level 3"
                    onTriggered: {
                        contentWrapper.itemAt(
                                    contentWrapper.currentIndex).formatHeading(
                                    3)
                    }
                }

                MenuItem {
                    text: "Level 4"
                    onTriggered: {
                        contentWrapper.itemAt(
                                    contentWrapper.currentIndex).formatHeading(
                                    4)
                    }
                }

                MenuItem {
                    text: "Level 5"
                    onTriggered: {
                        contentWrapper.itemAt(
                                    contentWrapper.currentIndex).formatHeading(
                                    5)
                    }
                }

                MenuItem {
                    text: "Level 6"
                    onTriggered: {
                        contentWrapper.itemAt(
                                    contentWrapper.currentIndex).formatHeading(
                                    6)
                    }
                }
            }

            MenuItem {
                text: "Link"
                onTriggered: {
                    contentWrapper.itemAt(
                                contentWrapper.currentIndex).formatLink()
                }
            }

            MenuItem {
                text: "Unordered list"
                onTriggered: {
                    contentWrapper.itemAt(
                                contentWrapper.currentIndex).formatUL()
                }
            }

            MenuItem {
                text: "Ordered list"
                onTriggered: {
                    contentWrapper.itemAt(
                                contentWrapper.currentIndex).formatOL()
                }
            }

            MenuItem {
                text: "Blockquote"
                onTriggered: {
                    contentWrapper.itemAt(
                                contentWrapper.currentIndex).formatBlockquote()
                }
            }

            MenuItem {
                text: "Inline code"
                onTriggered: {
                    contentWrapper.itemAt(
                                contentWrapper.currentIndex).formatInlineCode()
                }
            }

            MenuItem {
                text: "Code block"
                onTriggered: {
                    contentWrapper.itemAt(
                                contentWrapper.currentIndex).formatCodeblock()
                }
            }

            MenuItem {
                text: "Image"
                onTriggered: {
                    contentWrapper.itemAt(
                                contentWrapper.currentIndex).formatImage()
                }
            }
        }

        Menu {
            title: "More"

            MenuItem {
                text: "Settings"
                onTriggered: {
                    settingsScreen.open()
                }
            }

            MenuSeparator {}

            MenuItem {
                text: "About"
                onTriggered: {
                    aboutScreen.open()
                }
            }
        }
    }

    SettingsScreen {
        id: settingsScreen
    }

    AboutScreen{
        id: aboutScreen
    }

    Rectangle {
        color: Constants.backgroundColor
        radius: Constants.windowRadius
        anchors.fill: parent

        FileHandler {
            id: fileHandler

            onFileSavedAs: function (filename) {
                TabManager.getTabById(tabBar.currentId).save(filename)
            }

            onFileExportedTo: function (filename, type) {
                if (type === FileHandler.ExportFormats.Pdf) {
                    TabManager.getTabById(tabBar.currentId).exportPdf(filename)
                    console.log("export pdf")
                } else if (type === FileHandler.ExportFormats.Html) {
                    TabManager.getTabById(tabBar.currentId).exportHtml(filename)
                    console.log("export html")
                } else {
                    console.error("Invalid export type")
                }
            }
        }

        QtObject {
            id: openedTabs

            property Connections connections: Connections {
                target: TabManager

                function onOpenedTabsChanged() {}

                function onTabOpened(id) {
                    contentWrapper.createTabEditorScreen(id)
                    tabBar.onOpenedTab(id)
                }

                function onTabClosed(id) {
                    tabBar.onClosedTab(id)
                    contentWrapper.closeTabEditorScreen(id)
                }
            }
        }

        WindowTabBar {
            id: tabBar
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 0
            anchors.rightMargin: 0
            anchors.leftMargin: 0

            isMaximized: window.visibility === 4

            onClose: {
                window.close()
                Qt.quit()
            }
            onMinimize: {
                window.visibility = window.visibility !== 3 ? 3 : 1
            }
            onResize: {
                window.visibility = window.visibility !== 4 ? 4 : 2
            }

            onStartSystemMove: {
                supportsSystemMove = window.startSystemMove()
            }
            onAddWindowX: function (dX) {
                window.setX(window.x + dX)
            }
            onAddWindowY: function (dY) {
                window.setY(window.y + dY)
            }

            onAddNewFile: fileHandler.createNewFileOrOverwrite()
        }

        StackLayout {
            id: contentWrapper
            anchors.fill: parent
            anchors.topMargin: tabBar.height
            currentIndex: tabBar.currentIndex

            readonly property var editorScreenCreator: Qt.createComponent(
                                                           "qrc:/views/EditorScreen.qml")

            property var createdEditors: ({})

            function createdTabEditorScreen(tab, incubator) {
                const editorScreen = incubator.object
                createdEditors[tab.id] = editorScreen
                editorScreen.textChanged.connect(() => {
                                                     tab.content = editorScreen.text
                                                 })
                tab.htmlContentChanged.connect(() => {
                                                   editorScreen.htmlText = tab.htmlContent
                                               })
            }

            function createTabEditorScreen(id) {
                const tab = TabManager.getTabById(id)

                const incubator = editorScreenCreator.incubateObject(
                                    contentWrapper, {
                                        "text": Qt.binding(() => tab.content),
                                        "htmlText": Qt.binding(
                                                        () => tab.htmlContent)
                                    })
                if (incubator.status !== Component.Ready) {
                    incubator.onStatusChanged = function (status) {
                        if (status === Component.Ready) {
                            createdTabEditorScreen(tab, incubator)
                        }
                    }
                } else {
                    createdTabEditorScreen(tab, incubator)
                }
            }

            function closeTabEditorScreen(id) {
                if (createdEditors.hasOwnProperty(id)) {
                    createdEditors[id].destroy()
                    delete createdEditors[id]
                }
            }

            HomeScreen {
                onAddNewFile: fileHandler.createNewFileOrOverwrite()
                onOpenFile: fileHandler.openFile()
            }
        }

        Rectangle {
            // Subtle frame
            anchors.fill: parent
            color: "#00000000"
            border.width: 1
            border.color: "#40ffffff"
            radius: 8
        }
    }

    ResizeHandler {
        anchors.fill: parent
        onChangeGeometry: function (x, y, w, h) {
            window.setGeometry(x, y, w, h)
        }
    }

    onWidthChanged: {
        if (width < minimumWidth) {
            width = minimumWidth
        }
    }

    onHeightChanged: {
        if (height < minimumHeight) {
            height = minimumHeight
        }
    }
}
