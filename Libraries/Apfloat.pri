win32 {
  # Windows only
  message("Apfloat 2.4.1, built for Windows")

  INCLUDEPATH += \
      ../../Libraries/apf241

  HEADERS += \
      ../../Libraries/apf241/ap.h \
      ../../Libraries/apf241/apcplx.h \
      ../../Libraries/apf241/apfloat.h \
      ../../Libraries/apf241/apint.h \
      ../../Libraries/apf241/aprat.h \
      ../../Libraries/apf241/baseint.h \
      ../../Libraries/apf241/bigint.h \
      ../../Libraries/apf241/modint.h \
      ../../Libraries/apf241/raw.h \
      ../../Libraries/apf241/tapfloat.h

  SOURCES += \
      ../../Libraries/apf241/apcfunc.cpp \
      ../../Libraries/apf241/apcplx.cpp \
      ../../Libraries/apf241/apfloat.cpp \
      ../../Libraries/apf241/apfunc.cpp \
      ../../Libraries/apf241/apifunc.cpp \
      ../../Libraries/apf241/apint.cpp \
      ../../Libraries/apf241/aprat.cpp \
      ../../Libraries/apf241/aprfunc.cpp \
      ../../Libraries/apf241/apstruct.cpp \
      ../../Libraries/apf241/baseint.cpp \
      ../../Libraries/apf241/bigint.cpp \
      ../../Libraries/apf241/carrycrt.cpp \
      ../../Libraries/apf241/convolut.cpp \
      ../../Libraries/apf241/crt.cpp \
      ../../Libraries/apf241/datastru.cpp \
      ../../Libraries/apf241/file.cpp \
      ../../Libraries/apf241/fnt.cpp \
      ../../Libraries/apf241/fourstep.cpp \
      ../../Libraries/apf241/global.cpp \
      ../../Libraries/apf241/init.cpp \
      ../../Libraries/apf241/modfunc.cpp \
      ../../Libraries/apf241/move.cpp \
      ../../Libraries/apf241/scramble.cpp \
      ../../Libraries/apf241/sixstep.cpp \
      ../../Libraries/apf241/tablefnt.cpp \
      ../../Libraries/apf241/tablefou.cpp \
      ../../Libraries/apf241/tablesit.cpp \
      ../../Libraries/apf241/tablesix.cpp \
      ../../Libraries/apf241/tabletwo.cpp \
      ../../Libraries/apf241/tabletwt.cpp \
      ../../Libraries/apf241/tapfloat.cpp \
      ../../Libraries/apf241/tapfunc.cpp \
      ../../Libraries/apf241/tapstruc.cpp \
      ../../Libraries/apf241/transpos.cpp \
      ../../Libraries/apf241/wfta_asm.cpp

}

macx {
  # Mac only
  message("Apfloat 2.4.1, built for Mac")
  error("?Apfloat 2.4.1 does not work under Mac")
}

unix:!macx {
  # Linux only
  message("Apfloat 2.4.1, built for Linux")

  INCLUDEPATH += \
      ../../Libraries/apf241

  HEADERS += \
      ../../Libraries/apf241/ap.h \
      ../../Libraries/apf241/apcplx.h \
      ../../Libraries/apf241/apfloat.h \
      ../../Libraries/apf241/apint.h \
      ../../Libraries/apf241/aprat.h \
      ../../Libraries/apf241/baseint.h \
      ../../Libraries/apf241/bigint.h \
      ../../Libraries/apf241/modint.h \
      ../../Libraries/apf241/raw.h \
      ../../Libraries/apf241/tapfloat.h

  SOURCES += \
      ../../Libraries/apf241/apcfunc.cpp \
      ../../Libraries/apf241/apcplx.cpp \
      ../../Libraries/apf241/apfloat.cpp \
      ../../Libraries/apf241/apfunc.cpp \
      ../../Libraries/apf241/apifunc.cpp \
      ../../Libraries/apf241/apint.cpp \
      ../../Libraries/apf241/aprat.cpp \
      ../../Libraries/apf241/aprfunc.cpp \
      ../../Libraries/apf241/apstruct.cpp \
      ../../Libraries/apf241/baseint.cpp \
      ../../Libraries/apf241/bigint.cpp \
      ../../Libraries/apf241/carrycrt.cpp \
      ../../Libraries/apf241/convolut.cpp \
      ../../Libraries/apf241/crt.cpp \
      ../../Libraries/apf241/datastru.cpp \
      ../../Libraries/apf241/file.cpp \
      ../../Libraries/apf241/fnt.cpp \
      ../../Libraries/apf241/fourstep.cpp \
      ../../Libraries/apf241/global.cpp \
      ../../Libraries/apf241/init.cpp \
      ../../Libraries/apf241/modfunc.cpp \
      ../../Libraries/apf241/move.cpp \
      ../../Libraries/apf241/scramble.cpp \
      ../../Libraries/apf241/sixstep.cpp \
      ../../Libraries/apf241/tablefnt.cpp \
      ../../Libraries/apf241/tablefou.cpp \
      ../../Libraries/apf241/tablesit.cpp \
      ../../Libraries/apf241/tablesix.cpp \
      ../../Libraries/apf241/tabletwo.cpp \
      ../../Libraries/apf241/tabletwt.cpp \
      ../../Libraries/apf241/tapfloat.cpp \
      ../../Libraries/apf241/tapfunc.cpp \
      ../../Libraries/apf241/tapstruc.cpp \
      ../../Libraries/apf241/transpos.cpp \
      ../../Libraries/apf241/wfta_asm.cpp
}

