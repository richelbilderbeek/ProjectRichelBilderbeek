#include "trianglemeshcellscreator.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/make_shared.hpp>

#include "Shiny.h"

#include "geometry.h"
#include "trianglemeshcell.h"
#include "trianglemeshcellfactory.h"
#include "trianglemeshcellscreator.h"
#include "trianglemeshcellscreatorfactory.h"
#include "trianglemeshface.h"
#include "trianglemeshfacefactory.h"
#include "trianglemeshhelper.h"
#include "trianglemeshpoint.h"
#include "trianglemeshpointfactory.h"
#include "trianglemeshtemplate.h"
#include "trianglemeshcreateverticalfacesstrategies.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::trim::CellsCreator::CellsCreator(
  const boost::shared_ptr<const Template> t,
  const int n_layers,
  const boost::units::quantity<boost::units::si::length> layer_height,
  const CreateVerticalFacesStrategy strategy,
  const CellsCreatorFactory&
) : m_cells(CreateCells(t,n_layers,layer_height,strategy)),
    m_strategy(strategy)
{
  #ifndef NDEBUG
  Test();
  assert(t);
  assert(n_layers >= 2);
  assert(strategy == m_strategy);
  #endif
}

void ribi::trim::CellsCreator::CheckCells(const std::vector<boost::shared_ptr<Cell>>& cells) noexcept
{
  for (const auto cell: cells)
  {
    assert(cell);
    assert(cell->GetFaces().size() == 5 || cell->GetFaces().size() == 8);
  }
}

std::vector<boost::shared_ptr<ribi::trim::Cell>> ribi::trim::CellsCreator::CreateCells(
  const boost::shared_ptr<const Template> t,
  const int n_layers,
  const boost::units::quantity<boost::units::si::length> layer_height,
  const CreateVerticalFacesStrategy strategy
) noexcept
{
  PROFILE_FUNC();
  assert(t);
  const bool verbose = false;

  if (verbose) { TRACE("Create points"); }
  const std::vector<boost::shared_ptr<Point>> all_points
    = CreatePoints(t,n_layers,layer_height);

  if (verbose) { TRACE("Create horizontal faces"); }
  const std::vector<boost::shared_ptr<Face>> hor_faces
    = CreateHorizontalFaces(t,all_points,n_layers);

  if (verbose) { TRACE("Create vertical faces"); }

  const std::vector<boost::shared_ptr<Face>> ver_faces
    = CreateVerticalFaces(t,all_points,n_layers,layer_height,strategy);

  assert(!ver_faces.empty());
  #ifndef NDEBUG
  if (ver_faces.size() <= hor_faces.size())
  {
    TRACE("ERROR");
    TRACE(ver_faces.size());
    TRACE(hor_faces.size());
    TRACE(Helper().ToStr(AddConst(all_points)));
    TRACE("BREAK");
  }
  #endif
  assert(ver_faces.size() > hor_faces.size());
  #ifndef NDEBUG
  for(auto f:ver_faces) { assert(f); }
  #endif

  const int n_hor_faces_per_layer = static_cast<int>(t->GetFaces().size());
  const int n_cells_per_layer = n_hor_faces_per_layer;

  if (verbose) { TRACE("Creating cells"); }
  std::vector<boost::shared_ptr<Cell>> cells;
  for (int layer=0; layer!=n_layers-1; ++layer) //-1 because there are no points above the top layer
  {
    std::clog << ".";
    for (int i=0; i!=n_cells_per_layer; ++i)
    {

      const int bottom_face_index = ((layer + 0) * n_hor_faces_per_layer) + i;
      const int top_face_index    = ((layer + 1) * n_hor_faces_per_layer) + i;
      assert(bottom_face_index >= 0);
      assert(top_face_index    >= 0);
      assert(bottom_face_index < static_cast<int>(hor_faces.size()));
      assert(top_face_index    < static_cast<int>(hor_faces.size()));
      const std::vector<boost::shared_ptr<Face>> these_ver_faces {
        FindKnownFacesBetween(
          hor_faces[bottom_face_index],
          hor_faces[top_face_index]
        )
      };

      if (strategy == CreateVerticalFacesStrategy::one_face_per_square )
      {
        assert(these_ver_faces.size() == 3);
        assert(hor_faces[bottom_face_index]);
        assert(hor_faces[top_face_index]);
        assert(these_ver_faces[0]);
        assert(these_ver_faces[1]);
        assert(these_ver_faces[2]);
        const boost::shared_ptr<Cell> cell(
          CellFactory().Create(
            {
              hor_faces[bottom_face_index],
              hor_faces[top_face_index],
              these_ver_faces[0],
              these_ver_faces[1],
              these_ver_faces[2]
            },
            strategy
          )
        );
        assert(hor_faces[bottom_face_index]);
        assert(hor_faces[top_face_index]);
        assert(Helper().IsHorizontal(*hor_faces[bottom_face_index]));
        assert(Helper().IsHorizontal(*hor_faces[top_face_index]));
        assert(Helper().IsVertical(*these_ver_faces[0]));
        assert(Helper().IsVertical(*these_ver_faces[1]));
        assert(Helper().IsVertical(*these_ver_faces[2]));

        cells.push_back(cell);
      }
      else
      {
        assert(these_ver_faces.size() == 6);
        const boost::shared_ptr<Cell> cell {
          CellFactory().Create(
            {
              hor_faces[bottom_face_index],
              hor_faces[top_face_index],
              these_ver_faces[0],
              these_ver_faces[1],
              these_ver_faces[2],
              these_ver_faces[3],
              these_ver_faces[4],
              these_ver_faces[5]
            },
            strategy
          )
        };
        assert(hor_faces[bottom_face_index]);
        assert(hor_faces[top_face_index]);
        assert(Helper().IsHorizontal(*hor_faces[bottom_face_index]));
        assert(Helper().IsHorizontal(*hor_faces[top_face_index]));
        assert(Helper().IsVertical(*these_ver_faces[0]));
        assert(Helper().IsVertical(*these_ver_faces[1]));
        assert(Helper().IsVertical(*these_ver_faces[2]));
        assert(Helper().IsVertical(*these_ver_faces[3]));
        assert(Helper().IsVertical(*these_ver_faces[4]));
        assert(Helper().IsVertical(*these_ver_faces[5]));

        cells.push_back(cell);
      }
    }
  }

  CheckCells(cells);
  return cells;
}

