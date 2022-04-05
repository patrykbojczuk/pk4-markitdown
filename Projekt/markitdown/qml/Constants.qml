pragma Singleton

import QtQuick

QtObject {
    // Background
    readonly property color backgroundColor: "#121212"
    readonly property color lighterBackgroundColor: "#3A3A3A"

    // Font
    readonly property color fontColor: "#ffffff"
    readonly property color fontColor50: "#80ffffff"
    readonly property color fontColor25: "#40ffffff"
    readonly property color fontColor10: "#0affffff"

    // Close Button
    readonly property color closeButtonColor: "#FF453A"
    readonly property color closeButtonBorderColor: "#9F312B"
    readonly property url closeIcon: "qrc:/assets/window/buttons/close.svg"

    // Minimize Button
    readonly property color minimizeButtonColor: "#FFCC00"
    readonly property color minimizeButtonBorderColor: "#A48713"
    readonly property url minimizeIcon: "qrc:/assets/window/buttons/minimize.svg"

    // Resize Button
    readonly property color resizeButtonColor: "#32D74B"
    readonly property color resizeButtonBorderColor: "#20842F"
    readonly property url maximizeIcon: "qrc:/assets/window/buttons/maximize.svg"
    readonly property url demaximizeIcon: "qrc:/assets/window/buttons/demaximize.svg"
}
