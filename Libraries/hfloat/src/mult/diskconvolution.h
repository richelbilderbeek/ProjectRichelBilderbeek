#if !defined  HAVE_DISKCONVOLUTION_H__
#define       HAVE_DISKCONVOLUTION_H__

#include "fxttypes.h"

// mult/diskcnvla.cc:
void disk_weighted_complex_auto_convolution(int fd1, int fd2,
                                            double *fr, ulong fn, ulong al,
                                            double v, double nx,
                                            int zq1=0, int zq3=0);

#endif  // !defined HAVE_DISKCONVOLUTION_H__