std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::CellsCreator::CreateHorizontalFaces(
  const boost::shared_ptr<const Template> t,
  const std::vector<boost::shared_ptr<Point>>& all_points,
  const int n_layers
)
{
  PROFILE_FUNC();
  std::vector<boost::shared_ptr<Face> > v;
  assert(t);
  assert(!all_points.empty());

  const int n_points_per_layer = static_cast<int>(t->GetPoints().size());
  #ifndef NDEBUG
  const int n_faces_per_layer = static_cast<int>(t->GetFaces().size());
  assert(n_layers > 0);
  #endif
  if (n_layers < 2) { TRACE("WARNING: NEED AT LEAST TWO HORIZONTAL PLANES TO CREATE CELLS"); }
  v.reserve(n_layers * n_points_per_layer);

  for (int layer=0; layer!=n_layers; ++layer)
  {
    const int point_offset = n_points_per_layer * layer;
    for (const std::vector<int>& face_point_indices: t->GetFacePointIndices())
    {
      #ifndef NDEBUG
      const int face_index = static_cast<int>(v.size());
      assert(face_point_indices.size() == 3); //Triangulation
      #endif
      std::vector<boost::shared_ptr<Point>> face_points;
      for (int point_index: face_point_indices)
      {
        assert(point_index + point_offset < static_cast<int>(all_points.size()));
        face_points.push_back(all_points[point_index + point_offset]);
        #ifndef NDEBUG
        if (face_points.size() >= 2 && face_points[0]->CanGetZ())
        {
          assert(face_points.front()->GetZ() == face_points.back()->GetZ());
        }
        #endif
      }

      assert(layer == 0 || face_index - n_faces_per_layer >= 0);
      assert(layer == 0 || face_index - n_faces_per_layer < static_cast<int>(v.size()));
      if ( (layer % 2 == 0 && !Helper().IsClockwiseHorizontal(face_points))
        || (layer % 2 == 1 &&  Helper().IsClockwiseHorizontal(face_points))
      )
      {
        std::reverse(face_points.begin(),face_points.end());
      }

      if(!Helper().IsConvex(face_points)) { Helper().MakeConvex(face_points); }
      assert(Helper().IsConvex(face_points));
      const FaceFactory face_factory;
      const boost::shared_ptr<Face> face {
        face_factory.Create(
          face_points,
          FaceOrientation::horizontal
        )
      };
      v.push_back(face);
    }
  }
  return v;
}

