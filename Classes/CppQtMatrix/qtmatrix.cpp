#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtmatrix.h"

#include <cassert>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <QTableWidget>

#include "trace.h"

#pragma GCC diagnostic pop

std::string ribi::QtMatrix::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::QtMatrix::GetVersionHistory() noexcept
{
  return {
    "2013-04-28: version 1.0: initial version",
    "2013-05-13: version 1.1: improved support for empty tables/vectors/matrices"
  };
}

void ribi::QtMatrix::MatrixToTable(const boost::numeric::ublas::matrix<double>& m, QTableWidget * const table)
{
  //
  assert(table);
  //assert(m.size1() >= 0); //Inevitable for std::size_t
  //assert(m.size2() >= 0); //Inevitable for std::size_t
  const std::size_t n_rows = m.size1();
  const std::size_t n_cols = m.size2();
  table->setRowCount(   boost::numeric_cast<int>(m.size1()));
  table->setColumnCount(boost::numeric_cast<int>(m.size2()));
  assert(table->rowCount()    == boost::numeric_cast<int>(m.size1()));
  assert(table->columnCount() == boost::numeric_cast<int>(m.size2()));
  for (std::size_t row=0; row!=n_rows; ++row)
  {
    for (std::size_t col=0; col!=n_cols; ++col)
    {
      QTableWidgetItem * const item = new QTableWidgetItem;
      assert(row < m.size1());
      assert(col < m.size2());
      item->setText(boost::lexical_cast<std::string>(m(row,col)).c_str());
      table->setItem(row,col,item);
    }
  }
  //
  assert((m.size1() == 0 && m.size2() == 0)
    || boost::numeric::ublas::detail::equals(ToMatrix(table),m,0.00001,0.00001));
}

void ribi::QtMatrix::StrVectorToTable(const std::vector<std::string>& v, QTableWidget * const table)
{
  assert(table);
  if (v.empty())
  {
    table->setRowCount(0);
    table->setColumnCount(0);
    return;
  }
  assert(!v.empty());
  const int sz = boost::numeric_cast<int>(v.size());
  table->setRowCount(sz);
  table->setColumnCount(1);
  assert(table->rowCount() == sz);
  assert(table->columnCount() == 1);
  for (int i=0; i!=sz; ++i)
  {
    QTableWidgetItem * const item = new QTableWidgetItem;
    assert(item);
    assert(i < boost::numeric_cast<int>(v.size()));
    assert(i < table->rowCount());
    assert(table->rowCount() == sz);
    const std::string s = v[i];
    item->setText(s.c_str());
    assert(table->rowCount() == sz);
    table->setItem(i,0,item);
    assert(table);
    assert(table->rowCount() == sz); //FAILS???
  }
  assert(table->rowCount() == sz);
  assert(ribi::QtMatrix::ToStrVector(table) == v);
}


void ribi::QtMatrix::StdVectorDoubleToTable(const std::vector<double>& v, QTableWidget * const table)
{
  
  boost::numeric::ublas::vector<double> w(v.size());
  assert(w.size() == v.size());
  std::copy(v.begin(),v.end(),w.begin());
  assert(v.empty()    || v[0] == w(0));
  assert(v.size() < 1 || v[1] == w(1));
  assert(v.size() < 2 || v[2] == w(2));
  assert(v.size() < 3 || v[3] == w(3));
  
  UblasVectorDoubleToTable(w,table);
}

void ribi::QtMatrix::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef REALLY_WANNA_CHECK_2463986504397503
  {
    const std::vector<std::string> v = {};
    QTableWidget * const table = new QTableWidget;
    StrVectorToTable(v,table);
    assert(table->rowCount() == 0);
    assert(table->columnCount() == 0);
  }
  {
    const std::vector<std::string> v = { "X" };
    QTableWidget * const table = new QTableWidget;
    StrVectorToTable(v,table);
    assert(table->rowCount() == 1);
    assert(table->columnCount() == 1);
  }
  {
    const std::vector<std::string> v = { "A","B" };
    QTableWidget * const table = new QTableWidget;
    StrVectorToTable(v,table);
    assert(table->rowCount() == 2);
    assert(table->columnCount() == 1);
  }
  {
    const std::vector<std::string> v = { "A","BB","CCC" };
    QTableWidget * const table = new QTableWidget;
    StrVectorToTable(v,table);
    assert(table->rowCount() == 3);
    assert(table->columnCount() == 1);
  }
  #endif
}

