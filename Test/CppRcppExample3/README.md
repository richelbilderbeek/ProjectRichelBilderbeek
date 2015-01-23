# CppRcppExample 3

Example that uses C++ code (main.cpp) in an R project (main.R).

In this case, the C++ function DoMagic is called, a function that works on a std::vector<int> using the C++11 standard.

This approach failed, because I could not get R updated to 3.1.2 (a requirement for the R package Rcpp11) due to amongst others broken dependencies in my apt-get repositories.