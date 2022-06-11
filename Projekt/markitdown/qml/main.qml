import QtQuick
import QtQuick.Layouts
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

    Rectangle {
        color: Constants.backgroundColor
        radius: Constants.windowRadius
        anchors.fill: parent

        FileHandler {
            id: fileHandler
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
                console.log('created editor for', tab.id)
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
