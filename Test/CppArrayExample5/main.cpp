#include <array>
#include <cstdlib>
#include <vector>

#include <iostream>
#include <string>

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/microsec_time_clock.hpp>

const int n_repeats = 100000;
const int sz = 10000;

class TestTimer
{
public:
    TestTimer(const std::string & name) : name(name),
        start(boost::date_time::microsec_clock<boost::posix_time::ptime>::local_time())
    {
    }

    ~TestTimer()
    {
        using namespace std;
        using namespace boost;

        posix_time::ptime now(date_time::microsec_clock<posix_time::ptime>::local_time());
        posix_time::time_duration d = now - start;

        cout << name << " completed in " << d.total_milliseconds() / 1000.0 <<
            " seconds" << endl;
    }

private:
    std::string name;
    boost::posix_time::ptime start;
};

struct Pixel
{
    Pixel(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0) : r(r), g(g), b(b)
    {
    }

    unsigned char r, g, b;
};

void UseVector()
{
  TestTimer t("UseVector");

  for(int i = 0; i < n_repeats; ++i)
  {
    std::vector<Pixel> pixels(sz, Pixel(255,0,0));
  }
}

void UseStdArray()
{
  TestTimer t("UseStdArry");

  for(int i = 0; i!=n_repeats; ++i)
  {
    std::array<Pixel,sz> pixels;
    pixels.fill(Pixel(255,0,0));
  }
}

void UseArray()
{
  TestTimer t("UseArray");

  for(int i = 0; i < n_repeats; ++i)
  {
    Pixel * pixels = (Pixel *)malloc(sizeof(Pixel) * sz);

    for(int i = 0 ; i < sz; ++i)
    {
        pixels[i].r = 255;
        pixels[i].g =   0;
        pixels[i].b =   0;
    }

    free(pixels);
  }
}

int main()
{
  TestTimer t1("The whole thing");

  UseArray();
  UseStdArray();
  UseVector();
}


/* When #define USE_IMPROVED in debug mode


*/

/* When #define USE_IMPROVED in release mode



*/
