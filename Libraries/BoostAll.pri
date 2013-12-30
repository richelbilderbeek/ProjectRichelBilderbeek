win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
  message("No idea how to link to Boost libraries under current Windows computer")
}

LIBS += \
  -lboost_date_time \
  -lboost_filesystem \
  -lboost_program_options \
  -lboost_regex \
  -lboost_signals \
  -lboost_system
