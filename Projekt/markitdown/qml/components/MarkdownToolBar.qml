import QtQuick
import QtQuick.Controls
import "qrc:/"
import "qrc:/components"

Item {
    id: toolBar
    width: 1920
    height: 50

    Rectangle {
        id: rectangle
        height: 1
        color: "#40ffffff"
        border.width: 0
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.rightMargin: 1
        anchors.leftMargin: 1
    }

    Image {
        id: markdownIcon
        width: height
        opacity: 0.25
        source: "qrc:/assets/icons/HomeScreen/markdown.svg"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        anchors.leftMargin: 13
        fillMode: Image.PreserveAspectFit
    }

    Row {
        id: tools
        anchors.left: markdownIcon.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        spacing: 10
        anchors.rightMargin: 13
        anchors.leftMargin: 20
        anchors.bottomMargin: 10
        anchors.topMargin: 10

        IconButton {
            id: boldTool
            width: height
            color: Constants.lighterBackgroundColor
            hoveredColor: Constants.lighterLighterBackgroundColor
            iconPadding: 3
            iconSource: "qrc:/assets/icons/EditorScreen/MarkdownToolBar/bold.svg"
            radius: 6
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            toolTipText: "Bold"
            toolTipEnterDirection: CustomToolTip.EnterDirection.FromLeft
            toolTipPosition: CustomToolTip.Position.Right
        }

        IconButton {
            id: italicTool
            width: height
            color: Constants.lighterBackgroundColor
            hoveredColor: Constants.lighterLighterBackgroundColor
            iconPadding: 3
            iconSource: "qrc:/assets/icons/EditorScreen/MarkdownToolBar/italic.svg"
            radius: 6
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            toolTipText: "Italic"
            toolTipEnterDirection: CustomToolTip.EnterDirection.FromRight
            toolTipPosition: CustomToolTip.Position.Left
        }

        IconButton {
            id: strikethroughTool
            width: height
            color: Constants.lighterBackgroundColor
            hoveredColor: Constants.lighterLighterBackgroundColor
            iconPadding: 3
            iconSource: "qrc:/assets/icons/EditorScreen/MarkdownToolBar/strikethrough.svg"
            radius: 6
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            toolTipText: "Strikethrough"
            toolTipEnterDirection: CustomToolTip.EnterDirection.FromRight
            toolTipPosition: CustomToolTip.Position.Left
        }

        IconButton {
            id: headingTool
            width: height
            color: Constants.lighterBackgroundColor
            hoveredColor: Constants.lighterLighterBackgroundColor
            iconPadding: 3
            iconSource: "qrc:/assets/icons/EditorScreen/MarkdownToolBar/heading.svg"
            radius: 6
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            toolTipText: "Heading"
            toolTipEnterDirection: CustomToolTip.EnterDirection.FromRight
            toolTipPosition: CustomToolTip.Position.Left

            onClicked: {
                headerLevelSelector.opacity = 1
            }
        }

        IconButton {
            id: linkTool
            width: height
            color: Constants.lighterBackgroundColor
            hoveredColor: Constants.lighterLighterBackgroundColor
            iconPadding: 3
            iconSource: "qrc:/assets/icons/EditorScreen/MarkdownToolBar/link.svg"
            radius: 6
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            toolTipText: "Link"
            toolTipEnterDirection: CustomToolTip.EnterDirection.FromRight
            toolTipPosition: CustomToolTip.Position.Left
        }

        IconButton {
            id: ulTool
            width: height
            color: Constants.lighterBackgroundColor
            hoveredColor: Constants.lighterLighterBackgroundColor
            iconPadding: 3
            iconSource: "qrc:/assets/icons/EditorScreen/MarkdownToolBar/unordered-list.svg"
            radius: 6
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            toolTipText: "Unordered list"
            toolTipEnterDirection: CustomToolTip.EnterDirection.FromRight
            toolTipPosition: CustomToolTip.Position.Left
        }

        IconButton {
            id: olTool
            width: height
            color: Constants.lighterBackgroundColor
            hoveredColor: Constants.lighterLighterBackgroundColor
            iconPadding: 3
            iconSource: "qrc:/assets/icons/EditorScreen/MarkdownToolBar/ordered-list.svg"
            radius: 6
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            toolTipText: "Ordered list"
            toolTipEnterDirection: CustomToolTip.EnterDirection.FromRight
            toolTipPosition: CustomToolTip.Position.Left
        }

        IconButton {
            id: blockquoteTool
            width: height
            color: Constants.lighterBackgroundColor
            hoveredColor: Constants.lighterLighterBackgroundColor
            iconPadding: 3
            iconSource: "qrc:/assets/icons/EditorScreen/MarkdownToolBar/blockquote.svg"
            radius: 6
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            toolTipText: "Blockquote"
            toolTipEnterDirection: CustomToolTip.EnterDirection.FromRight
            toolTipPosition: CustomToolTip.Position.Left
        }

        IconButton {
            id: inlineCodeTool
            width: height
            color: Constants.lighterBackgroundColor
            hoveredColor: Constants.lighterLighterBackgroundColor
            iconPadding: 3
            iconSource: "qrc:/assets/icons/EditorScreen/MarkdownToolBar/inline-code.svg"
            radius: 6
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            toolTipText: "Inline code"
            toolTipEnterDirection: CustomToolTip.EnterDirection.FromRight
            toolTipPosition: CustomToolTip.Position.Left
        }

        IconButton {
            id: codeblockTool
            width: height
            color: Constants.lighterBackgroundColor
            hoveredColor: Constants.lighterLighterBackgroundColor
            iconPadding: 3
            iconSource: "qrc:/assets/icons/EditorScreen/MarkdownToolBar/codeblock.svg"
            radius: 6
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            toolTipText: "Code block"
            toolTipEnterDirection: CustomToolTip.EnterDirection.FromRight
            toolTipPosition: CustomToolTip.Position.Left
        }

        IconButton {
            id: imageTool
            width: height
            color: Constants.lighterBackgroundColor
            hoveredColor: Constants.lighterLighterBackgroundColor
            iconPadding: 3
            iconSource: "qrc:/assets/icons/EditorScreen/MarkdownToolBar/image.svg"
            radius: 6
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            toolTipText: "Image"
            toolTipEnterDirection: CustomToolTip.EnterDirection.FromRight
            toolTipPosition: CustomToolTip.Position.Left
        }
    }

    HeaderLevelSelector {
        id: headerLevelSelector
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: tools.x + headingTool.x + headingTool.width + 5
        visible: opacity > 0
        opacity: 0

        onClosed: {
            headerLevelSelector.opacity = 0
        }

        Behavior on opacity {
            NumberAnimation {
                target: headerLevelSelector
                property: "opacity"
                duration: 150
                easing.type: Easing.OutQuad
            }
        }
    }
}
