/* Compile output without 'DEFINES += B3_USE_CLEW' (warnings removed):

In file included from ..\..\Libraries\bullet3\src\Bullet3OpenCL\Initialize\b3OpenCLUtils.h:22:0,
                 from ..\..\Libraries\bullet3\src\Bullet3OpenCL\Initialize\b3OpenCLUtils.cpp:30:
..\..\Libraries\bullet3\src\Bullet3OpenCL\Initialize\b3OpenCLInclude.h:34:19: fatal error: CL/cl.h: No such file or directory
 #include <CL/cl.h>
                   ^
*/

/* Compile output with 'DEFINES += B3_USE_CLEW' (warnings removed):
                                                       ^
..\..\Libraries\bullet3\src\Bullet3OpenCL\Initialize\b3OpenCLUtils.cpp: In function '_cl_program* b3OpenCLUtils_compileCLProgramFromString(cl_context, cl_device_id, const char*, cl_int*, const char*, const char*, bool)':
..\..\Libraries\bullet3\src\Bullet3OpenCL\Initialize\b3OpenCLUtils.cpp:640:38: error: cannot convert 'const char*' to 'LPCWSTR {aka const wchar_t*}' for argument '1' to 'WINBOOL CreateDirectoryW(LPCWSTR, LPSECURITY_ATTRIBUTES)'
   CreateDirectory(sCachedBinaryPath,0);
                                      ^
..\..\Libraries\bullet3\src\Bullet3OpenCL\Initialize\b3OpenCLUtils.cpp:643:110: error: cannot convert 'char*' to 'LPCWSTR {aka const wchar_t*}' for argument '1' to 'void* CreateFileW(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE)'
    HANDLE binaryFileHandle = CreateFile(binaryFileName,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
                                                                                                              ^
..\..\Libraries\bullet3\src\Bullet3OpenCL\Initialize\b3OpenCLUtils.cpp:681:114: error: cannot convert 'const char*' to 'LPCWSTR {aka const wchar_t*}' for argument '1' to 'void* CreateFileW(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE)'
     HANDLE srcFileHandle = CreateFile(clFileNameForCaching,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
                                                                                                                  ^
..\..\Libraries\bullet3\src\Bullet3OpenCL\Initialize\b3OpenCLUtils.cpp:690:105: error: cannot convert 'char*' to 'LPCWSTR {aka const wchar_t*}' for argument '1' to 'void* CreateFileW(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE)'
       srcFileHandle = CreateFile(relativeFileName,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
                                                                                                         ^
*/
