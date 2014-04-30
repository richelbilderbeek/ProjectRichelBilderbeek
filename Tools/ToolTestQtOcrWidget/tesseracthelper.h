#ifndef TESSERACTHELPER_H
#define TESSERACTHELPER_H

#include <string>

//These functions must be in the global namespace,
//because tesseract assumes these exist in the
//namespace-absent C header files
#include <signal.h>
#include <unistd.h>

#define BILDERBIKKEL_FIX_COMPILER_ERROR_CREATEPROCESS

#define BILDERBIKKEL_REMOVE_FSYNC
#define BILDERBIKKEL_REMOVE_OTHER_MAIN
#define BILDERBIKKEL_REMOVE_SLEEP

//Call of Linux fork() or the Windows equivalent
#define BILDERBIKKEL_REMOVE_SVSYNCH_STARTPROCESS_SVUTIL_CPP

//Call of Linux fork() or the Windows equivalent
#define BILDERBIKKEL_REMOVE_SVNETWORK_RECEIVE_SVUTIL_CPP

#define BILDERBIKKEL_REMOVE_USELESS_GLOBAL_DEMODIR

#ifndef BILDERBIKKEL_STRTOK_R_ALREADY_DEFINED
#define strtok_r(s, d, p) strtok(s, d)
#endif

long int Nrand48(unsigned short int xsubi[3]);

#ifndef M_PI
#define M_PI 3.14159265359
#endif

#endif // TESSERACTHELPER_H
