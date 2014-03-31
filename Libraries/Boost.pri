win32 {
  #exists( ../../Libraries/boost_1_55_0/index.htm ) {
  INCLUDEPATH += \
    ../../Libraries/boost_1_55_0
  #}

  #!exists( ../../Libraries/boost_1_55_0/index.htm ) {
  #  exists( ../../Libraries/boost_1_54_0/index.htm ) {
  #  INCLUDEPATH += \
  #    ../../Libraries/boost_1_54_0
  #  }
  #  !exists( ../../Libraries/boost_1_54_0/index.htm ) {
  #    error(Cannot find Boost)
  #  }
  #}
}
