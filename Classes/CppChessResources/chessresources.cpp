#include "chessresources.h"

#include <algorithm>
#include <cassert>
#include <thread>

#include <boost/filesystem.hpp>
#include <boost/scoped_ptr.hpp>

#include "chesscolor.h"
#include "chesspiece.h"
#include "chesssquare.h"
#include "trace.h"

namespace Chess {

//Resources * Resources::m_instance = 0;

const std::string Resources::Find(
  const boost::shared_ptr<const Chess::Piece>& piece,
  const Chess::Color selection_color,
  const bool big)
{
  #ifndef NDEBUG
  Test();
  #endif

  assert(piece);
  std::string filename;

  //Piece its color
  assert(piece->GetColor() != Color::indeterminate);
  if (piece->GetColor() == Color::black) filename+="b";
  if (piece->GetColor() == Color::white) filename+="w";

  //Piece its type
  if (dynamic_cast<const PieceBishop*>(piece.get())) filename+="b";
  if (dynamic_cast<const PieceKing*  >(piece.get())) filename+="k";
  if (dynamic_cast<const PieceKnight*>(piece.get())) filename+="n";
  if (dynamic_cast<const PiecePawn*  >(piece.get())) filename+="p";
  if (dynamic_cast<const PieceQueen* >(piece.get())) filename+="q";
  if (dynamic_cast<const PieceRook*  >(piece.get())) filename+="r";

  //The square the piece is standing on
  assert(piece->GetSquare()->GetColor() != Color::indeterminate);
  if (piece->GetSquare()->GetColor() == Color::black) filename+="ds";
  if (piece->GetSquare()->GetColor() == Color::white) filename+="ls";

  //The selection color
  assert(selection_color != Color::black);
  assert(selection_color != Color::white);
  if (selection_color == Color::indeterminate) {;}
  if (selection_color == Color::red) filename+="r";
  if (selection_color == Color::green) filename+="g";
  if (selection_color == Color::blue) filename+="b";

  if (big) filename+="_big";

  filename+=".png";

  assert(!filename.empty() && "Assume there is a graphic for the piece");
  if (!boost::filesystem::exists(filename)) { TRACE(filename); }
  assert(boost::filesystem::exists(filename));
  return filename;
}

const std::string Resources::Find(
  const Chess::Square& square,
  const Chess::Color selection_color)
{
  #ifndef NDEBUG
  Test();
  #endif

  std::string filename;

  //The square
  assert(square.GetColor() != Color::indeterminate);
  if (square.GetColor() == Color::black) filename+="ds";
  if (square.GetColor() == Color::white) filename+="ls";

  //The selection color
  assert(selection_color != Color::black);
  assert(selection_color != Color::white);
  if (selection_color == Color::indeterminate) {;}
  if (selection_color == Color::red) filename+="r";
  if (selection_color == Color::green) filename+="g";
  if (selection_color == Color::blue) filename+="b";

  filename+=".png";

  assert(!filename.empty() && "Assume there is a graphic for the piece");
  if (!boost::filesystem::exists(filename)) { TRACE(filename); }
  assert(boost::filesystem::exists(filename));
  return filename;
}

const std::vector<std::string> Resources::GetFilenames()
{
  #ifndef NDEBUG
  //Test(); //Cannot do this: QtResources calls this member function to create the resources

  #endif

  std::vector<std::string> filenames;

  for (int i=0; i!=2*6*2*4*2; ++i)
  {
    int j = i;
    std::string filename;



    //Piece its color
    if (j % 2 == 0) filename+="b";
    if (j % 2 == 1) filename+="w";

    j/=2;

    //Piece its type
    if (j % 6 == 0) filename+="b";
    if (j % 6 == 1) filename+="k";
    if (j % 6 == 2) filename+="n";
    if (j % 6 == 3) filename+="p";
    if (j % 6 == 4) filename+="q";
    if (j % 6 == 5) filename+="r";

    j/=6;

    //The square the piece is standing on
    if (j % 2 == 0) filename+="ds";
    if (j % 2 == 1) filename+="ls";

    j/=2;

    //The selection color
    if (j % 4 == 0) {;}
    if (j % 4 == 1) filename+="r";
    if (j % 4 == 2) filename+="g";
    if (j % 4 == 3) filename+="b";

    j/= 4;

    //Bigger or not?
    if (j % 2 == 0) {;}
    if (j % 2 == 1) filename+="_big";

    filename+=".png";
    filenames.push_back(filename);
  }

  for (int i=0; i!=2*4; ++i)
  {
    int j = i;
    std::string filename;

    //The square
    if (j % 2 == 0) filename+="ds";
    if (j % 2 == 1) filename+="ls";

    j/=2;

    //The selection color
    if (j % 4 == 0) {;}
    if (j % 4 == 1) filename+="r";
    if (j % 4 == 2) filename+="g";
    if (j % 4 == 3) filename+="b";

    filename+=".png";
    filenames.push_back(filename);
  }

  filenames.push_back("question_mark.png");

  return filenames;
}

const std::string Resources::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> Resources::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2012-01-25: version 1.0: initial version");
  v.push_back("2012-02-07: version 1.1: added resources for selection");
  return v;
}

/*
Resources * Resources::Get()
{
  if (m_instance == 0)
  {
    m_instance = new Resources;
  }
  return m_instance;
}
*/

void Resources::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  std::thread t(
    []
    {
      const std::vector<std::string> filenames = GetFilenames();

      std::for_each(filenames.begin(),filenames.end(),
        [](const std::string& s)
        {
          if (!boost::filesystem::exists(s))
          {
            TRACE(s);
          }
          assert(boost::filesystem::exists(s));
        }
      );
    }
  );
  t.join();
}

} //~namespace Chess

