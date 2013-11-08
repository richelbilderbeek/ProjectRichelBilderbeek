
#include <cassert>

#include "chessmoves.h"

const std::vector<std::string> ribi::Chess::Moves::GetGameKasparovVersusTheWorld()
{
  return
  {
    "e4"   , "c5"  , //1
    "Nf3"  , "d6"  , //2
    "Bb5+" , "Bd7" , //3
    "Bxd7+", "Qxd7", //4
    "c4"   , "Nc6" , //5
    "Nc3"  , "Nf6" , //6
    "0-0"  , "g6"  , //7
    "d4"   , "cxd4", //8
    "Nxd4" , "Bg7" , //9
    "Nde2" , "Qe6" , //10
    "Nd5"  , "Qxe4", //11
    "Nc7+" , "Kd7" , //12
    "Nxa8" , "Qxc4", //13
    "Nb6+" , "axb6", //14
    "Nc3"  , "Ra8" , //15
    "a4"   , "Ne4" , //16
    "Nxe4" , "Qxe4", //17
    "Qb3"  , "f5"  , //18
    "Bg5"  , "Qb4" , //19
    "Qf7"  , "Be5" , //20
    "h3"   , "Rxa4", //21
    "Rxa4" , "Qxa4", //22
    "Qxh7" , "Bxb2", //23
    "Qxg6" , "Qe4" , //24
    "Qf7"  , "Bd4" , //25
    "Qb3"  , "f4"  , //26
    "Qf7"  , "Be5" , //27
    "h4"   , "b5"  , //28
    "h5"   , "Qc4" , //29
    "Qf5+" , "Qe6" , //30
    "Qxe6+", "Kxe6", //31
    "g3"   , "fxg3", //32
    "fxg3" , "b4"  , //33
    "Bf4"  , "Bd4+", //34
    "Kh1"  , "b3"  , //35
    "g4"   , "Kd5" , //36
    "g5"   , "e6"  , //37
    "h6"   , "Ne7" , //38
    "Rd1"  , "e5"  , //39
    "Be3"  , "Kc4" , //40
    "Bxd4" , "exd4", //41
    "Kg2"  , "b2"  , //42
    "Kf3"  , "Kc3" , //43
    "h7"   , "Ng6" , //44
    "Ke4"  , "Kc2" , //45
    "Rh1"  , "d3"  , //46
    "Kf5"  , "b1Q" , //47
    "Rxb1" , "Kxb1", //48
    "Kxg6" , "d2"  , //49
    "h8Q"  , "d1Q" , //50
    "Qh7"  , "b5"  , //51
    "Kf6+" , "Kb2" , //52
    "Qh2+" , "Ka1" , //53
    "Qf4"  , "b4"  , //54
    "Qxb4" , "Qf3+", //55
    "Kg7"  , "d5"  , //56
    "Qd4+" , "Kb1" , //57
    "g6"   , "Qe4" , //58
    "Qg1+" , "Kb2" , //59
    "Qf2+" , "Kc1" , //60
    "Kf6"  , "d4"  , //61
    "g7"   , "1-0"   //62
  };
}

const std::vector<std::string> ribi::Chess::Moves::GetGameShephardsMate()
{
  return
  {
    "e2 e4", "e7 e5",
    "Bf1 c4", "a7 a6",
    "Qd1 f3", "a6 a5",
    "Qf3xf7#"
  };
}

const std::vector<std::string> ribi::Chess::Moves::GetInvalidBishopMoves()
{
  return
  {
    "Ba1 b1", "Ba1 a2", "Ba1xb1", "Ba1xa2","Ba1 h2","Ba1 b8",
    "Ba1 a1",
    "0-0" , "0-0-0" , "O-O" , "O-O-O" ,
    "0-0+", "0-0-0+", "O-O+", "O-O-O+",
    "0-0#", "0-0-0#", "O-O#", "O-O-O#",
    "1-0", "0-1", "1/2-1/2"
  };
}

const std::vector<std::string> ribi::Chess::Moves::GetInvalidCaptureMoves()
{
  return
  {

  };
}

