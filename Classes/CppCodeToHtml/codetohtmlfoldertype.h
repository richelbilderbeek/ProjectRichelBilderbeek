#ifndef CODETOHTMLFOLDERTYPE_H
#define CODETOHTMLFOLDERTYPE_H

namespace ribi {
namespace c2h {

///The type of folder content:



enum class FolderType
{
  foam, ///an OpenFOAM project
  pro,  ///a Qt Creator project
  txt   ///a collection of text files
};

} //~namespace ribi
} //~namespace c2h

#endif // CODETOHTMLFOLDERTYPE_H
