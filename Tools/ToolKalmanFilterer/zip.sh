#!/bin/sh
# Created from file '../../Tools/ToolKalmanFilterer/ToolKalmanFiltererDesktop.pro'

echo "Creating of all folders"

mkdir Projects
mkdir Projects/Tools
mkdir Projects/Classes
mkdir Projects/Libraries
mkdir Projects/Classes/CppAbout
mkdir Projects/Classes/CppTrace
mkdir Projects/Classes/CppMatrix
mkdir Projects/Classes/CppQtModel
mkdir Projects/Classes/CppQtMatrix
mkdir Projects/Libraries/qwt-6.0.1
mkdir Projects/Libraries/boost_1_53_0
mkdir Projects/Libraries/fparser4.5.1
mkdir Projects/Classes/CppKalmanFilter
mkdir Projects/Libraries/qwt-6.0.1/src
mkdir Projects/Classes/CppQtAboutDialog
mkdir Projects/Tools/ToolKalmanFilterer
mkdir Projects/Libraries/boost_1_53_0/libs
mkdir Projects/Libraries/qwt-6.0.1/include
mkdir Projects/Classes/CppQtHideAndShowDialog
mkdir Projects/Libraries/fparser4.5.1/extrasrc
mkdir Projects/Libraries/boost_1_53_0/libs/regex
mkdir Projects/Libraries/boost_1_53_0/libs/system
mkdir Projects/Libraries/boost_1_53_0/libs/date_time
mkdir Projects/Libraries/boost_1_53_0/libs/regex/src
mkdir Projects/Libraries/boost_1_53_0/libs/filesystem
mkdir Projects/Libraries/boost_1_53_0/libs/system/src
mkdir Projects/Libraries/boost_1_53_0/libs/date_time/src
mkdir Projects/Libraries/boost_1_53_0/libs/filesystem/src
mkdir Projects/Libraries/boost_1_53_0/libs/date_time/src/gregorian

echo "Copying files"

