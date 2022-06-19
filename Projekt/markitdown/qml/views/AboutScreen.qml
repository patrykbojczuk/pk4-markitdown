import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import "qrc:/"

Dialog {
    id: aboutDialog
    height: 420
    width: 630

    visible: false
    dim: true
    anchors.centerIn: parent
    modal: true

    header: Item {}

    background: Rectangle {
        color: Constants.lighterBackgroundColor
        radius: 20
    }
    Text {
        id: titleText
        text: "About"
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
        id: mainText
        height: 60
        text: qsTrId(
                  "App created as a project in the Computer Programming course.")
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: titleText.bottom
        font.pixelSize: 24
        wrapMode: Text.WordWrap
        anchors.topMargin: 20
        anchors.rightMargin: 60
        anchors.leftMargin: 60
        color: Constants.fontColor
    }

    MouseArea {
        id: pbGithubLinkMouseArea
        width: pbGithubLink.implicitWidth
        height: 31
        anchors.verticalCenter: licensesHeader.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 60
        cursorShape: Qt.PointingHandCursor

        Text {
            id: pbGithubLink
            x: 0
            y: 0
            text: qsTrId("@patrykbojczuk")
            font.pixelSize: 24
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignTop
            wrapMode: Text.WordWrap
            font.underline: true
            color: Constants.fontColor
        }

        onClicked: {
            Qt.openUrlExternally("https://github.com/patrykbojczuk")
        }
    }

    Text {
        id: licensesHeader
        height: 30
        text: qsTrId("Licenses")
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: mainText.bottom
        font.pixelSize: 24
        wrapMode: Text.NoWrap
        font.bold: true
        anchors.rightMargin: 60
        anchors.leftMargin: 60
        anchors.topMargin: 15
        color: Constants.fontColor
    }

    Column {
        id: column
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: licensesHeader.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 135
        anchors.topMargin: 10
        anchors.rightMargin: 60
        anchors.leftMargin: 60
        spacing: 10

        Row {
            id: licensedRowQt
            height: 17
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            spacing: 10

            Text {
                id: licensedNameQt
                width: licensedNameCheatsheet.width
                text: qsTrId("Qt 6")
                font.pixelSize: 14
                font.bold: true
                color: Constants.fontColor
            }

            MouseArea {
                width: licensedLinkCheatsheet.implicitWidth
                height: licensedLinkQt.implicitHeight
                cursorShape: Qt.PointingHandCursor

                Text {
                    id: licensedLinkQt
                    width: licensedLinkCheatsheet.width
                    text: qsTrId("https://www.qt.io/")
                    font.pixelSize: 14
                    font.underline: true
                    color: Constants.fontColor
                }

                onClicked: {
                    Qt.openUrlExternally("https://www.qt.io/")
                }
            }

            MouseArea {
                width: licensedLicenseQt.implicitWidth
                height: licensedLicenseQt.implicitHeight
                cursorShape: Qt.PointingHandCursor

                Text {
                    id: licensedLicenseQt
                    text: qsTrId("GNU LGPL v3")
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignRight
                    font.underline: true
                    color: Constants.fontColor
                }

                onClicked: {
                    Qt.openUrlExternally("https://doc.qt.io/qt-6/lgpl.html")
                }
            }
        }

        Row {
            id: licensedRowRangeV3
            height: 17
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            spacing: 10

            Text {
                id: licensedNameRangeV3
                width: licensedNameCheatsheet.width
                text: qsTrId("range-v3")
                font.pixelSize: 14
                font.bold: true
                color: Constants.fontColor
            }

            MouseArea {
                width: licensedLinkCheatsheet.implicitWidth
                height: licensedLinkRangeV3.implicitHeight
                cursorShape: Qt.PointingHandCursor

                Text {
                    id: licensedLinkRangeV3
                    text: qsTrId("@ericniebler/range-v3")
                    font.pixelSize: 14
                    font.underline: true
                    color: Constants.fontColor
                }

                onClicked: {
                    Qt.openUrlExternally(
                                "https://github.com/ericniebler/range-v3/")
                }
            }

            MouseArea {
                width: licensedLicenseRangeV3.implicitWidth
                height: licensedLicenseRangeV3.implicitHeight
                cursorShape: Qt.PointingHandCursor

                Text {
                    id: licensedLicenseRangeV3
                    text: qsTrId("Boost Software License")
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignRight
                    font.underline: true
                    color: Constants.fontColor
                }

                onClicked: {
                    Qt.openUrlExternally(
                                "https://github.com/ericniebler/range-v3/blob/master/LICENSE.txt")
                }
            }
        }

        Row {
            id: licensedRowBoxIcons
            height: 17
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: 0
            spacing: 10
            anchors.leftMargin: 0

            Text {
                id: licensedNameBoxIcons
                width: licensedNameCheatsheet.width
                text: qsTrId("BoxIcons")
                font.pixelSize: 14
                font.bold: true
                color: Constants.fontColor
            }

            MouseArea {
                id: mouseArea
                width: licensedLinkCheatsheet.width
                height: licensedLinkBoxIcons.implicitHeight
                cursorShape: Qt.PointingHandCursor

                Text {
                    id: licensedLinkBoxIcons
                    text: qsTrId("https://boxicons.com/")
                    font.pixelSize: 14
                    font.underline: true
                    color: Constants.fontColor
                }

                onClicked: {
                    Qt.openUrlExternally("https://boxicons.com/")
                }
            }

            MouseArea {
                width: licensedLicenseBoxIcons.implicitWidth
                height: licensedLicenseBoxIcons.implicitHeight
                cursorShape: Qt.PointingHandCursor

                Text {
                    id: licensedLicenseBoxIcons
                    text: qsTrId("The MIT License")
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignRight
                    font.underline: true
                    color: Constants.fontColor
                }

                onClicked: {
                    Qt.openUrlExternally("https://boxicons.com/usage#license")
                }
            }
        }

        Row {
            id: licensedRowCheatsheet
            height: 17
            anchors.left: parent.left
            anchors.right: parent.right

            Text {
                id: licensedNameCheatsheet
                text: qsTrId("MD Cheatsheet")
                font.pixelSize: 14
                font.bold: true
                color: Constants.fontColor
            }

            MouseArea {
                width: licensedLinkCheatsheet.implicitWidth
                height: licensedLinkCheatsheet.implicitHeight
                cursorShape: Qt.PointingHandCursor

                Text {
                    id: licensedLinkCheatsheet
                    text: qsTrId("@adam-p/markdown-here")
                    font.pixelSize: 14
                    font.underline: true
                    color: Constants.fontColor
                }

                onClicked: {
                    Qt.openUrlExternally(
                                "https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet")
                }
            }

            MouseArea {
                width: licensedLicenseCheatsheet.implicitWidth
                height: licensedLicenseCheatsheet.implicitHeight
                cursorShape: Qt.PointingHandCursor

                Text {
                    id: licensedLicenseCheatsheet
                    text: qsTrId("CC-BY 3.0")
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignRight
                    font.underline: true
                    color: Constants.fontColor
                }

                onClicked: {
                    Qt.openUrlExternally(
                                "https://creativecommons.org/licenses/by/3.0/")
                }
            }
            anchors.rightMargin: 0
            spacing: 10
            anchors.leftMargin: 0
        }
    }

    footer: Item {}
}
