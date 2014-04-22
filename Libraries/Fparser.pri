#
#
# Warp's function parser
#
#
INCLUDEPATH += \
  ../../Libraries/fparser4.5.1

HEADERS += \
  ../../Libraries/fparser4.5.1/extrasrc/fpaux.hh \
  ../../Libraries/fparser4.5.1/extrasrc/fptypes.hh \
  ../../Libraries/fparser4.5.1/fparser_gmpint.hh \
  ../../Libraries/fparser4.5.1/fparser.hh \
  ../../Libraries/fparser4.5.1/fparser_mpfr.hh \
  ../../Libraries/fparser4.5.1/fpconfig.hh

SOURCES += \
  ../../Libraries/fparser4.5.1/fparser.cc \
  ../../Libraries/fparser4.5.1/fpoptimizer.cc


OTHER_FILES += \
  ../../Libraries/fparser4.5.1/extrasrc/fp_identifier_parser.inc \
  ../../Libraries/fparser4.5.1/extrasrc/fp_opcode_add.inc
