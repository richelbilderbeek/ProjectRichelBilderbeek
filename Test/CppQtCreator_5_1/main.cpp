#include "qtdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtDialog w;
  w.show();
  return a.exec();
}

/*


#
#
# Boost
#
#

unix {
  LIBS += \
  -lboost_date_time \
  -lboost_filesystem \
  -lboost_program_options \
  -lboost_regex \
  -lboost_signals \
  -lboost_system
}

win32 {

  #Boost libraries
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0

  #Prevent the following error:
  #../../Libraries/boost_1_54_0/libs/program_options/src/parsers.cpp: In function 'boost::program_options::parsed_options boost::program_options::parse_environment(const boost::program_options::options_description&, const boost::function1<std::basic_string<char>, std::basic_string<char> >&)':
  #../../Libraries/boost_1_54_0/libs/program_options/src/parsers.cpp:194:36: error: 'environ' was not declared in this scope
  #DEFINES += __COMO_VERSION__


  #Boost.Data_time
  HEADERS += \
    ../../Libraries/boost_1_54_0/libs/date_time/src/gregorian/greg_names.hpp
  SOURCES += \
    ../../Libraries/boost_1_54_0/libs/date_time/src/gregorian/greg_weekday.cpp \
    ../../Libraries/boost_1_54_0/libs/date_time/src/gregorian/gregorian_types.cpp \
    ../../Libraries/boost_1_54_0/libs/date_time/src/gregorian/greg_month.cpp \
    ../../Libraries/boost_1_54_0/libs/date_time/src/gregorian/date_generators.cpp

  #Boost.Filesystem
  HEADERS += \
    ../../Libraries/boost_1_54_0/libs/filesystem/src/windows_file_codecvt.hpp
  SOURCES += \
    ../../Libraries/boost_1_54_0/libs/filesystem/src/codecvt_error_category.cpp \
    ../../Libraries/boost_1_54_0/libs/filesystem/src/operations.cpp \
    ../../Libraries/boost_1_54_0/libs/filesystem/src/path.cpp \
    ../../Libraries/boost_1_54_0/libs/filesystem/src/path_traits.cpp \
    ../../Libraries/boost_1_54_0/libs/filesystem/src/portability.cpp \
    ../../Libraries/boost_1_54_0/libs/filesystem/src/unique_path.cpp \
    ../../Libraries/boost_1_54_0/libs/filesystem/src/utf8_codecvt_facet.cpp \ #Keep, comment program_options/src/utf8_codecvt_facet.cpp
    ../../Libraries/boost_1_54_0/libs/filesystem/src/windows_file_codecvt.cpp

  #Boost.Program_options
  #
  #This lib does not seem to work well together with Boost.Filesystem
  #when compiled from source like this
  #
  #SOURCES += \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/cmdline.cpp \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/config_file.cpp \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/convert.cpp \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/options_description.cpp \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/parsers.cpp \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/positional_options.cpp \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/split.cpp \
  #  #../../Libraries/boost_1_54_0/libs/program_options/src/utf8_codecvt_facet.cpp \ #Comment, keep filesystem/src/utf8_codecvt_facet.cpp
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/value_semantic.cpp \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/variables_map.cpp \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/winmain.cpp

  #Boost.Regex
  HEADERS += \
    ../../Libraries/boost_1_54_0/libs/regex/src/internals.hpp

  SOURCES += \
    ../../Libraries/boost_1_54_0/libs/regex/src/winstances.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/wide_posix_api.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/wc_regex_traits.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/w32_regex_traits.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/usinstances.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/static_mutex.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/regex_traits_defaults.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/regex_raw_buffer.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/regex_debug.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/regex.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/posix_api.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/instances.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/icu.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/fileiter.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/c_regex_traits.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/cregex.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/cpp_regex_traits.cpp

  #Boost.System
  HEADERS += \
    ../../Libraries/boost_1_54_0/libs/system/src/local_free_on_destruction.hpp
  SOURCES += \
    ../../Libraries/boost_1_54_0/libs/system/src/error_code.cpp
}

#
#
# Warp's function parser
#
#
#unix {
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
#}

#
#
# Qwt
#
#

unix {
  INCLUDEPATH += /usr/include/qwt-qt4
  LIBS += -lqwt-qt4
}

win32 {
  message(Compile and link Qwt from source)
  INCLUDEPATH+=../../Libraries/Qwt/include

  SOURCES += \
    ../../Libraries/Qwt/src/qwt_arrbtn.cpp \
    ../../Libraries/Qwt/src/qwt_autoscl.cpp \
    ../../Libraries/Qwt/src/qwt_curve.cpp \
    ../../Libraries/Qwt/src/qwt_data.cpp \
    ../../Libraries/Qwt/src/qwt_dimap.cpp \
    ../../Libraries/Qwt/src/qwt_double_rect.cpp \
    ../../Libraries/Qwt/src/qwt_drange.cpp \
    ../../Libraries/Qwt/src/qwt_grid.cpp \
    ../../Libraries/Qwt/src/qwt_layout_metrics.cpp \
    ../../Libraries/Qwt/src/qwt_marker.cpp \
    ../../Libraries/Qwt/src/qwt_paint_buffer.cpp \
    ../../Libraries/Qwt/src/qwt_plot_print.cpp \
    ../../Libraries/Qwt/src/qwt_plot_printfilter.cpp \
    ../../Libraries/Qwt/src/qwt_push_button.cpp \
    ../../Libraries/Qwt/src/qwt_rect.cpp \
    ../../Libraries/Qwt/src/qwt_scale.cpp \
    ../../Libraries/Qwt/src/qwt_scldiv.cpp \
    ../../Libraries/Qwt/src/qwt_scldraw.cpp \
    ../../Libraries/Qwt/src/qwt_sclif.cpp \
    ../../Libraries/Qwt/src/qwt_sldbase.cpp

HEADERS  +=  \
    ../../Libraries/Qwt/include/qwt.h \
    ../../Libraries/Qwt/include/qwt_analog_clock.h \
    ../../Libraries/Qwt/include/qwt_array.h \
    ../../Libraries/Qwt/include/qwt_arrbtn.h \
    ../../Libraries/Qwt/include/qwt_autoscl.h \
    ../../Libraries/Qwt/include/qwt_compass.h \
    ../../Libraries/Qwt/include/qwt_compass_rose.h \
    ../../Libraries/Qwt/include/qwt_counter.h \
    ../../Libraries/Qwt/include/qwt_curve.h \
    ../../Libraries/Qwt/include/qwt_data.h \
    ../../Libraries/Qwt/include/qwt_dial.h \
    ../../Libraries/Qwt/include/qwt_dial_needle.h \
    ../../Libraries/Qwt/include/qwt_dimap.h \
    ../../Libraries/Qwt/include/qwt_double_rect.h \
    ../../Libraries/Qwt/include/qwt_drange.h \
    ../../Libraries/Qwt/include/qwt_dyngrid_layout.h \
    ../../Libraries/Qwt/include/qwt_event_pattern.h \
    ../../Libraries/Qwt/include/qwt_global.h \
    ../../Libraries/Qwt/include/qwt_grid.h \
    ../../Libraries/Qwt/include/qwt_knob.h \
    ../../Libraries/Qwt/include/qwt_layout_metrics.h \
    ../../Libraries/Qwt/include/qwt_legend.h \
    ../../Libraries/Qwt/include/qwt_marker.h \
    ../../Libraries/Qwt/include/qwt_math.h \
    ../../Libraries/Qwt/include/qwt_paint_buffer.h \
    ../../Libraries/Qwt/include/qwt_painter.h \
    ../../Libraries/Qwt/include/qwt_picker.h \
    ../../Libraries/Qwt/include/qwt_picker_machine.h \
    ../../Libraries/Qwt/include/qwt_plot.h \
    ../../Libraries/Qwt/include/qwt_plot_canvas.h \
    ../../Libraries/Qwt/include/qwt_plot_classes.h \
    ../../Libraries/Qwt/include/qwt_plot_dict.h \
    ../../Libraries/Qwt/include/qwt_plot_item.h \
    ../../Libraries/Qwt/include/qwt_plot_layout.h \
    ../../Libraries/Qwt/include/qwt_plot_picker.h \
    ../../Libraries/Qwt/include/qwt_plot_printfilter.h \
    ../../Libraries/Qwt/include/qwt_plot_zoomer.h \
    ../../Libraries/Qwt/include/qwt_push_button.h \
    ../../Libraries/Qwt/include/qwt_rect.h \
    ../../Libraries/Qwt/include/qwt_scale.h \
    ../../Libraries/Qwt/include/qwt_scldiv.h \
    ../../Libraries/Qwt/include/qwt_scldraw.h \
    ../../Libraries/Qwt/include/qwt_sclif.h \
    ../../Libraries/Qwt/include/qwt_sldbase.h \
    ../../Libraries/Qwt/include/qwt_slider.h \
    ../../Libraries/Qwt/include/qwt_spline.h \
    ../../Libraries/Qwt/include/qwt_symbol.h \
    ../../Libraries/Qwt/include/qwt_text.h \
    ../../Libraries/Qwt/include/qwt_thermo.h \
    ../../Libraries/Qwt/include/qwt_wheel.h

}

*/
