#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "ocr.h"

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include <QFile>

#include "tesseract-3.00/api/baseapi.h"
#pragma GCC diagnostic pop

Ocr::Ocr(
  const std::string& datafile,
  const std::string& whitelist)
  : m_api(new tesseract::TessBaseAPI)
{
  //assert(QFile::exists(datafile.c_str())); //Tesseract adds path

  const int success = m_api->Init(datafile.c_str(),"eng"); //English
  assert(success == 0);

  //CCUtil::main_setup(

  //tesseract::TessdataManager::Init(datafile.c_str());
  m_api->SetVariable("tessedit_char_whitelist", whitelist.c_str());
  //m_api->SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

const std::string Ocr::Read(
  const unsigned char * const image_data,
  const int bytes_per_pixel,
  const int bytes_per_line,
  const int left,
  const int top,
  const int width,
  const int height) const
{
  assert(width  > 0);
  assert(height > 0);

  const std::string text
    = m_api->TesseractRect(
    image_data,
    bytes_per_pixel,
    bytes_per_line,
    left,
    top,
    width,
    height);
  return text;
}
