# Attempt to port Triangle to C++

INCLUDEPATH += \
    ../../Tools/ToolTriangleCpp

SOURCES += \
    # ../../Tools/ToolTriangleCpp/trianglecppmain.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppmesh.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppmemorypool.cpp \
    ../../Tools/ToolTriangleCpp/trianglecpparguments.cpp \
    ../../Tools/ToolTriangleCpp/trianglecpptriangle.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppotri.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppedge.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppinfo.cpp \
    ../../Tools/ToolTriangleCpp/trianglecpposub.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppvertex.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppbadsubseg.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppbadtriang.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppflipstacker.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppevent.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppsplaynode.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppsyntax.cpp \
    ../../Tools/ToolTriangleCpp/trianglecpptriangulateio.cpp \
    ../../Tools/ToolTriangleCpp/trianglecpptrimalloc.cpp \
    ../../Tools/ToolTriangleCpp/trianglecpplocateresult.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppinsertvertexresult.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppfinddirectionresult.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppfile.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppstring.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppglobals.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppdefines.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppvertextype.cpp \
    ../../Tools/ToolTriangleCpp/trianglecpphelper.cpp \
    ../../Tools/ToolTriangleCpp/trianglecppmeshbuilder.cpp

HEADERS += \
    ../../Tools/ToolTriangleCpp/trianglecppmain.h \
    ../../Tools/ToolTriangleCpp/trianglecppmesh.h \
    ../../Tools/ToolTriangleCpp/trianglecppmemorypool.h \
    ../../Tools/ToolTriangleCpp/trianglecpparguments.h \
    ../../Tools/ToolTriangleCpp/trianglecpptriangle.h \
    ../../Tools/ToolTriangleCpp/trianglecppotri.h \
    ../../Tools/ToolTriangleCpp/trianglecppedge.h \
    ../../Tools/ToolTriangleCpp/trianglecppinfo.h \
    ../../Tools/ToolTriangleCpp/trianglecpposub.h \
    ../../Tools/ToolTriangleCpp/trianglecppvertex.h \
    ../../Tools/ToolTriangleCpp/trianglecppbadsubseg.h \
    ../../Tools/ToolTriangleCpp/trianglecppbadtriang.h \
    ../../Tools/ToolTriangleCpp/trianglecppflipstacker.h \
    ../../Tools/ToolTriangleCpp/trianglecppevent.h \
    ../../Tools/ToolTriangleCpp/trianglecppsplaynode.h \
    ../../Tools/ToolTriangleCpp/trianglecppsyntax.h \
    ../../Tools/ToolTriangleCpp/trianglecpptriangulateio.h \
    ../../Tools/ToolTriangleCpp/trianglecppglobals.h \
    ../../Tools/ToolTriangleCpp/trianglecpptrimalloc.h \
    ../../Tools/ToolTriangleCpp/trianglecppfwd.h \
    ../../Tools/ToolTriangleCpp/trianglecppdefines.h \
    ../../Tools/ToolTriangleCpp/trianglecpplocateresult.h \
    ../../Tools/ToolTriangleCpp/trianglecppinsertvertexresult.h \
    ../../Tools/ToolTriangleCpp/trianglecppfinddirectionresult.h \
    ../../Tools/ToolTriangleCpp/trianglecppfile.h \
    ../../Tools/ToolTriangleCpp/trianglecppstring.h \
    ../../Tools/ToolTriangleCpp/trianglecppvertextype.h \
    ../../Tools/ToolTriangleCpp/trianglecpphelper.h \
    ../../Tools/ToolTriangleCpp/trianglecpptypedefs.h \
    ../../Tools/ToolTriangleCpp/trianglecppmeshbuilder.h

OTHER_FILES += \
    ../ToolTriangleCpp/ToolTriangleCpp.txt
