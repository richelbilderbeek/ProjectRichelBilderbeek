#include "trianglemeshcellscreator.h"

#include <cassert>

#include "Shiny.h"

#include "trianglemeshcell.h"
#include "trianglemeshcellfactory.h"
//#include "container.h"
#include "trianglemeshface.h"
#include "trianglemeshfacefactory.h"
#include "trianglemeshhelper.h"
#include "trianglemeshpoint.h"
#include "trianglemeshtemplate.h"
#include "trace.h"

ribi::trim::CellsCreator::CellsCreator(
  const boost::shared_ptr<const Template> t,
  const int n_layers,
  const boost::units::quantity<boost::units::si::length> layer_height
) : m_cells(CreateCells(t,n_layers,layer_height))
{

}

/*
const std::vector<boost::shared_ptr<const ribi::trim::Point>> ribi::trim::CellsCreator::CollectPoints(
  const std::vector<int>& point_indices,
  const std::vector<boost::shared_ptr<const Point> >& all_points
)
{
  PROFILE_FUNC();
  std::vector<boost::shared_ptr<const Point>> v;
  for (const auto i: point_indices)
  {
    assert(i < static_cast<int>(all_points.size()));
    assert(all_points[i]);
    v.push_back(all_points[i]);
  }
  return v;
}
*/

const std::vector<boost::shared_ptr<ribi::trim::Cell>> ribi::trim::CellsCreator::CreateCells(
  const boost::shared_ptr<const Template> t,
  const int n_layers,
  const boost::units::quantity<boost::units::si::length> layer_height
) const noexcept
{
  PROFILE_FUNC();
  TRACE_FUNC();
  const std::vector<boost::shared_ptr<Point> > all_points {
    CreateAllPoints(t,n_layers,layer_height)
  };

  TRACE_FUNC();

  const std::vector<boost::shared_ptr<Face> > hor_faces {
    CreateAllHorizontalFaces(t,all_points,n_layers)
  };

  TRACE_FUNC();

  const std::vector<boost::shared_ptr<Face> > ver_faces {
    CreateAllVerticalFaces(t,all_points,n_layers)
  };

  TRACE_FUNC();

  const int n_hor_faces_per_layer = static_cast<int>(t->GetFaces().size());
  //const int n_ver_faces_per_layer = static_cast<int>(ver_faces.size()) / (n_layers - 1);
  const int n_cells_per_layer = n_hor_faces_per_layer;

  TRACE_FUNC();

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
      const std::vector<boost::shared_ptr<Face> > these_ver_faces {
        FindKnownFacesBetween(
          hor_faces[bottom_face_index],
          hor_faces[top_face_index]
        )
      };
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
          }
        )
      };
      cells.push_back(cell);
    }
  }
  return cells;
}

const std::vector<boost::shared_ptr<ribi::trim::Point> > ribi::trim::CellsCreator::CreateAllPoints(
  const boost::shared_ptr<const Template> t,
  const int n_layers,
  const boost::units::quantity<boost::units::si::length> layer_height
)
{
  PROFILE_FUNC();
  std::vector<boost::shared_ptr<Point> > v;

  TRACE(n_layers);

  for (int i=0; i!=n_layers; ++i)
  {
    for (const boost::shared_ptr<const Point> point: t->GetPoints())
    {
      const boost::shared_ptr<Point> new_point {
        new Point(
          point->GetCoordinat(),
          point->GetBoundaryType()
        )
      };
      new_point->SetZ(static_cast<double>(i) * layer_height );
      v.push_back(new_point);
    }
  }
  assert(static_cast<int>(v.size()) == static_cast<int>(t->GetPoints().size()) * n_layers);

  return v;
}


