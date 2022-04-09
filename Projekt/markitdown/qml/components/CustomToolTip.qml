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

    property int enterTransition: CustomToolTip.EnterDirection.Center

    id: toolTip
    delay: 250
    horizontalPadding: tooltipTextEl.font.pointSize * 1.2
    background: Rectangle {
        color: Constants.lighterBackgroundColor
        border.width: 0
        radius: Constants.windowRadius / 2
    }
    contentItem: Text {
        id: tooltipTextEl
        color: Constants.fontColor
        text: toolTip.text
    }

    enter: Transition {
        ParallelAnimation {
            NumberAnimation {
                target: toolTip
                property: "opacity"
                from: 0
                to: 1
                duration: enterTransition === CustomToolTip.EnterDirection.Center ? 250 : 200
                easing.type: Easing.OutQuad
            }
            NumberAnimation {
                target: toolTip
                property: (enterTransition === CustomToolTip.EnterDirection.Center ||
                           enterTransition === CustomToolTip.EnterDirection.FromLeft ||
                           enterTransition === CustomToolTip.EnterDirection.FromRight)
                           ? "x"
                           : "y"
                from: {
                    switch (enterTransition) {
                        case CustomToolTip.EnterDirection.Center: {
                            return toolTip.x
                        }
                        case CustomToolTip.EnterDirection.FromTop: {
                            return toolTip.y - 25
                        }
                        case CustomToolTip.EnterDirection.FromRight: {
                            return toolTip.x + 25
                        }
                        case CustomToolTip.EnterDirection.FromBottom: {
                            return toolTip.y + 25
                        }
                        case CustomToolTip.EnterDirection.FromLeft: {
                            return toolTip.x - 25
                        }
                    }
                }
                to: {
                    switch (enterTransition) {
                        case CustomToolTip.EnterDirection.Center:
                        case CustomToolTip.EnterDirection.FromRight:
                        case CustomToolTip.EnterDirection.FromLeft: {
                            return toolTip.x
                        }
                        case CustomToolTip.EnterDirection.FromTop:
                        case CustomToolTip.EnterDirection.FromBottom: {
                            return toolTip.y
                        }
                    }
                }
                duration: enterTransition === CustomToolTip.EnterDirection.Center ? 250 : 200
                easing.type: Easing.OutQuad
            }
        }
    }
    exit: Transition {
        ParallelAnimation {
            NumberAnimation {
                target: toolTip
                property: "opacity"
                from: 1
                to: 0
                duration: enterTransition === CustomToolTip.EnterDirection.Center ? 250 : 200
                easing.type: Easing.OutQuad
            }
            SequentialAnimation {
                NumberAnimation {
                    target: toolTip
                    property: (enterTransition === CustomToolTip.EnterDirection.Center ||
                               enterTransition === CustomToolTip.EnterDirection.FromLeft ||
                               enterTransition === CustomToolTip.EnterDirection.FromRight)
                               ? "x"
                               : "y"
                    from: {
                        switch (enterTransition) {
                            case CustomToolTip.EnterDirection.Center:
                            case CustomToolTip.EnterDirection.FromRight:
                            case CustomToolTip.EnterDirection.FromLeft: {
                                return toolTip.x
                            }
                            case CustomToolTip.EnterDirection.FromTop:
                            case CustomToolTip.EnterDirection.FromBottom: {
                                return toolTip.y
                            }
                        }
                    }
                    to: {
                        switch (enterTransition) {
                            case CustomToolTip.EnterDirection.Center: {
                                return toolTip.x
                            }
                            case CustomToolTip.EnterDirection.FromTop: {
                                return toolTip.y - 25
                            }
                            case CustomToolTip.EnterDirection.FromRight: {
                                return toolTip.x + 25
                            }
                            case CustomToolTip.EnterDirection.FromBottom: {
                                return toolTip.y + 25
                            }
                            case CustomToolTip.EnterDirection.FromLeft: {
                                return toolTip.x - 25
                            }
                        }
                    }
                    duration: enterTransition === CustomToolTip.EnterDirection.Center ? 250 : 200
                    easing.type: Easing.OutQuad
                }
                NumberAnimation {
                    target: toolTip
                    property: (enterTransition === CustomToolTip.EnterDirection.Center ||
                               enterTransition === CustomToolTip.EnterDirection.FromLeft ||
                               enterTransition === CustomToolTip.EnterDirection.FromRight)
                               ? "x"
                               : "y"
                    from: {
                        switch (enterTransition) {
                            case CustomToolTip.EnterDirection.Center:
                            case CustomToolTip.EnterDirection.FromRight:
                            case CustomToolTip.EnterDirection.FromLeft: {
                                return toolTip.x
                            }
                            case CustomToolTip.EnterDirection.FromTop:
                            case CustomToolTip.EnterDirection.FromBottom: {
                                return toolTip.y
                            }
                        }
                    }
                    to: {
                        switch (enterTransition) {
                            case CustomToolTip.EnterDirection.Center:
                            case CustomToolTip.EnterDirection.FromRight:
                            case CustomToolTip.EnterDirection.FromLeft: {
                                return toolTip.x
                            }
                            case CustomToolTip.EnterDirection.FromTop:
                            case CustomToolTip.EnterDirection.FromBottom: {
                                return toolTip.y
                            }
                        }
                    }
                    duration: 1
                }

            }
        }
    }
}
