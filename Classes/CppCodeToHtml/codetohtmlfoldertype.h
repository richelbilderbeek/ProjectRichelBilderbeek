#ifndef CODETOHTMLFOLDERTYPE_H
#define CODETOHTMLFOLDERTYPE_H

namespace ribi {
namespace c2h {

///The type of folder content:
///-cpp: a C++ project
///-foam: an OpenFOAM project
///-txt: a collection of text files
enum class FolderType { cpp, foam, txt };

} //~namespace ribi
} //~namespace c2h

#endif // CODETOHTMLFOLDERTYPE_H