const std::vector<std::string> ribi::Chess::Moves::GetInvalidCastlingMoves()
{
  return
  {

  };
}

const std::vector<std::string> ribi::Chess::Moves::GetInvalidEnPassantMoves()
{
  return
  {
    "d2 d3e.p.", "d2xd3e.p.", "d5 e6",
    "a5xb6" ,"b5xa6" ,"a4xb3" ,"b4xa3" ,
    "a5xb6+","b5xa6+","a4xb3+","b4xa3+",
    "a5xb6#","b5xa6#","a4xb3#","b4xa3#",
    "a5 b6e.p." ,"b5 a6e.p." ,"a4 b3e.p." ,"b4 a3e.p." ,
    "a5 b6e.p.+","b5 a6e.p.+","a4 b3e.p.+","b4 a3e.p.+",
    "a5 b6e.p.#","b5 a6e.p.#","a4 b3e.p.#","b4 a3e.p.#",
    "a4xb5e.p." ,"b4xa5e.p." ,"a5xb2e.p." ,"b5xa2e.p." ,
    "a4xb5e.p.+","b4xa5e.p.+","a5xb2e.p.+","b5xa2e.p.+",
    "a4xb5e.p.#","b4xa5e.p.#","a5xb2e.p.#","b5xa2e.p.#",
    "a6xb7e.p."
  };
}

const std::vector<std::string> ribi::Chess::Moves::GetInvalidKingMoves()
{
  return
  {
    "Kd4 b2", "Kd4 b3", "Kd4 b4", "Kd4 b5", "Kd4 b6",
    "Kd4 c1", "Kd4 c2", "Kd4 c6", "Kd4 c7",
    "Kd4 d1", "Kd4 d2", "Kd4 d4", "Kd4 d6", "Kd4 d7",
    "Kd4 e1", "Kd4 e2", "Kd4 e6", "Kd4 e7",
    "Kd4 f2", "Kd4 f3", "Kd4 f4", "Kd4 f5", "Kd4 f6",
    "Ka1 h8", "Ka1xh8", "Ka1 a8", "Ka1 a8",
    "0-0" , "0-0-0" , "O-O" , "O-O-O" ,
    "0-0+", "0-0-0+", "O-O+", "O-O-O+",
    "0-0#", "0-0-0#", "O-O#", "O-O-O#",
    "1-0", "0-1", "1/2-1/2"
  };
}

const std::vector<std::string> ribi::Chess::Moves::GetInvalidKnightMoves()
{
  return
  {
    "Nd4 d4",
    "Nd4 c3","Nd4 c4","Nd4 c5","Nd4 e3","Nd4 e4","Nd4 e5","Nd4 d3","Nd4 d5",
    "Nd4 b2","Nd4 f2","Nd4 f6","Nd4 b6",
    "Na1 h3","Na1 h7","Na1 g1","Na1 g8",
    "0-0" , "0-0-0" , "O-O" , "O-O-O" ,
    "0-0+", "0-0-0+", "O-O+", "O-O-O+",
    "0-0#", "0-0-0#", "O-O#", "O-O-O#",
    "1-0", "0-1", "1/2-1/2"
  };
}

const std::vector<std::string> ribi::Chess::Moves::GetInvalidPawnMoves(const Chess::Color& color)
{
  if (color == Color::indeterminate)
  return
  {
    "a2xa3", "a3xa2", "a2 b3", "a3 b2",
    "a6xb7e.p." , "b6xa7e.p." , "a3xb2e.p." , "b3xa2e.p.",
    "a6xb7e.p.+", "b6xa7e.p.+", "a3xb2e.p.+", "b3xa2e.p.+",
    "a6xb7e.p.#", "b6xa7e.p.#", "a3xb2e.p.#", "b3xa2e.p.#"
    "0-0" , "0-0-0" , "O-O" , "O-O-O" ,
    "0-0+", "0-0-0+", "O-O+", "O-O-O+",
    "0-0#", "0-0-0#", "O-O#", "O-O-O#",
    "1-0", "0-1", "1/2-1/2"
  };
  if (color == Color::white)
  return
  {
    "a2 a1Q", "a1Q", "e4 e3", "e4xd3e.p."
  };

  if (color == Color::black)
  return
  {
     "a2 a3", "a2 a4", "a7 a8Q", "a8Q", "e4 e5", "h5xg6e.p."
  };
  assert(!"Should not get here");
  throw std::vector<std::string>();
}

