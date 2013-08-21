QT       += core gui
TEMPLATE = app
LIBS += -L/usr/local/lib -lSDL \
  -L/usr/local/lib -lSDL_ttf \
  -L/usr/local/lib -lSDL_image \
  -L/usr/local/lib -lpng
SOURCES += \
    ucorridor.cpp