std::vector<boost::shared_ptr<ribi::trim::Point> > ribi::trim::CellsCreator::CreatePoints(
  const boost::shared_ptr<const Template> t,
  const int n_layers,
  const boost::units::quantity<boost::units::si::length> layer_height
)
{
  std::vector<boost::shared_ptr<Point>> v;

  for (int i=0; i!=n_layers; ++i)
  {
    for (const boost::shared_ptr<const Point> point: t->GetPoints())
    {
      const PointFactory point_factory;
      const auto new_point(point_factory.Create(point->GetCoordinat()));
      new_point->SetZ(static_cast<double>(i) * layer_height );
      v.push_back(new_point);
    }
  }
  assert(static_cast<int>(v.size()) == static_cast<int>(t->GetPoints().size()) * n_layers);

  return v;
}

std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::CellsCreator::CreateVerticalFaces(
  const boost::shared_ptr<const Template> t,
  const std::vector<boost::shared_ptr<Point>>& all_points,
  const int n_layers,
  const boost::units::quantity<boost::units::si::length> layer_height,
  const CreateVerticalFacesStrategy strategy
) noexcept
{
  PROFILE_FUNC();
  assert(t);
  #ifndef NDEBUG
  const FaceFactory face_factory;

  const bool verbose = false;
  for (const auto point: all_points) { assert(point); }
  if (verbose) { TRACE("Get edges"); }
  #endif
  const std::vector<std::pair<int,int>> edges = t->GetEdges();
  assert(!edges.empty());
  const int n_edges = static_cast<int>(edges.size());
  const int n_points_per_layer = static_cast<int>(t->GetPoints().size());
  assert(n_points_per_layer > 0);
  const int n_ver_faces
    = strategy == CreateVerticalFacesStrategy::one_face_per_square
    ? 1 * n_edges
    : 2 * n_edges //For every horizontal edge, two triangles are used instead
  ;

  std::vector<boost::shared_ptr<Face>> v;
  const int n_reserve = n_ver_faces * (n_layers - 1);
  assert(n_reserve > 0);
  assert(n_reserve < static_cast<int>(v.max_size()));
  v.reserve(n_ver_faces * (n_layers - 1));

  assert(n_layers > 0);
  if (n_layers < 2) { TRACE("WARNING: NEED AT LEAST TWO HORIZONTAL PLANES TO CREATE CELLS"); }

  #ifndef NDEBUG
  if (verbose) { TRACE("Start building layers"); }
  #endif

  for (int layer=0; layer!=n_layers-1; ++layer) //-1 because there are no points above the top layer
  {
    #ifndef NDEBUG
    if (verbose) { TRACE(layer); }
    #endif

    const int points_offset = n_points_per_layer * layer;
    const auto z_here( static_cast<double>(layer + 0) * layer_height);
    const auto z_above(static_cast<double>(layer + 1) * layer_height);
    for (const std::pair<int,int>& edge: edges)
    {
      assert(edge.first < edge.second);

      assert(points_offset + edge.first  < static_cast<int>(all_points.size()));
      assert(points_offset + edge.second < static_cast<int>(all_points.size()));
      assert(points_offset + edge.first  + n_points_per_layer < static_cast<int>(all_points.size()));
      assert(points_offset + edge.second + n_points_per_layer < static_cast<int>(all_points.size()));
      if (strategy == CreateVerticalFacesStrategy::one_face_per_square)
      {
        //Ordering cannot be known for sure to be convex from these indices
        assert(all_points[points_offset + edge.first]);
        assert(all_points[points_offset + edge.second]);
        assert(all_points[points_offset + edge.first  + n_points_per_layer]);
        assert(all_points[points_offset + edge.second + n_points_per_layer]);
        std::vector<boost::shared_ptr<Point>> face_points;
        face_points.push_back(all_points[points_offset + edge.first]);
        face_points.push_back(all_points[points_offset + edge.second]);
        face_points.push_back(all_points[points_offset + edge.first  + n_points_per_layer]);
        face_points.push_back(all_points[points_offset + edge.second + n_points_per_layer]);
        assert(face_points[0] != face_points[1]);
        assert(face_points[0] != face_points[2]);
        assert(face_points[0] != face_points[3]);
        assert(face_points[1] != face_points[2]);
        assert(face_points[1] != face_points[3]);
        assert(face_points[2] != face_points[3]);
        face_points[0]->SetZ(z_here);
        face_points[1]->SetZ(z_here);
        face_points[2]->SetZ(z_above);
        face_points[3]->SetZ(z_above);

        //Order face_points
        if (!Helper().IsConvex(face_points))
        {
          Helper().MakeConvex(face_points);
        }

        assert(Helper().IsConvex(face_points));

        //Cannot order face winding yet, need Cells for this
        const boost::shared_ptr<Face> face {
          face_factory.Create(
            face_points,
            FaceOrientation::vertical
          )
        };
        assert(face);
        v.push_back(face);
      }
      else
      {
        assert(all_points[points_offset + edge.first]);
        assert(all_points[points_offset + edge.second]);
        assert(all_points[points_offset + edge.first + n_points_per_layer]);
        const std::vector<boost::shared_ptr<Point>> face_points_1 {
          all_points[points_offset + edge.first],
          all_points[points_offset + edge.second],
          all_points[points_offset + edge.first + n_points_per_layer]
        };
        assert(face_points_1[0] != face_points_1[1]);
        assert(face_points_1[0] != face_points_1[2]);
        assert(face_points_1[1] != face_points_1[2]);

        face_points_1[0]->SetZ(z_here);
        face_points_1[1]->SetZ(z_here);
        face_points_1[2]->SetZ(z_above);

        assert(Helper().IsConvex(face_points_1)
          && "FaceFactory expects convex ordered points");

        //Cannot order face winding yet, need Cells for this
        const boost::shared_ptr<Face> face_1 {
          face_factory.Create(
            face_points_1,
            FaceOrientation::vertical
          )
        };
        assert(face_1);
        v.push_back(face_1);


        assert(all_points[points_offset + edge.second]);
        assert(all_points[points_offset + edge.second + n_points_per_layer]);
        assert(all_points[points_offset + edge.first  + n_points_per_layer]);
        std::vector<boost::shared_ptr<Point>> face_points_2 {
          all_points[points_offset + edge.second],
          all_points[points_offset + edge.second + n_points_per_layer],
          all_points[points_offset + edge.first  + n_points_per_layer]
        };
        assert(face_points_2[0] != face_points_2[1]);
        assert(face_points_2[0] != face_points_2[2]);
        assert(face_points_2[1] != face_points_2[2]);

        face_points_2[0]->SetZ(z_here );
        face_points_2[1]->SetZ(z_above);
        face_points_2[2]->SetZ(z_above);

        #ifndef NDEBUG
        if (!Helper().IsConvex(face_points_2))
        {
          TRACE("ERROR");

          for (auto point:face_points_2) { TRACE(Geometry().ToStr(point->GetCoordinat3D())); }
        }
        #endif

        assert(Helper().IsConvex(face_points_2)
          && "FaceFactory expects convex ordered points");

        const boost::shared_ptr<Face> face_2 {
          face_factory.Create(
            face_points_2,
            FaceOrientation::vertical
          )
        };
        assert(face_2);
        v.push_back(face_2);
      }
    }
  }

  assert(n_ver_faces * (n_layers - 1) == static_cast<int>(v.size()));
  return v;
}