const std::vector<std::string> ribi::Chess::Moves::GetInvalidPromotionMoves()
{
  return
  {

  };
}

const std::vector<std::string> ribi::Chess::Moves::GetInvalidQueenMoves()
{
  return
  {
    "Qa1 b7" , "Qa1 h2" , "Qa1 h7" ,
    "Qa1 b7+", "Qa1 h2+", "Qa1 h7+",
    "Qa1 b7#", "Qa1 h2#", "Qa1 h7#",
    "Qa1xb7" , "Qa1xh2" , "Qa1xh7" ,
    "Qa1xb7+", "Qa1xh2+", "Qa1xh7+",
    "Qa1xb7#", "Qa1xh2#", "Qa1xh7#",
    "Qd5xe6e.p.", "Qd5xe6e.p.+", "Qd5xe6+e.p.","Qd5xe6e.p.#", "Qd5xe6#e.p.",
    "0-0", "O-O"

  };
}

const std::vector<std::string> ribi::Chess::Moves::GetInvalidRookMoves()
{
  return
  {
    "Ra1 b8", "Ra1 h2", "Ra1 h8"
  };
}

const std::vector<std::string> ribi::Chess::Moves::GetValidBishopMoves()
{
  return
  {
    "Bd4 a1","Bd4 b2","Bd4 c3","Bd4 e5","Bd4 f6","Bd4 g7","Bd4 g7",
    "Bd4 a1+","Bd4 b2+","Bd4 c3+","Bd4 e5+","Bd4 f6+","Bd4 g7+","Bd4 g7+",
    "Bd4 a1#","Bd4 b2#","Bd4 c3#","Bd4 e5#","Bd4 f6#","Bd4 g7#","Bd4 g7#",
    "Ba1","Bb2","Bc3","Be5","Bf6","Bg7","Bg7",
    "Ba1+","Bb2+","Bc3+","Be5+","Bf6+","Bg7+","Bg7+",
    "Ba1#","Bb2#","Bc3#","Be5#","Bf6#","Bg7#","Bg7#"
  };
}

const std::vector<std::string> ribi::Chess::Moves::GetValidCaptureMoves()
{
  return
  {
    "axb3","axb3+","axb3#","a2xb3","a2xb3+","a2xb3#",
    "Baxb3","Baxb3+","Baxb3#","Ba2xb3","Ba2xb3+","Ba2xb3#",
    "a5xb6e.p." ,"b5xa6e.p." ,"a4xb3e.p." ,"b4xa3e.p." ,
    "a5xb6e.p.+","b5xa6e.p.+","a4xb3e.p.+","b4xa3e.p.+",
    "a5xb6e.p.#","b5xa6e.p.#","a4xb3e.p.#","b4xa3e.p.#"
  };
}

const std::vector<std::string> ribi::Chess::Moves::GetValidCastlingMoves()
{
  return
  {
    "0-0","0-0+","0-0#","0-0-0","0-0-0+","0-0-0#",
    "O-O","O-O+","O-O#","O-O-O","O-O-O+","O-O-O#"
  };
}

const std::vector<std::string> ribi::Chess::Moves::GetValidCheckMoves()
{
  return
  {
    "a3+","a2 a3+","a2xb3+","Ba3+",
    "Ba2 b3+","Ba2xb3+",
    "O-O+","O-O-O+","0-0+","0-0-0+", "Bf1 b5+"
  };
}

const std::vector<std::string> ribi::Chess::Moves::GetValidCheckmateMoves()
{
  return
  {

  };
}

