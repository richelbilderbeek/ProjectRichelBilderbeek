#include "trianglemeshtemplate.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/algorithm/string.hpp>
#include <boost/math/constants/constants.hpp>

#include "trianglemeshface.h"
#include "trianglemeshfacefactory.h"
#include "fileio.h"
#include "trianglemeshhelper.h"
#include "trianglemeshpoint.h"
#include "trianglemeshpointfactory.h"
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

  
  TRACE("Load the points and faces created by Triangle");
  {
    const std::vector<std::string> v {
      ribi::fileio::FileIo().FileToVector(
        filename_node
      )
    };
    const int sz = v.size();
    const int percent = sz / 100 ? sz / 100: 1;
    for(int n=0; n!=sz; ++n)
    {
      if (n % percent == 0) std::clog << '%';
      const std::string line = v[n];
      if(n==0) continue; //No idea why this has to be skipped
      const std::vector<std::string> w { SeperateString(line) };
      if (w.empty() || w[0].empty() ||  w[0] == "#")
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
      const boost::shared_ptr<const ConstCoordinat2D> bottom(
        new ConstCoordinat2D(x,y)
      );

      const boost::shared_ptr<Point> node {
        PointFactory().Create(bottom)
      };
      m_points.push_back(node);
    }
  }

  TRACE("Load and translate faces");
  {
    const std::vector<std::string> v
      = ribi::fileio::FileIo().FileToVector(filename_ele);
    const int sz = v.size();
    const int percent = sz / 100 ? sz / 100: 1;
    for(int n=0; n!=sz; ++n)
    {
      if (n % percent == 0)
      {
        std::clog << '%';
      }
      const std::string line = v[n];
      if(n==0) continue;
      const std::vector<std::string> w { SeperateString(line) };
      if (w.empty() || w[0].empty() ||  w[0] == "#")
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
      std::vector<boost::shared_ptr<Point>> face_points {
        m_points[point1-1],
        m_points[point2-1],
        m_points[point3-1]
      };
      if (!Helper().IsClockwiseHorizontal(face_points))
      {
        std::reverse(face_points.begin(),face_points.end());
      }
      assert(Helper().IsClockwiseHorizontal(face_points));
      if (!Helper().IsConvex(face_points)) { Helper().MakeConvex(face_points); }
      assert(Helper().IsConvex(face_points) && "FaceFacory only accepts convex ordered points");

      const boost::shared_ptr<Face> face {
        FaceFactory().Create(
          face_points,
          FaceOrientation::horizontal
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
    case 0: return CreateTestTriangle2x2();
    case 1: return CreateTestSquare2x2();
    case 2: return CreateTest2x3();
    case 3: return CreateTest3x3();
  }

  assert(!"Should not get here");
  return boost::shared_ptr<Template>();
}

const boost::shared_ptr<ribi::trim::Template> ribi::trim::Template::CreateTestSquare2x2() noexcept
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
      const boost::shared_ptr<const ConstCoordinat2D> bottom {
        new ConstCoordinat2D(x,y)
      };
      const boost::shared_ptr<Point> point {
        PointFactory().Create(bottom)
      };
      points.push_back(point);
    }
  }
  #ifndef NDEBUG
  //Check that there is no coordinat present twice
  {
    for (int i=0; i!=n_points; ++i)
    {
      const boost::shared_ptr<const ConstCoordinat2D> a { points[i]->GetCoordinat() };
      for (int j=0; j!=n_points; ++j)
      {
        const boost::shared_ptr<const ConstCoordinat2D> b { points[j]->GetCoordinat() };
        if (a == b)
        {
          //assert(ribi::Distance(*a,*b) < 0.001);
          assert(boost::geometry::distance(*a,*b) < 0.001);
        }
        else
        {
          //assert(ribi::Distance(*a,*b) > 0.001);
          assert(boost::geometry::distance(*a,*b) > 0.001);
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

  const std::vector<std::pair<int,int>> edges {
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
      std::vector<boost::shared_ptr<Point>> face_points {
        points[ v[0] ],
        points[ v[1] ],
        points[ v[2] ]
      };
      
      if (!Helper().IsClockwiseHorizontal(face_points))
      {
        std::reverse(face_points.begin(),face_points.end());
      }
      assert(Helper().IsClockwiseHorizontal(face_points));
      const boost::shared_ptr<Face> face {
        FaceFactory().Create(
          face_points,
          FaceOrientation::horizontal
        )
      };
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
    /*
    const int n_points = static_cast<int>(indices.size());
    for (int j=0; j!=n_points; ++j)
    {
      //Only true when points are not reversed
      assert(face->GetPoints()[j] == points[ indices[j] ]);
    }
    */
  }
  #endif

  assert(faces.size()  == 2 && "A square consists of 2 triangles");
  assert(edges.size()  == 5 && "A square with a diagonal has 5 edges");
  assert(points.size() == 4 && "A square has 4 nodes");

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


const boost::shared_ptr<ribi::trim::Template> ribi::trim::Template::CreateTestTriangle2x2() noexcept
{
  std::vector<boost::shared_ptr<Face>> faces;
  std::vector<std::vector<int>> face_point_indices;
  std::vector<boost::shared_ptr<Point>> points;
  const int width = 2;
  //const int height = 2;
  const int n_points = 3; //Triangle
  points.reserve(n_points);

  //Create points
  {
    for(int i=0; i!=n_points; ++i)
    {
      const double x = static_cast<double>(i % width);
      const double y = static_cast<double>(i / width);
      const std::string boundary_type = "two_times_two";
      const boost::shared_ptr<const ConstCoordinat2D> bottom {
        new ConstCoordinat2D(x,y)
      };
      const boost::shared_ptr<Point> point {
        PointFactory().Create(bottom)
      };
      points.push_back(point);
    }
  }
  #ifndef NDEBUG
  //Check that there is no coordinat present twice
  {
    for (int i=0; i!=n_points; ++i)
    {
      const boost::shared_ptr<const ConstCoordinat2D> a { points[i]->GetCoordinat() };
      for (int j=0; j!=n_points; ++j)
      {
        const boost::shared_ptr<const ConstCoordinat2D> b { points[j]->GetCoordinat() };
        if (a == b)
        {
          assert(boost::geometry::distance(*a,*b) < 0.001);
        }
        else
        {
          assert(boost::geometry::distance(*a,*b) > 0.001);
        }
      }
    }
  }
  #endif

  //Load and translate faces
  face_point_indices = {
    { 0,1,2 }
  };

  const std::vector<std::pair<int,int>> edges {
    { 0,1 },
    { 0,2 },
    { 1,2 }
  };

  {
    for(auto v: face_point_indices)
    {
      assert(v.size() == 3);
      //I do not correct for one-base Triangle.exe output
      assert(v[0] >= 0);
      assert(v[1] >= 0);
      assert(v[2] >= 0);
      std::vector<boost::shared_ptr<Point>> face_points {
        points[ v[0] ],
        points[ v[1] ],
        points[ v[2] ]
      };
      
      if (!Helper().IsClockwiseHorizontal(face_points))
      {
        std::reverse(face_points.begin(),face_points.end());
      }
      #ifndef NDEBUG
      if (!Helper().IsClockwiseHorizontal(face_points))
      {
        TRACE("ERROR");
        TRACE(*face_points[0]);
        TRACE(*face_points[1]);
        TRACE(*face_points[2]);
        TRACE("BREAK");
      }
      #endif
      assert(Helper().IsClockwiseHorizontal(face_points));
      const boost::shared_ptr<Face> face {
        FaceFactory().Create(
          face_points,
          FaceOrientation::horizontal //?20140224
        )
      };
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
    /*
    const int n_points = static_cast<int>(indices.size());
    for (int j=0; j!=n_points; ++j)
    {
      //Only true when points are not reversed
      assert(face->GetPoints()[j] == points[ indices[j] ]);
    }
    */
  }
  #endif

  assert(faces.size()  == 1 && "A triangle is only 1 triangle");
  assert(edges.size()  == 3 && "A triangle has 3 edges");
  assert(points.size() == 3 && "A triangle has 3 nodes");

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
      const boost::shared_ptr<const ConstCoordinat2D> bottom {
        new ConstCoordinat2D(x,y)
      };
      const boost::shared_ptr<Point> point {
        PointFactory().Create(bottom)
      };
      points.push_back(point);
    }
  }
  #ifndef NDEBUG
  //Check that there is no coordinat present twice
  {
    for (int i=0; i!=n_points; ++i)
    {
      const boost::shared_ptr<const ConstCoordinat2D> a { points[i]->GetCoordinat() };
      for (int j=0; j!=n_points; ++j)
      {
        const boost::shared_ptr<const ConstCoordinat2D> b { points[j]->GetCoordinat() };
        if (a == b)
        {
          assert(boost::geometry::distance(*a,*b) < 0.001);
        }
        else
        {
          assert(boost::geometry::distance(*a,*b) > 0.001);
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

  const std::vector<std::pair<int,int>> edges {
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
      std::vector<boost::shared_ptr<Point>> face_points {
        points[point1],
        points[point2],
        points[point3]
      };
      
      if (!Helper().IsClockwiseHorizontal(face_points))
      {
        std::reverse(face_points.begin(),face_points.end());
      }
      assert(Helper().IsClockwiseHorizontal(face_points));
      const boost::shared_ptr<Face> face {
        FaceFactory().Create(
          face_points,
          FaceOrientation::horizontal
        )
      };
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
    /*
    const int n_points = static_cast<int>(indices.size());
    for (int j=0; j!=n_points; ++j)
    {
      //Only true when points are not reversed
      assert(face->GetPoints()[j] == points[ indices[j] ]);
    }
    */
  }
  #endif

  assert(faces.size()  == 4 && "Two adjacent squares consist of 4 triangles");
  assert(edges.size()  == 9 && "Two adjacent squares (with diagonals) have 9 edges");
  assert(points.size() == 6 && "Two adjacent squares have 6 nodes");

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
      const boost::shared_ptr<const ConstCoordinat2D> bottom {
        new ConstCoordinat2D(x,y)
      };
      const boost::shared_ptr<Point> point {
        PointFactory().Create(bottom)
      };
      points.push_back(point);
    }
  }
  #ifndef NDEBUG
  //Check that there is no coordinat present twice
  {
    for (int i=0; i!=n_points; ++i)
    {
      const boost::shared_ptr<const ConstCoordinat2D> a { points[i]->GetCoordinat() };
      for (int j=0; j!=n_points; ++j)
      {
        const boost::shared_ptr<const ConstCoordinat2D> b { points[j]->GetCoordinat() };
        if (a == b)
        {
          assert(boost::geometry::distance(*a,*b) < 0.001);
        }
        else
        {
          assert(boost::geometry::distance(*a,*b) > 0.001);
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

  const std::vector<std::pair<int,int>> edges {
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
      std::vector<boost::shared_ptr<Point>> face_points {
        points[point1],
        points[point2],
        points[point3]
      };
      
      if (!Helper().IsClockwiseHorizontal(face_points))
      {
        std::reverse(face_points.begin(),face_points.end());
      }
      assert(Helper().IsClockwiseHorizontal(face_points));
      const boost::shared_ptr<Face> face {
        FaceFactory().Create(
          face_points,
          FaceOrientation::horizontal
        )
      };
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
    /*
    const int n_points = static_cast<int>(indices.size());
    for (int j=0; j!=n_points; ++j)
    {
      //Only true when points are not reversed
      assert(face->GetPoints()[j] == points[ indices[j] ]);
    }
    */
  }
  #endif

  assert(faces.size()  ==  8 && "2x2 adjacent squares consist of 8 triangles");
  assert(edges.size()  == 16 && "2x2 adjacent squares (with diagonals) have 16 edges");
  assert(points.size() ==  9 && "2x2 adjacent squares have 9 nodes");

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



std::vector<std::string> ribi::trim::Template::SeperateString(
  const std::string& input_original) noexcept
{

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
  
  //IsClockWise
  {
    {
      //12 o'clock
      const boost::shared_ptr<const ConstCoordinat2D> a {
        new ConstCoordinat2D(0.0,-1.0)
      };
      //4 o'clock
      const boost::shared_ptr<const ConstCoordinat2D> b {
        new ConstCoordinat2D(0.83,0.5)
      };
      //8 o'clock
      const boost::shared_ptr<const ConstCoordinat2D> c {
        new ConstCoordinat2D(-0.83,0.5)
      };
      std::vector<boost::shared_ptr<Point>> points {
        PointFactory().Create(a),
        PointFactory().Create(b),
        PointFactory().Create(c)
      };
      points[0]->SetZ(1.0 * boost::units::si::meter);
      points[1]->SetZ(1.0 * boost::units::si::meter);
      points[2]->SetZ(1.0 * boost::units::si::meter);
      assert(Helper().IsClockwiseHorizontal(points));
      std::reverse(points.begin(),points.end());
      assert(!Helper().IsClockwiseHorizontal(points));
    }
    {
      //12 o'clock
      const boost::shared_ptr<const ConstCoordinat2D> a {
        new ConstCoordinat2D(0.0,-1.0)
      };
      //8 o'clock
      const boost::shared_ptr<const ConstCoordinat2D> b {
        new ConstCoordinat2D(-0.83,0.5)
      };
      //4 o'clock
      const boost::shared_ptr<const ConstCoordinat2D> c {
        new ConstCoordinat2D(0.83,0.5)
      };
      std::vector<boost::shared_ptr<Point>> points {
        PointFactory().Create(a),
        PointFactory().Create(b),
        PointFactory().Create(c)
      };
      points[0]->SetZ(1.0 * boost::units::si::meter);
      points[1]->SetZ(1.0 * boost::units::si::meter);
      points[2]->SetZ(1.0 * boost::units::si::meter);
      assert(!Helper().IsClockwiseHorizontal(points));
      std::reverse(points.begin(),points.end());
      assert(Helper().IsClockwiseHorizontal(points));
    }
  }
  for (int i=0; i!=4; ++i)
  {
    const boost::shared_ptr<Template> my_template {
      CreateTest(i)
    };
    assert(my_template);
    for (auto face: my_template->GetFaces())
    {
      if (!Helper().IsClockwiseHorizontal(face->GetPoints()))
      {
        TRACE("BREAK");
      }
      assert(Helper().IsClockwiseHorizontal(face->GetPoints()));
    }
  }
  TRACE("Finished ribi::trim::Template::Test successfully");
}
#endif
