#CONFIG(release, debug|release) {
#    macx: LIBS += -lc++ -L$$PWD/lib/ -lmarkdownparser
#    macx: PRE_TARGETDEPS += $$PWD/lib/libmarkdownparser.a
#} else {
#    macx: LIBS += -lc++ -L$$PWD/lib/ -lmarkdownparserd
#    macx: PRE_TARGETDEPS += $$PWD/lib/libmarkdownparserd.a
#}

MD_LIB_SRC = lib/src/markdown-parser/markdown-document/markdown-elements/plaintextelement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/linkableelement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/linkelement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/imageelement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/nestedelement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/strikethroughelement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/strongemphasiselement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/emphasiselement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/inlinecodeelement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/textlineelement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/multilinetextelement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/listelement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/unorderedlistelement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/orderedlistelement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/headerelement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/codeblockelement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/blockquoteelement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/horizontalruleelement.cpp \
             lib/src/markdown-parser/markdown-document/markdown-elements/paragraphelement.cpp \
             lib/src/markdown-parser/markdown-document/markdowndocument.cpp \
             lib/src/markdown-parser/markdown-tokens/plaintexttoken.cpp \
             lib/src/markdown-parser/markdown-tokens/headertoken.cpp \
             lib/src/markdown-parser/markdown-tokens/headerunderlinetoken.cpp \
             lib/src/markdown-parser/markdown-tokens/codetoken.cpp \
             lib/src/markdown-parser/markdowntokenizer.cpp \
             lib/src/markdown-parser/helpers/trim.cpp \
             lib/src/markdown-parser/markdown-tokens/blockquotetoken.cpp \
             lib/src/markdown-parser/markdown-tokens/emptytoken.cpp \
             lib/src/markdown-parser/markdown-tokens/horizontalruletoken.cpp \
             lib/src/markdown-parser/markdown-tokens/orderedlisttoken.cpp \
             lib/src/markdown-parser/markdown-tokens/unorderedlisttoken.cpp \
             lib/src/markdown-parser/markdownparser.cpp \
             lib/src/markdown-parser/markdown-tokens/rawtexthandler.cpp \
             lib/src/markdown-parser/markdowninlineelementsparser.cpp

MD_LIB_HDR = lib/src/markdown-parser/markdown-document/markdown-elements/plaintextelement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/linkableelement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/linkelement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/imageelement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/nestedelement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/strikethroughelement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/strongemphasiselement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/emphasiselement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/inlinecodeelement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/vinlinemarkdownelement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/textlineelement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/multilinetextelement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/listelement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/unorderedlistelement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/orderedlistelement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/headerelement.h \
             lib/src/markdown-parser/markdownheaderlevel.enum.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/codeblockelement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/blockquoteelement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/horizontalruleelement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/paragraphelement.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/vtoplevelmarkdownelement.h \
             lib/src/markdown-parser/markdown-document/markdowndocument.h \
             lib/src/markdown-parser/markdown-tokens/plaintexttoken.h \
             lib/src/markdown-parser/markdown-tokens/headertoken.h \
             lib/src/markdown-parser/markdown-tokens/headerunderlinetoken.h \
             lib/src/markdown-parser/markdown-tokens/codetoken.h \
             lib/src/markdown-parser/markdowntokenizer.h \
             lib/src/markdown-parser/markdown-tokens/blockquotetoken.h \
             lib/src/markdown-parser/markdown-tokens/emptytoken.h \
             lib/src/markdown-parser/markdown-tokens/horizontalruletoken.h \
             lib/src/markdown-parser/markdown-tokens/orderedlisttoken.h \
             lib/src/markdown-parser/markdown-tokens/unorderedlisttoken.h \
             lib/src/markdown-parser/helpers/trim.h \
             lib/src/markdown-parser/regex.defs.h \
             lib/src/markdown-parser/markdownparser.h \
             lib/src/markdown-parser/markdown-tokens/rawtexthandler.h \
             lib/src/markdown-parser/markdown-document/markdown-elements/recursivevarianttype.h \
             lib/src/markdown-parser/markdowninlineelementsparser.h

QT += \
    quick \
    svg \
    xml \
    widgets \
    quickcontrols2

CONFIG += \
    c++latest
    qmltypes

SOURCES += \
        src/configfilemanager.cpp \
        src/configmanager.cpp \
        src/converters/iconverter.cpp \
        src/converters/htmlconverter.cpp \
        src/filemanager.cpp \
        main.cpp \
        src/backendconnection.cpp \
        src/markdownfilemanager.cpp \
        src/tab.cpp \
        src/tabmanager.cpp \
        $$MD_LIB_SRC

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

QMAKE_MACOSX_DEPLOYMENT_TARGET = 12.2

HEADERS += \
    src/configfilemanager.h \
    src/configmanager.h \
    src/converters/iconverter.h \
    src/converters/htmlconverter.h \
    src/filemanager.h \
    src/backendconnection.h \
    src/markdownfilemanager.h \
    src/tab.h \
    src/tabmanager.h \
    $$MD_LIB_HDR

INCLUDEPATH += $$PWD/lib/include $$PWD/lib/src/markdown-parser/lib
DEPENDPATH += $$PWD/lib/include $$PWD/lib/src/markdown-parser/lib