const std::vector<std::string> ribi::Chess::Moves::GetValidEnPassantMoves()
{
  return
  {
    "a5xb6e.p." ,"b5xa6e.p." ,"a4xb3e.p." ,"b4xa3e.p." ,
    "a5xb6e.p.+","b5xa6e.p.+","a4xb3e.p.+","b4xa3e.p.+",
    "a5xb6e.p.#","b5xa6e.p.#","a4xb3e.p.#","b4xa3e.p.#"
  };
}

const std::vector<std::string> ribi::Chess::Moves::GetValidKingMoves()
{
  return
  {
    "Kd4 c3","Kd4 c4","Kd4 c5","Kd4 d5","Kd4 e5","Kd4 e4","Kd4 e3","Kd4 d3",
    "Kd4xc3","Kd4xc4","Kd4xc5","Kd4xd5","Kd4xe5","Kd4xe4","Kd4xe3","Kd4xd3",
    "Kd4 c3+","Kd4 c4+","Kd4 c5+","Kd4 d5+","Kd4 e5+","Kd4 e4+","Kd4 e3+","Kd4 d3+",
    "Kd4xc3+","Kd4xc4+","Kd4xc5+","Kd4xd5+","Kd4xe5+","Kd4xe4+","Kd4xe3+","Kd4xd3+",
    "Kd4 c3#","Kd4 c4#","Kd4 c5#","Kd4 d5#","Kd4 e5#","Kd4 e4#","Kd4 e3#","Kd4 d3#",
    "Kd4xc3#","Kd4xc4#","Kd4xc5#","Kd4xd5#","Kd4xe5#","Kd4xe4#","Kd4xe3#","Kd4xd3#",
    "Kf1 g1"
   };
}

const std::vector<std::string> ribi::Chess::Moves::GetValidKnightMoves()
{
  return
  {
    "Nd4 b3" ,"Nd4 c2" ,"Nd4 e2" ,"Nd4 f3" ,"Nd4 f5" ,"Nd4 e6" ,"Nd4 c6" ,"Nd4 b5" ,
    "Nd4 b3+","Nd4 c2+","Nd4 e2+","Nd4 f3+","Nd4 f5+","Nd4 e6+","Nd4 c6+","Nd4 b5+",
    "Nd4 b3#","Nd4 c2#","Nd4 e2#","Nd4 f3#","Nd4 f5#","Nd4 e6#","Nd4 c6#","Nd4 b5#",
    "Nd4xb3" ,"Nd4xc2" ,"Nd4xe2" ,"Nd4xf3" ,"Nd4xf5" ,"Nd4xe6" ,"Nd4xc6" ,"Nd4xb5" ,
    "Nd4xb3+","Nd4xc2+","Nd4xe2+","Nd4xf3+","Nd4xf5+","Nd4xe6+","Nd4xc6+","Nd4xb5+",
    "Nd4xb3#","Nd4xc2#","Nd4xe2#","Nd4xf3#","Nd4xf5#","Nd4xe6#","Nd4xc6#","Nd4xb5#",
    "Nb3" ,"Nc2" ,"Ne2" ,"Nf3" ,"Nf5" ,"Ne6" ,"Nc6" ,"Nb5" ,
    "Nb3+","Nc2+","Ne2+","Nf3+","Nf5+","Ne6+","Nc6+","Nb5+",
    "Nb3#","Nc2#","Ne2#","Nf3#","Nf5#","Ne6#","Nc6#","Nb5#"
  };
}

