unix {

  exists(/usr/include/qwt-qt4) {
    message(Linux: Qwt: use qwt-qt4)
    INCLUDEPATH += /usr/include/qwt-qt4
    LIBS += -lqwt-qt4
  }

  exists(/usr/include/qwt) {
    message(Linux: Qwt: link to qwt)
    INCLUDEPATH += /usr/include/qwt
    LIBS += -lqwt
  }

}

win32 {

  exists (../../Libraries/qwt-6.0.1/src) {
    message(Windows: Qwt: 6.0.1)
    INCLUDEPATH+= ../../Libraries/qwt-6.0.1/src
  }

  SOURCES += \
      ../../Libraries/qwt-6.0.1/src/qwt_wheel.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_thermo.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_text_label.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_text_engine.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_text.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_system_clock.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_symbol.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_spline.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_slider.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_series_data.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_scale_widget.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_scale_map.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_scale_engine.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_scale_draw.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_scale_div.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_sampling_thread.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_round_scale_draw.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_raster_data.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_point_polar.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_point_3d.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_zoomer.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_xml.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_spectrocurve.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_seriesitem.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_scaleitem.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_rescaler.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_renderer.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_rasteritem.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_picker.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_panner.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_marker.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_magnifier.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_layout.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_item.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_histogram.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_grid.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_directpainter.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_dict.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_curve.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_canvas.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot_axis.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_plot.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_picker_machine.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_picker.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_panner.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_painter.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_null_paintdevice.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_matrix_raster_data.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_math.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_magnifier.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_legend_item.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_legend.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_knob.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_interval_symbol.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_interval.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_event_pattern.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_dyngrid_layout.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_double_range.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_dial_needle.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_dial.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_curve_fitter.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_counter.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_compass_rose.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_compass.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_column_symbol.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_color_map.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_clipper.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_arrow_button.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_analog_clock.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_abstract_slider.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale_draw.cpp \
      ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale.cpp

}

