#-------------------------------------------------
#
# Project created by QtCreator 2014-09-06T12:40:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameOfLife
TEMPLATE = app


SOURCES += \
    ../../src/Sources/Board.cpp \
    ../../src/Sources/Definitions.cpp \
    ../../src/Sources/gameoflife.cpp \
    ../../src/Sources/main.cpp

HEADERS  += \
    ../../src/Headers/Board.h \
    ../../src/Headers/Cell.h \
    ../../src/Headers/CellGuard.h \
    ../../src/Headers/Characteristic.h \
    ../../src/Headers/Creature.h \
    ../../src/Headers/CreatureGuard.h \
    ../../src/Headers/Definitions.h \
    ../../src/Headers/gameoflife.h \
    ../../src/Headers/LifePolicy.h \
    ../../src/Headers/Position.h \
    ../../src/Headers/Predator.h \
    ../../src/Headers/Prey.h \
    ../../src/Headers/RenderBoard.h

FORMS += \
    ../../src/Forms/HelpWindow.ui \
    ../../src/Forms/RunTimeInformation.ui
