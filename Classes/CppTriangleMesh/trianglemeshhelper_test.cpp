#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "trianglemeshhelper.h"

//#include <iomanip>
//#include <iostream>
#include <sstream>

//#include <boost/lexical_cast.hpp>
//#include <boost/make_shared.hpp>
#include <boost/math/constants/constants.hpp>

#include "geometry.h"
#include "testtimer.h"
#include "trace.h"
#include "trianglemeshface.h"
#include "trianglemeshhelper.h"
#include "trianglemeshpoint.h"
#include "trianglemeshpointfactory.h"
//#include "xml.h"
#pragma GCC diagnostic pop

#ifndef NDEBUG
void ribi::trim::Helper::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  Geometry();

  const TestTimer test_timer(__func__,__FILE__,1.0);
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  using boost::geometry::get;
  const bool verbose{false};

  //CalcCenter
  //CalcWindingHorizontal
  const Helper h;
  //IsClockwiseHorizontal 1
  //IsClockwiseHorizontal 2
  //IsClockwiseVertical
  if (verbose) { TRACE("IsConvex, 2D, from error"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
    std::vector<boost::shared_ptr<const Coordinat2D>> coordinats2d;
    {
      const auto coordinat
        = boost::make_shared<Coordinat2D>(9.2885,29.5639);
      assert(coordinat);
      coordinats2d.push_back(coordinat);
    }
    {
      const auto coordinat
        = boost::make_shared<Coordinat2D>(9.2885,40.6764);
      assert(coordinat);
      coordinats2d.push_back(coordinat);
    }
    {
      const auto coordinat
        = boost::make_shared<Coordinat2D>(17.497,44.4009);
      assert(coordinat);
      coordinats2d.push_back(coordinat);
    }
    {
      const auto coordinat
        = boost::make_shared<Coordinat2D>(17.497,33.0765);
      assert(coordinat);
      coordinats2d.push_back(coordinat);
    }
    std::vector<boost::shared_ptr<Point>> points;
    for (const auto& coordinat2d: coordinats2d)
    {
      const auto point(PointFactory().Create(coordinat2d));
      assert(point);
      point->SetZ(0.0 * boost::units::si::meter);
      points.push_back(point);
    }
    assert(coordinats2d.size() == points.size());
    assert(h.IsConvex(points));
    assert(h.IsConvex(AddConst(points)));
  }
  if (verbose) { TRACE("IsConvex, 3D, from error"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
    std::vector<boost::shared_ptr<const Coordinat3D>> coordinats3d;
    {
      const auto coordinat = boost::make_shared<Coordinat3D>(0.0,2.0,1.0);
      assert(coordinat);
      coordinats3d.push_back(coordinat);
    }
    {
      const auto coordinat = boost::make_shared<Coordinat3D>(0.0,2.0,2.0);
      assert(coordinat);
      coordinats3d.push_back(coordinat);
    }
    {
      const auto coordinat = boost::make_shared<Coordinat3D>(1.0,1.0,2.0);
      assert(coordinat);
      coordinats3d.push_back(coordinat);
    }
    std::vector<boost::shared_ptr<Point>> points;
    for (const auto& coordinat: coordinats3d)
    {
      boost::shared_ptr<const Coordinat2D> coordinat2d(
        new Coordinat2D(
          boost::geometry::get<0>(*coordinat),
          boost::geometry::get<1>(*coordinat)
        )
      );
      const auto point(PointFactory().Create(coordinat2d));
      assert(point);
      point->SetZ(boost::geometry::get<2>(*coordinat) * boost::units::si::meter);
      points.push_back(point);
    }
    assert(points.size() == coordinats3d.size());
    assert(h.IsConvex(points));
    assert(h.IsConvex(AddConst(points)));
  }
  if (verbose) { TRACE("IsConvex, 2D, from #228, this is the 2D projection of the next test"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
  /*
    This is not convex

    (-14.335613337899998705,100)
    (-14.335613337899998705,0)
    (-0.302499999969750000,100)
    (-0.302499999969750000,0)
  */

    const Geometry::Coordinats2D points {
      Geometry::Coordinat2D(-14.335613337899998705,100),
      Geometry::Coordinat2D(-14.335613337899998705,0),
      Geometry::Coordinat2D(-0.302499999969750000,100),
      Geometry::Coordinat2D(-0.302499999969750000,0)
    };
    assert(!Geometry().IsConvex(points));
  }
  #ifdef FIX_ISSUE_228
  if (verbose) { TRACE("IsCounterClockwise, 3D, from #228"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
    /*
    This is not counterclockwise, it is a Z shape on the Y=2 plane

    Observer is behind these points

           Z           Y
           |          /
           |         /
     A---C-|-+      /
    /|  /| |/|     /
   +---+---+ |    /
   | | | | | |   /
   | | | | | |  /
   | | | | | | /
   | | | | | |/
  -|-B-|-D-|-+- - - - - - Y = 2.0
   |/  |/  |/
  -+---+---O------------- X
          /|
         / |
        /  |

    (-3.78624,2,10)'
    (-3.78624,2,0)'
    (-0.55,2,10)'
    (-0.55,2,0)'
    Observer: (-2.1871,3.74169,5)
    */
    boost::shared_ptr<const Coordinat2D> left{new Coordinat2D(-3.78624,2)};
    boost::shared_ptr<const Coordinat2D> right{new Coordinat2D(-0.55,2)};
    std::vector<boost::shared_ptr<ribi::trim::Point>> points {
      PointFactory().Create( left,10.0 * boost::units::si::meter),
      PointFactory().Create( left, 0.0 * boost::units::si::meter),
      PointFactory().Create(right,10.0 * boost::units::si::meter),
      PointFactory().Create(right, 0.0 * boost::units::si::meter)
    };

    assert(!h.IsConvex(points));
    assert(!h.IsConvex(AddConst(points)));
    assert(!h.IsPlane(points));

    const Coordinat3D observer{-2.1871,3.74169,5};
    assert(!h.IsCounterClockwise(points,observer));
    assert(!h.IsCounterClockwise(AddConst(points),observer));
    assert(!h.IsClockwise(points,observer));
    assert(!h.IsClockwise(AddConst(points),observer));

    h.MakeCounterClockwise(points,observer);
    assert( h.IsCounterClockwise(points,observer));
    assert( h.IsCounterClockwise(AddConst(points),observer));
    assert(!h.IsClockwise(points,observer));
    assert(!h.IsClockwise(AddConst(points),observer));
  }
  if (verbose) { TRACE("IsCounterClockwise, 3D, from #228, test for positive"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
    /*
    This is counterclockwise

    Observer is behind these points

           Z           Y
           |          /
           |         /
     C---D-|-+      /
    /|  /| |/|     /
   +---+---+ |    /
   | | | | | |   /
   | | | | | |  /
   | | | | | | /
   | | | | | |/
  -|-B-|-A-|-+-
   |/  |/  |/
  -+---+---O-------- X
          /|
         / |
        /  |

    (-0.55,2,0)
    (-3.78624,2,0)
    (-3.78624,2,10)
    (-0.55,2,10)
    Observer: (-2.1871,3.74169,5)
    */
    boost::shared_ptr<const Coordinat2D> left{new Coordinat2D(-3.78624,2)};
    boost::shared_ptr<const Coordinat2D> right{new Coordinat2D(-0.55,2)};
    std::vector<boost::shared_ptr<ribi::trim::Point>> points {
      PointFactory().Create(right, 0.0 * boost::units::si::meter),
      PointFactory().Create( left, 0.0 * boost::units::si::meter),
      PointFactory().Create( left,10.0 * boost::units::si::meter),
      PointFactory().Create(right,10.0 * boost::units::si::meter)
    };

    assert(h.IsConvex(points));
    assert(h.IsConvex(AddConst(points)));

    const Coordinat3D observer{-2.1871,3.74169,5};
    assert(h.IsCounterClockwise(points,observer));
    assert(h.IsCounterClockwise(AddConst(points),observer));
    assert(!h.IsClockwise(points,observer));
    assert(!h.IsClockwise(AddConst(points),observer));

    h.MakeCounterClockwise(points,observer);
    assert( h.IsCounterClockwise(points,observer));
    assert( h.IsCounterClockwise(AddConst(points),observer));
    assert(!h.IsClockwise(points,observer));
    assert(!h.IsClockwise(AddConst(points),observer));
  }
  #endif // FIX_ISSUE_228
  #ifdef BRUTE_FORCE_TEST_MAKECOUNTERCLOCKWISE
  if (verbose) { TRACE("MakeCounterClockwise, make shuffled points counterclockwise, from #228"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
    /*

    Observer is behind these points

           Z           Y
           |          /
           |         /
     C---D-|-+      /
    /|  /| |/|     /
   +---+---+ |    /
   | | | | | |   /
   | | | | | |  /
   | | | | | | /
   | | | | | |/
  -|-B-|-A-|-+-
   |/  |/  |/
  -+---+---O-------- X
          /|
         / |
        /  |

    (-0.55,2,0)
    (-3.78624,2,0)
    (-3.78624,2,10)
    (-0.55,2,10)
    Observer: (-2.1871,3.74169,5)
    */
    boost::shared_ptr<const Coordinat2D> left{new Coordinat2D(-3.78624,2)};
    boost::shared_ptr<const Coordinat2D> right{new Coordinat2D(-0.55,2)};
    std::vector<boost::shared_ptr<ribi::trim::Point>> points {
      PointFactory().Create(right, 0.0 * boost::units::si::meter),
      PointFactory().Create( left, 0.0 * boost::units::si::meter),
      PointFactory().Create( left,10.0 * boost::units::si::meter),
      PointFactory().Create(right,10.0 * boost::units::si::meter)
    };

    assert(h.IsConvex(points));
    assert(h.IsConvex(AddConst(points)));

    const Coordinat3D observer{-2.1871,3.74169,5};

    for (int i{0}; i!=50; ++i)
    {
      std::random_shuffle(std::begin(points),std::end(points));

      h.MakeCounterClockwise(points,observer);
      assert( h.IsCounterClockwise(points,observer));
      assert( h.IsCounterClockwise(AddConst(points),observer));
      assert(!h.IsClockwise(points,observer));
      assert(!h.IsClockwise(AddConst(points),observer));
    }
  }
  #endif // BRUTE_FORCE_TEST_MAKECOUNTERCLOCKWISE
  //OrderByX
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
    const auto f = h.OrderByX();
    const auto v = ribi::trim::PointFactory().CreateTestPrism();
    const int sz { static_cast<int>(v.size()) };
    for (int i=0; i!=sz; ++i)
    {
      const auto lhs = v[i];
      for (int j=i; j!=sz; ++j)
      {
        const auto rhs = v[j];
        if (i == j)
        {
          assert(*lhs == *rhs);
          assert(!f(lhs,rhs));
          assert(!f(rhs,lhs));
        }
        if (i != j)
        {
          assert(*lhs != *rhs);
          assert(f(lhs,rhs) != f(rhs,lhs));
        }
      }
    }
  }
  //MakeConvex
  if (verbose) { TRACE("MakeConvex"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
    boost::shared_ptr<const Coordinat2D> left {new Coordinat2D(1.17557,2.35781)};
    boost::shared_ptr<const Coordinat2D> right{new Coordinat2D(2.23114,3.23607)};
    std::vector<boost::shared_ptr<ribi::trim::Point>> points {
      PointFactory().Create(right,6.0 * boost::units::si::meter),
      PointFactory().Create(right,5.0 * boost::units::si::meter),
      PointFactory().Create( left,6.0 * boost::units::si::meter),
      PointFactory().Create( left,5.0 * boost::units::si::meter)
    };
    h.MakeConvex(points);
    assert(h.IsConvex(points));
  }

  //MakeConvex
  if (verbose) { TRACE("MakeConvex, from #228"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
    /*
    (-0.55,2,0)
    (-3.78624,2,0)
    (-0.55,2,10)
    (-3.78624,2,10)
    Observer: (-2.1871,3.74169,5)
    */

    boost::shared_ptr<const Coordinat2D> left {new Coordinat2D(-3.78624,2)};
    boost::shared_ptr<const Coordinat2D> right{new Coordinat2D(-0.55,2)};
    std::vector<boost::shared_ptr<ribi::trim::Point>> points {
      PointFactory().Create(right, 0.0 * boost::units::si::meter),
      PointFactory().Create( left, 0.0 * boost::units::si::meter),
      PointFactory().Create(right,10.0 * boost::units::si::meter),
      PointFactory().Create( left,10.0 * boost::units::si::meter)
    };
    h.MakeConvex(points);
    assert(h.IsConvex(points));
  }
  #ifdef BRUTE_FORCE_TEST_ISSUE228
  if (verbose) { TRACE("MakeConvex, #228"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
    /*
    (-3.78624,2,10)
    (-0.55,2,10)
    (-0.55,2,20)
    (-3.78624,2,20)
    */
    boost::shared_ptr<const Coordinat2D> left{new Coordinat2D(-3.78624,2)};
    boost::shared_ptr<const Coordinat2D> right{new Coordinat2D(-0.55,2)};
    std::vector<boost::shared_ptr<ribi::trim::Point>> points {
      PointFactory().Create( left,10.0 * boost::units::si::meter),
      PointFactory().Create(right,10.0 * boost::units::si::meter),
      PointFactory().Create(right,20.0 * boost::units::si::meter),
      PointFactory().Create( left,20.0 * boost::units::si::meter)
    };
    for (int i=0; i!=5*4*3*2*1; ++i)
    {
      std::random_shuffle(std::begin(points),std::end(points));
      h.MakeConvex(points);
      #ifndef NDEBUG
      if(!h.IsConvex(points))
      {
        TRACE("ERROR");
      }
      #endif
      assert(h.IsConvex(points));
    }
  }
  if (verbose) { TRACE("Making CounterClockWise (seen from an observer), #228"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
    /* Make these counterclockwise
    (-3.78624,2,0)
    (-3.78624,2,10)
    (-0.55,2,0)
    (-0.55,2,10)
    Observer: (-2.1871,3.74169,5) and others
    */
    boost::shared_ptr<const Coordinat2D> left{new Coordinat2D(-3.78624,2)};
    boost::shared_ptr<const Coordinat2D> right{new Coordinat2D(-0.55,2)};
    std::vector<boost::shared_ptr<ribi::trim::Point>> points {
      PointFactory().Create( left, 0.0 * boost::units::si::meter),
      PointFactory().Create(right,10.0 * boost::units::si::meter),
      PointFactory().Create(right, 0.0 * boost::units::si::meter),
      PointFactory().Create( left,10.0 * boost::units::si::meter)
    };

    for (const Coordinat3D& observer:
      {
        Coordinat3D(-2.1871 ,3.74169 ,5),
        Coordinat3D(-1.50283,0.990808,5),
        Coordinat3D(-2.1871 ,3.74169 ,5)
      }
    )
    {
      std::sort(std::begin(points),std::end(points),Helper().OrderByX());

      for (int i=0; i!=5*4*3*2*1; ++i)
      {
        if (Helper().IsCounterClockwise(points,observer)) break;
        std::next_permutation(std::begin(points),std::end(points),Helper().OrderByX());
      }
      assert(Helper().IsCounterClockwise(points,observer));
    }
  }
  if (verbose) { TRACE("MakCounterClockWise, #228"); }
  {
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
    /* Make these counterclockwise

    (-0.55,2,0)
    (-3.78624,2,0)
    (-0.55,2,10)
    (-3.78624,2,10)
    Observer: (-2.1871,3.74169,5)

    */
    boost::shared_ptr<const Coordinat2D> left{new Coordinat2D(-3.78624,2)};
    boost::shared_ptr<const Coordinat2D> right{new Coordinat2D(-0.55,2)};
    std::vector<boost::shared_ptr<ribi::trim::Point>> points {
      PointFactory().Create( left, 0.0 * boost::units::si::meter),
      PointFactory().Create(right, 0.0 * boost::units::si::meter),
      PointFactory().Create(right,10.0 * boost::units::si::meter),
      PointFactory().Create( left,10.0 * boost::units::si::meter)
    };

    for (const Coordinat3D& observer:
      {
        Coordinat3D(-2.1871 ,3.74169 ,5),
        Coordinat3D(-1.50283,0.990808,5),
        Coordinat3D(-2.1871 ,3.74169 ,5)
      }
    )
    {
      for (int i=0; i!=4*3*2*1*2; ++i) //Try -on average- each permutation twice
      {
        std::random_shuffle(std::begin(points),std::end(points));
        Helper().MakeCounterClockwise(points,observer);
        assert(Helper().IsCounterClockwise(points,observer));
      }
    }
  }
  #endif // BRUTE_FORCE_TEST_ISSUE228

  //assert(!"Yay, fixed #228");
}
#endif
