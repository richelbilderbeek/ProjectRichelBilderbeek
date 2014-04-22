//---------------------------------------------------------------------------

#ifndef UnitLoopReaderH
#define UnitLoopReaderH
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl/CppLoopReader.htm
// Reads a container in a loop:
//   when the end is reached, it starts
//   reading from the beginning again
template <class Iterator>
struct LoopReader
{
  LoopReader(const Iterator begin, const Iterator end)
    : begin_(begin), read_(begin), end_(end)
  {

  }
  
  const Iterator Read() const { return read_; }

  void Next()
  {
    ++read_;
    if (read_ == end_) read_ = begin_;
  }

  private:
  const Iterator begin_;
  const Iterator end_;
  Iterator read_;
};

#endif
 