std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::CellsCreator::FindKnownFacesBetween(
  const boost::shared_ptr<const Face> a, const boost::shared_ptr<const Face> b
)
{
  PROFILE_FUNC();
  assert(a->GetOrientation() == FaceOrientation::horizontal);
  assert(b->GetOrientation() == FaceOrientation::horizontal);
  assert(a->GetPoints().size() == 3);
  assert(b->GetPoints().size() == 3);

  //Collect the points the candidates must be a subset of
  std::vector<boost::shared_ptr<Point>> points {
    a->GetPoints()
  };
  for (auto p: b->GetPoints()) { points.push_back(p); }

  std::sort(points.begin(),points.end(),Helper().OrderByX());
  assert(std::unique(points.begin(),points.end()) == points.end());
  assert(std::count(points.begin(),points.end(),nullptr) == 0);

  //Collect the candidates
  #ifdef TRIANGLEMESH_USE_SIGNALS2
  std::vector<boost::shared_ptr<Face>> candidates;
  for (auto p: a->GetPoints()) { for (auto q: p->GetConnected()) { assert(q); candidates.push_back(q); } }
  for (auto p: b->GetPoints()) { for (auto q: p->GetConnected()) { assert(q); candidates.push_back(q); } }
  #else
  std::vector<boost::weak_ptr<Face>> weak_candidates;
  for (auto p: a->GetPoints()) { for (auto q: p->GetConnected()) { weak_candidates.push_back(q); } }
  for (auto p: b->GetPoints()) { for (auto q: p->GetConnected()) { weak_candidates.push_back(q); } }
  std::vector<boost::shared_ptr<Face>> candidates;
  for (auto p: weak_candidates) { const auto q = p.lock(); if (q) candidates.push_back(q); }
  #endif
  //std::vector<boost::shared_ptr<Face>> candidates;
  //for (auto p: candidates) { const auto q = p.lock(); if (q) candidates.push_back(q); }
  std::sort(candidates.begin(),candidates.end(),Helper().OrderByIndex());
  candidates.erase(std::unique(candidates.begin(),candidates.end()),candidates.end());
  assert(std::count(candidates.begin(),candidates.end(),nullptr) == 0);

  //Collect the faces between
  std::vector<boost::shared_ptr<Face>> faces;
  for (auto c: candidates)
  {
    if (IsSubset(c->GetPoints(),points)) { faces.push_back(c); }
  }
  assert(std::is_sorted(faces.begin(),faces.end(),Helper().OrderByIndex()));
  assert(std::unique(faces.begin(),faces.end()) == faces.end());
  assert(std::count(faces.begin(),faces.end(),nullptr) == 0);

  //Remove the faces a and b
  assert(std::count(faces.begin(),faces.end(),a) == 1);
  assert(std::count(faces.begin(),faces.end(),b) == 1);
  std::remove(faces.begin(),faces.end(),a);
  faces.pop_back();
  std::remove(faces.begin(),faces.end(),b);
  faces.pop_back();
  return faces;
}

