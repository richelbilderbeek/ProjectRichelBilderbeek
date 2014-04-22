// Slightly adapted from the Boost.Multiprecision library its tutorial:
//
// http://www.boost.org/doc/libs/1_55_0/libs/multiprecision/doc/html/boost_multiprecision/tut/ints/egs/factorials.html

#include <iostream>
#include <iomanip>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/multiprecision/cpp_int.hpp>
#pragma GCC diagnostic pop

int main()
{
   using boost::multiprecision::cpp_int;
   //
   // Print all the factorials that will fit inside a 128-bit integer.
   //
   // Begin by building a big table of factorials, once we know just how
   // large the largest is, we'll be able to "pretty format" the results.
   //
   // Calculate the largest number that will fit inside 128 bits, we could
   // also have used numeric_limits<int128_t>::max() for this value:
   cpp_int limit = (cpp_int(1) << 128) - 1;
   //
   // Our table of values:
   std::vector<cpp_int> results;
   //
   // Initial values:
   unsigned i = 1;
   cpp_int factorial = 1;
   //
   // Cycle through the factorials till we reach the limit:
   while(factorial < limit)
   {
      results.push_back(factorial);
      ++i;
      factorial *= i;
   }
   //
   // Lets see how many digits the largest factorial was:
   unsigned digits = results.back().str().size();
   //
   // Now print them out, using right justification, while we're at it
   // we'll indicate the limit of each integer type, so begin by defining
   // the limits for 16, 32, 64 etc bit integers:
   cpp_int limits[] = {
      (cpp_int(1) << 16) - 1,
      (cpp_int(1) << 32) - 1,
      (cpp_int(1) << 64) - 1,
      (cpp_int(1) << 128) - 1,
   };
   std::string bit_counts[] = { "16", "32", "64", "128" };
   unsigned current_limit = 0;
   for(unsigned j = 0; j < results.size(); ++j)
   {
      if(limits[current_limit] < results[j])
      {
         std::string message = "Limit of " + bit_counts[current_limit] + " bit integers";
         std::cout << std::setfill('.') << std::setw(digits+1) << std::right << message << std::setfill(' ') << std::endl;
         ++current_limit;
      }
      std::cout << std::setw(digits + 1) << std::right << results[j] << std::endl;
   }
}
