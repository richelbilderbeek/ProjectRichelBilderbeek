win32 {
  #Add the line below when cross-compiling
  #CONFIG += static
}

QT += core gui
#QT += webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# undefined reference to `_imp___ZNK8QWebView8settingsEv'
#greaterThan(QT_MAJOR_VERSION, 4): QT += webkitwidgets

TEMPLATE = app

#
#
# Common
#
#

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppKalmanFilter \
    ../../Classes/CppMatrix \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtMatrix \
    ../../Classes/CppQtModel \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystem.cpp \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystemfactory.cpp \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystemparameters.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexample.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexperiment.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexperimentparameter.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexperimentparametertype.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparameter.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparametertype.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltertype.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltertypes.cpp \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystem.cpp \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystemfactory.cpp \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystemparameters.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystem.cpp \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemfactory.cpp \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemparameters.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystem.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemfactory.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameter.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameters.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemparametertype.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemtype.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemtypes.cpp \
    ../../Classes/CppMatrix/matrix.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppQtMatrix/qtmatrix.cpp \
    ../../Classes/CppQtModel/modelfunctionparser.cpp \
    ../../Classes/CppQtModel/qtstdvectorfunctionmodel.cpp \
    ../../Classes/CppQtModel/qtstdvectorstringmodel.cpp \
    ../../Classes/CppQtModel/qtublasmatrixdoublemodel.cpp \
    ../../Classes/CppQtModel/qtublasvectordoublemodel.cpp \
    ../../Classes/CppQtModel/qtublasvectorintmodel.cpp \
    kalmanfilterermenudialog.cpp \
    qtcopyalltablewidget.cpp \
    qtfixedlagsmootherkalmanfiltercalculationdialog.cpp \
    qtkalmanfiltercalculationdialog.cpp \
    qtkalmanfilterdialog.cpp \
    qtkalmanfilterermaindialog.cpp \
    qtkalmanfilterermenudialog.cpp \
    qtkalmanfilterermodel.cpp \
    qtkalmanfiltererparameterdialog.cpp \
    qtkalmanfilterexamplesdialog.cpp \
    qtkalmanfilterexperimentdialog.cpp \
    qtkalmanfilterexperimentmodel.cpp \
    qtmain.cpp \
    qtstandardkalmanfiltercalculationdialog.cpp \
    qtsteadystatekalmanfiltercalculationdialog.cpp \
    qtwhitenoisesystemparametersdialog.cpp \
    qtcopyalltableview.cpp


HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilter.h \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystem.h \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystemfactory.h \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystemparameters.h \
    ../../Classes/CppKalmanFilter/kalmanfilter.h \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexample.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexperiment.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexperimentparameter.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexperimentparametertype.h \
    ../../Classes/CppKalmanFilter/kalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparameter.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparametertype.h \
    ../../Classes/CppKalmanFilter/kalmanfiltertype.h \
    ../../Classes/CppKalmanFilter/kalmanfiltertypes.h \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystem.h \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystemfactory.h \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystemparameters.h \
    ../../Classes/CppKalmanFilter/standardkalmanfilter.h \
    ../../Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/standardkalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/standardkalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystem.h \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemfactory.h \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemparameters.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilter.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/whitenoisesystem.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemfactory.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameter.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameters.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemparametertype.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemtype.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemtypes.h \
    ../../Classes/CppMatrix/matrix.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppQtMatrix/qtmatrix.h \
    ../../Classes/CppQtModel/modelfunctionparser.h \
    ../../Classes/CppQtModel/qtstdvectorfunctionmodel.h \
    ../../Classes/CppQtModel/qtstdvectorstringmodel.h \
    ../../Classes/CppQtModel/qtublasmatrixdoublemodel.h \
    ../../Classes/CppQtModel/qtublasvectordoublemodel.h \
    ../../Classes/CppQtModel/qtublasvectorintmodel.h \
    ../../Classes/CppTrace/trace.h \
    kalmanfilterermenudialog.h \
    qtcopyalltablewidget.h \
    qtfixedlagsmootherkalmanfiltercalculationdialog.h \
    qtkalmanfiltercalculationdialog.h \
    qtkalmanfilterdialog.h \
    qtkalmanfilterermaindialog.h \
    qtkalmanfilterermenudialog.h \
    qtkalmanfilterermodel.h \
    qtkalmanfiltererparameterdialog.h \
    qtkalmanfilterexamplesdialog.h \
    qtkalmanfilterexperimentdialog.h \
    qtkalmanfilterexperimentmodel.h \
    qtstandardkalmanfiltercalculationdialog.h \
    qtsteadystatekalmanfiltercalculationdialog.h \
    qtwhitenoisesystemparametersdialog.h \
    qtcopyalltableview.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtfixedlagsmootherkalmanfiltercalculationdialog.ui \
    qtkalmanfiltercalculationdialog.ui \
    qtkalmanfilterdialog.ui \
    qtkalmanfilterermaindialog.ui \
    qtkalmanfilterermenudialog.ui \
    qtkalmanfiltererparameterdialog.ui \
    qtkalmanfilterexamplesdialog.ui \
    qtkalmanfilterexperimentdialog.ui \
    qtstandardkalmanfiltercalculationdialog.ui \
    qtsteadystatekalmanfiltercalculationdialog.ui \
    qtwhitenoisesystemparametersdialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppKalmanFilter/Licence.txt \
    ../../Classes/CppMatrix/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppQtMatrix/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    crosscompiletowindows.sh \
    Licence.txt \
    zip.sh

