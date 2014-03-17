#ifndef TRIANGLEMESHFWD_H
#define TRIANGLEMESHFWD_H

namespace ribi {

namespace trim {

struct Cell;
struct CellFactory;
struct CellsCreator;
struct CellsCreatorFactory;

#ifdef USE_TRIANGLEMESHEDGE
struct Edge;
struct EdgeFactory;
#endif

struct Face;
struct FaceFactory;
struct Point;
struct PointFactory;
struct Template;

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHFWD_H
