import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import "qrc:/"
import "qrc:/components"

Dialog {
    enum LinkableType {
        Link,
        Image
    }

    id: dialog
    width: 630
    height: 500
    visible: false
    dim: true
    anchors.centerIn: parent
    modal: true
    clip: false

    header: Item {}

    background: Rectangle {
        color: Constants.lighterBackgroundColor
        radius: 20
    }

    property alias urlInputText: urlInput.text
    property alias textInputText: textInput.text
    property alias titleInputText: titleInput.text

    property int type: LinkableElementScreen.LinkableType.Link
    title: type === LinkableElementScreen.LinkableType.Link ? 'Add link' : 'Add image'

    Item {
        id: mainContent
        anchors.fill: parent

        Text {
            id: titleText
            text: dialog.title
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            font.pixelSize: 48
            anchors.rightMargin: 60
            anchors.topMargin: 44
            anchors.leftMargin: 60
            font.styleName: "Bold"
            color: Constants.fontColor
        }

        Column {
            id: mainColumn

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: titleText.bottom
            anchors.topMargin: 15
            spacing: 15
            anchors.rightMargin: 60
            anchors.leftMargin: 60
            padding: 0

            InputBox {
                id: urlInput
                inputName: "URL"
                inputDescription: ""
            }

            InputBox {
                id: textInput
                inputName: type
                           === LinkableElementScreen.LinkableType.Link ? 'Text' : 'Alternative text'
                inputDescription: type === LinkableElementScreen.LinkableType.Link ? 'Shown instead of URL' : 'Shown when image cannot be loaded'
            }

            InputBox {
                id: titleInput
                inputName: "Title"
                inputDescription: "Shown as tooltip when hovered"
            }
        }

        Item {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: mainColumn.bottom
            anchors.rightMargin: 60
            anchors.leftMargin: 60
            anchors.topMargin: 35
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 60

            DialogButton {
                anchors.left: parent.left
                iconPosition: DialogButton.IconPosition.Left
                iconSource: 'qrc:/assets/icons/tab-close.svg'
                iconWidth: 20
                text: 'Cancel'
                DialogButtonBox.buttonRole: DialogButtonBox.DestructiveRole
                onClicked: dialog.reject()
            }

            DialogButton {
                anchors.right: parent.right
                iconPosition: DialogButton.IconPosition.Right
                iconSource: 'qrc:/assets/icons/tab-new.svg'
                iconWidth: 16
                text: 'Save'
                DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
                onClicked: dialog.accept()
            }
        }
    }

    footer: Item {}
}