RESOURCES += \
    ToolKalmanFilterer.qrc

#
#
# Type of compile
#
#

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)

  #Remove all asserts and TRACE
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

#
#
# Platform specific
#
#

#
#
# Compiler flags
#
#
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra


unix {
  message(Unix)
  QMAKE_CXXFLAGS += -Werror
}

win32 {
  !static {
    message(Native Windows)
    #QMAKE_CXXFLAGS += -Werror

  }

  static {
    message(Crosscompiling from Lubuntu to Windows)
    #Allow the crosscompiler to emit warnings without terminating
  }
}

#
#
# Boost
#
#

unix {
  # Cannot link to the the non-header-only libraries when crosscompiling
}

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0

  # Cannot link to the the non-header-only libraries when crosscompiling
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

  exists(/usr/include/qwt-qt4) {
    INCLUDEPATH += /usr/include/qwt-qt4
    LIBS += -lqwt-qt4
  }

  exists(/usr/include/qwt) {
    INCLUDEPATH += /usr/include/qwt
    LIBS += -lqwt
  }

  #equals(QT_MAJOR_VERSION, 4) {
  #  message(Qt4 Qwt)
  #  INCLUDEPATH += /usr/include/qwt-qt4
  #  LIBS += -lqwt-qt4
  #}
  #equals(QT_MAJOR_VERSION, 5) {
  #  message(Qt5 Qwt)
  #  INCLUDEPATH += /usr/include/qwt
  #  LIBS += -lqwt
  #}
}

win32:!static {
  message(Windows: Qwt: link dynamically)
  INCLUDEPATH+= ../../Libraries/qwt-6.1/src
  LIBS+= -L../../Libraries/qwt-6.1/lib

  CONFIG(release, debug|release) {
    message(Windows: Qwt: Linking to qwt)
    LIBS += -lqwt
  }

  CONFIG(debug, debug|release) {
    message(Windows: Qwt: Linking to qwtd)
    LIBS += -lqwtd
  }
}

