#include "mydata.h"

MyData::MyData()
  : m_data(CreateData())
{
}

const std::vector<std::tuple<bool,bool,std::string> > MyData::CreateData()
{
  return
  {
    std::make_tuple(false,false,"Question A"),
    std::make_tuple(false,true ,"Question B"),
    std::make_tuple(true ,false,"Question C"),
    std::make_tuple(true ,true ,"Question D"),
  };
}
