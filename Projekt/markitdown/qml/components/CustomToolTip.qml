import QtQuick
import QtQuick.Controls
import "qrc:/"

ToolTip {
    enum EnterDirection {
        Center,
        FromTop,
        FromRight,
        FromBottom,
        FromLeft
    }

    property int transitionDuration: 150
    property int transitionDirection: CustomToolTip.EnterDirection.Center

    id: toolTip
    delay: 250
    horizontalPadding: tooltipTextEl.font.pointSize * 1.2
    background: Rectangle {
        id: tooltipBackgroundEl
        color: Constants.lighterBackgroundColor
        border.width: 0
        radius: Constants.windowRadius / 2

        transform: Translate {
            id: tooltipBackgroundElTranslate
            x: 0
            y: 0
        }
    }
    contentItem: Text {
        id: tooltipTextEl
        color: Constants.fontColor
        text: toolTip.text
        elide: Text.ElideRight

        transform: Translate {
            id: tooltipTextElTranslate
            x: 0
            y: 0
        }
    }


    enter: Transition {
        id: enterTransition

        ParallelAnimation {
            id: enterTransitionMainAnimation
            NumberAnimation {
                target: toolTip
                property: "opacity"
                from: 0
                to: 1
                duration: transitionDuration
                easing.type: Easing.OutQuad
            }
            PropertyAnimation {
                targets:[tooltipBackgroundElTranslate, tooltipTextElTranslate]
                property: {
                    switch (transitionDirection) {
                        case CustomToolTip.EnterDirection.Center:
                        case CustomToolTip.EnterDirection.FromLeft:
                        case CustomToolTip.EnterDirection.FromRight: {
                            return 'x'
                        }
                        case CustomToolTip.EnterDirection.FromTop:
                        case CustomToolTip.EnterDirection.FromBottom: {
                            return 'y'
                        }
                    }
                }
                from: {
                    switch (transitionDirection) {
                        case CustomToolTip.EnterDirection.FromLeft: {
                            return -25
                        }
                        case CustomToolTip.EnterDirection.FromRight: {
                            return 25
                        }
                        case CustomToolTip.EnterDirection.FromTop: {
                            return -25
                        }
                        case CustomToolTip.EnterDirection.FromBottom: {
                            return 25
                        }
                        case CustomToolTip.EnterDirection.Center: {
                            return 0
                        }
                    }
                }
                to: 0
                duration: transitionDuration
            }
        }
    }
    exit: Transition {
        id: exitTransition

        ParallelAnimation {
            id: exitTransitionMainAnimation
            NumberAnimation {
                target: toolTip
                property: "opacity"
                from: 1
                to: 0
                duration: transitionDuration
                easing.type: Easing.OutQuad
            }

            PropertyAnimation {
                targets: [tooltipBackgroundElTranslate, tooltipTextElTranslate]
                property: {
                    switch (transitionDirection) {
                        case CustomToolTip.EnterDirection.Center:
                        case CustomToolTip.EnterDirection.FromLeft:
                        case CustomToolTip.EnterDirection.FromRight: {
                            return 'x'
                        }
                        case CustomToolTip.EnterDirection.FromTop:
                        case CustomToolTip.EnterDirection.FromBottom: {
                            return 'y'
                        }
                    }
                }
                to: {
                    switch (transitionDirection) {
                        case CustomToolTip.EnterDirection.FromLeft: {
                            return -25
                        }
                        case CustomToolTip.EnterDirection.FromRight: {
                            return 25
                        }
                        case CustomToolTip.EnterDirection.FromTop: {
                            return -25
                        }
                        case CustomToolTip.EnterDirection.FromBottom: {
                            return 25
                        }
                        case CustomToolTip.EnterDirection.Center: {
                            return 0
                        }
                    }

                }
                from: 0
                duration: transitionDuration
            }
        }
    }
}