win32:static {

message(Build Qwt from source)

#See http://www.richelbilderbeek.nl/CppCompileErrorParseErrorAtBOOST_JOIN.htm
#Prevents error:
#/my_boost_folder/boost/type_traits/detail/has_binary_operator.hp:50: Parse error at "BOOST_JOIN"
DEFINES += BOOST_TT_HAS_OPERATOR_HPP_INCLUDED

INCLUDEPATH+= \
  ../../Libraries/qwt-6.1/include

SOURCES += \
  ../../Libraries/qwt-6.1/src/qwt_abstract_scale_draw.cpp \
  ../../Libraries/qwt-6.1/src/qwt_abstract_slider.cpp \
  ../../Libraries/qwt-6.1/src/qwt_analog_clock.cpp \
  ../../Libraries/qwt-6.1/src/qwt_arrow_button.cpp \
  ../../Libraries/qwt-6.1/src/qwt_clipper.cpp \
  ../../Libraries/qwt-6.1/src/qwt_color_map.cpp \
  ../../Libraries/qwt-6.1/src/qwt_column_symbol.cpp \
  ../../Libraries/qwt-6.1/src/qwt_compass.cpp \
  ../../Libraries/qwt-6.1/src/qwt_compass_rose.cpp \
  ../../Libraries/qwt-6.1/src/qwt_counter.cpp \
  ../../Libraries/qwt-6.1/src/qwt_curve_fitter.cpp \
  ../../Libraries/qwt-6.1/src/qwt_dial.cpp \
  ../../Libraries/qwt-6.1/src/qwt_dial_needle.cpp \
  ../../Libraries/qwt-6.1/src/qwt_double_range.cpp \
  ../../Libraries/qwt-6.1/src/qwt_dyngrid_layout.cpp \
  ../../Libraries/qwt-6.1/src/qwt_event_pattern.cpp \
  ../../Libraries/qwt-6.1/src/qwt_interval.cpp \
  ../../Libraries/qwt-6.1/src/qwt_interval_symbol.cpp \
  ../../Libraries/qwt-6.1/src/qwt_knob.cpp \
  ../../Libraries/qwt-6.1/src/qwt_legend.cpp \
  ../../Libraries/qwt-6.1/src/qwt_legend_item.cpp \
  ../../Libraries/qwt-6.1/src/qwt_magnifier.cpp \
  ../../Libraries/qwt-6.1/src/qwt_math.cpp \
  ../../Libraries/qwt-6.1/src/qwt_matrix_raster_data.cpp \
  ../../Libraries/qwt-6.1/src/qwt_null_paintdevice.cpp \
  ../../Libraries/qwt-6.1/src/qwt_painter.cpp \
  ../../Libraries/qwt-6.1/src/qwt_panner.cpp \
  ../../Libraries/qwt-6.1/src/qwt_picker.cpp \
  ../../Libraries/qwt-6.1/src/qwt_picker_machine.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_axis.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_canvas.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_curve.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_dict.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_directpainter.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_grid.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_histogram.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_item.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_layout.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_magnifier.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_marker.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_panner.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_picker.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_rasteritem.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_renderer.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_rescaler.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_scaleitem.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_seriesitem.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_spectrocurve.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_xml.cpp \
  ../../Libraries/qwt-6.1/src/qwt_plot_zoomer.cpp \
  ../../Libraries/qwt-6.1/src/qwt_point_3d.cpp \
  ../../Libraries/qwt-6.1/src/qwt_point_polar.cpp \
  ../../Libraries/qwt-6.1/src/qwt_raster_data.cpp \
  ../../Libraries/qwt-6.1/src/qwt_round_scale_draw.cpp \
  ../../Libraries/qwt-6.1/src/qwt_sampling_thread.cpp \
  ../../Libraries/qwt-6.1/src/qwt_scale_div.cpp \
  ../../Libraries/qwt-6.1/src/qwt_scale_draw.cpp \
  ../../Libraries/qwt-6.1/src/qwt_scale_engine.cpp \
  ../../Libraries/qwt-6.1/src/qwt_scale_map.cpp \
  ../../Libraries/qwt-6.1/src/qwt_scale_widget.cpp \
  ../../Libraries/qwt-6.1/src/qwt_series_data.cpp \
  ../../Libraries/qwt-6.1/src/qwt_slider.cpp \
  ../../Libraries/qwt-6.1/src/qwt_spline.cpp \
  ../../Libraries/qwt-6.1/src/qwt_symbol.cpp \
  ../../Libraries/qwt-6.1/src/qwt_system_clock.cpp \
  ../../Libraries/qwt-6.1/src/qwt_text.cpp \
  ../../Libraries/qwt-6.1/src/qwt_text_engine.cpp \
  ../../Libraries/qwt-6.1/src/qwt_text_label.cpp \
  ../../Libraries/qwt-6.1/src/qwt_thermo.cpp \
  ../../Libraries/qwt-6.1/src/qwt_wheel.cpp \
# ../../Libraries/qwt-6.1/src/qwt_plot_intervalcurve.cpp \
# ../../Libraries/qwt-6.1/src/qwt_plot_spectrogram.cpp \
# ../../Libraries/qwt-6.1/src/qwt_plot_svgitem.cpp \
  ../../Libraries/qwt-6.1/src/qwt_abstract_scale.cpp

HEADERS += \
  ../../Libraries/qwt-6.1/include/qwt_abstract_scale.h \
  ../../Libraries/qwt-6.1/include/qwt_abstract_scale_draw.h \
  ../../Libraries/qwt-6.1/include/qwt_abstract_slider.h \
  ../../Libraries/qwt-6.1/include/qwt_analog_clock.h \
  ../../Libraries/qwt-6.1/include/qwt_arrow_button.h \
  ../../Libraries/qwt-6.1/include/qwt_clipper.h \
  ../../Libraries/qwt-6.1/include/qwt_color_map.h \
  ../../Libraries/qwt-6.1/include/qwt_column_symbol.h \
  ../../Libraries/qwt-6.1/include/qwt_compass.h \
  ../../Libraries/qwt-6.1/include/qwt_compass_rose.h \
  ../../Libraries/qwt-6.1/include/qwt_compat.h \
  ../../Libraries/qwt-6.1/include/qwt_counter.h \
  ../../Libraries/qwt-6.1/include/qwt_curve_fitter.h \
  ../../Libraries/qwt-6.1/include/qwt_dial.h \
  ../../Libraries/qwt-6.1/include/qwt_dial_needle.h \
  ../../Libraries/qwt-6.1/include/qwt_double_range.h \
  ../../Libraries/qwt-6.1/include/qwt_dyngrid_layout.h \
  ../../Libraries/qwt-6.1/include/qwt_event_pattern.h \
  ../../Libraries/qwt-6.1/include/qwt_global.h \
  ../../Libraries/qwt-6.1/include/qwt_interval.h \
  ../../Libraries/qwt-6.1/include/qwt_interval_symbol.h \
  ../../Libraries/qwt-6.1/include/qwt_knob.h \
  ../../Libraries/qwt-6.1/include/qwt_legend.h \
  ../../Libraries/qwt-6.1/include/qwt_legend_item.h \
  ../../Libraries/qwt-6.1/include/qwt_legend_itemmanager.h \
  ../../Libraries/qwt-6.1/include/qwt_magnifier.h \
  ../../Libraries/qwt-6.1/include/qwt_math.h \
  ../../Libraries/qwt-6.1/include/qwt_mathml_text_engine.h \
  ../../Libraries/qwt-6.1/include/qwt_matrix_raster_data.h \
  ../../Libraries/qwt-6.1/include/qwt_null_paintdevice.h \
  ../../Libraries/qwt-6.1/include/qwt_painter.h \
  ../../Libraries/qwt-6.1/include/qwt_panner.h \
  ../../Libraries/qwt-6.1/include/qwt_picker.h \
  ../../Libraries/qwt-6.1/include/qwt_picker_machine.h \
  ../../Libraries/qwt-6.1/include/qwt_plot.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_canvas.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_curve.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_dict.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_directpainter.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_grid.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_histogram.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_item.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_layout.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_magnifier.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_marker.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_panner.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_picker.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_rasteritem.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_renderer.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_rescaler.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_scaleitem.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_seriesitem.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_spectrocurve.h \
  ../../Libraries/qwt-6.1/include/qwt_plot_zoomer.h \
  ../../Libraries/qwt-6.1/include/qwt_point_3d.h \
  ../../Libraries/qwt-6.1/include/qwt_point_polar.h \
  ../../Libraries/qwt-6.1/include/qwt_raster_data.h \
  ../../Libraries/qwt-6.1/include/qwt_round_scale_draw.h \
  ../../Libraries/qwt-6.1/include/qwt_sampling_thread.h \
  ../../Libraries/qwt-6.1/include/qwt_scale_div.h \
  ../../Libraries/qwt-6.1/include/qwt_scale_draw.h \
  ../../Libraries/qwt-6.1/include/qwt_scale_engine.h \
  ../../Libraries/qwt-6.1/include/qwt_scale_map.h \
  ../../Libraries/qwt-6.1/include/qwt_scale_widget.h \
  ../../Libraries/qwt-6.1/include/qwt_series_data.h \
  ../../Libraries/qwt-6.1/include/qwt_slider.h \
  ../../Libraries/qwt-6.1/include/qwt_spline.h \
  ../../Libraries/qwt-6.1/include/qwt_symbol.h \
  ../../Libraries/qwt-6.1/include/qwt_system_clock.h \
  ../../Libraries/qwt-6.1/include/qwt_text.h \
  ../../Libraries/qwt-6.1/include/qwt_text_engine.h \
  ../../Libraries/qwt-6.1/include/qwt_text_label.h \
  ../../Libraries/qwt-6.1/include/qwt_thermo.h \
  ../../Libraries/qwt-6.1/include/qwt_wheel.h \
  ../../Libraries/qwt-6.1/src/qwt.h \
  ../../Libraries/qwt-6.1/src/qwt_abstract_scale.h \
  ../../Libraries/qwt-6.1/src/qwt_abstract_scale_draw.h \
  ../../Libraries/qwt-6.1/src/qwt_abstract_slider.h \
  ../../Libraries/qwt-6.1/src/qwt_analog_clock.h \
  ../../Libraries/qwt-6.1/src/qwt_arrow_button.h \
  ../../Libraries/qwt-6.1/src/qwt_clipper.h \
  ../../Libraries/qwt-6.1/src/qwt_color_map.h \
  ../../Libraries/qwt-6.1/src/qwt_column_symbol.h \
  ../../Libraries/qwt-6.1/src/qwt_compass.h \
  ../../Libraries/qwt-6.1/src/qwt_compass_rose.h \
  ../../Libraries/qwt-6.1/src/qwt_compat.h \
  ../../Libraries/qwt-6.1/src/qwt_counter.h \
  ../../Libraries/qwt-6.1/src/qwt_curve_fitter.h \
  ../../Libraries/qwt-6.1/src/qwt_dial.h \
  ../../Libraries/qwt-6.1/src/qwt_dial_needle.h \
  ../../Libraries/qwt-6.1/src/qwt_double_range.h \
  ../../Libraries/qwt-6.1/src/qwt_dyngrid_layout.h \
  ../../Libraries/qwt-6.1/src/qwt_event_pattern.h \
  ../../Libraries/qwt-6.1/src/qwt_global.h \
  ../../Libraries/qwt-6.1/src/qwt_interval.h \
  ../../Libraries/qwt-6.1/src/qwt_interval_symbol.h \
  ../../Libraries/qwt-6.1/src/qwt_knob.h \
  ../../Libraries/qwt-6.1/src/qwt_legend.h \
  ../../Libraries/qwt-6.1/src/qwt_legend_item.h \
  ../../Libraries/qwt-6.1/src/qwt_legend_itemmanager.h \
  ../../Libraries/qwt-6.1/src/qwt_magnifier.h \
  ../../Libraries/qwt-6.1/src/qwt_math.h \
  ../../Libraries/qwt-6.1/src/qwt_matrix_raster_data.h \
  ../../Libraries/qwt-6.1/src/qwt_null_paintdevice.h \
  ../../Libraries/qwt-6.1/src/qwt_painter.h \
  ../../Libraries/qwt-6.1/src/qwt_panner.h \
  ../../Libraries/qwt-6.1/src/qwt_picker.h \
  ../../Libraries/qwt-6.1/src/qwt_picker_machine.h \
  ../../Libraries/qwt-6.1/src/qwt_plot.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_canvas.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_curve.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_dict.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_directpainter.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_grid.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_histogram.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_item.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_layout.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_magnifier.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_marker.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_panner.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_picker.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_rasteritem.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_renderer.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_rescaler.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_scaleitem.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_seriesitem.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_spectrocurve.h \
  ../../Libraries/qwt-6.1/src/qwt_plot_zoomer.h \
  ../../Libraries/qwt-6.1/src/qwt_point_3d.h \
  ../../Libraries/qwt-6.1/src/qwt_point_polar.h \
  ../../Libraries/qwt-6.1/src/qwt_raster_data.h \
  ../../Libraries/qwt-6.1/src/qwt_round_scale_draw.h \
  ../../Libraries/qwt-6.1/src/qwt_sampling_thread.h \
  ../../Libraries/qwt-6.1/src/qwt_scale_div.h \
  ../../Libraries/qwt-6.1/src/qwt_scale_draw.h \
  ../../Libraries/qwt-6.1/src/qwt_scale_engine.h \
  ../../Libraries/qwt-6.1/src/qwt_scale_map.h \
  ../../Libraries/qwt-6.1/src/qwt_scale_widget.h \
  ../../Libraries/qwt-6.1/src/qwt_series_data.h \
  ../../Libraries/qwt-6.1/src/qwt_slider.h \
  ../../Libraries/qwt-6.1/src/qwt_spline.h \
  ../../Libraries/qwt-6.1/src/qwt_symbol.h \
  ../../Libraries/qwt-6.1/src/qwt_system_clock.h \
  ../../Libraries/qwt-6.1/src/qwt_text.h \
  ../../Libraries/qwt-6.1/src/qwt_text_engine.h \
  ../../Libraries/qwt-6.1/src/qwt_text_label.h \
  ../../Libraries/qwt-6.1/src/qwt_thermo.h \
  ../../Libraries/qwt-6.1/src/qwt_wheel.h \
# ../../Libraries/qwt-6.1/include/qwt_plot_intervalcurve.h \
# ../../Libraries/qwt-6.1/include/qwt_plot_spectrogram.h \
# ../../Libraries/qwt-6.1/include/qwt_plot_svgitem.h \
# ../../Libraries/qwt-6.1/src/qwt_plot_intervalcurve.h \
# ../../Libraries/qwt-6.1/src/qwt_plot_spectrogram.h \
# ../../Libraries/qwt-6.1/src/qwt_plot_svgitem.h \
  ../../Libraries/qwt-6.1/include/qwt.h
}
