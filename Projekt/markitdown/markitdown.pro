QT += \
    quick \
    svg \
    xml \
    quickcontrols2

CONFIG += \
    c++latest
    qmltypes

SOURCES += \
        main.cpp \
        src/backendconnection.cpp

RESOURCES += qml.qrc

QML_IMPORT_NAME = pb.pk.markitdown
QML_IMPORT_MAJOR_VERSION = 1

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15

HEADERS += \
    src/backendconnection.h

INCLUDEPATH += $$PWD/lib/include
DEPENDPATH += $$PWD/lib/include

CONFIG(release, debug|release) {
    macx: LIBS += -L$$PWD/lib/ -lmarkdownparser
    macx: PRE_TARGETDEPS += $$PWD/lib/libmarkdownparser.a
} else {
    macx: LIBS += -L$$PWD/lib/ -lmarkdownparserd
    macx: PRE_TARGETDEPS += $$PWD/lib/libmarkdownparserd.a
}
