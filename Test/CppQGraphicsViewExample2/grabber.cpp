#include "grabber.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QImage>
#include <QPixmap>
#pragma GCC diagnostic pop

Grabber::Grabber(
  const int win_id,
  const std::string& filename
)
  : m_filename{filename},
    m_win_id{win_id}
{

}

Grabber::~Grabber() noexcept {}

void Grabber::Grab() const noexcept
{
  const QImage screenshot{QPixmap::grabWindow(m_win_id).toImage()};
  screenshot.save(m_filename.c_str());
}
