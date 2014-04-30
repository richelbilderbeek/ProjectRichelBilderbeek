win32 {
  # Windows only
  message("CLN, built for Windows")
}

macx {
  # Mac only
  message("CLN, built for Mac")
}

unix:!macx {
  # Linux only
  message("CLN, built for Linux")
}

cross_compile {
  # Crosscompile only
  message("CLN, built for cross-compiling from Linux to Windows")
}
