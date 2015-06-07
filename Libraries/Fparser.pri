#
#
# Warp's function parser
#
#
INCLUDEPATH += \
  ../../Libraries/fparser4.5.2

HEADERS += \
  ../../Libraries/fparser4.5.2/extrasrc/fpaux.hh \
  ../../Libraries/fparser4.5.2/extrasrc/fptypes.hh \
  ../../Libraries/fparser4.5.2/fparser_gmpint.hh \
  ../../Libraries/fparser4.5.2/fparser.hh \
  ../../Libraries/fparser4.5.2/fparser_mpfr.hh \
  ../../Libraries/fparser4.5.2/fpconfig.hh

SOURCES += \
  ../../Libraries/fparser4.5.2/fparser.cc \
  ../../Libraries/fparser4.5.2/fpoptimizer.cc


OTHER_FILES += \
  ../../Libraries/fparser4.5.2/extrasrc/fp_identifier_parser.inc \
  ../../Libraries/fparser4.5.2/extrasrc/fp_opcode_add.inc