cp ../../Classes/CppAbout/about.h Projects/Classes/CppAbout/about.h
cp ../../Classes/CppTrace/trace.h Projects/Classes/CppTrace/trace.h
cp ../../Classes/CppAbout/about.cpp Projects/Classes/CppAbout/about.cpp
cp ../../Classes/CppMatrix/matrix.h Projects/Classes/CppMatrix/matrix.h
cp ../../Classes/CppAbout/Licence.txt Projects/Classes/CppAbout/Licence.txt
cp ../../Classes/CppMatrix/matrix.cpp Projects/Classes/CppMatrix/matrix.cpp
cp ../../Classes/CppTrace/Licence.txt Projects/Classes/CppTrace/Licence.txt
cp ../../Classes/CppMatrix/Licence.txt Projects/Classes/CppMatrix/Licence.txt
cp ../../Libraries/qwt-6.0.1/src/qwt.h Projects/Libraries/qwt-6.0.1/src/qwt.h
cp ../../Classes/CppQtMatrix/qtmatrix.h Projects/Classes/CppQtMatrix/qtmatrix.h
cp ../../Tools/ToolKalmanFilterer/0.txt Projects/Tools/ToolKalmanFilterer/0.txt
cp ../../Tools/ToolKalmanFilterer/R.png Projects/Tools/ToolKalmanFilterer/R.png
cp ../../Classes/CppQtMatrix/Licence.txt Projects/Classes/CppQtMatrix/Licence.txt
cp ../../Tools/ToolKalmanFilterer/zip.sh Projects/Tools/ToolKalmanFilterer/zip.sh
cp ../../Classes/CppQtMatrix/qtmatrix.cpp Projects/Classes/CppQtMatrix/qtmatrix.cpp
cp ../../Libraries/fparser4.5.1/fparser.cc Projects/Libraries/fparser4.5.1/fparser.cc
cp ../../Libraries/fparser4.5.1/fparser.hh Projects/Libraries/fparser4.5.1/fparser.hh
cp ../../Libraries/qwt-6.0.1/include/qwt.h Projects/Libraries/qwt-6.0.1/include/qwt.h
cp ../../Libraries/fparser4.5.1/fpconfig.hh Projects/Libraries/fparser4.5.1/fpconfig.hh
cp ../../Libraries/qwt-6.0.1/src/qwt_dial.h Projects/Libraries/qwt-6.0.1/src/qwt_dial.h
cp ../../Libraries/qwt-6.0.1/src/qwt_knob.h Projects/Libraries/qwt-6.0.1/src/qwt_knob.h
cp ../../Libraries/qwt-6.0.1/src/qwt_math.h Projects/Libraries/qwt-6.0.1/src/qwt_math.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot.h Projects/Libraries/qwt-6.0.1/src/qwt_plot.h
cp ../../Libraries/qwt-6.0.1/src/qwt_text.h Projects/Libraries/qwt-6.0.1/src/qwt_text.h
cp ../../Classes/CppKalmanFilter/Licence.txt Projects/Classes/CppKalmanFilter/Licence.txt
cp ../../Libraries/qwt-6.0.1/src/qwt_wheel.h Projects/Libraries/qwt-6.0.1/src/qwt_wheel.h
cp ../../Tools/ToolKalmanFilterer/PicRed.png Projects/Tools/ToolKalmanFilterer/PicRed.png
cp ../../Tools/ToolKalmanFilterer/qtmain.cpp Projects/Tools/ToolKalmanFilterer/qtmain.cpp
cp ../../Classes/CppQtAboutDialog/Licence.txt Projects/Classes/CppQtAboutDialog/Licence.txt
cp ../../Libraries/qwt-6.0.1/src/qwt_compat.h Projects/Libraries/qwt-6.0.1/src/qwt_compat.h
cp ../../Libraries/qwt-6.0.1/src/qwt_dial.cpp Projects/Libraries/qwt-6.0.1/src/qwt_dial.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_global.h Projects/Libraries/qwt-6.0.1/src/qwt_global.h
cp ../../Libraries/qwt-6.0.1/src/qwt_knob.cpp Projects/Libraries/qwt-6.0.1/src/qwt_knob.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_legend.h Projects/Libraries/qwt-6.0.1/src/qwt_legend.h
cp ../../Libraries/qwt-6.0.1/src/qwt_math.cpp Projects/Libraries/qwt-6.0.1/src/qwt_math.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_panner.h Projects/Libraries/qwt-6.0.1/src/qwt_panner.h
cp ../../Libraries/qwt-6.0.1/src/qwt_picker.h Projects/Libraries/qwt-6.0.1/src/qwt_picker.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_slider.h Projects/Libraries/qwt-6.0.1/src/qwt_slider.h
cp ../../Libraries/qwt-6.0.1/src/qwt_spline.h Projects/Libraries/qwt-6.0.1/src/qwt_spline.h
cp ../../Libraries/qwt-6.0.1/src/qwt_symbol.h Projects/Libraries/qwt-6.0.1/src/qwt_symbol.h
cp ../../Libraries/qwt-6.0.1/src/qwt_text.cpp Projects/Libraries/qwt-6.0.1/src/qwt_text.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_thermo.h Projects/Libraries/qwt-6.0.1/src/qwt_thermo.h
cp ../../Tools/ToolKalmanFilterer/Licence.txt Projects/Tools/ToolKalmanFilterer/Licence.txt
cp ../../Libraries/fparser4.5.1/fpoptimizer.cc Projects/Libraries/fparser4.5.1/fpoptimizer.cc
cp ../../Libraries/qwt-6.0.1/src/qwt_clipper.h Projects/Libraries/qwt-6.0.1/src/qwt_clipper.h
cp ../../Libraries/qwt-6.0.1/src/qwt_compass.h Projects/Libraries/qwt-6.0.1/src/qwt_compass.h
cp ../../Libraries/qwt-6.0.1/src/qwt_counter.h Projects/Libraries/qwt-6.0.1/src/qwt_counter.h
cp ../../Libraries/qwt-6.0.1/src/qwt_painter.h Projects/Libraries/qwt-6.0.1/src/qwt_painter.h
cp ../../Libraries/qwt-6.0.1/src/qwt_wheel.cpp Projects/Libraries/qwt-6.0.1/src/qwt_wheel.cpp
cp ../../Tools/ToolKalmanFilterer/PicBlack.png Projects/Tools/ToolKalmanFilterer/PicBlack.png
cp ../../Tools/ToolKalmanFilterer/PicGreen.png Projects/Tools/ToolKalmanFilterer/PicGreen.png
cp ../../Classes/CppKalmanFilter/kalmanfilter.h Projects/Classes/CppKalmanFilter/kalmanfilter.h
cp ../../Libraries/fparser4.5.1/fparser_mpfr.hh Projects/Libraries/fparser4.5.1/fparser_mpfr.hh
cp ../../Libraries/qwt-6.0.1/include/qwt_dial.h Projects/Libraries/qwt-6.0.1/include/qwt_dial.h
cp ../../Libraries/qwt-6.0.1/include/qwt_knob.h Projects/Libraries/qwt-6.0.1/include/qwt_knob.h
cp ../../Libraries/qwt-6.0.1/include/qwt_math.h Projects/Libraries/qwt-6.0.1/include/qwt_math.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot.h Projects/Libraries/qwt-6.0.1/include/qwt_plot.h
cp ../../Libraries/qwt-6.0.1/include/qwt_text.h Projects/Libraries/qwt-6.0.1/include/qwt_text.h
cp ../../Libraries/qwt-6.0.1/src/qwt_interval.h Projects/Libraries/qwt-6.0.1/src/qwt_interval.h
cp ../../Libraries/qwt-6.0.1/src/qwt_legend.cpp Projects/Libraries/qwt-6.0.1/src/qwt_legend.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_panner.cpp Projects/Libraries/qwt-6.0.1/src/qwt_panner.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_picker.cpp Projects/Libraries/qwt-6.0.1/src/qwt_picker.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_point_3d.h Projects/Libraries/qwt-6.0.1/src/qwt_point_3d.h
cp ../../Libraries/qwt-6.0.1/src/qwt_slider.cpp Projects/Libraries/qwt-6.0.1/src/qwt_slider.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_spline.cpp Projects/Libraries/qwt-6.0.1/src/qwt_spline.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_symbol.cpp Projects/Libraries/qwt-6.0.1/src/qwt_symbol.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_thermo.cpp Projects/Libraries/qwt-6.0.1/src/qwt_thermo.cpp
cp ../../Tools/ToolKalmanFilterer/PicOrange.png Projects/Tools/ToolKalmanFilterer/PicOrange.png
cp ../../Tools/ToolKalmanFilterer/PicYellow.png Projects/Tools/ToolKalmanFilterer/PicYellow.png
cp ../../Libraries/qwt-6.0.1/include/qwt_wheel.h Projects/Libraries/qwt-6.0.1/include/qwt_wheel.h
cp ../../Libraries/qwt-6.0.1/src/qwt_clipper.cpp Projects/Libraries/qwt-6.0.1/src/qwt_clipper.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_color_map.h Projects/Libraries/qwt-6.0.1/src/qwt_color_map.h
cp ../../Libraries/qwt-6.0.1/src/qwt_compass.cpp Projects/Libraries/qwt-6.0.1/src/qwt_compass.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_counter.cpp Projects/Libraries/qwt-6.0.1/src/qwt_counter.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_magnifier.h Projects/Libraries/qwt-6.0.1/src/qwt_magnifier.h
cp ../../Libraries/qwt-6.0.1/src/qwt_painter.cpp Projects/Libraries/qwt-6.0.1/src/qwt_painter.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_dict.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_dict.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_grid.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_grid.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_item.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_item.h
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_div.h Projects/Libraries/qwt-6.0.1/src/qwt_scale_div.h
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_map.h Projects/Libraries/qwt-6.0.1/src/qwt_scale_map.h
cp ../../Classes/CppKalmanFilter/kalmanfilter.cpp Projects/Classes/CppKalmanFilter/kalmanfilter.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h Projects/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtModel/modelfunctionparser.h Projects/Classes/CppQtModel/modelfunctionparser.h
cp ../../Libraries/fparser4.5.1/extrasrc/fpaux.hh Projects/Libraries/fparser4.5.1/extrasrc/fpaux.hh
cp ../../Libraries/fparser4.5.1/fparser_gmpint.hh Projects/Libraries/fparser4.5.1/fparser_gmpint.hh
cp ../../Libraries/qwt-6.0.1/include/qwt_compat.h Projects/Libraries/qwt-6.0.1/include/qwt_compat.h
cp ../../Libraries/qwt-6.0.1/include/qwt_global.h Projects/Libraries/qwt-6.0.1/include/qwt_global.h
cp ../../Libraries/qwt-6.0.1/include/qwt_legend.h Projects/Libraries/qwt-6.0.1/include/qwt_legend.h
cp ../../Libraries/qwt-6.0.1/include/qwt_panner.h Projects/Libraries/qwt-6.0.1/include/qwt_panner.h
cp ../../Libraries/qwt-6.0.1/include/qwt_picker.h Projects/Libraries/qwt-6.0.1/include/qwt_picker.h
cp ../../Libraries/qwt-6.0.1/include/qwt_slider.h Projects/Libraries/qwt-6.0.1/include/qwt_slider.h
cp ../../Libraries/qwt-6.0.1/include/qwt_spline.h Projects/Libraries/qwt-6.0.1/include/qwt_spline.h
cp ../../Libraries/qwt-6.0.1/include/qwt_symbol.h Projects/Libraries/qwt-6.0.1/include/qwt_symbol.h
cp ../../Libraries/qwt-6.0.1/include/qwt_thermo.h Projects/Libraries/qwt-6.0.1/include/qwt_thermo.h
cp ../../Libraries/qwt-6.0.1/src/qwt_interval.cpp Projects/Libraries/qwt-6.0.1/src/qwt_interval.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_curve.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_curve.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_xml.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_xml.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_point_3d.cpp Projects/Libraries/qwt-6.0.1/src/qwt_point_3d.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_draw.h Projects/Libraries/qwt-6.0.1/src/qwt_scale_draw.h
cp ../../Libraries/qwt-6.0.1/src/qwt_text_label.h Projects/Libraries/qwt-6.0.1/src/qwt_text_label.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui Projects/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Libraries/qwt-6.0.1/include/qwt_clipper.h Projects/Libraries/qwt-6.0.1/include/qwt_clipper.h
cp ../../Libraries/qwt-6.0.1/include/qwt_compass.h Projects/Libraries/qwt-6.0.1/include/qwt_compass.h
cp ../../Libraries/qwt-6.0.1/include/qwt_counter.h Projects/Libraries/qwt-6.0.1/include/qwt_counter.h
cp ../../Libraries/qwt-6.0.1/include/qwt_painter.h Projects/Libraries/qwt-6.0.1/include/qwt_painter.h
cp ../../Libraries/qwt-6.0.1/src/qwt_color_map.cpp Projects/Libraries/qwt-6.0.1/src/qwt_color_map.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_dial_needle.h Projects/Libraries/qwt-6.0.1/src/qwt_dial_needle.h
cp ../../Libraries/qwt-6.0.1/src/qwt_legend_item.h Projects/Libraries/qwt-6.0.1/src/qwt_legend_item.h
cp ../../Libraries/qwt-6.0.1/src/qwt_magnifier.cpp Projects/Libraries/qwt-6.0.1/src/qwt_magnifier.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_axis.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_axis.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_canvas.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_canvas.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_dict.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_dict.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_grid.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_grid.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_item.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_item.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_layout.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_layout.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_marker.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_marker.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_panner.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_panner.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_picker.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_picker.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_zoomer.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_zoomer.h
cp ../../Libraries/qwt-6.0.1/src/qwt_point_polar.h Projects/Libraries/qwt-6.0.1/src/qwt_point_polar.h
cp ../../Libraries/qwt-6.0.1/src/qwt_raster_data.h Projects/Libraries/qwt-6.0.1/src/qwt_raster_data.h
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_div.cpp Projects/Libraries/qwt-6.0.1/src/qwt_scale_div.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_map.cpp Projects/Libraries/qwt-6.0.1/src/qwt_scale_map.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_series_data.h Projects/Libraries/qwt-6.0.1/src/qwt_series_data.h
cp ../../Libraries/qwt-6.0.1/src/qwt_text_engine.h Projects/Libraries/qwt-6.0.1/src/qwt_text_engine.h
cp ../../Classes/CppKalmanFilter/kalmanfiltertype.h Projects/Classes/CppKalmanFilter/kalmanfiltertype.h
cp ../../Classes/CppKalmanFilter/whitenoisesystem.h Projects/Classes/CppKalmanFilter/whitenoisesystem.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp Projects/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/Licence.txt Projects/Classes/CppQtHideAndShowDialog/Licence.txt
cp ../../Classes/CppQtModel/modelfunctionparser.cpp Projects/Classes/CppQtModel/modelfunctionparser.cpp
cp ../../Classes/CppQtModel/qtublasvectorintmodel.h Projects/Classes/CppQtModel/qtublasvectorintmodel.h
cp ../../Libraries/fparser4.5.1/extrasrc/fptypes.hh Projects/Libraries/fparser4.5.1/extrasrc/fptypes.hh
cp ../../Libraries/qwt-6.0.1/include/qwt_interval.h Projects/Libraries/qwt-6.0.1/include/qwt_interval.h
cp ../../Libraries/qwt-6.0.1/include/qwt_point_3d.h Projects/Libraries/qwt-6.0.1/include/qwt_point_3d.h
cp ../../Libraries/qwt-6.0.1/src/qwt_analog_clock.h Projects/Libraries/qwt-6.0.1/src/qwt_analog_clock.h
cp ../../Libraries/qwt-6.0.1/src/qwt_arrow_button.h Projects/Libraries/qwt-6.0.1/src/qwt_arrow_button.h
cp ../../Libraries/qwt-6.0.1/src/qwt_compass_rose.h Projects/Libraries/qwt-6.0.1/src/qwt_compass_rose.h
cp ../../Libraries/qwt-6.0.1/src/qwt_curve_fitter.h Projects/Libraries/qwt-6.0.1/src/qwt_curve_fitter.h
cp ../../Libraries/qwt-6.0.1/src/qwt_double_range.h Projects/Libraries/qwt-6.0.1/src/qwt_double_range.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_curve.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_curve.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_draw.cpp Projects/Libraries/qwt-6.0.1/src/qwt_scale_draw.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_engine.h Projects/Libraries/qwt-6.0.1/src/qwt_scale_engine.h
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_widget.h Projects/Libraries/qwt-6.0.1/src/qwt_scale_widget.h
cp ../../Libraries/qwt-6.0.1/src/qwt_system_clock.h Projects/Libraries/qwt-6.0.1/src/qwt_system_clock.h
cp ../../Libraries/qwt-6.0.1/src/qwt_text_label.cpp Projects/Libraries/qwt-6.0.1/src/qwt_text_label.cpp
cp ../../Classes/CppKalmanFilter/kalmanfiltertypes.h Projects/Classes/CppKalmanFilter/kalmanfiltertypes.h
cp ../../Classes/CppQtModel/qtstdvectorstringmodel.h Projects/Classes/CppQtModel/qtstdvectorstringmodel.h
cp ../../Libraries/qwt-6.0.1/include/qwt_color_map.h Projects/Libraries/qwt-6.0.1/include/qwt_color_map.h
cp ../../Libraries/qwt-6.0.1/include/qwt_magnifier.h Projects/Libraries/qwt-6.0.1/include/qwt_magnifier.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_dict.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_dict.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_grid.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_grid.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_item.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_item.h
cp ../../Libraries/qwt-6.0.1/include/qwt_scale_div.h Projects/Libraries/qwt-6.0.1/include/qwt_scale_div.h
cp ../../Libraries/qwt-6.0.1/include/qwt_scale_map.h Projects/Libraries/qwt-6.0.1/include/qwt_scale_map.h
cp ../../Libraries/qwt-6.0.1/src/qwt_column_symbol.h Projects/Libraries/qwt-6.0.1/src/qwt_column_symbol.h
cp ../../Libraries/qwt-6.0.1/src/qwt_dial_needle.cpp Projects/Libraries/qwt-6.0.1/src/qwt_dial_needle.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_event_pattern.h Projects/Libraries/qwt-6.0.1/src/qwt_event_pattern.h
cp ../../Libraries/qwt-6.0.1/src/qwt_legend_item.cpp Projects/Libraries/qwt-6.0.1/src/qwt_legend_item.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_canvas.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_canvas.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_layout.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_layout.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_marker.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_marker.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_panner.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_panner.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_picker.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_picker.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_renderer.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_renderer.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_rescaler.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_rescaler.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_zoomer.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_zoomer.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_point_polar.cpp Projects/Libraries/qwt-6.0.1/src/qwt_point_polar.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_raster_data.cpp Projects/Libraries/qwt-6.0.1/src/qwt_raster_data.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_series_data.cpp Projects/Libraries/qwt-6.0.1/src/qwt_series_data.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_text_engine.cpp Projects/Libraries/qwt-6.0.1/src/qwt_text_engine.cpp
cp ../../Tools/ToolKalmanFilterer/PicTransparent.png Projects/Tools/ToolKalmanFilterer/PicTransparent.png
cp ../../Classes/CppKalmanFilter/kalmanfiltertype.cpp Projects/Classes/CppKalmanFilter/kalmanfiltertype.cpp
cp ../../Classes/CppKalmanFilter/whitenoisesystem.cpp Projects/Classes/CppKalmanFilter/whitenoisesystem.cpp
cp ../../Classes/CppQtModel/qtublasvectorintmodel.cpp Projects/Classes/CppQtModel/qtublasvectorintmodel.cpp
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_curve.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_curve.h
cp ../../Libraries/qwt-6.0.1/include/qwt_scale_draw.h Projects/Libraries/qwt-6.0.1/include/qwt_scale_draw.h
cp ../../Libraries/qwt-6.0.1/include/qwt_text_label.h Projects/Libraries/qwt-6.0.1/include/qwt_text_label.h
cp ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale.h Projects/Libraries/qwt-6.0.1/src/qwt_abstract_scale.h
cp ../../Libraries/qwt-6.0.1/src/qwt_analog_clock.cpp Projects/Libraries/qwt-6.0.1/src/qwt_analog_clock.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_arrow_button.cpp Projects/Libraries/qwt-6.0.1/src/qwt_arrow_button.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_compass_rose.cpp Projects/Libraries/qwt-6.0.1/src/qwt_compass_rose.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_curve_fitter.cpp Projects/Libraries/qwt-6.0.1/src/qwt_curve_fitter.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_double_range.cpp Projects/Libraries/qwt-6.0.1/src/qwt_double_range.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_dyngrid_layout.h Projects/Libraries/qwt-6.0.1/src/qwt_dyngrid_layout.h
cp ../../Libraries/qwt-6.0.1/src/qwt_picker_machine.h Projects/Libraries/qwt-6.0.1/src/qwt_picker_machine.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_histogram.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_histogram.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_magnifier.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_magnifier.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_scaleitem.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_scaleitem.h
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_engine.cpp Projects/Libraries/qwt-6.0.1/src/qwt_scale_engine.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_widget.cpp Projects/Libraries/qwt-6.0.1/src/qwt_scale_widget.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_system_clock.cpp Projects/Libraries/qwt-6.0.1/src/qwt_system_clock.cpp
cp ../../Classes/CppKalmanFilter/kalmanfilterexample.h Projects/Classes/CppKalmanFilter/kalmanfilterexample.h
cp ../../Classes/CppKalmanFilter/kalmanfilterfactory.h Projects/Classes/CppKalmanFilter/kalmanfilterfactory.h
cp ../../Classes/CppKalmanFilter/kalmanfiltertypes.cpp Projects/Classes/CppKalmanFilter/kalmanfiltertypes.cpp
cp ../../Classes/CppQtModel/qtstdvectorfunctionmodel.h Projects/Classes/CppQtModel/qtstdvectorfunctionmodel.h
cp ../../Classes/CppQtModel/qtstdvectorstringmodel.cpp Projects/Classes/CppQtModel/qtstdvectorstringmodel.cpp
cp ../../Classes/CppQtModel/qtublasmatrixdoublemodel.h Projects/Classes/CppQtModel/qtublasmatrixdoublemodel.h
cp ../../Classes/CppQtModel/qtublasvectordoublemodel.h Projects/Classes/CppQtModel/qtublasvectordoublemodel.h
cp ../../Libraries/boost_1_53_0/libs/regex/src/icu.cpp Projects/Libraries/boost_1_53_0/libs/regex/src/icu.cpp
cp ../../Libraries/qwt-6.0.1/include/qwt_dial_needle.h Projects/Libraries/qwt-6.0.1/include/qwt_dial_needle.h
cp ../../Libraries/qwt-6.0.1/include/qwt_legend_item.h Projects/Libraries/qwt-6.0.1/include/qwt_legend_item.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_canvas.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_canvas.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_layout.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_layout.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_marker.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_marker.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_panner.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_panner.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_picker.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_picker.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_zoomer.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_zoomer.h
cp ../../Libraries/qwt-6.0.1/include/qwt_point_polar.h Projects/Libraries/qwt-6.0.1/include/qwt_point_polar.h
cp ../../Libraries/qwt-6.0.1/include/qwt_raster_data.h Projects/Libraries/qwt-6.0.1/include/qwt_raster_data.h
cp ../../Libraries/qwt-6.0.1/include/qwt_series_data.h Projects/Libraries/qwt-6.0.1/include/qwt_series_data.h
cp ../../Libraries/qwt-6.0.1/include/qwt_text_engine.h Projects/Libraries/qwt-6.0.1/include/qwt_text_engine.h
cp ../../Libraries/qwt-6.0.1/src/qwt_abstract_slider.h Projects/Libraries/qwt-6.0.1/src/qwt_abstract_slider.h
cp ../../Libraries/qwt-6.0.1/src/qwt_column_symbol.cpp Projects/Libraries/qwt-6.0.1/src/qwt_column_symbol.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_event_pattern.cpp Projects/Libraries/qwt-6.0.1/src/qwt_event_pattern.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_interval_symbol.h Projects/Libraries/qwt-6.0.1/src/qwt_interval_symbol.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_rasteritem.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_rasteritem.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_renderer.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_renderer.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_rescaler.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_rescaler.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_seriesitem.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_seriesitem.h
cp ../../Libraries/qwt-6.0.1/src/qwt_sampling_thread.h Projects/Libraries/qwt-6.0.1/src/qwt_sampling_thread.h
cp ../../Classes/CppKalmanFilter/standardkalmanfilter.h Projects/Classes/CppKalmanFilter/standardkalmanfilter.h
cp ../../Classes/CppKalmanFilter/whitenoisesystemtype.h Projects/Classes/CppKalmanFilter/whitenoisesystemtype.h
cp ../../Libraries/qwt-6.0.1/include/qwt_analog_clock.h Projects/Libraries/qwt-6.0.1/include/qwt_analog_clock.h
cp ../../Libraries/qwt-6.0.1/include/qwt_arrow_button.h Projects/Libraries/qwt-6.0.1/include/qwt_arrow_button.h
cp ../../Libraries/qwt-6.0.1/include/qwt_compass_rose.h Projects/Libraries/qwt-6.0.1/include/qwt_compass_rose.h
cp ../../Libraries/qwt-6.0.1/include/qwt_curve_fitter.h Projects/Libraries/qwt-6.0.1/include/qwt_curve_fitter.h
cp ../../Libraries/qwt-6.0.1/include/qwt_double_range.h Projects/Libraries/qwt-6.0.1/include/qwt_double_range.h
cp ../../Libraries/qwt-6.0.1/include/qwt_scale_engine.h Projects/Libraries/qwt-6.0.1/include/qwt_scale_engine.h
cp ../../Libraries/qwt-6.0.1/include/qwt_scale_widget.h Projects/Libraries/qwt-6.0.1/include/qwt_scale_widget.h
cp ../../Libraries/qwt-6.0.1/include/qwt_system_clock.h Projects/Libraries/qwt-6.0.1/include/qwt_system_clock.h
cp ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale.cpp Projects/Libraries/qwt-6.0.1/src/qwt_abstract_scale.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_dyngrid_layout.cpp Projects/Libraries/qwt-6.0.1/src/qwt_dyngrid_layout.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_null_paintdevice.h Projects/Libraries/qwt-6.0.1/src/qwt_null_paintdevice.h
cp ../../Libraries/qwt-6.0.1/src/qwt_picker_machine.cpp Projects/Libraries/qwt-6.0.1/src/qwt_picker_machine.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_histogram.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_histogram.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_magnifier.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_magnifier.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_scaleitem.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_scaleitem.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_round_scale_draw.h Projects/Libraries/qwt-6.0.1/src/qwt_round_scale_draw.h
cp ../../Classes/CppKalmanFilter/kalmanfilterexample.cpp Projects/Classes/CppKalmanFilter/kalmanfilterexample.cpp
cp ../../Classes/CppKalmanFilter/kalmanfilterfactory.cpp Projects/Classes/CppKalmanFilter/kalmanfilterfactory.cpp
cp ../../Classes/CppKalmanFilter/kalmanfilterparameter.h Projects/Classes/CppKalmanFilter/kalmanfilterparameter.h
cp ../../Classes/CppKalmanFilter/whitenoisesystemtypes.h Projects/Classes/CppKalmanFilter/whitenoisesystemtypes.h
cp ../../Classes/CppQtModel/qtstdvectorfunctionmodel.cpp Projects/Classes/CppQtModel/qtstdvectorfunctionmodel.cpp
cp ../../Classes/CppQtModel/qtublasmatrixdoublemodel.cpp Projects/Classes/CppQtModel/qtublasmatrixdoublemodel.cpp
cp ../../Classes/CppQtModel/qtublasvectordoublemodel.cpp Projects/Classes/CppQtModel/qtublasvectordoublemodel.cpp
cp ../../Libraries/boost_1_53_0/libs/regex/src/regex.cpp Projects/Libraries/boost_1_53_0/libs/regex/src/regex.cpp
cp ../../Libraries/qwt-6.0.1/include/qwt_column_symbol.h Projects/Libraries/qwt-6.0.1/include/qwt_column_symbol.h
cp ../../Libraries/qwt-6.0.1/include/qwt_event_pattern.h Projects/Libraries/qwt-6.0.1/include/qwt_event_pattern.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_renderer.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_renderer.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_rescaler.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_rescaler.h
cp ../../Libraries/qwt-6.0.1/src/qwt_abstract_slider.cpp Projects/Libraries/qwt-6.0.1/src/qwt_abstract_slider.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_interval_symbol.cpp Projects/Libraries/qwt-6.0.1/src/qwt_interval_symbol.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_rasteritem.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_rasteritem.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_seriesitem.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_seriesitem.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_spectrocurve.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_spectrocurve.h
cp ../../Libraries/qwt-6.0.1/src/qwt_sampling_thread.cpp Projects/Libraries/qwt-6.0.1/src/qwt_sampling_thread.cpp
cp ../../Tools/ToolKalmanFilterer/ToolKalmanFilterer.qrc Projects/Tools/ToolKalmanFilterer/ToolKalmanFilterer.qrc
cp ../../Tools/ToolKalmanFilterer/qtcopyalltablewidget.h Projects/Tools/ToolKalmanFilterer/qtcopyalltablewidget.h
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterdialog.h Projects/Tools/ToolKalmanFilterer/qtkalmanfilterdialog.h
cp ../../Classes/CppKalmanFilter/kalmanfilterexperiment.h Projects/Classes/CppKalmanFilter/kalmanfilterexperiment.h
cp ../../Classes/CppKalmanFilter/kalmanfilterparameters.h Projects/Classes/CppKalmanFilter/kalmanfilterparameters.h
cp ../../Classes/CppKalmanFilter/laggedwhitenoisesystem.h Projects/Classes/CppKalmanFilter/laggedwhitenoisesystem.h
cp ../../Classes/CppKalmanFilter/standardkalmanfilter.cpp Projects/Classes/CppKalmanFilter/standardkalmanfilter.cpp
cp ../../Classes/CppKalmanFilter/whitenoisesystemtype.cpp Projects/Classes/CppKalmanFilter/whitenoisesystemtype.cpp
cp ../../Libraries/boost_1_53_0/libs/regex/src/cregex.cpp Projects/Libraries/boost_1_53_0/libs/regex/src/cregex.cpp
cp ../../Libraries/qwt-6.0.1/include/qwt_abstract_scale.h Projects/Libraries/qwt-6.0.1/include/qwt_abstract_scale.h
cp ../../Libraries/qwt-6.0.1/include/qwt_dyngrid_layout.h Projects/Libraries/qwt-6.0.1/include/qwt_dyngrid_layout.h
cp ../../Libraries/qwt-6.0.1/include/qwt_picker_machine.h Projects/Libraries/qwt-6.0.1/include/qwt_picker_machine.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_histogram.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_histogram.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_magnifier.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_magnifier.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_scaleitem.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_scaleitem.h
cp ../../Libraries/qwt-6.0.1/src/qwt_legend_itemmanager.h Projects/Libraries/qwt-6.0.1/src/qwt_legend_itemmanager.h
cp ../../Libraries/qwt-6.0.1/src/qwt_matrix_raster_data.h Projects/Libraries/qwt-6.0.1/src/qwt_matrix_raster_data.h
cp ../../Libraries/qwt-6.0.1/src/qwt_null_paintdevice.cpp Projects/Libraries/qwt-6.0.1/src/qwt_null_paintdevice.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_directpainter.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_directpainter.h
cp ../../Libraries/qwt-6.0.1/src/qwt_round_scale_draw.cpp Projects/Libraries/qwt-6.0.1/src/qwt_round_scale_draw.cpp
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterdialog.ui Projects/Tools/ToolKalmanFilterer/qtkalmanfilterdialog.ui
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterermodel.h Projects/Tools/ToolKalmanFilterer/qtkalmanfilterermodel.h
cp ../../Classes/CppKalmanFilter/kalmanfilterparameter.cpp Projects/Classes/CppKalmanFilter/kalmanfilterparameter.cpp
cp ../../Classes/CppKalmanFilter/steadystatekalmanfilter.h Projects/Classes/CppKalmanFilter/steadystatekalmanfilter.h
cp ../../Classes/CppKalmanFilter/whitenoisesystemfactory.h Projects/Classes/CppKalmanFilter/whitenoisesystemfactory.h
cp ../../Classes/CppKalmanFilter/whitenoisesystemtypes.cpp Projects/Classes/CppKalmanFilter/whitenoisesystemtypes.cpp
cp ../../Libraries/fparser4.5.1/extrasrc/fp_opcode_add.inc Projects/Libraries/fparser4.5.1/extrasrc/fp_opcode_add.inc
cp ../../Libraries/qwt-6.0.1/include/qwt_abstract_slider.h Projects/Libraries/qwt-6.0.1/include/qwt_abstract_slider.h
cp ../../Libraries/qwt-6.0.1/include/qwt_interval_symbol.h Projects/Libraries/qwt-6.0.1/include/qwt_interval_symbol.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_rasteritem.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_rasteritem.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_seriesitem.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_seriesitem.h
cp ../../Libraries/qwt-6.0.1/include/qwt_sampling_thread.h Projects/Libraries/qwt-6.0.1/include/qwt_sampling_thread.h
cp ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale_draw.h Projects/Libraries/qwt-6.0.1/src/qwt_abstract_scale_draw.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_spectrocurve.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_spectrocurve.cpp
cp ../../Tools/ToolKalmanFilterer/crosscompiletowindows.sh Projects/Tools/ToolKalmanFilterer/crosscompiletowindows.sh
cp ../../Tools/ToolKalmanFilterer/qtcopyalltablewidget.cpp Projects/Tools/ToolKalmanFilterer/qtcopyalltablewidget.cpp
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterdialog.cpp Projects/Tools/ToolKalmanFilterer/qtkalmanfilterdialog.cpp
cp ../../Classes/CppKalmanFilter/kalmanfilterexperiment.cpp Projects/Classes/CppKalmanFilter/kalmanfilterexperiment.cpp
cp ../../Classes/CppKalmanFilter/kalmanfilterparameters.cpp Projects/Classes/CppKalmanFilter/kalmanfilterparameters.cpp
cp ../../Classes/CppKalmanFilter/laggedwhitenoisesystem.cpp Projects/Classes/CppKalmanFilter/laggedwhitenoisesystem.cpp
cp ../../Classes/CppKalmanFilter/standardwhitenoisesystem.h Projects/Classes/CppKalmanFilter/standardwhitenoisesystem.h
cp ../../Libraries/boost_1_53_0/libs/regex/src/fileiter.cpp Projects/Libraries/boost_1_53_0/libs/regex/src/fileiter.cpp
cp ../../Libraries/qwt-6.0.1/include/qwt_null_paintdevice.h Projects/Libraries/qwt-6.0.1/include/qwt_null_paintdevice.h
cp ../../Libraries/qwt-6.0.1/include/qwt_round_scale_draw.h Projects/Libraries/qwt-6.0.1/include/qwt_round_scale_draw.h
cp ../../Libraries/qwt-6.0.1/src/qwt_matrix_raster_data.cpp Projects/Libraries/qwt-6.0.1/src/qwt_matrix_raster_data.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_directpainter.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_directpainter.cpp
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterermodel.cpp Projects/Tools/ToolKalmanFilterer/qtkalmanfilterermodel.cpp
cp ../../Classes/CppKalmanFilter/kalmanfilterparametertype.h Projects/Classes/CppKalmanFilter/kalmanfilterparametertype.h
cp ../../Classes/CppKalmanFilter/steadystatekalmanfilter.cpp Projects/Classes/CppKalmanFilter/steadystatekalmanfilter.cpp
cp ../../Classes/CppKalmanFilter/whitenoisesystemfactory.cpp Projects/Classes/CppKalmanFilter/whitenoisesystemfactory.cpp
cp ../../Classes/CppKalmanFilter/whitenoisesystemparameter.h Projects/Classes/CppKalmanFilter/whitenoisesystemparameter.h
cp ../../Libraries/boost_1_53_0/libs/filesystem/src/path.cpp Projects/Libraries/boost_1_53_0/libs/filesystem/src/path.cpp
cp ../../Libraries/boost_1_53_0/libs/regex/src/instances.cpp Projects/Libraries/boost_1_53_0/libs/regex/src/instances.cpp
cp ../../Libraries/boost_1_53_0/libs/regex/src/internals.hpp Projects/Libraries/boost_1_53_0/libs/regex/src/internals.hpp
cp ../../Libraries/boost_1_53_0/libs/regex/src/posix_api.cpp Projects/Libraries/boost_1_53_0/libs/regex/src/posix_api.cpp
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_spectrocurve.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_spectrocurve.h
cp ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale_draw.cpp Projects/Libraries/qwt-6.0.1/src/qwt_abstract_scale_draw.cpp
cp ../../Tools/ToolKalmanFilterer/kalmanfilterermenudialog.h Projects/Tools/ToolKalmanFilterer/kalmanfilterermenudialog.h
cp ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystem.h Projects/Classes/CppKalmanFilter/gapsfilledwhitenoisesystem.h
cp ../../Classes/CppKalmanFilter/standardwhitenoisesystem.cpp Projects/Classes/CppKalmanFilter/standardwhitenoisesystem.cpp
cp ../../Classes/CppKalmanFilter/whitenoisesystemparameters.h Projects/Classes/CppKalmanFilter/whitenoisesystemparameters.h
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h Projects/Classes/CppQtHideAndShowDialog/qthideandshowdialog.h
cp ../../Libraries/boost_1_53_0/libs/regex/src/winstances.cpp Projects/Libraries/boost_1_53_0/libs/regex/src/winstances.cpp
cp ../../Libraries/qwt-6.0.1/include/qwt_legend_itemmanager.h Projects/Libraries/qwt-6.0.1/include/qwt_legend_itemmanager.h
cp ../../Libraries/qwt-6.0.1/include/qwt_mathml_text_engine.h Projects/Libraries/qwt-6.0.1/include/qwt_mathml_text_engine.h
cp ../../Libraries/qwt-6.0.1/include/qwt_matrix_raster_data.h Projects/Libraries/qwt-6.0.1/include/qwt_matrix_raster_data.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_directpainter.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_directpainter.h
cp ../../Classes/CppKalmanFilter/kalmanfilterparametertype.cpp Projects/Classes/CppKalmanFilter/kalmanfilterparametertype.cpp
cp ../../Classes/CppKalmanFilter/standardkalmanfilterfactory.h Projects/Classes/CppKalmanFilter/standardkalmanfilterfactory.h
cp ../../Classes/CppKalmanFilter/whitenoisesystemparameter.cpp Projects/Classes/CppKalmanFilter/whitenoisesystemparameter.cpp
cp ../../Libraries/boost_1_53_0/libs/regex/src/regex_debug.cpp Projects/Libraries/boost_1_53_0/libs/regex/src/regex_debug.cpp
cp ../../Libraries/boost_1_53_0/libs/regex/src/usinstances.cpp Projects/Libraries/boost_1_53_0/libs/regex/src/usinstances.cpp
cp ../../Libraries/boost_1_53_0/libs/system/src/error_code.cpp Projects/Libraries/boost_1_53_0/libs/system/src/error_code.cpp
cp ../../Libraries/qwt-6.0.1/include/qwt_abstract_scale_draw.h Projects/Libraries/qwt-6.0.1/include/qwt_abstract_scale_draw.h
cp ../../Tools/ToolKalmanFilterer/kalmanfilterermenudialog.cpp Projects/Tools/ToolKalmanFilterer/kalmanfilterermenudialog.cpp
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterermaindialog.h Projects/Tools/ToolKalmanFilterer/qtkalmanfilterermaindialog.h
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterermenudialog.h Projects/Tools/ToolKalmanFilterer/qtkalmanfilterermenudialog.h
cp ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilter.h Projects/Classes/CppKalmanFilter/fixedlagsmootherkalmanfilter.h
cp ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystem.cpp Projects/Classes/CppKalmanFilter/gapsfilledwhitenoisesystem.cpp
cp ../../Classes/CppKalmanFilter/whitenoisesystemparameters.cpp Projects/Classes/CppKalmanFilter/whitenoisesystemparameters.cpp
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp Projects/Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp
cp ../../Libraries/boost_1_53_0/libs/regex/src/static_mutex.cpp Projects/Libraries/boost_1_53_0/libs/regex/src/static_mutex.cpp
cp ../../Tools/ToolKalmanFilterer/ToolKalmanFiltererDesktop.pro Projects/Tools/ToolKalmanFilterer/ToolKalmanFiltererDesktop.pro
cp ../../Tools/ToolKalmanFilterer/ToolKalmanFiltererWelcome.png Projects/Tools/ToolKalmanFilterer/ToolKalmanFiltererWelcome.png
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterermaindialog.ui Projects/Tools/ToolKalmanFilterer/qtkalmanfilterermaindialog.ui
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterermenudialog.ui Projects/Tools/ToolKalmanFilterer/qtkalmanfilterermenudialog.ui
cp ../../Classes/CppKalmanFilter/laggedwhitenoisesystemfactory.h Projects/Classes/CppKalmanFilter/laggedwhitenoisesystemfactory.h
cp ../../Classes/CppKalmanFilter/standardkalmanfilterfactory.cpp Projects/Classes/CppKalmanFilter/standardkalmanfilterfactory.cpp
cp ../../Classes/CppKalmanFilter/whitenoisesystemparametertype.h Projects/Classes/CppKalmanFilter/whitenoisesystemparametertype.h
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterermaindialog.cpp Projects/Tools/ToolKalmanFilterer/qtkalmanfilterermaindialog.cpp
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterermenudialog.cpp Projects/Tools/ToolKalmanFilterer/qtkalmanfilterermenudialog.cpp
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterexamplesdialog.h Projects/Tools/ToolKalmanFilterer/qtkalmanfilterexamplesdialog.h
cp ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilter.cpp Projects/Classes/CppKalmanFilter/fixedlagsmootherkalmanfilter.cpp
cp ../../Classes/CppKalmanFilter/standardkalmanfilterparameters.h Projects/Classes/CppKalmanFilter/standardkalmanfilterparameters.h
cp ../../Classes/CppKalmanFilter/steadystatekalmanfilterfactory.h Projects/Classes/CppKalmanFilter/steadystatekalmanfilterfactory.h
cp ../../Libraries/boost_1_53_0/libs/regex/src/c_regex_traits.cpp Projects/Libraries/boost_1_53_0/libs/regex/src/c_regex_traits.cpp
cp ../../Libraries/boost_1_53_0/libs/regex/src/wide_posix_api.cpp Projects/Libraries/boost_1_53_0/libs/regex/src/wide_posix_api.cpp
cp ../../Libraries/fparser4.5.1/extrasrc/fp_identifier_parser.inc Projects/Libraries/fparser4.5.1/extrasrc/fp_identifier_parser.inc
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterexamplesdialog.ui Projects/Tools/ToolKalmanFilterer/qtkalmanfilterexamplesdialog.ui
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterexperimentmodel.h Projects/Tools/ToolKalmanFilterer/qtkalmanfilterexperimentmodel.h
cp ../../Classes/CppKalmanFilter/kalmanfiltercalculationelements.h Projects/Classes/CppKalmanFilter/kalmanfiltercalculationelements.h
cp ../../Classes/CppKalmanFilter/kalmanfilterexperimentparameter.h Projects/Classes/CppKalmanFilter/kalmanfilterexperimentparameter.h
cp ../../Classes/CppKalmanFilter/laggedwhitenoisesystemfactory.cpp Projects/Classes/CppKalmanFilter/laggedwhitenoisesystemfactory.cpp
cp ../../Classes/CppKalmanFilter/standardwhitenoisesystemfactory.h Projects/Classes/CppKalmanFilter/standardwhitenoisesystemfactory.h
cp ../../Classes/CppKalmanFilter/whitenoisesystemparametertype.cpp Projects/Classes/CppKalmanFilter/whitenoisesystemparametertype.cpp
cp ../../Libraries/boost_1_53_0/libs/filesystem/src/operations.cpp Projects/Libraries/boost_1_53_0/libs/filesystem/src/operations.cpp
cp ../../Libraries/boost_1_53_0/libs/regex/src/wc_regex_traits.cpp Projects/Libraries/boost_1_53_0/libs/regex/src/wc_regex_traits.cpp
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterexamplesdialog.cpp Projects/Tools/ToolKalmanFilterer/qtkalmanfilterexamplesdialog.cpp
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterexperimentdialog.h Projects/Tools/ToolKalmanFilterer/qtkalmanfilterexperimentdialog.h
cp ../../Classes/CppKalmanFilter/laggedwhitenoisesystemparameters.h Projects/Classes/CppKalmanFilter/laggedwhitenoisesystemparameters.h
cp ../../Classes/CppKalmanFilter/standardkalmanfilterparameters.cpp Projects/Classes/CppKalmanFilter/standardkalmanfilterparameters.cpp
cp ../../Classes/CppKalmanFilter/steadystatekalmanfilterfactory.cpp Projects/Classes/CppKalmanFilter/steadystatekalmanfilterfactory.cpp
cp ../../Libraries/boost_1_53_0/libs/filesystem/src/path_traits.cpp Projects/Libraries/boost_1_53_0/libs/filesystem/src/path_traits.cpp
cp ../../Libraries/boost_1_53_0/libs/filesystem/src/portability.cpp Projects/Libraries/boost_1_53_0/libs/filesystem/src/portability.cpp
cp ../../Libraries/boost_1_53_0/libs/filesystem/src/unique_path.cpp Projects/Libraries/boost_1_53_0/libs/filesystem/src/unique_path.cpp
cp ../../Libraries/boost_1_53_0/libs/regex/src/cpp_regex_traits.cpp Projects/Libraries/boost_1_53_0/libs/regex/src/cpp_regex_traits.cpp
cp ../../Libraries/boost_1_53_0/libs/regex/src/regex_raw_buffer.cpp Projects/Libraries/boost_1_53_0/libs/regex/src/regex_raw_buffer.cpp
cp ../../Libraries/boost_1_53_0/libs/regex/src/w32_regex_traits.cpp Projects/Libraries/boost_1_53_0/libs/regex/src/w32_regex_traits.cpp
cp ../../Tools/ToolKalmanFilterer/qtkalmanfiltercalculationdialog.h Projects/Tools/ToolKalmanFilterer/qtkalmanfiltercalculationdialog.h
cp ../../Tools/ToolKalmanFilterer/qtkalmanfiltererparameterdialog.h Projects/Tools/ToolKalmanFilterer/qtkalmanfiltererparameterdialog.h
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterexperimentdialog.ui Projects/Tools/ToolKalmanFilterer/qtkalmanfilterexperimentdialog.ui
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterexperimentmodel.cpp Projects/Tools/ToolKalmanFilterer/qtkalmanfilterexperimentmodel.cpp
cp ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystemfactory.h Projects/Classes/CppKalmanFilter/gapsfilledwhitenoisesystemfactory.h
cp ../../Classes/CppKalmanFilter/kalmanfiltercalculationelements.cpp Projects/Classes/CppKalmanFilter/kalmanfiltercalculationelements.cpp
cp ../../Classes/CppKalmanFilter/kalmanfilterexperimentparameter.cpp Projects/Classes/CppKalmanFilter/kalmanfilterexperimentparameter.cpp
cp ../../Classes/CppKalmanFilter/standardwhitenoisesystemfactory.cpp Projects/Classes/CppKalmanFilter/standardwhitenoisesystemfactory.cpp
cp ../../Classes/CppKalmanFilter/steadystatekalmanfilterparameters.h Projects/Classes/CppKalmanFilter/steadystatekalmanfilterparameters.h
cp ../../Tools/ToolKalmanFilterer/qtkalmanfiltercalculationdialog.ui Projects/Tools/ToolKalmanFilterer/qtkalmanfiltercalculationdialog.ui
cp ../../Tools/ToolKalmanFilterer/qtkalmanfiltererparameterdialog.ui Projects/Tools/ToolKalmanFilterer/qtkalmanfiltererparameterdialog.ui
cp ../../Tools/ToolKalmanFilterer/qtkalmanfilterexperimentdialog.cpp Projects/Tools/ToolKalmanFilterer/qtkalmanfilterexperimentdialog.cpp
cp ../../Classes/CppKalmanFilter/laggedwhitenoisesystemparameters.cpp Projects/Classes/CppKalmanFilter/laggedwhitenoisesystemparameters.cpp
cp ../../Classes/CppKalmanFilter/standardwhitenoisesystemparameters.h Projects/Classes/CppKalmanFilter/standardwhitenoisesystemparameters.h
cp ../../Tools/ToolKalmanFilterer/qtkalmanfiltercalculationdialog.cpp Projects/Tools/ToolKalmanFilterer/qtkalmanfiltercalculationdialog.cpp
cp ../../Tools/ToolKalmanFilterer/qtkalmanfiltererparameterdialog.cpp Projects/Tools/ToolKalmanFilterer/qtkalmanfiltererparameterdialog.cpp
cp ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterfactory.h Projects/Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterfactory.h
cp ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystemfactory.cpp Projects/Classes/CppKalmanFilter/gapsfilledwhitenoisesystemfactory.cpp
cp ../../Classes/CppKalmanFilter/kalmanfilterexperimentparametertype.h Projects/Classes/CppKalmanFilter/kalmanfilterexperimentparametertype.h
cp ../../Classes/CppKalmanFilter/steadystatekalmanfilterparameters.cpp Projects/Classes/CppKalmanFilter/steadystatekalmanfilterparameters.cpp
cp ../../Tools/ToolKalmanFilterer/qtwhitenoisesystemparametersdialog.h Projects/Tools/ToolKalmanFilterer/qtwhitenoisesystemparametersdialog.h
cp ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystemparameters.h Projects/Classes/CppKalmanFilter/gapsfilledwhitenoisesystemparameters.h
cp ../../Classes/CppKalmanFilter/standardwhitenoisesystemparameters.cpp Projects/Classes/CppKalmanFilter/standardwhitenoisesystemparameters.cpp
cp ../../Tools/ToolKalmanFilterer/qtwhitenoisesystemparametersdialog.ui Projects/Tools/ToolKalmanFilterer/qtwhitenoisesystemparametersdialog.ui
cp ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterfactory.cpp Projects/Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterfactory.cpp
cp ../../Classes/CppKalmanFilter/kalmanfilterexperimentparametertype.cpp Projects/Classes/CppKalmanFilter/kalmanfilterexperimentparametertype.cpp
cp ../../Libraries/boost_1_53_0/libs/regex/src/regex_traits_defaults.cpp Projects/Libraries/boost_1_53_0/libs/regex/src/regex_traits_defaults.cpp
cp ../../Tools/ToolKalmanFilterer/qtwhitenoisesystemparametersdialog.cpp Projects/Tools/ToolKalmanFilterer/qtwhitenoisesystemparametersdialog.cpp
cp ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterparameters.h Projects/Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterparameters.h
cp ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystemparameters.cpp Projects/Classes/CppKalmanFilter/gapsfilledwhitenoisesystemparameters.cpp
cp ../../Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.h Projects/Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.h
cp ../../Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.h Projects/Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.h
cp ../../Libraries/boost_1_53_0/libs/filesystem/src/utf8_codecvt_facet.cpp Projects/Libraries/boost_1_53_0/libs/filesystem/src/utf8_codecvt_facet.cpp
cp ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterparameters.cpp Projects/Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterparameters.cpp
cp ../../Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.cpp Projects/Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.cpp
cp ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/greg_month.cpp Projects/Libraries/boost_1_53_0/libs/date_time/src/gregorian/greg_month.cpp
cp ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/greg_names.hpp Projects/Libraries/boost_1_53_0/libs/date_time/src/gregorian/greg_names.hpp
cp ../../Tools/ToolKalmanFilterer/qtstandardkalmanfiltercalculationdialog.h Projects/Tools/ToolKalmanFilterer/qtstandardkalmanfiltercalculationdialog.h
cp ../../Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.cpp Projects/Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.cpp
cp ../../Libraries/boost_1_53_0/libs/filesystem/src/windows_file_codecvt.cpp Projects/Libraries/boost_1_53_0/libs/filesystem/src/windows_file_codecvt.cpp
cp ../../Libraries/boost_1_53_0/libs/filesystem/src/windows_file_codecvt.hpp Projects/Libraries/boost_1_53_0/libs/filesystem/src/windows_file_codecvt.hpp
cp ../../Tools/ToolKalmanFilterer/qtstandardkalmanfiltercalculationdialog.ui Projects/Tools/ToolKalmanFilterer/qtstandardkalmanfiltercalculationdialog.ui
cp ../../Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.h Projects/Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.h
cp ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/greg_weekday.cpp Projects/Libraries/boost_1_53_0/libs/date_time/src/gregorian/greg_weekday.cpp
cp ../../Libraries/boost_1_53_0/libs/system/src/local_free_on_destruction.hpp Projects/Libraries/boost_1_53_0/libs/system/src/local_free_on_destruction.hpp
cp ../../Tools/ToolKalmanFilterer/qtstandardkalmanfiltercalculationdialog.cpp Projects/Tools/ToolKalmanFilterer/qtstandardkalmanfiltercalculationdialog.cpp
cp ../../Libraries/boost_1_53_0/libs/filesystem/src/codecvt_error_category.cpp Projects/Libraries/boost_1_53_0/libs/filesystem/src/codecvt_error_category.cpp
cp ../../Tools/ToolKalmanFilterer/qtsteadystatekalmanfiltercalculationdialog.h Projects/Tools/ToolKalmanFilterer/qtsteadystatekalmanfiltercalculationdialog.h
cp ../../Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.cpp Projects/Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.cpp
cp ../../Tools/ToolKalmanFilterer/qtsteadystatekalmanfiltercalculationdialog.ui Projects/Tools/ToolKalmanFilterer/qtsteadystatekalmanfiltercalculationdialog.ui
cp ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/date_generators.cpp Projects/Libraries/boost_1_53_0/libs/date_time/src/gregorian/date_generators.cpp
cp ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/gregorian_types.cpp Projects/Libraries/boost_1_53_0/libs/date_time/src/gregorian/gregorian_types.cpp
cp ../../Tools/ToolKalmanFilterer/qtsteadystatekalmanfiltercalculationdialog.cpp Projects/Tools/ToolKalmanFilterer/qtsteadystatekalmanfiltercalculationdialog.cpp
cp ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.h Projects/Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.h
cp ../../Tools/ToolKalmanFilterer/qtfixedlagsmootherkalmanfiltercalculationdialog.h Projects/Tools/ToolKalmanFilterer/qtfixedlagsmootherkalmanfiltercalculationdialog.h
cp ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.cpp Projects/Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.cpp
cp ../../Tools/ToolKalmanFilterer/qtfixedlagsmootherkalmanfiltercalculationdialog.ui Projects/Tools/ToolKalmanFilterer/qtfixedlagsmootherkalmanfiltercalculationdialog.ui
cp ../../Tools/ToolKalmanFilterer/qtfixedlagsmootherkalmanfiltercalculationdialog.cpp Projects/Tools/ToolKalmanFilterer/qtfixedlagsmootherkalmanfiltercalculationdialog.cpp

