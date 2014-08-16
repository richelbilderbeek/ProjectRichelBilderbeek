
FXTMULTOBJS = \
src/mult/auxil.o \
src/mult/workspace.o \
src/mult/carry.o \
src/mult/fxtmult.o \
src/mult/fxtsquare.o \
src/mult/fxtmultiply.o \
src/mult/diskaux.o \
src/mult/diskaux2.o \
src/mult/disk-row-col.o \
src/mult/diskcnvla.o \
src/mult/disksquare.o \
src/mult/diskmultiply.o \

DTOBJS= \
src/dt/hfdata.o  \
src/dt/dtadd.o \
src/dt/dtsub.o \
src/dt/dtmul.o \
src/dt/dtmulsh.o \
src/dt/dtldexp.o \
src/dt/dtconvdbl.o \
src/dt/dtconvint.o \
src/dt/dtdivsh.o \
src/dt/dtcmp.o \

HFOBJS= \
src/hf/hfloat.o \
src/hf/hfloatop.o \
src/hf/hfloatios.o \
src/hf/init.o \
src/hf/hfverbosity.o \
src/hf/compare.o \
src/hf/convert.o \
src/hf/print.o \
src/hf/binsave.o \
src/hf/funcsadd.o \
src/hf/funcsmul.o \
src/hf/funcsdiv.o \
src/hf/funcspow.o \
src/hf/funcs2pw.o \
src/hf/funcsrt.o  \
src/hf/mean.o \
src/hf/mulpow.o \
src/hf/frac.o \
src/hf/round.o \
src/hf/contfrac.o \
src/hf/sumalt.o \
src/hf/ratpoly.o \
src/hf/itiroot.o \
src/hf/itsqrt.o \
src/hf/itinverse.o \

PIOBJS=\
src/pi/piagmsch.o \
src/pi/pi4th.o \
src/pi/piagm.o \
src/pi/piarctan.o \
src/pi/pideriv.o \
src/pi/piagm3.o \
src/pi/pi5th.o \
src/pi/pi2nd.o \
src/pi/pi3rd.o \
src/pi/pi9th.o \
src/pi/picubagm.o \
src/pi/rprimesum.o \
src/pi/rprimesum4th.o \

TZOBJS= \
src/tz/hfconst.o \
src/tz/pilogq.o \
src/tz/log.o \
src/tz/funcstrz.o \
src/tz/itexp.o \
src/tz/power.o \
src/tz/zeta3.o \
src/tz/elliptic-k.o \
src/tz/elliptic-e.o \

OBJS =
OBJS += $(FXTMULTOBJS)
OBJS += $(DTOBJS)
OBJS += $(HFOBJS)
OBJS += $(PIOBJS)
OBJS += $(TZOBJS)

#
SRC=$(OBJS:.o=.cc)

#-------------------------------------
