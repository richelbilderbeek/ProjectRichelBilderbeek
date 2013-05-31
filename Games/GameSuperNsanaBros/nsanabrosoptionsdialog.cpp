//---------------------------------------------------------------------------
#include "nsanabrosstlheader.h"
//---------------------------------------------------------------------------
NsanaBrosOptionsDialog::NsanaBrosOptionsDialog()
  : m_options(new NsanaBrosOptions)
{
}
//---------------------------------------------------------------------------
const NsanaBrosOptions * NsanaBrosOptionsDialog::GetOptions() const
{
  return m_options.get();
}
//---------------------------------------------------------------------------
//boost::shared_ptr<NsanaBrosOptions> NsanaBrosOptionsDialog::UseOptions()
//{
//  return m_options;
//}
//---------------------------------------------------------------------------


