import QtQuick
import QtQuick.Controls
import pb.pk.markitdown 1.0
import "qrc:/"
import "qrc:/components"

Rectangle {
    id: windowTabBar
    width: 720
    height: 40
    color: Constants.lighterBackgroundColor
    radius: Constants.windowRadius
    border.color: "transparent"
    border.width: 0

    QtObject {
        id: readonlyProperties
        property int currentId: -1
    }

    property bool isMaximized: false
    property bool supportsSystemMove: false

    readonly property alias currentId: readonlyProperties.currentId
    readonly property alias currentIndex: tabs.currentIndex

    signal addNewFile

    signal close
    signal minimize
    signal resize

    signal startSystemMove
    signal addWindowX(real dX)
    signal addWindowY(real dY)

    signal openedTab(int id)
    signal closedTab(int id)

    signal focusOnTab(int id)

    function onOpenedTab(id) {
        tabs.openedTab(id)
    }

    function onClosedTab(id) {
        tabs.closedTab(id)
    }

    function onFocusOnTab(id) {
        tabs.focusOnTab(id)
    }

    Rectangle {
        // Hides bottom radius
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        height: Constants.windowRadius
        color: Constants.lighterBackgroundColor
    }

    MouseArea {
        // Move window
        anchors.fill: parent
        anchors.rightMargin: 5
        anchors.leftMargin: 5
        anchors.topMargin: 5
        propagateComposedEvents: true
        preventStealing: true

        property real previousX: 0
        property real previousY: 0

        onPressed: function (mouse) {
            startSystemMove()
            if (!supportsSystemMove) {
                previousX = mouseX
                previousY = mouseY
            }
        }

        onMouseXChanged: function (mouse) {
            if (previousX) {
                var dx = mouseX - previousX
                addWindowX(dx)
            }
        }
        onMouseYChanged: function (mouse) {
            if (previousY) {
                var dy = mouseY - previousY
                addWindowY(dy)
            }
        }
    }

    ScrollableTabBar {
        id: tabs
        position: TabBar.Header
        anchors.fill: parent
        contentHeight: 40
        activeFocusOnTab: false
        spacing: 0
        anchors.leftMargin: appButtons.width + appButtons.anchors.leftMargin * 2
        anchors.rightMargin: anchors.leftMargin
        background: Rectangle {
            color: "transparent"
        }
        onCurrentItemChanged: {
            readonlyProperties.currentId = tabs.currentItem.customId
            //tabs.cu
        }

        function closeTab(id) {
            TabManager.closeTab(id)
        }

        property var createdTabs: ({})

        readonly property var closableTabButtonCreator: Qt.createComponent(
                                                            "qrc:/components/ClosableTabButton.qml")

        function tabCreated(incubator, tab) {
            const tabButton = incubator.object
            tab.filenameChanged.connect(() => {
                                            tabButton.text = tab.getFilenameStem()
                                        })

            let i = tabs.contentChildren.length - 1
            for (i; i > 0; --i) {
                if (tabs.itemAt(i) === tabButton) {
                    tabs.moveItem(i, tabs.contentChildren.length - 2)
                    tabButton.visible = true
                    tabButton.closed.connect(tabs.closeTab)
                    createdTabs[tabButton.customId] = tabButton
                    focusOnTab(tabButton.customId)
                    break
                }
            }
        }

        function tabCreator(id, tab) {
            const incubator = closableTabButtonCreator.incubateObject(tabs, {
                                                                          "y": 0,
                                                                          "height": parent.height,
                                                                          "text": tab.getFilenameStem(),
                                                                          "customId": id,
                                                                          "visible": false
                                                                      })
            if (incubator.status !== Component.Ready) {
                incubator.onStatusChanged = function (status) {
                    if (status === Component.Ready) {
                        tabCreated(incubator, tab)
                    }
                }
            } else {
                tabCreated(incubator, tab)
            }
        }

        function createTabOfId(id) {
            const tab = TabManager.getTabById(id)
            tabCreator(id, tab)
        }

        function openedTab(id) {
            if (!createdTabs.hasOwnProperty(id)) {
                createTabOfId(id)
            } else {
                console.error(`Trying to add tab of existing id (${id})`)
            }
        }

        function closedTab(id) {
            if (createdTabs.hasOwnProperty(id)) {
                createdTabs[id].destroy()
                delete createdTabs[id]
            } else {
                console.error(`Trying to close not existing tab of id (${id})`)
            }
        }

        function focusOnTab(id) {
            if (createdTabs.hasOwnProperty(id)) {
                setCurrentIndex(createdTabs[id].TabBar.index)
            } else {
                console.error(`Trying to focus not existing tab of id (${id})`)
            }
        }

        ImageTabButton {
            y: 0
            width: parent.height
            height: parent.height
            text: "Home Screen"
            imageSource: "qrc:/assets/icons/home-screen.svg"
            imageSize: 18
            checked: true
            property int customId: -1
        }

        ImageTabButton {
            y: 0
            width: parent.height
            height: parent.height
            text: "New tab"
            imageSource: "qrc:/assets/icons/tab-new.svg"
            imageSize: 15
            checkable: false
            onClicked: addNewFile()
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 80
        color: Constants.lighterBackgroundColor
        radius: Constants.windowRadius

        Rectangle {
            // Hide
            color: Constants.lighterBackgroundColor
            width: Constants.windowRadius
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top
        }

        Row {
            id: appButtons
            width: 54
            height: 14
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 12
            topPadding: 1
            rightPadding: 1
            bottomPadding: 1
            leftPadding: 1
            spacing: 8

            HoverHandler {
                onHoveredChanged: {
                    if (hovered) {
                        closeButton.color = Constants.closeButtonColor
                        closeButton.borderColor = Constants.closeButtonBorderColor

                        minimizeButton.color = Constants.minimizeButtonColor
                        minimizeButton.borderColor = Constants.minimizeButtonBorderColor

                        resizeButton.color = Constants.resizeButtonColor
                        resizeButton.borderColor = Constants.resizeButtonBorderColor
                    } else if (!closeButton.hovered && !minimizeButton.hovered
                               && !resizeButton.hovered) {
                        closeButton.color = "#00000000"
                        closeButton.borderColor = Constants.backgroundColor

                        minimizeButton.color = "#00000000"
                        minimizeButton.borderColor = Constants.backgroundColor

                        resizeButton.color = "#00000000"
                        resizeButton.borderColor = Constants.backgroundColor
                    }
                }
            }

            WindowButton {
                id: closeButton
                width: 12
                height: 12
                color: "#00000000"
                borderColor: Constants.backgroundColor
                iconUrl: Constants.closeIcon
                onClicked: windowTabBar.close()
            }
            WindowButton {
                id: minimizeButton
                width: 12
                height: 12
                color: "#00000000"
                borderColor: Constants.backgroundColor
                iconUrl: Constants.minimizeIcon
                onClicked: windowTabBar.minimize()
            }
            WindowButton {
                id: resizeButton
                width: 12
                height: 12
                color: "#00000000"
                borderColor: Constants.backgroundColor
                iconUrl: isMaximized ? Constants.demaximizeIcon : Constants.maximizeIcon
                onClicked: windowTabBar.resize()
            }
        }
    }
}
