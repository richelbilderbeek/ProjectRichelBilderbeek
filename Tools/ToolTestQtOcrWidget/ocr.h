#ifndef OCR_H
#define OCR_H

#include <string>
//#include <utility>
//#include <vector>

#include <boost/shared_ptr.hpp>

namespace tesseract { struct TessBaseAPI; }

///OCR is an adapter for Tesseract
struct Ocr
{
  Ocr(const std::string& data_path,
  const std::string& whitelist);
  const std::string Read(
    const unsigned char * const image_data,
    const int bytes_per_pixel,
    const int bytes_per_line,
    const int left,
    const int top,
    const int width,
    const int height) const;

  private:
  const boost::shared_ptr<tesseract::TessBaseAPI> m_api;
};

#endif // OCR_H