const std::vector<std::string> ribi::Chess::Moves::GetValidPawnMoves(const Chess::Color& color)
{
  if (color == Color::indeterminate)
  return
  {
    "a2 a3" , "a2 a4" , "a2 a1Q" , "a7 a8Q" , "a3" , "a4" , "a8Q" , "a1Q",
    "a2 a3+", "a2 a4+", "a2 a1Q+", "a7 a8Q+", "a3+", "a4+", "a8Q+", "a1Q+",
    "a2 a3#", "a2 a4#", "a2 a1Q#", "a7 a8Q#", "a3#", "a4#", "a8Q#", "a1Q#",
    "a2xb3" , "a3xb2" , "b3xa4" , "b3xc4" , "b3xa2" , "b3xc2" ,
    "a2xb3+", "a3xb2+", "b3xa4+", "b3xc4+", "b3xa2+", "b3xc2+",
    "a2xb3#", "a3xb2#", "b3xa4#", "b3xc4#", "b3xa2#", "b3xc2#",
    "e4 e5", "e4 e3",
    "a5xb6e.p." , "b5xa6e.p." , "a4xb3e.p." , "b4xa3e.p.",
    "a5xb6e.p.+", "b5xa6e.p.+", "a4xb3e.p.+", "b4xa3e.p.+",
    "a5xb6e.p.#", "b5xa6e.p.#", "a4xb3e.p.#", "b4xa3e.p.#"
  };
  if (color == Color::white)
  return
  {
    "a2 a3", "a2 a4", "a7 a8Q", "a3", "a4", "a8Q", "e4 e5"
  };
  if (color == Color::black)
  return
  {
    "a2 a1Q", "a1Q", "a3", "a4", "a7 a6", "a7 a5", "e4 e3"
  };
  assert(!"Should not get here");
  return std::vector<std::string>();
}

const std::vector<std::string> ribi::Chess::Moves::GetValidPromotionMoves()
{
  return
  {
    "a8B","a8N","a8Q","a8R","a1B","a1N","a1Q","a1R",
    "a8B+","a8N+","a8Q+","a8R+","a1B+","a1N+","a1Q+","a1R+",
    "a8B#","a8N#","a8Q#","a8R#","a1B#","a1N#","a1Q#","a1R#",
    "a2 a1Q","a2 a1Q+","a2 a1Q#"
  };
}

const std::vector<std::string> ribi::Chess::Moves::GetValidQueenMoves()
{
  return
  {
    "Qd4 d1","Qd4 d2","Qd4 d3","Qd4 d5","Qd4 d6","Qd4 d7","Qd4 d8",
    "Qd4 a4","Qd4 b4","Qd4 c4","Qd4 e4","Qd4 f4","Qd4 g4","Qd4 h4",
    "Qd4xd1","Qd4xd2","Qd4xd3","Qd4xd5","Qd4xd6","Qd4xd7","Qd4xd8",
    "Qd4xa4","Qd4xb4","Qd4xc4","Qd4xe4","Qd4xf4","Qd4xg4","Qd4xh4",
    "Qd4 d1+","Qd4 d2+","Qd4 d3+","Qd4 d5+","Qd4 d6+","Qd4 d7+","Qd4 d8+",
    "Qd4 a4+","Qd4 b4+","Qd4 c4+","Qd4 e4+","Qd4 f4+","Qd4 g4+","Qd4 h4+",
    "Qd4xd1+","Qd4xd2+","Qd4xd3+","Qd4xd5+","Qd4xd6+","Qd4xd7+","Qd4xd8+",
    "Qd4xa4+","Qd4xb4+","Qd4xc4+","Qd4xe4+","Qd4xf4+","Qd4xg4+","Qd4xh4+",
    "Qd4 d1#","Qd4 d2#","Qd4 d3#","Qd4 d5#","Qd4 d6#","Qd4 d7#","Qd4 d8#",
    "Qd4 a4#","Qd4 b4#","Qd4 c4#","Qd4 e4#","Qd4 f4#","Qd4 g4#","Qd4 h4#",
    "Qd4xd1#","Qd4xd2#","Qd4xd3#","Qd4xd5#","Qd4xd6#","Qd4xd7#","Qd4xd8#",
    "Qd4xa4#","Qd4xb4#","Qd4xc4#","Qd4xe4#","Qd4xf4#","Qd4xg4#","Qd4xh4#",
    "Qd1","Qd2","Qd3","Qd5","Qd6","Qd7","Qd8",
    "Qa4","Qb4","Qc4","Qe4","Qf4","Qg4","Qh4",
    "Qd1+","Qd2+","Qd3+","Qd5+","Qd6+","Qd7+","Qd8+",
    "Qa4+","Qb4+","Qc4+","Qe4+","Qf4+","Qg4+","Qh4+",
    "Qd1#","Qd2#","Qd3#","Qd5#","Qd6#","Qd7#","Qd8#",
    "Qa4#","Qb4#","Qc4#","Qe4#","Qf4#","Qg4#","Qh4#",
    "Qd4 a1","Qd4 b2","Qd4 c3","Qd4 e5","Qd4 f6","Qd4 g7","Qd4 g7",
    "Qd4 a1+","Qd4 b2+","Qd4 c3+","Qd4 e5+","Qd4 f6+","Qd4 g7+","Qd4 g7+",
    "Qd4 a1#","Qd4 b2#","Qd4 c3#","Qd4 e5#","Qd4 f6#","Qd4 g7#","Qd4 g7#",
    "Qa1","Qb2","Qc3","Qe5","Qf6","Qg7","Qg7",
    "Qa1+","Qb2+","Qc3+","Qe5+","Qf6+","Qg7+","Qg7+",
    "Qa1#","Qb2#","Qc3#","Qe5#","Qf6#","Qg7#","Qg7#", "Qf7 f6"
  };
}

