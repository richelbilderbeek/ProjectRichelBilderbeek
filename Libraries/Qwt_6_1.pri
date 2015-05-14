win32 {
  # Windows only
  message("Qwt 6.1, built for Windows")

  greaterThan(QT_MAJOR_VERSION, 4): QT += widgets concurrent opengl printsupport

  INCLUDEPATH += \
      ../../Libraries/qwt-6.1/src

  HEADERS += \
      ../../Libraries/qwt-6.1/src/qwt_widget_overlay.h \
      ../../Libraries/qwt-6.1/src/qwt_wheel.h \
      ../../Libraries/qwt-6.1/src/qwt_transform.h \
      ../../Libraries/qwt-6.1/src/qwt_thermo.h \
      ../../Libraries/qwt-6.1/src/qwt_text_label.h \
      ../../Libraries/qwt-6.1/src/qwt_text_engine.h \
      ../../Libraries/qwt-6.1/src/qwt_text.h \
      ../../Libraries/qwt-6.1/src/qwt_system_clock.h \
      ../../Libraries/qwt-6.1/src/qwt_symbol.h \
      ../../Libraries/qwt-6.1/src/qwt_spline.h \
      ../../Libraries/qwt-6.1/src/qwt_slider.h \
      ../../Libraries/qwt-6.1/src/qwt_series_store.h \
      ../../Libraries/qwt-6.1/src/qwt_series_data.h \
      ../../Libraries/qwt-6.1/src/qwt_scale_widget.h \
      ../../Libraries/qwt-6.1/src/qwt_scale_map.h \
      ../../Libraries/qwt-6.1/src/qwt_scale_engine.h \
      ../../Libraries/qwt-6.1/src/qwt_scale_draw.h \
      ../../Libraries/qwt-6.1/src/qwt_scale_div.h \
      ../../Libraries/qwt-6.1/src/qwt_sampling_thread.h \
      ../../Libraries/qwt-6.1/src/qwt_samples.h \
      ../../Libraries/qwt-6.1/src/qwt_round_scale_draw.h \
      ../../Libraries/qwt-6.1/src/qwt_raster_data.h \
      ../../Libraries/qwt-6.1/src/qwt_point_polar.h \
      ../../Libraries/qwt-6.1/src/qwt_point_mapper.h \
      ../../Libraries/qwt-6.1/src/qwt_point_data.h \
      ../../Libraries/qwt-6.1/src/qwt_point_3d.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_zoomer.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_zoneitem.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_tradingcurve.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_textlabel.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_svgitem.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_spectrogram.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_spectrocurve.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_shapeitem.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_seriesitem.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_scaleitem.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_rescaler.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_renderer.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_rasteritem.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_picker.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_panner.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_multi_barchart.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_marker.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_magnifier.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_legenditem.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_layout.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_item.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_intervalcurve.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_histogram.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_grid.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_glcanvas.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_directpainter.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_dict.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_curve.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_canvas.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_barchart.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_abstract_barchart.h \
      ../../Libraries/qwt-6.1/src/qwt_plot.h \
      ../../Libraries/qwt-6.1/src/qwt_pixel_matrix.h \
      ../../Libraries/qwt-6.1/src/qwt_picker_machine.h \
      ../../Libraries/qwt-6.1/src/qwt_picker.h \
      ../../Libraries/qwt-6.1/src/qwt_panner.h \
      ../../Libraries/qwt-6.1/src/qwt_painter_command.h \
      ../../Libraries/qwt-6.1/src/qwt_painter.h \
      ../../Libraries/qwt-6.1/src/qwt_null_paintdevice.h \
      ../../Libraries/qwt-6.1/src/qwt_matrix_raster_data.h \
      ../../Libraries/qwt-6.1/src/qwt_math.h \
      ../../Libraries/qwt-6.1/src/qwt_magnifier.h \
      ../../Libraries/qwt-6.1/src/qwt_legend_label.h \
      ../../Libraries/qwt-6.1/src/qwt_legend_data.h \
      ../../Libraries/qwt-6.1/src/qwt_legend.h \
      ../../Libraries/qwt-6.1/src/qwt_knob.h \
      ../../Libraries/qwt-6.1/src/qwt_interval_symbol.h \
      ../../Libraries/qwt-6.1/src/qwt_interval.h \
      ../../Libraries/qwt-6.1/src/qwt_graphic.h \
      ../../Libraries/qwt-6.1/src/qwt_global.h \
      ../../Libraries/qwt-6.1/src/qwt_event_pattern.h \
      ../../Libraries/qwt-6.1/src/qwt_dyngrid_layout.h \
      ../../Libraries/qwt-6.1/src/qwt_dial_needle.h \
      ../../Libraries/qwt-6.1/src/qwt_dial.h \
      ../../Libraries/qwt-6.1/src/qwt_date_scale_engine.h \
      ../../Libraries/qwt-6.1/src/qwt_date_scale_draw.h \
      ../../Libraries/qwt-6.1/src/qwt_date.h \
      ../../Libraries/qwt-6.1/src/qwt_curve_fitter.h \
      ../../Libraries/qwt-6.1/src/qwt_counter.h \
      ../../Libraries/qwt-6.1/src/qwt_compat.h \
      ../../Libraries/qwt-6.1/src/qwt_compass_rose.h \
      ../../Libraries/qwt-6.1/src/qwt_compass.h \
      ../../Libraries/qwt-6.1/src/qwt_column_symbol.h \
      ../../Libraries/qwt-6.1/src/qwt_color_map.h \
      ../../Libraries/qwt-6.1/src/qwt_clipper.h \
      ../../Libraries/qwt-6.1/src/qwt_arrow_button.h \
      ../../Libraries/qwt-6.1/src/qwt_analog_clock.h \
      ../../Libraries/qwt-6.1/src/qwt_abstract_slider.h \
      ../../Libraries/qwt-6.1/src/qwt_abstract_scale_draw.h \
      ../../Libraries/qwt-6.1/src/qwt_abstract_scale.h \
      ../../Libraries/qwt-6.1/src/qwt_abstract_legend.h \
      ../../Libraries/qwt-6.1/src/qwt.h

  SOURCES += \
      ../../Libraries/qwt-6.1/src/qwt_widget_overlay.cpp \
      ../../Libraries/qwt-6.1/src/qwt_wheel.cpp \
      ../../Libraries/qwt-6.1/src/qwt_transform.cpp \
      ../../Libraries/qwt-6.1/src/qwt_thermo.cpp \
      ../../Libraries/qwt-6.1/src/qwt_text_label.cpp \
      ../../Libraries/qwt-6.1/src/qwt_text_engine.cpp \
      ../../Libraries/qwt-6.1/src/qwt_text.cpp \
      ../../Libraries/qwt-6.1/src/qwt_system_clock.cpp \
      ../../Libraries/qwt-6.1/src/qwt_symbol.cpp \
      ../../Libraries/qwt-6.1/src/qwt_spline.cpp \
      ../../Libraries/qwt-6.1/src/qwt_slider.cpp \
      ../../Libraries/qwt-6.1/src/qwt_series_data.cpp \
      ../../Libraries/qwt-6.1/src/qwt_scale_widget.cpp \
      ../../Libraries/qwt-6.1/src/qwt_scale_map.cpp \
      ../../Libraries/qwt-6.1/src/qwt_scale_engine.cpp \
      ../../Libraries/qwt-6.1/src/qwt_scale_draw.cpp \
      ../../Libraries/qwt-6.1/src/qwt_scale_div.cpp \
      ../../Libraries/qwt-6.1/src/qwt_sampling_thread.cpp \
      ../../Libraries/qwt-6.1/src/qwt_round_scale_draw.cpp \
      ../../Libraries/qwt-6.1/src/qwt_raster_data.cpp \
      ../../Libraries/qwt-6.1/src/qwt_point_polar.cpp \
      ../../Libraries/qwt-6.1/src/qwt_point_mapper.cpp \
      ../../Libraries/qwt-6.1/src/qwt_point_data.cpp \
      ../../Libraries/qwt-6.1/src/qwt_point_3d.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_zoomer.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_zoneitem.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_xml.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_tradingcurve.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_textlabel.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_svgitem.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_spectrogram.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_spectrocurve.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_shapeitem.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_seriesitem.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_scaleitem.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_rescaler.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_renderer.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_rasteritem.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_picker.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_panner.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_multi_barchart.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_marker.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_magnifier.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_legenditem.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_layout.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_item.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_intervalcurve.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_histogram.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_grid.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_glcanvas.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_directpainter.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_dict.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_curve.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_canvas.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_barchart.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_axis.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_abstract_barchart.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot.cpp \
      ../../Libraries/qwt-6.1/src/qwt_pixel_matrix.cpp \
      ../../Libraries/qwt-6.1/src/qwt_picker_machine.cpp \
      ../../Libraries/qwt-6.1/src/qwt_picker.cpp \
      ../../Libraries/qwt-6.1/src/qwt_panner.cpp \
      ../../Libraries/qwt-6.1/src/qwt_painter_command.cpp \
      ../../Libraries/qwt-6.1/src/qwt_painter.cpp \
      ../../Libraries/qwt-6.1/src/qwt_null_paintdevice.cpp \
      ../../Libraries/qwt-6.1/src/qwt_matrix_raster_data.cpp \
      ../../Libraries/qwt-6.1/src/qwt_math.cpp \
      ../../Libraries/qwt-6.1/src/qwt_magnifier.cpp \
      ../../Libraries/qwt-6.1/src/qwt_legend_label.cpp \
      ../../Libraries/qwt-6.1/src/qwt_legend_data.cpp \
      ../../Libraries/qwt-6.1/src/qwt_legend.cpp \
      ../../Libraries/qwt-6.1/src/qwt_knob.cpp \
      ../../Libraries/qwt-6.1/src/qwt_interval_symbol.cpp \
      ../../Libraries/qwt-6.1/src/qwt_interval.cpp \
      ../../Libraries/qwt-6.1/src/qwt_graphic.cpp \
      ../../Libraries/qwt-6.1/src/qwt_event_pattern.cpp \
      ../../Libraries/qwt-6.1/src/qwt_dyngrid_layout.cpp \
      ../../Libraries/qwt-6.1/src/qwt_dial_needle.cpp \
      ../../Libraries/qwt-6.1/src/qwt_dial.cpp \
      ../../Libraries/qwt-6.1/src/qwt_date_scale_engine.cpp \
      ../../Libraries/qwt-6.1/src/qwt_date_scale_draw.cpp \
      ../../Libraries/qwt-6.1/src/qwt_date.cpp \
      ../../Libraries/qwt-6.1/src/qwt_curve_fitter.cpp \
      ../../Libraries/qwt-6.1/src/qwt_counter.cpp \
      ../../Libraries/qwt-6.1/src/qwt_compass_rose.cpp \
      ../../Libraries/qwt-6.1/src/qwt_compass.cpp \
      ../../Libraries/qwt-6.1/src/qwt_column_symbol.cpp \
      ../../Libraries/qwt-6.1/src/qwt_color_map.cpp \
      ../../Libraries/qwt-6.1/src/qwt_clipper.cpp \
      ../../Libraries/qwt-6.1/src/qwt_arrow_button.cpp \
      ../../Libraries/qwt-6.1/src/qwt_analog_clock.cpp \
      ../../Libraries/qwt-6.1/src/qwt_abstract_slider.cpp \
      ../../Libraries/qwt-6.1/src/qwt_abstract_scale_draw.cpp \
      ../../Libraries/qwt-6.1/src/qwt_abstract_scale.cpp \
      ../../Libraries/qwt-6.1/src/qwt_abstract_legend.cpp


  # Option #2
  # INCLUDEPATH += ../../Libraries/qwt-6.1/src
  # LIBS+= -L../../Libraries/qwt-6.1/lib
  #
  # CONFIG(release, debug|release) {
  #   message("Qwt 6.1, built for Windows, release")
  #   LIBS += -lqwt
  # }
  #
  # CONFIG(debug, debug|release) {
  #   message("Qwt 6.1, built for Windows, debug")
  #   LIBS += -lqwtd
  # }
}