# It appears that the crosscompiler already uses the win32 flag
# Adding these directives will only result in duplicate linkages

#cross_compile!win32 {
#  message("Apfloat 2.4.1, built for cross-compiling from Linux to Windows")

#  INCLUDEPATH += \
#      ../../Libraries/apf241

#  HEADERS += \
#      ../../Libraries/apf241/ap.h \
#      ../../Libraries/apf241/apcplx.h \
#      ../../Libraries/apf241/apfloat.h \
#      ../../Libraries/apf241/apint.h \
#      ../../Libraries/apf241/aprat.h \
#      ../../Libraries/apf241/baseint.h \
#      ../../Libraries/apf241/bigint.h \
#      ../../Libraries/apf241/modint.h \
#      ../../Libraries/apf241/raw.h \
#      ../../Libraries/apf241/tapfloat.h

#  SOURCES += \
#      ../../Libraries/apf241/apcfunc.cpp \
#      ../../Libraries/apf241/apcplx.cpp \
#      ../../Libraries/apf241/apfloat.cpp \
#      ../../Libraries/apf241/apfunc.cpp \
#      ../../Libraries/apf241/apifunc.cpp \
#      ../../Libraries/apf241/apint.cpp \
#      ../../Libraries/apf241/aprat.cpp \
#      ../../Libraries/apf241/aprfunc.cpp \
#      ../../Libraries/apf241/apstruct.cpp \
#      ../../Libraries/apf241/baseint.cpp \
#      ../../Libraries/apf241/bigint.cpp \
#      ../../Libraries/apf241/carrycrt.cpp \
#      ../../Libraries/apf241/convolut.cpp \
#      ../../Libraries/apf241/crt.cpp \
#      ../../Libraries/apf241/datastru.cpp \
#      ../../Libraries/apf241/file.cpp \
#      ../../Libraries/apf241/fnt.cpp \
#      ../../Libraries/apf241/fourstep.cpp \
#      ../../Libraries/apf241/global.cpp \
#      ../../Libraries/apf241/init.cpp \
#      ../../Libraries/apf241/modfunc.cpp \
#      ../../Libraries/apf241/move.cpp \
#      ../../Libraries/apf241/scramble.cpp \
#      ../../Libraries/apf241/sixstep.cpp \
#      ../../Libraries/apf241/tablefnt.cpp \
#      ../../Libraries/apf241/tablefou.cpp \
#      ../../Libraries/apf241/tablesit.cpp \
#      ../../Libraries/apf241/tablesix.cpp \
#      ../../Libraries/apf241/tabletwo.cpp \
#      ../../Libraries/apf241/tabletwt.cpp \
#      ../../Libraries/apf241/tapfloat.cpp \
#      ../../Libraries/apf241/tapfunc.cpp \
#      ../../Libraries/apf241/tapstruc.cpp \
#      ../../Libraries/apf241/transpos.cpp \
#      ../../Libraries/apf241/wfta_asm.cpp
#}
