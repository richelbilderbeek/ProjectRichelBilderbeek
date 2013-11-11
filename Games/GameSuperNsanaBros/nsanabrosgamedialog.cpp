#include "nsanabrosgamedialog.h"
#include "nsanabroskeyswidget.h"

ribi::NsanaBrosGameDialog::NsanaBrosGameDialog(
  const boost::shared_ptr<const NsanaBrosOptions> options)
  : m_area{},
    m_keys{},
    m_options(options)

{
  //d->m_signal_close.connect(
  //  boost::bind(
  //  &WtTestAsciiArterDialog::ShowMain,
  //  this));

}

ribi::NsanaBrosGameDialog::~NsanaBrosGameDialog() noexcept
{

}


