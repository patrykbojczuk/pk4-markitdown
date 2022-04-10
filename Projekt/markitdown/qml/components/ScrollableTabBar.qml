import QtQuick
import QtQuick.Controls
import "qrc:/"
import "qrc:/components"


TabBar {
    id: tabBar

    contentItem: ListView {
        model: tabBar.contentModel
        currentIndex: tabBar.currentIndex

        spacing: tabBar.spacing
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds
        flickableDirection: Flickable.AutoFlickIfNeeded
        snapMode: ListView.SnapToItem

        ScrollBar.horizontal: CustomScrollBar {}

        highlightMoveDuration: 0
        highlightRangeMode: ListView.ApplyRange
        preferredHighlightBegin: 40
        preferredHighlightEnd: tabBar.height - 40
    }
}
