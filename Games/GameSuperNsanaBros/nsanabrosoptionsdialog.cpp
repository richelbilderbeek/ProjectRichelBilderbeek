
#include "nsanabrosstlheader.h"

ribi::NsanaBrosOptionsDialog::NsanaBrosOptionsDialog()
  : m_options(new NsanaBrosOptions)
{
}

const boost::shared_ptr<const ribi::NsanaBrosOptions> ribi::NsanaBrosOptionsDialog::GetOptions() const
{
  return m_options;
}

//boost::shared_ptr<NsanaBrosOptions> NsanaBrosOptionsDialog::UseOptions()
//{
//  return m_options;
//}



