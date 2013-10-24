QT += core
QT -= gui
TEMPLATE = app

CONFIG   += console
CONFIG   -= app_bundle

include ( ToolHometrainer.pri )

SOURCES += \
    main.cpp \

OTHER_FILES += \
    ToolHometrainer.pri