bool ribi::trim::CellsCreator::IsSubset(
  std::vector<boost::shared_ptr<Point>> v,
  std::vector<boost::shared_ptr<Point>> w
) noexcept
{
  PROFILE_FUNC();

  std::sort(v.begin(),v.end(),Helper().OrderByX());
  std::sort(w.begin(),w.end(),Helper().OrderByX());
  assert(std::is_sorted(v.begin(),v.end(),Helper().OrderByX()));
  assert(std::is_sorted(w.begin(),w.end(),Helper().OrderByX()));
  assert(std::unique(v.begin(),v.end()) == v.end());
  assert(std::unique(w.begin(),w.end()) == w.end());
  assert(std::count(v.begin(),v.end(),nullptr) == 0);
  assert(std::count(w.begin(),w.end(),nullptr) == 0);
  std::vector<boost::shared_ptr<Point>> x;
  std::set_intersection(
    v.begin(),v.end(),
    w.begin(),w.end(),
    std::back_inserter(x),
    Helper().OrderByX()
  );
  assert(std::count(x.begin(),x.end(),nullptr) == 0);

  return x.size() == std::min(v.size(),w.size());
}

std::vector<boost::shared_ptr<ribi::trim::Cell>> ribi::trim::CellsCreator::GetCells() noexcept
{
  return m_cells;
}

