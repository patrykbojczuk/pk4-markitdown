import QtQuick

Rectangle {
    color: "transparent"
    border.color: "transparent"
    border.width: 0

    property int previousX
    property int previousY

    signal changeGeometry(int x, int y, int w, int h)

    // Edge Resize
    MouseArea {
        // Resize right
        width: 5
        drag.axis: Drag.XAxis
        cursorShape: Qt.SizeHorCursor
        anchors {
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }

        onPressed: function (mouse) {
            previousX = mouse.x
            previousY = mouse.y
        }
        onMouseXChanged: function (mouse) {
            changeGeometry(window.x, window.y, window.width + Math.floor(mouse.x - previousX), window.height)
        }
    }

    MouseArea {
        // Resize left
        width: 5
        drag.axis: Drag.XAxis
        cursorShape: Qt.SizeHorCursor
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }

        onPressed: function (mouse) {
            previousX = mouse.x
            previousY = mouse.y
        }
        onMouseXChanged: function (mouse) {
            const dX = Math.floor(mouse.x - previousX)
            changeGeometry(window.x + dX, window.y, window.width - dX, window.height)
        }
    }

    MouseArea {
        // Resize bottom
        height: 5
        drag.axis: Drag.YAxis
        cursorShape: Qt.SizeVerCursor
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        onPressed: function (mouse) {
            previousX = mouse.x
            previousY = mouse.y
        }
        onMouseYChanged: function (mouse) {
            changeGeometry(window.x, window.y, window.width, window.height + Math.floor(mouse.y - previousY))
        }
    }

    MouseArea {
        // Resize top
        height: 5
        drag.smoothed: false
        smooth: false
        drag.axis: Drag.YAxis
        cursorShape: Qt.SizeVerCursor
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        onPressed: function (mouse) {
            previousX = mouse.x
            previousY = mouse.y
        }
        onMouseYChanged: function (mouse) {
            const dY = Math.floor(mouse.y - previousY)
            changeGeometry(window.x, window.y + dY, window.width, window.height - dY)
        }
    }

    // Corner Resize
    MouseArea {
        // Resize top right
        height: 8
        width: 8
        cursorShape: Qt.SizeBDiagCursor
        anchors {
            top: parent.top
            right: parent.right
        }

        function posChanged (mouse) {
            const dY = Math.floor(mouse.y - previousY)
            changeGeometry(window.x, window.y + dY, window.width + Math.floor(mouse.x - previousX), window.height - dY)
        }

        onPressed: function (mouse) {
            previousY = mouse.y
            previousX = mouse.x
        }
        onMouseYChanged: (mouse) => posChanged(mouse)
        onMouseXChanged: (mouse) => posChanged(mouse)
    }

    MouseArea {
        // Resize bottom right
        height: 8
        width: 8
        cursorShape: Qt.SizeFDiagCursor
        anchors {
            right: parent.right
            bottom: parent.bottom
        }

        function posChanged (mouse){
            changeGeometry(window.x, window.y, window.width + Math.floor(mouse.x - previousX), window.height + Math.floor(mouse.y - previousY))
        }

        onPressed: function (mouse) {
            previousY = mouse.y
            previousX = mouse.x
        }
        onMouseYChanged: (mouse) => posChanged(mouse)
        onMouseXChanged: (mouse) => posChanged(mouse)
    }

    MouseArea {
        // Resize bottom left
        height: 8
        width: 8
        cursorShape: Qt.SizeBDiagCursor
        anchors {
            left: parent.left
            bottom: parent.bottom
        }

        function posChanged (mouse) {
            const dX = Math.floor(mouse.x - previousX)
            changeGeometry(window.x + dX, window.y, window.width - dX, window.height + Math.floor(mouse.y - previousY))
        }

        onPressed: function (mouse) {
            previousY = mouse.y
            previousX = mouse.x
        }
        onMouseYChanged: (mouse) => posChanged(mouse)
        onMouseXChanged: (mouse) => posChanged(mouse)
    }

    MouseArea {
        // Resize top left
        height: 8
        width: 8
        cursorShape: Qt.SizeFDiagCursor
        anchors {
            top: parent.top
            left: parent.left
        }

        function posChanged (mouse) {
            const dY = Math.floor(mouse.y - previousY)
            const dX = Math.floor(mouse.x - previousX)
            changeGeometry(window.x + dX, window.y + dY, window.width - dX, window.height - dY)
        }

        onPressed: function (mouse) {
            previousY = mouse.y
            previousX = mouse.x
        }
        onMouseYChanged: (mouse) => posChanged(mouse)
        onMouseXChanged: (mouse) => posChanged(mouse)
    }
}