FILENAME="../../Tools/ToolKalmanFiltererSource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

zip -r $FILENAME Projects

echo "Cleaning up"

echo "Emptying subfolders"

rm Projects/Libraries/boost_1_53_0/libs/date_time/src/gregorian/*.*
rm Projects/Libraries/boost_1_53_0/libs/filesystem/src/*.*
rm Projects/Libraries/boost_1_53_0/libs/date_time/src/*.*
rm Projects/Libraries/boost_1_53_0/libs/system/src/*.*
rm Projects/Libraries/boost_1_53_0/libs/filesystem/*.*
rm Projects/Libraries/boost_1_53_0/libs/regex/src/*.*
rm Projects/Libraries/boost_1_53_0/libs/date_time/*.*
rm Projects/Libraries/boost_1_53_0/libs/system/*.*
rm Projects/Libraries/boost_1_53_0/libs/regex/*.*
rm Projects/Libraries/fparser4.5.1/extrasrc/*.*
rm Projects/Classes/CppQtHideAndShowDialog/*.*
rm Projects/Libraries/qwt-6.0.1/include/*.*
rm Projects/Libraries/boost_1_53_0/libs/*.*
rm Projects/Tools/ToolKalmanFilterer/*.*
rm Projects/Classes/CppQtAboutDialog/*.*
rm Projects/Libraries/qwt-6.0.1/src/*.*
rm Projects/Classes/CppKalmanFilter/*.*
rm Projects/Libraries/fparser4.5.1/*.*
rm Projects/Libraries/boost_1_53_0/*.*
rm Projects/Libraries/qwt-6.0.1/*.*
rm Projects/Classes/CppQtMatrix/*.*
rm Projects/Classes/CppQtModel/*.*
rm Projects/Classes/CppMatrix/*.*
rm Projects/Classes/CppTrace/*.*
rm Projects/Classes/CppAbout/*.*
rm Projects/Libraries/*.*
rm Projects/Classes/*.*
rm Projects/Tools/*.*
rm Projects/*.*
rmdir Projects/Libraries/boost_1_53_0/libs/date_time/src/gregorian
rmdir Projects/Libraries/boost_1_53_0/libs/filesystem/src
rmdir Projects/Libraries/boost_1_53_0/libs/date_time/src
rmdir Projects/Libraries/boost_1_53_0/libs/system/src
rmdir Projects/Libraries/boost_1_53_0/libs/filesystem
rmdir Projects/Libraries/boost_1_53_0/libs/regex/src
rmdir Projects/Libraries/boost_1_53_0/libs/date_time
rmdir Projects/Libraries/boost_1_53_0/libs/system
rmdir Projects/Libraries/boost_1_53_0/libs/regex
rmdir Projects/Libraries/fparser4.5.1/extrasrc
rmdir Projects/Classes/CppQtHideAndShowDialog
rmdir Projects/Libraries/qwt-6.0.1/include
rmdir Projects/Libraries/boost_1_53_0/libs
rmdir Projects/Tools/ToolKalmanFilterer
rmdir Projects/Classes/CppQtAboutDialog
rmdir Projects/Libraries/qwt-6.0.1/src
rmdir Projects/Classes/CppKalmanFilter
rmdir Projects/Libraries/fparser4.5.1
rmdir Projects/Libraries/boost_1_53_0
rmdir Projects/Libraries/qwt-6.0.1
rmdir Projects/Classes/CppQtMatrix
rmdir Projects/Classes/CppQtModel
rmdir Projects/Classes/CppMatrix
rmdir Projects/Classes/CppTrace
rmdir Projects/Classes/CppAbout
rmdir Projects/Libraries
rmdir Projects/Classes
rmdir Projects/Tools
rmdir Projects

echo "Done"

# QtCreatorProFileZipScript, version 1.0
# Copyright (C) 2013 Richel Bilderbeek
# Programmed on the 19th of May 2013
# by Richel Bilderbeek
# 
# QtCreatorProFileZipScript can be downloaded from http://www.richelbilderbeek.nl/CppQtCreatorProFileZipScript.htm
# Licenced under GPL 3.0

