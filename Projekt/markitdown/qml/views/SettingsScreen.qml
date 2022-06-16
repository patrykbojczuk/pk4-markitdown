import QtQuick
import QtQuick.Controls
import pb.pk.markitdown 1.0
import QtQuick.Dialogs
import "qrc:/"

Dialog {
    id: dialog
    width: 475
    height: 300

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

    Connections {
        target: ConfigManager

        function onFontSizeChanged() {
            fontSizeText.text = ConfigManager.fontSize
        }

        function onFontFamilyChanged() {
            fontDialog.selectedFont = ConfigManager.fontFamily
        }

        function onAutosaveChanged() {
            autosaveSwitch.checked = ConfigManager.autosave
        }

        function onAutosaveTimeoutChanged() {
            autosaveTimeoutText.text = ConfigManager.autosaveTimeout
        }
    }

    FontDialog {
        id: fontDialog
        title: "Select display font"
        onAccepted: {
            ConfigManager.fontFamily = fontDialog.selectedFont
        }
        modality: Qt.WindowModal
    }

    Item {
        id: mainContent
        anchors.fill: parent
        anchors.bottomMargin: 0
        anchors.rightMargin: 0

        Text {
            id: titleText
            text: "Settings"
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

        Text {
            id: autosaveSwitchText
            anchors.left: autosaveSwitch.left
            anchors.bottom: autosaveSwitch.top
            anchors.bottomMargin: 5
            font.pointSize: 12
            color: autosaveSwitch.checked ? Constants.fontColor : Constants.fontColor50
            text: "Autosave"
        }

        Switch {
            id: autosaveSwitch
            anchors.left: parent.left
            anchors.top: titleText.bottom
            anchors.leftMargin: 60
            anchors.topMargin: 20
            padding: 0
            rightPadding: 0
            leftPadding: 0
            bottomPadding: 0
            topPadding: 0
            onCheckedChanged: {
                ConfigManager.autosave = autosaveSwitch.checked
            }
        }

        Button {
            id: fontButton
            y: 175
            text: qsTrId("Choose font")
            anchors.left: parent.left
            anchors.leftMargin: 60
            rightPadding: 12
            leftPadding: 12
            bottomPadding: 6
            topPadding: 6
            display: AbstractButton.TextOnly
            background: Rectangle {
                radius: 6
                anchors.fill: fontButton
                color: Constants.lighterLighterBackgroundColor
            }

            onClicked: {
                fontDialog.open()
            }
        }

        TextField {
            id: autosaveTimeoutText
            x: 274
            anchors.verticalCenter: autosaveSwitch.verticalCenter
            anchors.right: parent.right
            anchors.verticalCenterOffset: 0
            anchors.rightMargin: 60
            placeholderText: qsTrId("Autosave interval (ms)")
            color: Constants.fontColor
            validator: IntValidator {
                bottom: 500
            }

            background: Rectangle {
                radius: 6
                anchors.fill: autosaveTimeoutText
                color: Constants.lighterLighterBackgroundColor
                border.width: 1
                border.color: autosaveTimeoutText.acceptableInput ? "transparent" : "#aa0000"
            }

            onFocusChanged: {
                if (!autosaveTimeoutText.focus
                        && autosaveTimeoutText.acceptableInput) {
                    ConfigManager.autosaveTimeout = parseInt(
                                autosaveTimeoutText.text)
                }
            }
        }

        TextField {
            id: fontSizeText
            x: 274
            anchors.verticalCenter: fontButton.verticalCenter
            anchors.right: parent.right
            anchors.verticalCenterOffset: 0
            anchors.rightMargin: 60
            placeholderText: qsTrId("Font size (pt)")
            color: Constants.fontColor
            validator: IntValidator {
                bottom: 10
                top: 64
            }

            background: Rectangle {
                radius: 6
                anchors.fill: fontSizeText
                color: Constants.lighterLighterBackgroundColor
                border.width: 1
                border.color: fontSizeText.acceptableInput ? "transparent" : "#aa0000"
            }

            onFocusChanged: {
                if (!fontSizeText.focus && fontSizeText.acceptableInput) {
                    ConfigManager.fontSize = parseInt(fontSizeText.text)
                }
            }
        }

        Text {
            id: text1
            y: 213
            text: qsTrId("All settings are automatically saved")
            anchors.left: parent.left
            anchors.right: parent.right
            font.pixelSize: 12
            anchors.rightMargin: 60
            anchors.leftMargin: 60
            color: Constants.fontColor
        }
    }

    footer: Item {}
}