const std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::CellsCreator::CreateAllHorizontalFaces(
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
  const int n_faces_per_layer = static_cast<int>(t->GetFaces().size());
  assert(n_layers > 0);
  if (n_layers < 2) { TRACE("WARNING: NEED AT LEAST TWO HORIZONTAL PLANES TO CREATE CELLS"); }
  v.reserve(n_layers * n_points_per_layer);

  for (int layer=0; layer!=n_layers; ++layer)
  {
    const int point_offset = n_points_per_layer * layer;
    for (const std::vector<int>& face_point_indices: t->GetFacePointIndices())
    {
      const int face_index = static_cast<int>(v.size());
      assert(face_point_indices.size() == 3); //Triangulation
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
      const boost::weak_ptr<const Face> face_below(
          layer == 0
        ? boost::weak_ptr<const Face>()
        : v[ face_index - n_faces_per_layer ]
      );
      const boost::shared_ptr<Face> face {
        FaceFactory().Create(
          face_points,
          FaceOrientation::horizontal,
          face_below
        )
      };
      v.push_back(face);
    }
  }
  return v;
}

const std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::CellsCreator::CreateAllVerticalFaces(
  const boost::shared_ptr<const Template> t,
  const std::vector<boost::shared_ptr<Point>>& all_points,
  const int n_layers
)
{
  PROFILE_FUNC();
  const std::vector<std::pair<int,int>> edges {
    t->GetEdges()
  };
  assert(!edges.empty());
  const int n_edges = static_cast<int>(edges.size());
  const int n_points_per_layer = static_cast<int>(t->GetPoints().size());
  const int n_ver_faces = 2 * n_edges; //For every horizontal square face, two triangles are used instead

  std::vector<boost::shared_ptr<Face> > v;
  v.reserve(n_ver_faces * (n_layers - 1));

  assert(n_layers > 0);
  if (n_layers < 2) { TRACE("WARNING: NEED AT LEAST TWO HORIZONTAL PLANES TO CREATE CELLS"); }

  for (int layer=0; layer!=n_layers-1; ++layer) //-1 because there are no points above the top layer
  {
    const int points_offset = n_points_per_layer * layer;
    for (const std::pair<int,int>& edge: edges)
    {
      assert(edge.first < edge.second);

      assert(points_offset + edge.first < static_cast<int>(all_points.size()));
      assert(points_offset + edge.second < static_cast<int>(all_points.size()));
      assert(points_offset + edge.first + n_points_per_layer < static_cast<int>(all_points.size()));
      const std::vector<boost::shared_ptr<Point>> face_points_1 {
        all_points[points_offset + edge.first],
        all_points[points_offset + edge.second],
        all_points[points_offset + edge.first + n_points_per_layer]
      };

      const boost::weak_ptr<const Face> no_face_below;

      const boost::shared_ptr<Face> face_1 {
        FaceFactory().Create(
          face_points_1,
          FaceOrientation::vertical,
          no_face_below
        )
      };
      v.push_back(face_1);

      assert(points_offset + edge.second < static_cast<int>(all_points.size()));
      assert(points_offset + edge.second + n_points_per_layer < static_cast<int>(all_points.size()));
      assert(points_offset + edge.first  + n_points_per_layer < static_cast<int>(all_points.size()));
      const std::vector<boost::shared_ptr<Point>> face_points_2 {
        all_points[points_offset + edge.second],
        all_points[points_offset + edge.second + n_points_per_layer],
        all_points[points_offset + edge.first + n_points_per_layer]
      };

      const boost::shared_ptr<Face> face_2 {
        FaceFactory().Create(
          face_points_2,
          FaceOrientation::vertical,
          no_face_below
        )
      };
      v.push_back(face_2);
    }
  }

  assert(n_ver_faces * (n_layers - 1) == static_cast<int>(v.size()));
  return v;
}

/*
const std::vector<std::vector<boost::shared_ptr<const ribi::trim::Point>>>
  ribi::trim::CellsCreator::CreateSimilarFaces(
    const std::vector<std::vector<int>>& face_point_indices,
    const std::vector<boost::shared_ptr<Point> >& points
  ) noexcept
{
  PROFILE_FUNC();
  std::vector<std::vector<boost::shared_ptr<Point>>> v;
  const int n_faces = static_cast<int>(face_point_indices.size());
  v.reserve(n_faces);

  for (int i=0; i!=n_faces; ++i)
  {
    assert(i < static_cast<int>(face_point_indices.size()));
    const std::vector<int>& indices = face_point_indices[i];
    const int n_indices = static_cast<int>(indices.size());
    std::vector<boost::shared_ptr<Point>> w;
    w.reserve(n_indices);
    for (int j=0; j!=n_indices; ++j)
    {
      assert(j >=0);
      assert(j < static_cast<int>(indices.size()));
      const int index = indices[j];
      assert(index >= 0);
      assert(index < static_cast<int>(points.size()));
      assert(points[index]);
      w.push_back(points[index]);
    }
    v.push_back(w);
  }
  return v;
}
*/

const boost::shared_ptr<const ribi::trim::Face> ribi::trim::CellsCreator::FindKnownFace(
  const std::vector<boost::shared_ptr<const Point> >& face_points
)
{
  PROFILE_FUNC();
  const int n_points = static_cast<int>(face_points.size());

  //Find the Face that is present in every face_point
  std::vector<boost::shared_ptr<const Face>> all_candidates;
  for (auto point: face_points)
  {
    for(auto weak_candidate: point->GetConnected())
    {
      const auto candidate = weak_candidate.lock();
      if (candidate) all_candidates.push_back(candidate);
    }
  }
  std::sort(all_candidates.begin(),all_candidates.end());

  const int n = static_cast<int>(all_candidates.size()) - n_points;
  for (int i=0; i!=n; ++i)
  {
    const int j = i + n_points - 1;
    assert(j < static_cast<int>(all_candidates.size()));
    if (all_candidates[i] == all_candidates[j])
    {
      assert(all_candidates[i]);
      return all_candidates[i];
    }
  }
  const boost::shared_ptr<const Face> no_known_face;
  return no_known_face;
}

const std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::CellsCreator::FindKnownFacesBetween(
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

  std::sort(points.begin(),points.end());
  assert(std::unique(points.begin(),points.end()) == points.end());

  //Collect the candidates
  std::vector<boost::weak_ptr<Face>> weak_candidates;
  for (auto p: a->GetPoints()) { for (auto q: p->GetConnected()) { weak_candidates.push_back(q); } }
  for (auto p: b->GetPoints()) { for (auto q: p->GetConnected()) { weak_candidates.push_back(q); } }

  std::vector<boost::shared_ptr<Face>> candidates;
  for (auto p: weak_candidates) { const auto q = p.lock(); if (q) candidates.push_back(q); }
  std::sort(candidates.begin(),candidates.end());
  candidates.erase(std::unique(candidates.begin(),candidates.end()),candidates.end());

  //Collect the faces between
  std::vector<boost::shared_ptr<Face>> faces;
  for (auto c: candidates)
  {
    if (IsSubset(c->GetPoints(),points)) { faces.push_back(c); }
  }
  assert(std::is_sorted(faces.begin(),faces.end()));
  assert(std::unique(faces.begin(),faces.end()) == faces.end());

  //Remove the faces a and b
  assert(std::count(faces.begin(),faces.end(),a) == 1);
  assert(std::count(faces.begin(),faces.end(),b) == 1);
  std::remove(faces.begin(),faces.end(),a);
  faces.pop_back();
  std::remove(faces.begin(),faces.end(),b);
  faces.pop_back();
  assert(faces.size() == 6);
  return faces;
}

bool ribi::trim::CellsCreator::IsSubset(
  std::vector<boost::shared_ptr<Point>> v,
  std::vector<boost::shared_ptr<Point>> w
) noexcept
{
  PROFILE_FUNC();
  std::sort(v.begin(),v.end());
  std::sort(w.begin(),w.end());
  assert(std::is_sorted(v.begin(),v.end()));
  assert(std::is_sorted(w.begin(),w.end()));
  assert(std::unique(v.begin(),v.end()) == v.end());
  assert(std::unique(w.begin(),w.end()) == w.end());
  std::vector<boost::shared_ptr<Point>> x;
  std::set_intersection(v.begin(),v.end(),w.begin(),w.end(),
    std::back_inserter(x));
  return x.size() == std::min(v.size(),w.size());
}