const std::vector<std::string> ribi::Chess::Moves::GetValidRookMoves()
{
  return
  {
    "Rd4 d1","Rd4 d2","Rd4 d3","Rd4 d5","Rd4 d6","Rd4 d7","Rd4 d8",
    "Rd4 a4","Rd4 b4","Rd4 c4","Rd4 e4","Rd4 f4","Rd4 g4","Rd4 h4",
    "Rd4xd1","Rd4xd2","Rd4xd3","Rd4xd5","Rd4xd6","Rd4xd7","Rd4xd8",
    "Rd4xa4","Rd4xb4","Rd4xc4","Rd4xe4","Rd4xf4","Rd4xg4","Rd4xh4",
    "Rd4 d1+","Rd4 d2+","Rd4 d3+","Rd4 d5+","Rd4 d6+","Rd4 d7+","Rd4 d8+",
    "Rd4 a4+","Rd4 b4+","Rd4 c4+","Rd4 e4+","Rd4 f4+","Rd4 g4+","Rd4 h4+",
    "Rd4xd1+","Rd4xd2+","Rd4xd3+","Rd4xd5+","Rd4xd6+","Rd4xd7+","Rd4xd8+",
    "Rd4xa4+","Rd4xb4+","Rd4xc4+","Rd4xe4+","Rd4xf4+","Rd4xg4+","Rd4xh4+",
    "Rd4 d1#","Rd4 d2#","Rd4 d3#","Rd4 d5#","Rd4 d6#","Rd4 d7#","Rd4 d8#",
    "Rd4 a4#","Rd4 b4#","Rd4 c4#","Rd4 e4#","Rd4 f4#","Rd4 g4#","Rd4 h4#",
    "Rd4xd1#","Rd4xd2#","Rd4xd3#","Rd4xd5#","Rd4xd6#","Rd4xd7#","Rd4xd8#",
    "Rd4xa4#","Rd4xb4#","Rd4xc4#","Rd4xe4#","Rd4xf4#","Rd4xg4#","Rd4xh4#",
    "Rd1","Rd2","Rd3","Rd5","Rd6","Rd7","Rd8",
    "Ra4","Rb4","Rc4","Re4","Rf4","Rg4","Rh4",
    "Rd1+","Rd2+","Rd3+","Rd5+","Rd6+","Rd7+","Rd8+",
    "Ra4+","Rb4+","Rc4+","Re4+","Rf4+","Rg4+","Rh4+",
    "Rd1#","Rd2#","Rd3#","Rd5#","Rd6#","Rd7#","Rd8#",
    "Ra4#","Rb4#","Rc4#","Re4#","Rf4#","Rg4#","Rh4#"
  };
}

const std::string ribi::Chess::Moves::GetVersion() noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::Chess::Moves::GetVersionHistory() noexcept
{
  return {
    "2012-01-25: version 1.0: initial version"
  };
}
