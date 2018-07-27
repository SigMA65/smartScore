TEMPLATE = app
include(src/smartScoreWindow/smartScoreWindow.pri)
include(src/orgStruct/orgStruct.pri)
include(src/scoreCard/scoreCard.pri)
include(src/common/common.pri)
include(src/test/test.pri)

QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG -= debug_and_release debug_and_release_target

#CONFIG+=qtestlib

DEBUG_TARGET = smartScored
RELEASE_TARGET = smartScore
TARGET = SmartScore

CONFIG(debug, debug|release){
    TARGET = $$DEBUG_TARGET
}

CONFIG(release, debug|release){
    TARGET = $$RELEASE_TARGET
}

#INCLUDEPATH += $(INCLUDE_C++)

DESTDIR = bin
OBJECTS_DIR = obj
MOC_DIR = moc

SOURCES += \
    src/main.cpp


HEADERS  +=

RESOURCES += \
    src/images.qrc