#ifndef NDEBUG
void ribi::trim::CellsCreator::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::CellsCreator::Test");

  TRACE("Trying out to build cells from the testing templates");
  for (CreateVerticalFacesStrategy strategy: CreateVerticalFacesStrategies().GetAll())
  {
    for (int i=0; i!=4; ++i)
    {
      const boost::shared_ptr<Template> my_template {
        Template::CreateTest(i)
      };

      const int n_layers = 3;
      const boost::shared_ptr<CellsCreator> cells_creator {
        CellsCreatorFactory().Create(
          my_template,
          n_layers,
          1.0 * boost::units::si::meter,
          strategy
        )
      };
      const std::vector<boost::shared_ptr<Cell>> cells { cells_creator->GetCells() };
      assert(cells.size() > 0);
    }
  }
  TRACE("Specific: check if a Face really loses its neighbour: remove a prism from a cube");
  for (CreateVerticalFacesStrategy strategy: CreateVerticalFacesStrategies().GetAll())
  {
    //Create a 2x1 cell block
    const boost::shared_ptr<Template> my_template {
      Template::CreateTest(1)
    };
    assert(my_template->CountFaces() == 2);
    const int n_layers = 2;
    const boost::shared_ptr<CellsCreator> cells_creator {
      CellsCreatorFactory().Create(
        my_template,
        n_layers,
        1.0 * boost::units::si::meter,
        strategy
      )
    };
    const std::vector<boost::shared_ptr<Cell>> cells { cells_creator->GetCells() };
    assert(cells.size() == 2);
    const std::vector<boost::shared_ptr<Face>> faces_1 { cells[0]->GetFaces() };
    const std::vector<boost::shared_ptr<Face>> faces_2 { cells[1]->GetFaces() };
    //Find the one/two Faces that have a neighbour
    {
      const int n_faces_with_neighbour {
        std::count_if(faces_1.begin(),faces_1.end(),
          [](const boost::shared_ptr<Face> face)
          {
            return face->GetNeighbour().get();
          }
        )
      };
      TRACE(cells[0]->GetFaces().size());
      TRACE(cells[1]->GetFaces().size());
      TRACE(CreateVerticalFacesStrategies().ToStr(strategy));
      TRACE(n_faces_with_neighbour);
      assert(
           (strategy == CreateVerticalFacesStrategy::one_face_per_square
             && n_faces_with_neighbour == 1)
        || (strategy == CreateVerticalFacesStrategy::two_faces_per_square
             && n_faces_with_neighbour == 2)
      );
    }
    {
      const int n_faces_with_neighbour {
        std::count_if(faces_2.begin(),faces_2.end(),
          [](const boost::shared_ptr<Face> face)
          {
            return face->GetNeighbour().get();
          }
        )
      };
      assert(
           (strategy == CreateVerticalFacesStrategy::one_face_per_square
             && n_faces_with_neighbour == 1)
        || (strategy == CreateVerticalFacesStrategy::two_faces_per_square
             && n_faces_with_neighbour == 2)
      );
    }
    TRACE("Creating internal faces 1");

    Helper::FaceSet internal_faces_1 = Helper().CreateEmptyFaceSet();
    TRACE("Creating internal faces 1, std::copy_if");
    //std::set<boost::shared_ptr<Face>> internal_faces_1;
    std::copy_if(
      faces_1.begin(),faces_1.end(),
      std::inserter(internal_faces_1,internal_faces_1.begin()),
      [](const boost::shared_ptr<Face> face)
      {
        assert(face);
        const bool do_copy = face->GetNeighbour().get();
        return do_copy;
      }
    );

    TRACE("Creating internal faces 2");
    Helper::FaceSet internal_faces_2 = Helper().CreateEmptyFaceSet();
    std::copy_if(faces_2.begin(),faces_2.end(),std::inserter(internal_faces_2,internal_faces_2.begin()),
      [](const boost::shared_ptr<Face> face)
      {
        return face->GetNeighbour().get();
      }
    );
    TRACE("Creating internal faces 1");
    assert(
      std::equal(
        internal_faces_1.begin(),internal_faces_1.end(),
        internal_faces_2.begin(),
        [](boost::shared_ptr<Face> lhs, boost::shared_ptr<Face> rhs) { return *lhs == *rhs; }
      )
    );
  }
  TRACE("Create Face, from bug");
  {
    /*
    (1.17557,2.35781,5.0)
    (2.35114,3.23607,5.0)
    (1.17557,2.35781,6.0)
    (2.35114,3.23607,6.0)
    */
    //Ordering cannot be known for sure to be convex from these indices
    typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
    std::vector<boost::shared_ptr<Point>> face_points {
      PointFactory().Create(boost::make_shared<Coordinat2D>(1.17557,2.35781)),
      PointFactory().Create(boost::make_shared<Coordinat2D>(2.35114,3.23607)),
      PointFactory().Create(boost::make_shared<Coordinat2D>(1.17557,2.35781)),
      PointFactory().Create(boost::make_shared<Coordinat2D>(2.35114,3.23607))
    };
    face_points[0]->SetZ(5.0 * boost::units::si::meter);
    face_points[1]->SetZ(5.0 * boost::units::si::meter);
    face_points[2]->SetZ(6.0 * boost::units::si::meter);
    face_points[3]->SetZ(6.0 * boost::units::si::meter);
    #ifndef NDEBUG
    if (!Helper().IsConvex(face_points))
    {
      TRACE("NOT CONVEX");
      for (auto p: face_points) { assert(p); TRACE(*p); }
    }
    #endif

    //Order face_points
    if (!Helper().IsConvex(face_points)) { Helper().MakeConvex(face_points); }

    #ifndef NDEBUG
    if (!Helper().IsConvex(face_points))
    {
      TRACE("ERROR");
      for (auto p: face_points) { TRACE(*p); }
      TRACE("BREAK");
    }
    #endif

    assert(Helper().IsConvex(face_points));

    //Cannot order face winding yet, need Cells for this
    const boost::shared_ptr<Face> face {
      FaceFactory().Create(
        face_points,
        FaceOrientation::vertical
      )
    };
    //assert(1==2 && "Test should fail");
  }
  TRACE("Finished ribi::trim::CellsCreator::Test successfully");
}
#endif
