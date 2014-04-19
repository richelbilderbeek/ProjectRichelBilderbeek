exists(../../ConsoleApplication.pri)
{
  include(../../ConsoleApplication.pri)
}

!exists(../../ConsoleApplication.pri)
{
  QT       += core
  QT       -= gui
  CONFIG   += console
  CONFIG   -= app_bundle
  TEMPLATE = app
}

SOURCES += main.cpp
