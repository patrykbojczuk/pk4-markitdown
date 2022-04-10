import QtQuick
import "qrc:/"

Item {
    id: comparisonItem
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.rightMargin: 0
    anchors.leftMargin: 0

    Text {
        id: header
        color: Constants.fontColor
        text: headerText
        font.pixelSize: 18
        font.bold: true
    }

    Rectangle {
        color: Constants.lighterBackgroundColor
        radius: Constants.windowRadius / 2
        anchors.fill: textSource
        anchors.margins: -5
    }

    Text {
        id: textSource
        color: Constants.fontColor
        text: comparisonText
        font.pixelSize: 14
        wrapMode: Text.WordWrap
        textFormat: Text.PlainText
        anchors.leftMargin: 5
    }

    Text {
        id: textDisplay
        color: Constants.fontColor
        text: comparisonText
        font.pixelSize: 14
        wrapMode: Text.WordWrap
        textFormat: Text.MarkdownText
        anchors.rightMargin: 5
    }

    states: [
        State {
            name: 'horizontal'
            when: horizontalFlow

            AnchorChanges {
                target: textSource
                anchors.left: parent.left
                anchors.right: parent.horizontalCenter
                anchors.top: header.bottom
            }
            AnchorChanges {
                target: textDisplay
                anchors.left: parent.horizontalCenter
                anchors.right: parent.right
                anchors.top: textSource.top
            }

            PropertyChanges {
                target: textSource
                anchors.topMargin: 10
                anchors.rightMargin: 10
            }
            PropertyChanges {
                target: textDisplay
                anchors.topMargin: 0
                anchors.leftMargin: 10
            }

            PropertyChanges {
                target: comparisonItem
                height: header.implicitHeight + textSource.anchors.topMargin + (textSource.height > textDisplay.height ? textSource.height : textDisplay.height)
            }
        },
        State {
            name: 'vertical'
            when: !horizontalFlow

            AnchorChanges {
                target: textSource
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: header.bottom
            }
            AnchorChanges {
                target: textDisplay
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: textSource.bottom
            }

            PropertyChanges {
                target: textSource
                anchors.topMargin: 10
                anchors.rightMargin: 5
            }
            PropertyChanges {
                target: textDisplay
                anchors.topMargin: 10
                anchors.leftMargin: 5
            }

            PropertyChanges {
                target: comparisonItem
                height: header.implicitHeight + textSource.anchors.topMargin + textSource.height + textDisplay.anchors.topMargin + textDisplay.height
            }
        }
    ]

    property bool horizontalFlow: false
    property string headerText
    property string comparisonText
}

/*##^##
Designer {
    D{i:0;height:800;width:500}
}
##^##*/
