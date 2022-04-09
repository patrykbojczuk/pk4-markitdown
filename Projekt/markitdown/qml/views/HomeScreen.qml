import QtQuick
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
            color: "#ffffff"
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
            color: "#ffffff"
            text: "markdown editor"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: appNameHeader.bottom
            anchors.topMargin: -6
            font.pixelSize: 36
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.Thin
        }

        Text {
            id: startSectionHeader
            color: "#ffffff"
            text: "Start"
            anchors.left: parent.left
            anchors.top: appNameSubheader.bottom
            font.pixelSize: 24
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: 0
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
            color: "#ffffff"
            text: "Recent files"
            anchors.left: parent.left
            anchors.top: startSectionLinks.bottom
            font.pixelSize: 24
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
            name: 'oneColumn'
            when: homeScreen.width < 1400
//            PropertyChanges {
//                target: object
//            }
        },
        State {
            name: 'twoColumns'
            when: homeScreen.width >= 1400
//            PropertyChanges {
//                target: object
//            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/
