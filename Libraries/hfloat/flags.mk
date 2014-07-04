
# --- optimization and cpu type:
OFLAGS :=

## only use -march= if CPUTYPE is set:
ifeq ($(strip $(CPUTYPE)),) # CPUTYPE not set:
#CPU := $(shell uname -m)
#CPU := athlon
else # CPUTYPE is set:
ARCHFLAG := -march=$(CPUTYPE) -mcpu=$(CPUTYPE)
#  -march=  Generate code for given CPU
#  -mcpu=   Schedule code for given CPU
# Note that specifying `-march=CPU' implies `-mcpu=CPU'
# Mac PPC: -maltivec -mcpu=7450
OFLAGS += $(ARCHFLAG)
endif # CPUTYPE


OFLAGS += -O2
OFLAGS += -fomit-frame-pointer
#OFLAGS += -fno-exceptions # already in (main) makefile
OFLAGS += -ffast-math
#OFLAGS += -ftree-vectorize -ftree-vectorizer-verbose=9
#OFLAGS += -funsafe-math-optimizations # set by -ffast-math

# Control whether or not the compiler uses IEEE floating point
# comparisons.  These handle correctly the case where the result of a
# comparison is unordered.:
#OFLAGS += -mno-ieee-fp # only for i386 and x86-64

# Do not set ERRNO after calling math functions that are executed
# with a single instruction, e.g., sqrt.:
#OFLAGS += -fno-math-errno

#OFLAGS += -finline-limit=200
#OFLAGS += -mfancy-math-387 # Generate sin, cos, sqrt for FPU
#OFLAGS += -msse
#OFLAGS += -msse2
#OFLAGS += -foptimize-sibling-calls # Optimize sibling and tail recursive calls.
#OFLAGS += -fdelete-null-pointer-checks # Delete useless null pointer checks

#OFLAGS += -malign-double
#OFLAGS += -fschedule-insns2
#OFLAGS += -finline
#OFLAGS += -finline-functions
#OFLAGS += -fimplicit-templates


# --- warnings:
WFLAGS := -W -Wall
WFLAGS += -Wconversion # gives many warnings when llvm/clang is used
#WFLAGS += -Wno-conversion
WFLAGS += -Wsign-promo
WFLAGS += -Wsign-compare
WFLAGS += -Wunused
WFLAGS += -Wshadow
#WFLAGS += -Wold-style-cast # _only_ old-style casts are used
#WFLAGS += -Winline
#WFLAGS += -Wnested-externs
#WFLAGS += -Weffc++
#WFLAGS += -pedantic -Wno-long-long  # do not warn about using 'long long'
#WFLAGS += -Werror # warning is error

# Warn whenever an identifier which is not a macro is encountered in an #if
# directive, outside of defined.  Such identifiers are replaced with zero.
WFLAGS += -Wundef


# --- debuging:
GFLAGS = -g -fno-omit-frame-pointer
#GFLAGS += -fno-inline -fno-default-inline


# --- profiling:
PFLAGS = -pg -fno-omit-frame-pointer

# Emacs:
# Local Variables:
# frame-title-format: "HFLOAT flags"
# End:
