#include "trianglemeshtemplate.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/algorithm/string.hpp>

#include "Shiny.h"

#include "trianglemeshface.h"
#include "trianglemeshfacefactory.h"
#include "fileio.h"
#include "trianglemeshhelper.h"
#include "trianglemeshpoint.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::trim::Template::Template(
  const std::string& filename_node,
  const std::string& filename_ele
)
  : m_edges{},
    m_faces{},
    m_face_point_indices{},
    m_points{}
{
  #ifndef NDEBUG
  Test();
  #endif
  PROFILE_FUNC();

  TRACE("Load the points and faces created by Triangle");
  {
    const std::vector<std::string> v {
      ribi::fileio::FileToVector(
        filename_node
      )
    };
    const int sz = v.size();
    const int percent = sz / 100 ? sz / 100: 1;
    TRACE(sz);
    for(int n=0; n!=sz; ++n)
    {
      PROFILE_BLOCK(Load_the_points_and_faces_created_by_Triangle);
      if (n % percent == 0) std::clog << '%';
      const std::string line = v[n];
      if(n==0) continue; //No idea why this has to be skipped
      const std::vector<std::string> w { SeperateString(line) };
      if (w.empty() || w[0].empty() ||  w[0] == std::string("#"))
      {
        //The final comment line
        continue;
      }
      assert(w.size() == 4);
      assert(CanLexicalCast<int>(w[0]));
      assert(CanLexicalCast<double>(w[1]));
      assert(CanLexicalCast<double>(w[2]));
      assert(CanLexicalCast<int>(w[3]));
      const double x = boost::lexical_cast<double>(w[1]);
      const double y = boost::lexical_cast<double>(w[2]);
      //const std::string boundary_type
      //  = boost::lexical_cast<int>(w[3]) == 0
      //  ? "inside_from_template"
      //  : "outside_from_template";
      const boost::shared_ptr<const ribi::ConstCoordinat2D> bottom {
        new ribi::ConstCoordinat2D(x,y)
      };

      const boost::shared_ptr<Point> node {
        new Point(
          bottom
          //,boundary_type
        )
      };
      m_points.push_back(node);
    }
  }

  TRACE("Load and translate faces");
  {
    const std::vector<std::string> v {
      ribi::fileio::FileToVector(filename_ele)
    };
    const int sz = v.size();
    TRACE(sz);
    const int percent = sz / 100 ? sz / 100: 1;
    for(int n=0; n!=sz; ++n)
    {
      PROFILE_BLOCK(Load_and_translate_faces);
      if (n % percent == 0)
      {
        std::clog << '%';
      }
      const std::string line = v[n];
      if(n==0) continue;
      const std::vector<std::string> w { SeperateString(line) };
      if (w.empty() || w[0].empty() ||  w[0] == std::string("#"))
      {
        //The final comment line
        continue;
      }
      assert(w.size() == 4);
      assert(CanLexicalCast<int>(w[0]));
      assert(CanLexicalCast<int>(w[1]));
      assert(CanLexicalCast<int>(w[2]));
      assert(CanLexicalCast<int>(w[3]));

      //I do not correct for one-base Triangle.exe output
      const int point1 = boost::lexical_cast<int>(w[1]);
      const int point2 = boost::lexical_cast<int>(w[2]);
      const int point3 = boost::lexical_cast<int>(w[3]);
      assert(point1 > 0);
      assert(point2 > 0);
      assert(point3 > 0);
      const std::vector<int> face_point_indices {
        point1-1,
        point2-1,
        point3-1
      };
      m_edges.push_back(std::make_pair(face_point_indices[0],face_point_indices[1]));
      m_edges.push_back(std::make_pair(face_point_indices[0],face_point_indices[2]));
      m_edges.push_back(std::make_pair(face_point_indices[1],face_point_indices[2]));
      const std::vector<boost::shared_ptr<Point>> face_points {
        m_points[point1-1],
        m_points[point2-1],
        m_points[point3-1]
      };
      const boost::weak_ptr<const Face> no_face_below;

      const boost::shared_ptr<Face> face {
        FaceFactory().Create(
          face_points,
          FaceOrientation::horizontal,
          no_face_below
        )
      };
      m_faces.push_back(face);
      m_face_point_indices.push_back(face_point_indices);

      assert(std::unique(m_face_point_indices.begin(),m_face_point_indices.end())
        == m_face_point_indices.end()
        && "Every face should have unique point indices");
    }
  }

  #ifndef NDEBUG
  TRACE("Checking the result");
  const int n_faces = static_cast<int>(m_faces.size());
  assert(m_faces.size() == m_face_point_indices.size());
  for (int i=0; i!=n_faces; ++i)
  {
    const auto face = m_faces[i];
    const auto indices = m_face_point_indices[i];
    assert(face->GetPoints().size() == indices.size());
    const int n_points = static_cast<int>(indices.size());
    for (int j=0; j!=n_points; ++j)
    {
      assert(face->GetPoints()[j] == m_points[ indices[j] ]);
    }
  }
  #endif

  for (auto& p: m_edges)
  {
    if (p.first > p.second) std::swap(p.first,p.second);
    assert(p.first < p.second);
  }
  std::sort(m_edges.begin(),m_edges.end());

  auto new_end = std::unique(m_edges.begin(),m_edges.end());
  m_edges.erase(new_end,m_edges.end());
  assert(!m_edges.empty());
}

ribi::trim::Template::Template(
  std::vector<std::pair<int,int>> edges,
  std::vector<boost::shared_ptr<Face>> faces,
  std::vector<std::vector<int>> face_point_indices,
  std::vector<boost::shared_ptr<Point>> points
) : m_edges{edges}, m_faces{faces}, m_face_point_indices{face_point_indices}, m_points{points}
{

}

const boost::shared_ptr<ribi::trim::Template> ribi::trim::Template::CreateTest(const int i) noexcept
{
  switch (i)
  {
    case 1: return CreateTest2x2();
    case 2: return CreateTest2x3();
    case 3: return CreateTest3x3();
  }

  assert(!"Should not get here");
  return boost::shared_ptr<Template>();
}

const boost::shared_ptr<ribi::trim::Template> ribi::trim::Template::CreateTest2x2() noexcept
{
  std::vector<boost::shared_ptr<Face>> faces;
  std::vector<std::vector<int>> face_point_indices;
  std::vector<boost::shared_ptr<Point>> points;
  const int width = 2;
  const int height = 2;
  const int n_points = width * height;
  points.reserve(n_points);

  //Create points
  {
    for(int i=0; i!=n_points; ++i)
    {
      const double x = static_cast<double>(i % width);
      const double y = static_cast<double>(i / width);
      const std::string boundary_type = "two_times_two";
      const boost::shared_ptr<const ribi::ConstCoordinat2D> bottom {
        new ribi::ConstCoordinat2D(x,y)
      };
      const boost::shared_ptr<Point> point {
        new Point(
          bottom
          //,boundary_type
        )
      };
      points.push_back(point);
    }
  }
  #ifndef NDEBUG
  //Check that there is no coordinat present twice
  {
    for (int i=0; i!=n_points; ++i)
    {
      const boost::shared_ptr<const ribi::ConstCoordinat2D> a { points[i]->GetCoordinat() };
      for (int j=0; j!=n_points; ++j)
      {
        const boost::shared_ptr<const ribi::ConstCoordinat2D> b { points[j]->GetCoordinat() };
        if (a == b)
        {
          assert(ribi::Distance(*a,*b) < 0.001);
        }
        else
        {
          assert(ribi::Distance(*a,*b) > 0.001);
        }
      }
    }
  }
  #endif

  //Load and translate faces
  face_point_indices = {
    { 0,1,2 },
    { 1,2,3 }
  };

  const std::vector<std::pair<int,int> > edges {
    { 0,1 },
    { 0,2 },
    { 1,2 },
    { 1,3 },
    { 2,3 }
  };

  {
    for(auto v: face_point_indices)
    {
      assert(v.size() == 3);
      //I do not correct for one-base Triangle.exe output
      assert(v[0] >= 0);
      assert(v[1] >= 0);
      assert(v[2] >= 0);
      const std::vector<boost::shared_ptr<Point>> face_points {
        points[ v[0] ],
        points[ v[1] ],
        points[ v[2] ]
      };
      TRACE_FUNC();
      const boost::weak_ptr<const Face> no_face_below;
      TRACE_FUNC();
      const boost::shared_ptr<Face> face {
        FaceFactory().Create(
          face_points,
          FaceOrientation::horizontal,
          no_face_below
        )
      };
      TRACE_FUNC();
      faces.push_back(face);
    }
  }

  #ifndef NDEBUG
  const int n_faces = static_cast<int>(faces.size());
  assert(faces.size() == face_point_indices.size());
  for (int i=0; i!=n_faces; ++i)
  {
    const auto face = faces[i];
    const auto indices = face_point_indices[i];
    assert(face->GetPoints().size() == indices.size());
    const int n_points = static_cast<int>(indices.size());
    for (int j=0; j!=n_points; ++j)
    {
      assert(face->GetPoints()[j] == points[ indices[j] ]);
    }
  }
  #endif

  const boost::shared_ptr<Template> my_template {
    new Template(
      edges,
      faces,
      face_point_indices,
      points
    )
  };
  assert(my_template);
  return my_template;
}

const boost::shared_ptr<ribi::trim::Template> ribi::trim::Template::CreateTest2x3() noexcept
{
  std::vector<boost::shared_ptr<Face>> faces;
  std::vector<std::vector<int>> face_point_indices;
  std::vector<boost::shared_ptr<Point>> points;
  const int width = 3;
  const int height = 2;
  const int n_points = width * height;
  points.reserve(n_points);

  //Create points
  {
    for(int i=0; i!=n_points; ++i)
    {
      const double x = static_cast<double>(i % width);
      const double y = static_cast<double>(i / width);
      //const std::string boundary_type = "two_times_three";
      const boost::shared_ptr<const ribi::ConstCoordinat2D> bottom {
        new ribi::ConstCoordinat2D(x,y)
      };
      const boost::shared_ptr<Point> point {
        new Point(
          bottom
          //,boundary_type
        )
      };
      points.push_back(point);
    }
  }
  #ifndef NDEBUG
  //Check that there is no coordinat present twice
  {
    for (int i=0; i!=n_points; ++i)
    {
      const boost::shared_ptr<const ribi::ConstCoordinat2D> a { points[i]->GetCoordinat() };
      for (int j=0; j!=n_points; ++j)
      {
        const boost::shared_ptr<const ribi::ConstCoordinat2D> b { points[j]->GetCoordinat() };
        if (a == b)
        {
          assert(ribi::Distance(*a,*b) < 0.001);
        }
        else
        {
          assert(ribi::Distance(*a,*b) > 0.001);
        }
      }
    }
  }
  #endif

  //Load and translate faces
  face_point_indices = {
    { 0,1,3 },
    { 1,3,4 },
    { 1,2,4 },
    { 2,4,5 }
  };

  const std::vector<std::pair<int,int> > edges {
    { 0,1 },
    { 0,3 },
    { 1,2 },
    { 1,3 },
    { 1,4 },
    { 2,4 },
    { 2,5 },
    { 3,4 },
    { 4,5 }
  };

  {
    for(auto v: face_point_indices)
    {
      assert(v.size() == 3);
      //I do not correct for one-base Triangle.exe output
      const int point1 = v[0];
      const int point2 = v[1];
      const int point3 = v[2];
      assert(point1 >= 0);
      assert(point2 >= 0);
      assert(point3 >= 0);
      const std::vector<int> face_point_indices {
        point1,
        point2,
        point3
      };
      const std::vector<boost::shared_ptr<Point>> face_points {
        points[point1],
        points[point2],
        points[point3]
      };
      TRACE_FUNC();
      const boost::weak_ptr<const Face> no_face_below;
      TRACE_FUNC();
      const boost::shared_ptr<Face> face {
        FaceFactory().Create(
          face_points,
          FaceOrientation::horizontal,
          no_face_below
        )
      };
      TRACE_FUNC();
      faces.push_back(face);
    }
  }

  #ifndef NDEBUG
  const int n_faces = static_cast<int>(faces.size());
  assert(faces.size() == face_point_indices.size());
  for (int i=0; i!=n_faces; ++i)
  {
    const auto face = faces[i];
    const auto indices = face_point_indices[i];
    assert(face->GetPoints().size() == indices.size());
    const int n_points = static_cast<int>(indices.size());
    for (int j=0; j!=n_points; ++j)
    {
      assert(face->GetPoints()[j] == points[ indices[j] ]);
    }
  }
  #endif

  const boost::shared_ptr<Template> my_template {
    new Template(
      edges,
      faces,
      face_point_indices,
      points
    )
  };
  assert(my_template);
  return my_template;
}

const boost::shared_ptr<ribi::trim::Template> ribi::trim::Template::CreateTest3x3() noexcept
{
  std::vector<boost::shared_ptr<Face>> faces;
  std::vector<std::vector<int>> face_point_indices;
  std::vector<boost::shared_ptr<Point>> points;
  const int width = 3;
  const int height = 3;
  const int n_points = width * height;
  points.reserve(n_points);

  //Create points
  {
    for(int i=0; i!=n_points; ++i)
    {
      const double x = static_cast<double>(i % width);
      const double y = static_cast<double>(i / width);
      const std::string boundary_type = "three_times_three";
      const boost::shared_ptr<const ribi::ConstCoordinat2D> bottom {
        new ribi::ConstCoordinat2D(x,y)
      };
      const boost::shared_ptr<Point> point {
        new Point(
          bottom
        )
      };
      points.push_back(point);
    }
  }
  #ifndef NDEBUG
  //Check that there is no coordinat present twice
  {
    for (int i=0; i!=n_points; ++i)
    {
      const boost::shared_ptr<const ribi::ConstCoordinat2D> a { points[i]->GetCoordinat() };
      for (int j=0; j!=n_points; ++j)
      {
        const boost::shared_ptr<const ribi::ConstCoordinat2D> b { points[j]->GetCoordinat() };
        if (a == b)
        {
          assert(ribi::Distance(*a,*b) < 0.001);
        }
        else
        {
          assert(ribi::Distance(*a,*b) > 0.001);
        }
      }
    }
  }
  #endif

  //Load and translate faces
  face_point_indices = {
    { 0,1,3 },
    { 1,2,4 },
    { 1,3,4 },
    { 2,4,5 },
    { 3,4,6 },
    { 4,5,7 },
    { 4,6,7 },
    { 5,7,8 }
  };

  const std::vector<std::pair<int,int> > edges {
    { 0,1 },
    { 0,3 },
    { 1,2 },
    { 1,3 },
    { 1,4 },
    { 2,4 },
    { 2,5 },
    { 3,4 },
    { 3,6 },
    { 4,5 },
    { 4,6 },
    { 4,7 },
    { 5,7 },
    { 5,8 },
    { 6,7 },
    { 7,8 }
  };

  {
    for(auto v: face_point_indices)
    {
      assert(v.size() == 3);
      //I do not correct for one-base Triangle.exe output
      const int point1 = v[0];
      const int point2 = v[1];
      const int point3 = v[2];
      assert(point1 >= 0);
      assert(point2 >= 0);
      assert(point3 >= 0);
      const std::vector<int> face_point_indices {
        point1,
        point2,
        point3
      };
      const std::vector<boost::shared_ptr<Point>> face_points {
        points[point1],
        points[point2],
        points[point3]
      };
      TRACE_FUNC();
      const boost::weak_ptr<const Face> no_face_below;
      TRACE_FUNC();
      const boost::shared_ptr<Face> face {
        FaceFactory().Create(
          face_points,
          FaceOrientation::horizontal,
          no_face_below
        )
      };
      TRACE_FUNC();
      faces.push_back(face);
    }
  }

  #ifndef NDEBUG
  const int n_faces = static_cast<int>(faces.size());
  assert(faces.size() == face_point_indices.size());
  for (int i=0; i!=n_faces; ++i)
  {
    const auto face = faces[i];
    const auto indices = face_point_indices[i];
    assert(face->GetPoints().size() == indices.size());
    const int n_points = static_cast<int>(indices.size());
    for (int j=0; j!=n_points; ++j)
    {
      assert(face->GetPoints()[j] == points[ indices[j] ]);
    }
  }
  #endif

  const boost::shared_ptr<Template> my_template {
    new Template(
      edges,
      faces,
      face_point_indices,
      points
    )
  };
  assert(my_template);
  return my_template;
}

const std::vector<std::string> ribi::trim::Template::SeperateString(
  const std::string& input_original) noexcept
{
  PROFILE_FUNC();
  std::string input = boost::algorithm::replace_all_copy(input_original,"\t"," ");
  for (int i=0; i!=8; ++i)
  {
    input = boost::algorithm::replace_all_copy(input,"  "," ");
  }
  input = boost::algorithm::trim_copy(input_original);
  const char seperator  = ' ';
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}

#ifndef NDEBUG
void ribi::trim::Template::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::Template::Test");
  for (int i=1; i!=4; ++i)
  {
    const boost::shared_ptr<Template> my_template {
      CreateTest(i)
    };
    assert(my_template);
  }
  TRACE("Finished ribi::trim::Template::Test successfully");
}
#endif
