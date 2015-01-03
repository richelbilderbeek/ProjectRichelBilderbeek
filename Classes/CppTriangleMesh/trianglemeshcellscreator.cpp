#include "trianglemeshcellscreator.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/make_shared.hpp>



#include "geometry.h"
#include "testtimer.h"
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
  const int n_cell_layers,
  const boost::units::quantity<boost::units::si::length> layer_height,
  const CreateVerticalFacesStrategy strategy,
  const bool verbose,
  const CellsCreatorFactory&
) : m_cells(
      CreateCells(
        t,
        n_cell_layers + 1, //n_face_layers - 1 == n_cell_layers
        layer_height,
        strategy,
        verbose
      )
    ),
    m_strategy(strategy)
{
  #ifndef NDEBUG
  Test();
  assert(t);
  assert(strategy == m_strategy);
  #endif
}

#ifndef NDEBUG
void ribi::trim::CellsCreator::CheckCells(const std::vector<boost::shared_ptr<Cell>>& cells) noexcept
{
  for (const auto& cell: cells)
  {
    assert(cell);
    assert(cell->GetFaces().size() == 5 || cell->GetFaces().size() == 8);
  }
}
#endif // NDEBUG

std::vector<boost::shared_ptr<ribi::trim::Cell>> ribi::trim::CellsCreator::CreateCells(
  const boost::shared_ptr<const Template> t,
  const int n_face_layers,
  const boost::units::quantity<boost::units::si::length> layer_height,
  const CreateVerticalFacesStrategy strategy,
  const bool verbose
) noexcept
{
  assert(t);

  if (n_face_layers < 2
    || t->GetPoints().empty()
  )
  {
    std::vector<boost::shared_ptr<ribi::trim::Cell>> no_cells; return no_cells;
  }
  assert(n_face_layers >= 2);

  if (verbose)
  {
    std::clog << __FILE__ << "(" <<  (__LINE__) <<  ") : "
      << "Create points" << std::endl
    ;
  }
  const std::vector<boost::shared_ptr<Point>> all_points
    = CreatePoints(t,n_face_layers,layer_height);

  if (verbose)
  {
    std::clog << __FILE__ << "(" <<  (__LINE__) <<  ") : "
      << "Create horizontal faces" << std::endl
    ;
  }
  const std::vector<boost::shared_ptr<Face>> hor_faces
    = CreateHorizontalFaces(t,all_points,n_face_layers);

  if (verbose)
  {
    std::clog << __FILE__ << "(" <<  (__LINE__) <<  ") : "
      << "Create vertical faces" << std::endl
    ;
  }

  const std::vector<boost::shared_ptr<Face>> ver_faces
    = CreateVerticalFaces(t,all_points,n_face_layers,layer_height,strategy,verbose);

  if (verbose)
  {
    std::clog << __FILE__ << "(" <<  (__LINE__) <<  ") : "
      << "Created " << ver_faces.size() << " vertical faces" << std::endl
    ;
  }

  if (ver_faces.empty())
  {
    std::vector<boost::shared_ptr<ribi::trim::Cell>> no_cells;
    return no_cells;
  }

  #ifndef NDEBUG
  for(const auto f:ver_faces) { assert(f); }
  #endif

  const int n_hor_faces_per_layer = static_cast<int>(t->GetFaces().size());
  const int n_cells_per_layer = n_hor_faces_per_layer;

  if (verbose)
  {
    std::clog << __FILE__ << "(" <<  (__LINE__) <<  ") : "
      << "Creating cells" << std::endl
    ;
  }
  std::vector<boost::shared_ptr<Cell>> cells;
  for (int layer=0; layer!=n_face_layers-1; ++layer) //-1 because there are no points above the top layer
  {
    if (verbose) { std::clog << "."; }
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
        #ifndef NDEBUG
        if (these_ver_faces.size() != 3)
        {
          TRACE("BREAK");
        }
        #endif
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
  #ifndef NDEBUG
  if (verbose)
  {
    std::clog << __FILE__ << "(" <<  (__LINE__) <<  ") : "
      << "Checking cells" << std::endl
    ;
  }
  CheckCells(cells);
  #endif // NDEBUG
  if (verbose)
  {
    std::clog << __FILE__ << "(" <<  (__LINE__) <<  ") : "
      << "Done creating cells" << std::endl
    ;
  }
  return cells;
}

std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::CellsCreator::CreateHorizontalFaces(
  const boost::shared_ptr<const Template> t,
  const std::vector<boost::shared_ptr<Point>>& all_points,
  const int n_face_layers
)
{
  const bool verbose{false};
  std::vector<boost::shared_ptr<Face>> v;
  assert(t);
  #ifndef NDEBUG
  if (all_points.empty())
  {
    TRACE("ERROR");
    TRACE("BREAK");
  }
  #endif
  assert(!all_points.empty());

  const int n_points_per_layer{static_cast<int>(t->GetPoints().size())};
  #ifndef NDEBUG
  const int n_faces_per_layer{static_cast<int>(t->GetFaces().size())};
  assert(n_face_layers > 0);
  #endif
  v.reserve(n_face_layers * n_points_per_layer);

  for (int layer=0; layer!=n_face_layers; ++layer)
  {
    const int point_offset{n_points_per_layer * layer};
    for (const std::vector<int>& face_point_indices: t->GetFacePointIndices())
    {
      #ifndef NDEBUG
      const int face_index{static_cast<int>(v.size())};
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
      //const FaceFactory face_factory;
      const boost::shared_ptr<Face> face {
        FaceFactory().Create(
          face_points,
          FaceOrientation::horizontal,
          verbose
        )
      };
      v.push_back(face);
    }
  }
  return v;
}

std::vector<boost::shared_ptr<ribi::trim::Point>> ribi::trim::CellsCreator::CreatePoints(
  const boost::shared_ptr<const Template> t,
  const int n_face_layers,
  const boost::units::quantity<boost::units::si::length> layer_height
)
{
  std::vector<boost::shared_ptr<Point>> v;

  for (int i=0; i!=n_face_layers; ++i)
  {
    for (const boost::shared_ptr<const Point> point: t->GetPoints())
    {
      const PointFactory point_factory;
      const auto new_point(point_factory.Create(point->GetCoordinat()));
      new_point->SetZ(static_cast<double>(i) * layer_height );
      v.push_back(new_point);
    }
  }
  assert(static_cast<int>(v.size()) == static_cast<int>(t->GetPoints().size()) * n_face_layers);

  return v;
}

std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::CellsCreator::CreateVerticalFaces(
  const boost::shared_ptr<const Template> t,
  const std::vector<boost::shared_ptr<Point>>& all_points,
  const int n_face_layers,
  const boost::units::quantity<boost::units::si::length> layer_height,
  const CreateVerticalFacesStrategy strategy,
  const bool verbose
) noexcept
{
  assert(t);

  assert(n_face_layers > 0);
  if (n_face_layers < 2)
  {
    if (verbose)
    {
      std::clog << __FILE__ << "(" <<  (__LINE__) <<  ") : "
        << "Too few layers to create vertical faces" << std::endl
      ;
    }
    std::vector<boost::shared_ptr<ribi::trim::Face>> no_faces;
    return no_faces;
  }
  #ifndef NDEBUG
  const FaceFactory face_factory;

  if (verbose)
  {
    std::clog << __FILE__ << "(" <<  (__LINE__) <<  ") : "
      << "Checking points" << std::endl
    ;
  }

  for (const auto& point: all_points) { assert(point); }

  if (verbose)
  {
    std::clog << __FILE__ << "(" <<  (__LINE__) <<  ") : "
      << "Get edges" << std::endl
    ;
  }
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
  #ifndef NDEBUG
  const int n_reserve = n_ver_faces * (n_face_layers - 1);
  #endif
  assert(n_reserve > 0);
  assert(n_reserve < static_cast<int>(v.max_size()));
  v.reserve(n_ver_faces * (n_face_layers - 1));

  assert(n_face_layers > 0);
  if (n_face_layers == 1)
  {
    std::vector<boost::shared_ptr<ribi::trim::Face>> no_faces;
    return no_faces;
  }

  if (verbose)
  {
    std::clog << __FILE__ << "(" <<  (__LINE__) <<  ") : "
      << "Start building " << (n_face_layers-1) //Number of cell layers
      << " layers" << std::endl
    ;
  }

  for (int layer=0; layer!=n_face_layers-1; ++layer) //-1 because there are no points above the top layer
  {
    if (verbose)
    {
      std::clog << __FILE__ << "(" <<  (__LINE__) <<  ") : "
        << (layer+1) //Human-based
        << "/" << (n_face_layers-1) //Number of cell layers
        << std::endl
      ;
    }

    const int points_offset = n_points_per_layer * layer;
    assert(points_offset >= 0);
    const auto z_here  = static_cast<double>(layer + 0) * layer_height;
    const auto z_above = static_cast<double>(layer + 1) * layer_height;
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
        assert(face_points.size() == 4);
        assert(face_points[0]);
        assert(face_points[1]);
        assert(face_points[2]);
        assert(face_points[3]);
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
        #ifndef NDEBUG
        if(!IsPlane(face_points))
        {
          TRACE("ERROR");
          std::stringstream s;
          s
            << face_points.size() << '\n'
            << std::setprecision(99)
          ;
          for (const auto& point: face_points) { s << (*point) << " "; }
          TRACE(s.str());
          TRACE("BREAK");
        }
        #endif
        assert(IsPlane(face_points));

        //Order face_points
        if (!Helper().IsConvex(face_points))
        {
          Helper().MakeConvex(face_points);
        }

        assert(Helper().IsConvex(face_points));

        //Cannot order face winding yet, need Cells for this
        const boost::shared_ptr<Face> face {
          FaceFactory().Create(
            face_points,
            FaceOrientation::vertical,
            verbose
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
          FaceFactory().Create(
            face_points_1,
            FaceOrientation::vertical,
            verbose
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

          for (const auto& point:face_points_2) { TRACE(Geometry().ToStr(point->GetCoordinat3D())); }
        }
        #endif

        assert(Helper().IsConvex(face_points_2)
          && "FaceFactory expects convex ordered points");

        const boost::shared_ptr<Face> face_2 {
          FaceFactory().Create(
            face_points_2,
            FaceOrientation::vertical,
            verbose
          )
        };
        assert(face_2);
        v.push_back(face_2);
      }
    }
  }

  assert(n_ver_faces * (n_face_layers - 1) == static_cast<int>(v.size()));

  if (verbose)
  {
    std::clog << __FILE__ << "(" <<  (__LINE__) <<  ") : "
      << "Done building " << (n_face_layers-1) //Number of cell layers
      << " layers" << std::endl
    ;
  }

  return v;
}

std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::CellsCreator::FindKnownFacesBetween(
  const boost::shared_ptr<const Face> a, const boost::shared_ptr<const Face> b
)
{
  
  assert(a->GetOrientation() == FaceOrientation::horizontal);
  assert(b->GetOrientation() == FaceOrientation::horizontal);
  assert(a->GetPoints().size() == 3);
  assert(b->GetPoints().size() == 3);

  //Collect the points the candidates must be a subset of
  std::vector<boost::shared_ptr<Point>> points {
    a->GetPoints()
  };
  for (const auto& p: b->GetPoints()) { points.push_back(p); }

  std::sort(points.begin(),points.end(),Helper().OrderByX());
  assert(std::unique(points.begin(),points.end()) == points.end());
  assert(std::count(points.begin(),points.end(),nullptr) == 0);

  //Collect the candidates
  std::vector<boost::weak_ptr<Face>> weak_candidates;
  for (const auto& p: a->GetPoints()) { for (const auto& q: p->GetConnected()) { weak_candidates.push_back(q); } }
  for (const auto& p: b->GetPoints()) { for (const auto& q: p->GetConnected()) { weak_candidates.push_back(q); } }
  std::vector<boost::shared_ptr<Face>> candidates;
  for (const auto& p: weak_candidates) { const auto q = p.lock(); if (q) candidates.push_back(q); }
  //std::vector<boost::shared_ptr<Face>> candidates;
  //for (const auto& p: candidates) { const auto q = p.lock(); if (q) candidates.push_back(q); }
  std::sort(candidates.begin(),candidates.end(),Helper().OrderByIndex());
  candidates.erase(std::unique(candidates.begin(),candidates.end()),candidates.end());
  assert(std::count(candidates.begin(),candidates.end(),nullptr) == 0);

  //Collect the faces between
  std::vector<boost::shared_ptr<Face>> faces;
  for (const auto& c: candidates)
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

bool ribi::trim::CellsCreator::IsPlane(const std::vector<boost::shared_ptr<Point>>& v) noexcept
{
  std::vector<Point::Coordinat3D> w;
  std::transform(v.begin(),v.end(),std::back_inserter(w),
    [](const boost::shared_ptr<Point>& p)
    {
      assert(p);

      return p->GetCoordinat3D();
    }
  );
  assert(v.size() == w.size());
  return Geometry().IsPlane(w);
}

bool ribi::trim::CellsCreator::IsSubset(
  std::vector<boost::shared_ptr<Point>> v,
  std::vector<boost::shared_ptr<Point>> w
) noexcept
{
  

  std::sort(v.begin(),v.end(),Helper().OrderByX());
  std::sort(w.begin(),w.end(),Helper().OrderByX());
  assert(std::is_sorted(v.begin(),v.end(),Helper().OrderByX()));
  assert(std::is_sorted(w.begin(),w.end(),Helper().OrderByX()));
  assert(std::unique(std::begin(v),std::end(v)) == v.end());
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
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  CellFactory();
  FaceFactory();

  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};

  /*
  if (testing_depth > 1)
  {
    if (verbose) { TRACE("Trying out to build cells from the hardest testing templates"); }
    {
      //This is the longest test by far
      //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
      for (CreateVerticalFacesStrategy strategy: CreateVerticalFacesStrategies().GetAll())
      {
        const boost::shared_ptr<Template> my_template {
          Template::CreateTest(3)
        };

        const int n_cell_layers = 2;
        const boost::shared_ptr<CellsCreator> cells_creator {
          CellsCreatorFactory().Create(
            my_template,
            n_cell_layers,
            1.0 * boost::units::si::meter,
            strategy,
            verbose
          )
        };
        const std::vector<boost::shared_ptr<Cell>> cells { cells_creator->GetCells() };
        assert(cells.size() > 0);
      }
    }
  }
  */
  if (verbose) { TRACE("Specific: check if a Face really loses its neighbour: remove a prism from a cube"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
    for (CreateVerticalFacesStrategy strategy: CreateVerticalFacesStrategies().GetAll())
    {
      //Create a 2x1 cell block
      const boost::shared_ptr<Template> my_template {
        Template::CreateTest(1)
      };
      assert(my_template->CountFaces() == 2);
      const int n_cell_layers = 1;
      const boost::shared_ptr<CellsCreator> cells_creator {
        CellsCreatorFactory().Create(
          my_template,
          n_cell_layers,
          1.0 * boost::units::si::meter,
          strategy,
          verbose
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
      if (verbose) { TRACE("Creating internal faces 1"); }

      Helper::FaceSet internal_faces_1 = Helper().CreateEmptyFaceSet();
      if (verbose) { TRACE("Creating internal faces 1, std::copy_if"); }
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

      if (verbose) { TRACE("Creating internal faces 2"); }
      Helper::FaceSet internal_faces_2 = Helper().CreateEmptyFaceSet();
      std::copy_if(faces_2.begin(),faces_2.end(),std::inserter(internal_faces_2,internal_faces_2.begin()),
        [](const boost::shared_ptr<Face> face)
        {
          return face->GetNeighbour().get();
        }
      );
      if (verbose) { TRACE("Creating internal faces 1"); }
      assert(
        std::equal(
          internal_faces_1.begin(),internal_faces_1.end(),
          internal_faces_2.begin(),
          [](boost::shared_ptr<Face> lhs, boost::shared_ptr<Face> rhs) { return *lhs == *rhs; }
        )
      );
    }
  }
  if (verbose) { TRACE("Create Face, from bug"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
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

    //Order face_points
    if (!Helper().IsConvex(face_points)) { Helper().MakeConvex(face_points); }

    #ifndef NDEBUG
    if (!Helper().IsConvex(face_points))
    {
      TRACE("ERROR");
      for (const auto& p: face_points) { TRACE(*p); }
      TRACE("BREAK");
    }
    #endif

    assert(Helper().IsConvex(face_points));

    //Cannot order face winding yet, need Cells for this
    const boost::shared_ptr<Face> face {
      FaceFactory().Create(
        face_points,
        FaceOrientation::vertical,
        verbose
      )
    };
  }

  //From bug
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
    typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
    const double x1 = 0.0004035051226622692510832834944523028752882964909076690673828125;
    const double y1 = 0.00023296416881187433805568132161312178141088224947452545166015625;
    const double z1 = 0; //left out the '.0' intentionally

    const double x2 = 0.000403505141811931846741734464245610070065595209598541259765625;
    const double y2 = 0.00023296414405748076185791173298156309101614169776439666748046875;
    const double z2 = 0; //left out the '.0' intentionally

    const double x3 = 0.0004035051226622692510832834944523028752882964909076690673828125;
    const double y3 = 0.00023296416881187433805568132161312178141088224947452545166015625;
    const double z3 = 0.00025000000000000000520417042793042128323577344417572021484375;

    const double x4 = 0.000403505141811931846741734464245610070065595209598541259765625;
    const double y4 = 0.00023296414405748076185791173298156309101614169776439666748046875;
    const double z4 = 0.00025000000000000000520417042793042128323577344417572021484375;
    const auto c1 = boost::make_shared<Coordinat2D>(x1,y1);
    const auto c2 = boost::make_shared<Coordinat2D>(x2,y2);
    const auto c3 = boost::make_shared<Coordinat2D>(x3,y3);
    const auto c4 = boost::make_shared<Coordinat2D>(x4,y4);
    const auto p1 = PointFactory().Create(c1);
    const auto p2 = PointFactory().Create(c2);
    const auto p3 = PointFactory().Create(c3);
    const auto p4 = PointFactory().Create(c4);
    p1->SetZ(z1 * boost::units::si::meter);
    p2->SetZ(z2 * boost::units::si::meter);
    p3->SetZ(z3 * boost::units::si::meter);
    p4->SetZ(z4 * boost::units::si::meter);
    std::vector<boost::shared_ptr<Point>> face_points;
    face_points.push_back(p1);
    face_points.push_back(p2);
    face_points.push_back(p3);
    face_points.push_back(p4);
    assert(IsPlane(face_points));
  }
}
#endif