macx {
  # Mac only
  message("Qwt 6.1, built for Mac")
}

unix:!macx{
  # Linux only
  message("Qwt 6.1, built for Linux")

  greaterThan(QT_MAJOR_VERSION, 4): QT += widgets concurrent opengl printsupport

  INCLUDEPATH += \
      ../../Libraries/qwt-6.1/src

  HEADERS += \
      ../../Libraries/qwt-6.1/src/qwt_widget_overlay.h \
      ../../Libraries/qwt-6.1/src/qwt_wheel.h \
      ../../Libraries/qwt-6.1/src/qwt_transform.h \
      ../../Libraries/qwt-6.1/src/qwt_thermo.h \
      ../../Libraries/qwt-6.1/src/qwt_text_label.h \
      ../../Libraries/qwt-6.1/src/qwt_text_engine.h \
      ../../Libraries/qwt-6.1/src/qwt_text.h \
      ../../Libraries/qwt-6.1/src/qwt_system_clock.h \
      ../../Libraries/qwt-6.1/src/qwt_symbol.h \
      ../../Libraries/qwt-6.1/src/qwt_spline.h \
      ../../Libraries/qwt-6.1/src/qwt_slider.h \
      ../../Libraries/qwt-6.1/src/qwt_series_store.h \
      ../../Libraries/qwt-6.1/src/qwt_series_data.h \
      ../../Libraries/qwt-6.1/src/qwt_scale_widget.h \
      ../../Libraries/qwt-6.1/src/qwt_scale_map.h \
      ../../Libraries/qwt-6.1/src/qwt_scale_engine.h \
      ../../Libraries/qwt-6.1/src/qwt_scale_draw.h \
      ../../Libraries/qwt-6.1/src/qwt_scale_div.h \
      ../../Libraries/qwt-6.1/src/qwt_sampling_thread.h \
      ../../Libraries/qwt-6.1/src/qwt_samples.h \
      ../../Libraries/qwt-6.1/src/qwt_round_scale_draw.h \
      ../../Libraries/qwt-6.1/src/qwt_raster_data.h \
      ../../Libraries/qwt-6.1/src/qwt_point_polar.h \
      ../../Libraries/qwt-6.1/src/qwt_point_mapper.h \
      ../../Libraries/qwt-6.1/src/qwt_point_data.h \
      ../../Libraries/qwt-6.1/src/qwt_point_3d.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_zoomer.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_zoneitem.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_tradingcurve.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_textlabel.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_svgitem.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_spectrogram.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_spectrocurve.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_shapeitem.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_seriesitem.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_scaleitem.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_rescaler.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_renderer.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_rasteritem.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_picker.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_panner.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_multi_barchart.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_marker.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_magnifier.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_legenditem.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_layout.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_item.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_intervalcurve.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_histogram.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_grid.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_glcanvas.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_directpainter.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_dict.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_curve.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_canvas.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_barchart.h \
      ../../Libraries/qwt-6.1/src/qwt_plot_abstract_barchart.h \
      ../../Libraries/qwt-6.1/src/qwt_plot.h \
      ../../Libraries/qwt-6.1/src/qwt_pixel_matrix.h \
      ../../Libraries/qwt-6.1/src/qwt_picker_machine.h \
      ../../Libraries/qwt-6.1/src/qwt_picker.h \
      ../../Libraries/qwt-6.1/src/qwt_panner.h \
      ../../Libraries/qwt-6.1/src/qwt_painter_command.h \
      ../../Libraries/qwt-6.1/src/qwt_painter.h \
      ../../Libraries/qwt-6.1/src/qwt_null_paintdevice.h \
      ../../Libraries/qwt-6.1/src/qwt_matrix_raster_data.h \
      ../../Libraries/qwt-6.1/src/qwt_math.h \
      ../../Libraries/qwt-6.1/src/qwt_magnifier.h \
      ../../Libraries/qwt-6.1/src/qwt_legend_label.h \
      ../../Libraries/qwt-6.1/src/qwt_legend_data.h \
      ../../Libraries/qwt-6.1/src/qwt_legend.h \
      ../../Libraries/qwt-6.1/src/qwt_knob.h \
      ../../Libraries/qwt-6.1/src/qwt_interval_symbol.h \
      ../../Libraries/qwt-6.1/src/qwt_interval.h \
      ../../Libraries/qwt-6.1/src/qwt_graphic.h \
      ../../Libraries/qwt-6.1/src/qwt_global.h \
      ../../Libraries/qwt-6.1/src/qwt_event_pattern.h \
      ../../Libraries/qwt-6.1/src/qwt_dyngrid_layout.h \
      ../../Libraries/qwt-6.1/src/qwt_dial_needle.h \
      ../../Libraries/qwt-6.1/src/qwt_dial.h \
      ../../Libraries/qwt-6.1/src/qwt_date_scale_engine.h \
      ../../Libraries/qwt-6.1/src/qwt_date_scale_draw.h \
      ../../Libraries/qwt-6.1/src/qwt_date.h \
      ../../Libraries/qwt-6.1/src/qwt_curve_fitter.h \
      ../../Libraries/qwt-6.1/src/qwt_counter.h \
      ../../Libraries/qwt-6.1/src/qwt_compat.h \
      ../../Libraries/qwt-6.1/src/qwt_compass_rose.h \
      ../../Libraries/qwt-6.1/src/qwt_compass.h \
      ../../Libraries/qwt-6.1/src/qwt_column_symbol.h \
      ../../Libraries/qwt-6.1/src/qwt_color_map.h \
      ../../Libraries/qwt-6.1/src/qwt_clipper.h \
      ../../Libraries/qwt-6.1/src/qwt_arrow_button.h \
      ../../Libraries/qwt-6.1/src/qwt_analog_clock.h \
      ../../Libraries/qwt-6.1/src/qwt_abstract_slider.h \
      ../../Libraries/qwt-6.1/src/qwt_abstract_scale_draw.h \
      ../../Libraries/qwt-6.1/src/qwt_abstract_scale.h \
      ../../Libraries/qwt-6.1/src/qwt_abstract_legend.h \
      ../../Libraries/qwt-6.1/src/qwt.h

  SOURCES += \
      ../../Libraries/qwt-6.1/src/qwt_widget_overlay.cpp \
      ../../Libraries/qwt-6.1/src/qwt_wheel.cpp \
      ../../Libraries/qwt-6.1/src/qwt_transform.cpp \
      ../../Libraries/qwt-6.1/src/qwt_thermo.cpp \
      ../../Libraries/qwt-6.1/src/qwt_text_label.cpp \
      ../../Libraries/qwt-6.1/src/qwt_text_engine.cpp \
      ../../Libraries/qwt-6.1/src/qwt_text.cpp \
      ../../Libraries/qwt-6.1/src/qwt_system_clock.cpp \
      ../../Libraries/qwt-6.1/src/qwt_symbol.cpp \
      ../../Libraries/qwt-6.1/src/qwt_spline.cpp \
      ../../Libraries/qwt-6.1/src/qwt_slider.cpp \
      ../../Libraries/qwt-6.1/src/qwt_series_data.cpp \
      ../../Libraries/qwt-6.1/src/qwt_scale_widget.cpp \
      ../../Libraries/qwt-6.1/src/qwt_scale_map.cpp \
      ../../Libraries/qwt-6.1/src/qwt_scale_engine.cpp \
      ../../Libraries/qwt-6.1/src/qwt_scale_draw.cpp \
      ../../Libraries/qwt-6.1/src/qwt_scale_div.cpp \
      ../../Libraries/qwt-6.1/src/qwt_sampling_thread.cpp \
      ../../Libraries/qwt-6.1/src/qwt_round_scale_draw.cpp \
      ../../Libraries/qwt-6.1/src/qwt_raster_data.cpp \
      ../../Libraries/qwt-6.1/src/qwt_point_polar.cpp \
      ../../Libraries/qwt-6.1/src/qwt_point_mapper.cpp \
      ../../Libraries/qwt-6.1/src/qwt_point_data.cpp \
      ../../Libraries/qwt-6.1/src/qwt_point_3d.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_zoomer.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_zoneitem.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_xml.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_tradingcurve.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_textlabel.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_svgitem.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_spectrogram.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_spectrocurve.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_shapeitem.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_seriesitem.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_scaleitem.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_rescaler.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_renderer.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_rasteritem.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_picker.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_panner.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_multi_barchart.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_marker.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_magnifier.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_legenditem.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_layout.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_item.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_intervalcurve.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_histogram.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_grid.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_glcanvas.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_directpainter.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_dict.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_curve.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_canvas.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_barchart.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_axis.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot_abstract_barchart.cpp \
      ../../Libraries/qwt-6.1/src/qwt_plot.cpp \
      ../../Libraries/qwt-6.1/src/qwt_pixel_matrix.cpp \
      ../../Libraries/qwt-6.1/src/qwt_picker_machine.cpp \
      ../../Libraries/qwt-6.1/src/qwt_picker.cpp \
      ../../Libraries/qwt-6.1/src/qwt_panner.cpp \
      ../../Libraries/qwt-6.1/src/qwt_painter_command.cpp \
      ../../Libraries/qwt-6.1/src/qwt_painter.cpp \
      ../../Libraries/qwt-6.1/src/qwt_null_paintdevice.cpp \
      ../../Libraries/qwt-6.1/src/qwt_matrix_raster_data.cpp \
      ../../Libraries/qwt-6.1/src/qwt_math.cpp \
      ../../Libraries/qwt-6.1/src/qwt_magnifier.cpp \
      ../../Libraries/qwt-6.1/src/qwt_legend_label.cpp \
      ../../Libraries/qwt-6.1/src/qwt_legend_data.cpp \
      ../../Libraries/qwt-6.1/src/qwt_legend.cpp \
      ../../Libraries/qwt-6.1/src/qwt_knob.cpp \
      ../../Libraries/qwt-6.1/src/qwt_interval_symbol.cpp \
      ../../Libraries/qwt-6.1/src/qwt_interval.cpp \
      ../../Libraries/qwt-6.1/src/qwt_graphic.cpp \
      ../../Libraries/qwt-6.1/src/qwt_event_pattern.cpp \
      ../../Libraries/qwt-6.1/src/qwt_dyngrid_layout.cpp \
      ../../Libraries/qwt-6.1/src/qwt_dial_needle.cpp \
      ../../Libraries/qwt-6.1/src/qwt_dial.cpp \
      ../../Libraries/qwt-6.1/src/qwt_date_scale_engine.cpp \
      ../../Libraries/qwt-6.1/src/qwt_date_scale_draw.cpp \
      ../../Libraries/qwt-6.1/src/qwt_date.cpp \
      ../../Libraries/qwt-6.1/src/qwt_curve_fitter.cpp \
      ../../Libraries/qwt-6.1/src/qwt_counter.cpp \
      ../../Libraries/qwt-6.1/src/qwt_compass_rose.cpp \
      ../../Libraries/qwt-6.1/src/qwt_compass.cpp \
      ../../Libraries/qwt-6.1/src/qwt_column_symbol.cpp \
      ../../Libraries/qwt-6.1/src/qwt_color_map.cpp \
      ../../Libraries/qwt-6.1/src/qwt_clipper.cpp \
      ../../Libraries/qwt-6.1/src/qwt_arrow_button.cpp \
      ../../Libraries/qwt-6.1/src/qwt_analog_clock.cpp \
      ../../Libraries/qwt-6.1/src/qwt_abstract_slider.cpp \
      ../../Libraries/qwt-6.1/src/qwt_abstract_scale_draw.cpp \
      ../../Libraries/qwt-6.1/src/qwt_abstract_scale.cpp \
      ../../Libraries/qwt-6.1/src/qwt_abstract_legend.cpp

  # Option #2:
  #exists(/usr/include/qwt-qt4) {
  #  message("Qwt 6.1, built for Linux, use qwt-qt4")
  #  INCLUDEPATH += /usr/include/qwt-qt4
  #  #LIBS += -lqwt-qt4
  #  LIBS += -lqwt
  #}

  #exists(/usr/include/qwt) {
  #  message("Qwt 6.1, built for Linux, use qwt")
  #  INCLUDEPATH += /usr/include/qwt
  #  LIBS += -lqwt
  #}

  #INCLUDEPATH += /usr/include/qwt
  #LIBS += -lqwt


  # Option #3:
  #CONFIG(release, debug|release) {
  #  message("Qwt 6.1, built for Linux, release")
  #  LIBS += -lqwt
  #  INCLUDEPATH += /usr/include/qwt
  #}

  #CONFIG(debug, debug|release) {
  #  message("Qwt 6.1, built for Linux, debug")
  #  LIBS += -lqwt
  #  INCLUDEPATH += /usr/include/qwt
  #}
}