const boost::numeric::ublas::matrix<double> ribi::QtMatrix::ToMatrix(const QTableWidget * const table)
{
  assert(table);
  const int n_rows = table->rowCount();    //n_rows can be zero
  const int n_cols = table->columnCount(); //n_cols can be zero

  boost::numeric::ublas::matrix<double> v(n_rows,n_cols);

  for(int col=0;col!=n_cols;++col)
  {
    for(int row=0;row!=n_rows;++row)
    {
      assert(row < boost::numeric_cast<int>(v.size1()));
      assert(col < boost::numeric_cast<int>(v.size2()));
      const auto item = table->item(row,col);
      if (item)
      {
        const std::string text = item->text().toStdString();
        v(row,col) = boost::lexical_cast<double>(text);
      }
      else
      {
        v(row,col) = 0.0;
      }
    }
  }

  return v;
}

std::vector<std::string> ribi::QtMatrix::ToStrVector(const QTableWidget * const table)
{
  assert(table);
  if (table->rowCount() == 0) { return std::vector<std::string>(); }
  assert(table->columnCount() == 1);
  const int n_rows = table->rowCount(); //n_rows can be zero
  std::vector<std::string> v;
  for (int row=0; row!=n_rows; ++row)
  {
    assert(row < table->rowCount());
    const QTableWidgetItem * const item = table->item(row,0);
    const std::string s = item ? item->text().toStdString() : std::string();
    v.push_back(s);
  }
  assert(table->rowCount() == boost::numeric_cast<int>(v.size()));
  return v;
}

const boost::numeric::ublas::vector<double> ribi::QtMatrix::ToVector(const QTableWidget * const table)
{
  
  assert(table);
  const int n_rows = table->rowCount(); //n_rows can be zero
  boost::numeric::ublas::vector<double> v(n_rows);
  for(int row=0;row!=n_rows;++row)
  {
    const auto item = table->item(row,0);
    if (item)
    {
      const std::string text = item->text().toStdString();
      assert(row < boost::numeric_cast<int>(v.size()));
      v(row) = boost::lexical_cast<double>(text);
    }
    else
    {
      assert(row < boost::numeric_cast<int>(v.size()));
      v(row) = 0.0;
    }
  }
  
  return v;
}

void ribi::QtMatrix::UblasVectorDoubleToTable(const boost::numeric::ublas::vector<double>& v, QTableWidget * const table)
{

  assert(table);
  if (v.empty())
  {
    table->setRowCount(0);
    table->setColumnCount(0);
    return;
  }
  assert(!v.empty());
  table->setRowCount(boost::numeric_cast<int>(v.size()));
  table->setColumnCount(1);
  assert(table->rowCount() == boost::numeric_cast<int>(v.size()));
  assert(table->columnCount() == 1);
  const int sz = boost::numeric_cast<int>(v.size());
  for (int i=0; i!=sz; ++i)
  {
    QTableWidgetItem * const item = new QTableWidgetItem;
    assert(item);
    assert(i < boost::numeric_cast<int>(v.size()));
    assert(i < table->rowCount());
    try
    {
      const std::string s = boost::lexical_cast<std::string>(v[i]);
      item->setText(s.c_str());
    }
    catch(boost::bad_lexical_cast& e)
    {
      assert(!"Should never get here: conversion from double to std::string must always succeed");
    }
    table->setItem(i,0,item);
  }

  assert(boost::numeric::ublas::detail::equals(ToVector(table),v,0.00001,0.00001));

}

