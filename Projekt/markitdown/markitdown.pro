QT += \
    quick \
    svg \
    xml

CONFIG += \
    c++2b
    qmltypes

SOURCES += \
        main.cpp

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
