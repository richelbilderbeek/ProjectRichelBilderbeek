DEFINES += BOOST_SIGNALS_NO_DEPRECATION_WARNING

exists(../../Classes/CppWtAboutDialog/CppWtAboutDialog.pri) {
  include(../../Classes/CppWtAboutDialog/CppWtAboutDialog.pri)
  include(../../Classes/CppWtAutoConfig/CppWtAutoConfig.pri)
}

exists(../Classes/CppWtAboutDialog/CppWtAboutDialog.pri) {
  include(../Classes/CppWtAboutDialog/CppWtAboutDialog.pri)
  include(../Classes/CppWtAutoConfig/CppWtAutoConfig.pri)
}
