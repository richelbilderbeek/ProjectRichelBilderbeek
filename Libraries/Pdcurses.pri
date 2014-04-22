win32 {
  INCLUDEPATH += \
      ../../Libraries/pdc25_vc_w32

  HEADERS += \
      ../../Libraries/pdc25_vc_w32/panel.h \
      ../../Libraries/pdc25_vc_w32/curses.h

  LIBS += -L../../Libraries/pdc25_vc_w32 -lpdcurses
}
