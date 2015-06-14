win32 {
  # Windows only
  message("CLN, built for Windows")

  INCLUDEPATH += \
    ../../Libraries/cln-1.3.3 \
    ../../Libraries/cln-1.3.3/autoconf \
    ../../Libraries/cln-1.3.3/include \
    ../../Libraries/cln-1.3.3/src

  # Input
  HEADERS += \
    #../../Libraries/cln-1.3.3/autoconf/cl_config.h \
    #../../Libraries/cln-1.3.3/include/cln/cln.h \
    #../../Libraries/cln-1.3.3/include/cln/complex.h \
    #../../Libraries/cln-1.3.3/include/cln/complex_class.h \
    #../../Libraries/cln-1.3.3/include/cln/complex_io.h \
    #../../Libraries/cln-1.3.3/include/cln/complex_ring.h \
    #../../Libraries/cln-1.3.3/include/cln/condition.h \
    #../../Libraries/cln-1.3.3/include/cln/config.h \
    #../../Libraries/cln-1.3.3/include/cln/dfloat.h \
    #../../Libraries/cln-1.3.3/include/cln/dfloat_class.h \
    #../../Libraries/cln-1.3.3/include/cln/dfloat_io.h \
    #../../Libraries/cln-1.3.3/include/cln/exception.h \
    #../../Libraries/cln-1.3.3/include/cln/ffloat.h \
    #../../Libraries/cln-1.3.3/include/cln/ffloat_class.h \
    #../../Libraries/cln-1.3.3/include/cln/ffloat_io.h \
    #../../Libraries/cln-1.3.3/include/cln/float.h \
    #../../Libraries/cln-1.3.3/include/cln/float_class.h \
    #../../Libraries/cln-1.3.3/include/cln/float_io.h \
    #../../Libraries/cln-1.3.3/include/cln/floatformat.h \
    #../../Libraries/cln-1.3.3/include/cln/floatparam.h \
    #../../Libraries/cln-1.3.3/include/cln/GV.h \
    #../../Libraries/cln-1.3.3/include/cln/GV_complex.h \
    #../../Libraries/cln-1.3.3/include/cln/GV_integer.h \
    #../../Libraries/cln-1.3.3/include/cln/GV_modinteger.h \
    #../../Libraries/cln-1.3.3/include/cln/GV_number.h \
    #../../Libraries/cln-1.3.3/include/cln/GV_rational.h \
    #../../Libraries/cln-1.3.3/include/cln/GV_real.h \
    #../../Libraries/cln-1.3.3/include/cln/host_cpu.h \
    #../../Libraries/cln-1.3.3/include/cln/input.h \
    #../../Libraries/cln-1.3.3/include/cln/integer.h \
    #../../Libraries/cln-1.3.3/include/cln/integer_class.h \
    #../../Libraries/cln-1.3.3/include/cln/integer_io.h \
    #../../Libraries/cln-1.3.3/include/cln/integer_ring.h \
    #../../Libraries/cln-1.3.3/include/cln/intparam.h \
    #../../Libraries/cln-1.3.3/include/cln/io.h \
    #../../Libraries/cln-1.3.3/include/cln/lfloat.h \
    #../../Libraries/cln-1.3.3/include/cln/lfloat_class.h \
    #../../Libraries/cln-1.3.3/include/cln/lfloat_io.h \
    #../../Libraries/cln-1.3.3/include/cln/malloc.h \
    #../../Libraries/cln-1.3.3/include/cln/modinteger.h \
    #../../Libraries/cln-1.3.3/include/cln/modules.h \
    #../../Libraries/cln-1.3.3/include/cln/null_ring.h \
    #../../Libraries/cln-1.3.3/include/cln/number.h \
    #../../Libraries/cln-1.3.3/include/cln/number_io.h \
    #../../Libraries/cln-1.3.3/include/cln/numtheory.h \
    #../../Libraries/cln-1.3.3/include/cln/object.h \
    #../../Libraries/cln-1.3.3/include/cln/output.h \
    #../../Libraries/cln-1.3.3/include/cln/proplist.h \
    #../../Libraries/cln-1.3.3/include/cln/random.h \
    #../../Libraries/cln-1.3.3/include/cln/rational.h \
    #../../Libraries/cln-1.3.3/include/cln/rational_class.h \
    #../../Libraries/cln-1.3.3/include/cln/rational_io.h \
    #../../Libraries/cln-1.3.3/include/cln/rational_ring.h \
    #../../Libraries/cln-1.3.3/include/cln/real.h \
    #../../Libraries/cln-1.3.3/include/cln/real_class.h \
    #../../Libraries/cln-1.3.3/include/cln/real_io.h \
    #../../Libraries/cln-1.3.3/include/cln/real_ring.h \
    #../../Libraries/cln-1.3.3/include/cln/ring.h \
    #../../Libraries/cln-1.3.3/include/cln/sfloat.h \
    #../../Libraries/cln-1.3.3/include/cln/sfloat_class.h \
    #../../Libraries/cln-1.3.3/include/cln/sfloat_io.h \
    #../../Libraries/cln-1.3.3/include/cln/string.h \
    #../../Libraries/cln-1.3.3/include/cln/SV.h \
    #../../Libraries/cln-1.3.3/include/cln/SV_complex.h \
    #../../Libraries/cln-1.3.3/include/cln/SV_integer.h \
    #../../Libraries/cln-1.3.3/include/cln/SV_number.h \
    #../../Libraries/cln-1.3.3/include/cln/SV_rational.h \
    #../../Libraries/cln-1.3.3/include/cln/SV_real.h \
    #../../Libraries/cln-1.3.3/include/cln/SV_ringelt.h \
    #../../Libraries/cln-1.3.3/include/cln/symbol.h \
    #../../Libraries/cln-1.3.3/include/cln/timing.h \
    #../../Libraries/cln-1.3.3/include/cln/types.h \
    #../../Libraries/cln-1.3.3/include/cln/univpoly.h \
    #../../Libraries/cln-1.3.3/include/cln/univpoly_complex.h \
    #../../Libraries/cln-1.3.3/include/cln/univpoly_integer.h \
    #../../Libraries/cln-1.3.3/include/cln/univpoly_modint.h \
    #../../Libraries/cln-1.3.3/include/cln/univpoly_rational.h \
    #../../Libraries/cln-1.3.3/include/cln/univpoly_real.h \
    #../../Libraries/cln-1.3.3/include/cln/V.h \
    #../../Libraries/cln-1.3.3/include/cln/version.h \
    #../../Libraries/cln-1.3.3/src/base/cl_alloca.h \
    #../../Libraries/cln-1.3.3/src/base/cl_base_config.h \
    #../../Libraries/cln-1.3.3/src/base/cl_gmpconfig.h \
    #../../Libraries/cln-1.3.3/src/base/cl_inline.h \
    #../../Libraries/cln-1.3.3/src/base/cl_inline2.h \
    #../../Libraries/cln-1.3.3/src/base/cl_iterator.h \
    #../../Libraries/cln-1.3.3/src/base/cl_low.h \
    #../../Libraries/cln-1.3.3/src/base/cl_macros.h \
    #../../Libraries/cln-1.3.3/src/base/cl_maybe_inline.h \
    #../../Libraries/cln-1.3.3/src/base/cl_N.h \
    #../../Libraries/cln-1.3.3/src/base/cl_offsetof.h \
    #../../Libraries/cln-1.3.3/src/base/cl_sysdep.h \
    #../../Libraries/cln-1.3.3/src/base/cl_xmacros.h \
    #../../Libraries/cln-1.3.3/src/complex/cl_C.h \
    #../../Libraries/cln-1.3.3/src/float/cl_F.h \
    #../../Libraries/cln-1.3.3/src/integer/cl_I.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_fix16.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_fix29.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_fix32.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_int.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_int32.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_montgom.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_pow2.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_pow2m1.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_pow2p1.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_std.h \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_IF.h \
    #../../Libraries/cln-1.3.3/src/polynomial/cl_UP.h \
    #../../Libraries/cln-1.3.3/src/rational/cl_RA.h \
    #../../Libraries/cln-1.3.3/src/real/cl_R.h \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_config.h \
    #../../Libraries/cln-1.3.3/src/vector/cl_GV_io.h \
    #../../Libraries/cln-1.3.3/src/vector/cl_SV_io.h \
    #../../Libraries/cln-1.3.3/src/base/digit/cl_2D.h \
    #../../Libraries/cln-1.3.3/src/base/digit/cl_D.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_2DS.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_arm.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_hppa.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_i386.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_m68k.h \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_mips.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_sparc.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_sparc64.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_endian.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_fftc.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_fftcs.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_fftm.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_fftp.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_fftp3.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_fftp3m.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_fftr.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_kara.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_kara_sqr.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_nuss.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_hash.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_hash1.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_hash1weak.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_hash2.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_hash2weak.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_hashset.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_hashuniq.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_hashuniqweak.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_rcpointer2_hashweak_rcpointer.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_rcpointer_hashweak_rcpointer.h \
    #../../Libraries/cln-1.3.3/src/base/random/cl_random_impl.h \
    #../../Libraries/cln-1.3.3/src/base/string/cl_spushstring.h \
    #../../Libraries/cln-1.3.3/src/base/string/cl_sstring.h \
    #../../Libraries/cln-1.3.3/src/base/string/cl_st_make0.h \
    #../../Libraries/cln-1.3.3/src/float/dfloat/cl_DF.h \
    #../../Libraries/cln-1.3.3/src/float/ffloat/cl_FF.h \
    #../../Libraries/cln-1.3.3/src/float/lfloat/cl_LF.h \
    #../../Libraries/cln-1.3.3/src/float/lfloat/cl_LF_impl.h \
    #../../Libraries/cln-1.3.3/src/float/sfloat/cl_SF.h \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_catalanconst_var.h \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_eulerconst_var.h \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_exp1_var.h \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln10_var.h \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln2_var.h \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_pi_var.h \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_tran.h \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_tran.h \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_byte.h \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_log.h \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_cached_power.h \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_gcobject.h \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_gcpointer.h \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_pointer.h \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_rcobject.h \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_rcpointer.h \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hashweak_rcpointer.h \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_UP_gen.h \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_UP_GF2.h \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_UP_MI.h \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_UP_number.h \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_div_t.h \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_format.h \
    #../../Libraries/cln-1.3.3/src/integer/misc/combin/cl_I_combin.h
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_floor.cc \

  SOURCES += \
  #  ../../Libraries/cln-1.3.3/autoconf/floatparam.c \
  #  ../../Libraries/cln-1.3.3/autoconf/intparam.c \
  #  ../../Libraries/cln-1.3.3/benchmarks/timebench1.cc \
  #  ../../Libraries/cln-1.3.3/benchmarks/timebench2a.cc \
  #  ../../Libraries/cln-1.3.3/benchmarks/timebench2ap.cc \
  #  ../../Libraries/cln-1.3.3/benchmarks/timebench2b.cc \
  #  ../../Libraries/cln-1.3.3/examples/contfrac.cc \
  #  ../../Libraries/cln-1.3.3/examples/e.cc \
  #  ../../Libraries/cln-1.3.3/examples/fibonacci.cc \
  #  ../../Libraries/cln-1.3.3/examples/legendre.cc \
  #  ../../Libraries/cln-1.3.3/examples/lucaslehmer.cc \
  #  ../../Libraries/cln-1.3.3/examples/nextprime.cc \
  #  ../../Libraries/cln-1.3.3/examples/perfnum.cc \
  #  ../../Libraries/cln-1.3.3/examples/pi.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_gcd.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_sqrtp.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/main.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_abs.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_ash.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_boole.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_compare.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_dpb.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_dpf.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_evenp.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_gcd.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_GV.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_ilength.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_io.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_isqrt.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_ldb.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_ldbtest.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logand.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logandc1.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logandc2.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logbitp.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logcount.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logeqv.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logior.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_lognand.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_lognor.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_lognot.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logorc1.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logorc2.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logtest.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logxor.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_minus1.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_mkf.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_oddp.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_ord2.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_plus1.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_power2p.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_sqrtp.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_xgcd.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_MI.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_MI_canonhom.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_MI_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_MI_expt.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_MI_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_MI_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_MI_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_MI_recip.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_nt.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_nt_jacobi.cc \
  #  ../../Libraries/cln-1.3.3/tests/tests.cc \
  #  ../../Libraries/cln-1.3.3/tests/timecatalan.cc \
  #  ../../Libraries/cln-1.3.3/tests/timediv.cc \
  #  ../../Libraries/cln-1.3.3/tests/timediv2adic.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeeuler.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeexp1.cc \
  #  ../../Libraries/cln-1.3.3/tests/timefact.cc \
  #  ../../Libraries/cln-1.3.3/tests/timegcd.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFatan.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFatanh.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFcos.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFcosh.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFexp.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFln.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFRAmul.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFsin.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFsinh.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFsqrt.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeMImisc5.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeMIpow2div.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeMIpow2recip.cc \
  #  ../../Libraries/cln-1.3.3/tests/timemul.cc \
  #  ../../Libraries/cln-1.3.3/tests/timepi.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeprint.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeRALFdiv.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeRAtoLF.cc \
  #  ../../Libraries/cln-1.3.3/tests/timerecip2adic.cc \
  #  ../../Libraries/cln-1.3.3/tests/timesqrt.cc \
  #  ../../Libraries/cln-1.3.3/tests/timesqrtmodp.cc \
  #  ../../Libraries/cln-1.3.3/tests/timesquare.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeUPMImul.cc \
  #  ../../Libraries/cln-1.3.3/tests/timezeta3.cc \
    #../../Libraries/cln-1.3.3/src/base/cl_alloca.cc \
    #../../Libraries/cln-1.3.3/src/base/cl_as_exception.cc \
    #../../Libraries/cln-1.3.3/src/base/cl_condition.cc \
    #../../Libraries/cln-1.3.3/src/base/cl_d0_exception.cc \
    #../../Libraries/cln-1.3.3/src/base/cl_debug.cc \
    ../../Libraries/cln-1.3.3/src/base/cl_debugout.cc \
    ../../Libraries/cln-1.3.3/src/base/cl_free.cc \
    #../../Libraries/cln-1.3.3/src/base/cl_immclasses.cc \
    ../../Libraries/cln-1.3.3/src/base/cl_malloc.cc \
    #../../Libraries/cln-1.3.3/src/base/cl_notreached_exception.cc \
    #../../Libraries/cln-1.3.3/src/base/cl_version.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_mips_.cc \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI.cc \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_cond_composite.cc \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_debug.cc \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_err_comp.cc \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_lshift.cc \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_rshift.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_IF_millerrabin.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_IF_smallprimes.cc \
  #  ../../Libraries/cln-1.3.3/src/numtheory/cl_IF_trialdiv.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_IF_trialdiv1.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_IF_trialdiv2.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_nt_cornacchia1.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_nt_cornacchia4.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_nt_isprobprime.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_nt_jacobi.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_nt_jacobi_low.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_nt_nextprobprime.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_nt_sqrtmodp.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_c1.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_c2.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_current.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_current2.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_d.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_dec.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_inc.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_minus.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_report.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_td_minus.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_td_plus.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_GV_I.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_GV_I_copy.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_GV_I_debug.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_GV_number.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_GV_number_copy.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_GV_number_debug.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_SV_copy.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_SV_number.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_SV_number_debug.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_SV_ringelt.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_SV_ringelt_debug.cc \
    #../../Libraries/cln-1.3.3/src/base/digit/cl_2D_div.cc \
    #../../Libraries/cln-1.3.3/src/base/digit/cl_2D_exptpos.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_2DS_div.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_2DS_recip.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_arm_.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_hppa_.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_i386_.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_m68k_.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_mips_.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_mipsel_.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_sparc64_.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_sparc_.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_div.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_random.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_recip.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_recipsqrt.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_trandom.cc \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_rcpointer2_hashweak_rcpointer.cc \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_rcpointer_hashweak_rcpointer.cc \
    #../../Libraries/cln-1.3.3/src/base/input/cl_read_bad_syntax_exception.cc \
    #../../Libraries/cln-1.3.3/src/base/input/cl_read_eof_exception.cc \
    #../../Libraries/cln-1.3.3/src/base/input/cl_read_junk_exception.cc \
    #../../Libraries/cln-1.3.3/src/base/low/cl_low_div.cc \
    #../../Libraries/cln-1.3.3/src/base/low/cl_low_isqrt.cc \
    #../../Libraries/cln-1.3.3/src/base/low/cl_low_isqrt2.cc \
    #../../Libraries/cln-1.3.3/src/base/low/cl_low_mul.cc \
    ../../Libraries/cln-1.3.3/src/base/output/cl_output_dec.cc \
    ../../Libraries/cln-1.3.3/src/base/output/cl_output_hex.cc \
    ../../Libraries/cln-1.3.3/src/base/output/cl_prin_globals.cc \
    #../../Libraries/cln-1.3.3/src/base/proplist/cl_pl_add.cc \
    ../../Libraries/cln-1.3.3/src/base/proplist/cl_pl_d.cc \
    #../../Libraries/cln-1.3.3/src/base/proplist/cl_pl_get.cc \
    ../../Libraries/cln-1.3.3/src/base/random/cl_random_def.cc \
    ../../Libraries/cln-1.3.3/src/base/random/cl_random_from.cc \
    #../../Libraries/cln-1.3.3/src/base/random/cl_UL_random.cc \
    ../../Libraries/cln-1.3.3/src/base/ring/cl_no_ring.cc \
    #../../Libraries/cln-1.3.3/src/base/ring/cl_ring_debug.cc \
    #../../Libraries/cln-1.3.3/src/base/string/cl_spushstring_append.cc \
    #../../Libraries/cln-1.3.3/src/base/string/cl_spushstring_push.cc \
    #../../Libraries/cln-1.3.3/src/base/string/cl_sstring.cc \
    ../../Libraries/cln-1.3.3/src/base/string/cl_st_c2.cc \
    #../../Libraries/cln-1.3.3/src/base/string/cl_st_concat1.cc \
    #../../Libraries/cln-1.3.3/src/base/string/cl_st_concat2.cc \
    #../../Libraries/cln-1.3.3/src/base/string/cl_st_concat3.cc \
    #../../Libraries/cln-1.3.3/src/base/string/cl_st_debug.cc \
    #../../Libraries/cln-1.3.3/src/base/string/cl_st_hashcode.cc \
    ../../Libraries/cln-1.3.3/src/base/string/cl_st_make0.cc \
    ../../Libraries/cln-1.3.3/src/base/string/cl_st_make1.cc \
    ../../Libraries/cln-1.3.3/src/base/string/cl_st_make2.cc \
    #../../Libraries/cln-1.3.3/src/base/symbol/cl_sy_hashcode.cc \
    #../../Libraries/cln-1.3.3/src/base/symbol/cl_symbol.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_C_abs.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_C_abs_aux.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_C_signum.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_C_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_DF_hypot.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_FF_hypot.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_LF_hypot.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_R_hypot.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_SF_hypot.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_equal.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_from_R_R_complex.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_from_R_R_complex1.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_imagpart.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_minus.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_minus1.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_mul.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_plus.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_plus1.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_realpart.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_square.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_uminus.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_zerop.cc \
    #../../Libraries/cln-1.3.3/src/complex/input/cl_N_from_string.cc \
    #../../Libraries/cln-1.3.3/src/complex/input/cl_N_read.cc \
    #../../Libraries/cln-1.3.3/src/complex/input/cl_N_read_stream.cc \
    #../../Libraries/cln-1.3.3/src/complex/misc/cl_C_class.cc \
    #../../Libraries/cln-1.3.3/src/complex/misc/cl_C_conjugate.cc \
    #../../Libraries/cln-1.3.3/src/complex/misc/cl_C_debug.cc \
    #../../Libraries/cln-1.3.3/src/complex/misc/cl_C_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/complex/misc/cl_C_expt.cc \
    #../../Libraries/cln-1.3.3/src/complex/misc/cl_C_expt_I.cc \
    #../../Libraries/cln-1.3.3/src/complex/misc/cl_N_as.cc \
    #../../Libraries/cln-1.3.3/src/complex/output/cl_N_aprint.cc \
    #../../Libraries/cln-1.3.3/src/complex/output/cl_N_bprint.cc \
    #../../Libraries/cln-1.3.3/src/complex/ring/cl_C_ring.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_acos.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_acosh.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_asin.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_asinh.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_asinh_aux.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_atan.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_atanh.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_atanh_aux.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_cis.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_cos.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_cosh.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_exp.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_expt_C.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_log.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_log2.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_phase.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_sin.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_sinh.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_tan.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_tanh.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_R_cis.cc \
    #../../Libraries/cln-1.3.3/src/float/algebraic/cl_F_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/float/base/cl_F_globals.cc \
    #../../Libraries/cln-1.3.3/src/float/base/cl_F_nan_exception.cc \
    #../../Libraries/cln-1.3.3/src/float/base/cl_F_overflow_exception.cc \
    #../../Libraries/cln-1.3.3/src/float/base/cl_F_underflow_exception.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_DF_to_double.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_DF_to_FF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_DF_to_float.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_DF_to_LF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_DF_to_SF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_from_F.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_from_F_f.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_from_I.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_from_I_def.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_from_I_f.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_from_RA.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_from_RA_def.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_from_RA_f.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_to_DF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_to_double.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_to_FF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_to_float.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_to_LF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_to_SF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_FF_to_DF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_FF_to_double.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_FF_to_float.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_FF_to_LF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_FF_to_SF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_LF_to_DF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_LF_to_double.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_LF_to_FF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_LF_to_float.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_LF_to_SF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_SF_to_DF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_SF_to_double.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_SF_to_FF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_SF_to_float.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_SF_to_LF.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_ceil1.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_ceil2.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_ceil22.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_fceil1.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_fceil2.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_ffloor1.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_ffloor2.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_floor1.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_floor2.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_floor22.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_fround1.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_fround2.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_ftrunc1.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_ftrunc2.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_round1.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_round2.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_round22.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_trunc1.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_trunc2.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_trunc22.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_compare.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_div.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_I_div.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_I_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_minus.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_minusp.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_plus.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_plusp.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_RA_div.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_RA_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_recip.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_scale.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_scale_I.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_square.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_uminus.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_zerop.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_I_F_div.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_RA_F_div.cc \
    #../../Libraries/cln-1.3.3/src/float/input/cl_F_from_string.cc \
    #../../Libraries/cln-1.3.3/src/float/input/cl_F_read.cc \
    #../../Libraries/cln-1.3.3/src/float/input/cl_F_read_stream.cc \
    #../../Libraries/cln-1.3.3/src/float/input/cl_F_readparsed.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_abs.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_as.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_decode.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_digits.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_epsneg.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_epspos.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_exponent.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_extendsqrt.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_extendsqrtx.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_idecode.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_leastneg.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_leastpos.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_max.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_min.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_mostneg.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_mostpos.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_precision.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_rational.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_shortenrel.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_sign.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_sign2.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_signum.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_float_format.cc \
    #../../Libraries/cln-1.3.3/src/float/output/cl_F_aprint.cc \
    #../../Libraries/cln-1.3.3/src/float/output/cl_F_bprint.cc \
    #../../Libraries/cln-1.3.3/src/float/output/cl_F_cprint.cc \
    #../../Libraries/cln-1.3.3/src/float/output/cl_F_dprint.cc \
    #../../Libraries/cln-1.3.3/src/float/output/cl_F_printb.cc \
    #../../Libraries/cln-1.3.3/src/float/random/cl_F_random.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_atanhx.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_atanx.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_catalanconst.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_catalanconst_def.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_catalanconst_f.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_catalanconst_var.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_cos.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_cosh.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_coshsinh.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_cossin.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_eulerconst.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_eulerconst_def.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_eulerconst_f.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_eulerconst_var.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_exp.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_exp1.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_exp1_def.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_exp1_f.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_exp1_var.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_expx.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln10.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln10_f.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln10_var.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln2.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln2_f.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln2_var.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_lnx.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_pi.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_pi_def.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_pi_f.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_pi_var.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_roundpi.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_roundpi2.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_sin.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_sinh.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_sinhx.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_sinx.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_tan.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_tanh.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_zeta_int.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_zeta_int_def.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_zeta_int_f.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_atan_recip.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_atanh_recip.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_catalanconst.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_coshsinh.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_coshsinh_aux.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_cossin.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_cossin_aux.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_eulerconst.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_exp1.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_exp_aux.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ln10.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ln2.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_pi.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_a.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_ab.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_b.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_p.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_pa.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_pab.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_pb.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_pq.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_pqa.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_pqab.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_pqb.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_q.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_qa.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_qab.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_qb.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratsumseries_pqcd.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratsumseries_pqcd_aux.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratsumseries_pqd.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratsumseries_pqd_aux.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_zeta3.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_zeta_int.cc \
    #../../Libraries/cln-1.3.3/src/integer/2adic/cl_I_2adic_div.cc \
    #../../Libraries/cln-1.3.3/src/integer/2adic/cl_I_2adic_recip.cc \
    #../../Libraries/cln-1.3.3/src/integer/algebraic/cl_I_rootp.cc \
    #../../Libraries/cln-1.3.3/src/integer/algebraic/cl_I_rootp_aux.cc \
    #../../Libraries/cln-1.3.3/src/integer/algebraic/cl_I_rootp_I.cc \
    #../../Libraries/cln-1.3.3/src/integer/algebraic/cl_I_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/integer/algebraic/cl_I_sqrtp.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_ash.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_ash_exception.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_ash_I.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_boole.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_dpb.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_dpf.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_fullbyte.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_ilength.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_ldb.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_ldbtest.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_ldbx.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_ldbxtest.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_log_aux.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logand.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logandc2.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logbitp.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logbitp_I.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logcount.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logeqv.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logior.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_lognand.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_lognor.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_lognot.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logorc2.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logtest.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logxor.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_mkf.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_mkfx.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_cached_power.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_digits_need.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_digits.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_DS.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_L.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_L2.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_NDS.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_NUDS.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_Q.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_Q2.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_UDS.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_UL.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_UL2.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_UQ.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_mul10plus.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_to_digits.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_to_L.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_to_Q.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_to_UL.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_to_UQ.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_ceil1.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_ceil2.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_exquo.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_exquo_exception.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_exquopos.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_floor1.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_floor2.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_mod.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_rem.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_round1.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_round2.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_trunc1.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_trunc2.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_compare.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_div.cc \
    ../../Libraries/cln-1.3.3/src/integer/elem/cl_I_equal.cc \
    ../../Libraries/cln-1.3.3/src/integer/elem/cl_I_minus.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_minus1.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_minusp.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_mul.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_plus.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_plus1.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_plusp.cc \
    ../../Libraries/cln-1.3.3/src/integer/elem/cl_I_square.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_uminus.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_zerop.cc \
    #../../Libraries/cln-1.3.3/src/integer/gcd/cl_I_gcd.cc \
    #../../Libraries/cln-1.3.3/src/integer/gcd/cl_I_gcd_aux.cc \
    #../../Libraries/cln-1.3.3/src/integer/gcd/cl_I_gcd_aux2.cc \
    #../../Libraries/cln-1.3.3/src/integer/gcd/cl_I_lcm.cc \
    #../../Libraries/cln-1.3.3/src/integer/gcd/cl_I_xgcd.cc \
    #../../Libraries/cln-1.3.3/src/integer/gcd/cl_low_gcd.cc \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_gcobject.cc \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_gcpointer.cc \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_pointer.cc \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_rcobject.cc \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_rcpointer.cc \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hashcode.cc \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hashweak_rcpointer.cc \
    #../../Libraries/cln-1.3.3/src/integer/input/cl_I_from_string.cc \
    #../../Libraries/cln-1.3.3/src/integer/input/cl_I_read.cc \
    #../../Libraries/cln-1.3.3/src/integer/input/cl_I_read_stream.cc \
    #../../Libraries/cln-1.3.3/src/integer/input/cl_I_readparsed.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_BN_class.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_FN_class.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_abs.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_as.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_debug.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_exptpos.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_exptpos_I.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_max.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_min.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_oddp.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_ord2.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_power2p.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_signum.cc \
    #../../Libraries/cln-1.3.3/src/integer/output/cl_I_aprint.cc \
    #../../Libraries/cln-1.3.3/src/integer/output/cl_I_bprint.cc \
    #../../Libraries/cln-1.3.3/src/integer/output/cl_I_cprint.cc \
    #../../Libraries/cln-1.3.3/src/integer/output/cl_I_decstring.cc \
    #../../Libraries/cln-1.3.3/src/integer/output/cl_I_dprint.cc \
    #../../Libraries/cln-1.3.3/src/integer/output/cl_I_print.cc \
    #../../Libraries/cln-1.3.3/src/integer/output/cl_I_print_string.cc \
    #../../Libraries/cln-1.3.3/src/integer/random/cl_I_random.cc \
    #../../Libraries/cln-1.3.3/src/integer/random/cl_I_trandom.cc \
    #../../Libraries/cln-1.3.3/src/integer/ring/cl_0_ring.cc \
    ../../Libraries/cln-1.3.3/src/integer/ring/cl_I_ring.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_asm_GF2.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_asm_sparc_GF2.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_UP.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_UP_named.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_UP_no_ring.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_UP_unnamed.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/misc/cl_UP_debug.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/misc/cl_UP_deriv.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/misc/cl_UP_I_hermite.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/misc/cl_UP_I_laguerre.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/misc/cl_UP_I_tchebychev.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/misc/cl_UP_RA_legendre.cc \
    #../../Libraries/cln-1.3.3/src/rational/algebraic/cl_RA_rootp.cc \
    #../../Libraries/cln-1.3.3/src/rational/algebraic/cl_RA_rootp_I.cc \
    #../../Libraries/cln-1.3.3/src/rational/algebraic/cl_RA_sqrtp.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_ceil1.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_ceil12.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_ceil2.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_ceil22.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_floor1.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_floor12.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_floor2.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_floor22.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_round1.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_round12.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_round2.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_round22.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_trunc1.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_trunc12.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_trunc2.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_trunc22.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_compare.cc \
  #  ../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_denominator.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_div.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_equal.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_from_I_I_div.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_from_I_posI.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_from_I_posI1.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_from_I_posI_div.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_minus.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_minus1.cc \
  #  ../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_minusp.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_mul.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_numerator.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_plus.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_plus1.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_plusp.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_recip.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_square.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_uminus.cc \
  #  ../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_zerop.cc \
    #../../Libraries/cln-1.3.3/src/rational/input/cl_RA_from_string.cc \
    #../../Libraries/cln-1.3.3/src/rational/input/cl_RA_read.cc \
    #../../Libraries/cln-1.3.3/src/rational/input/cl_RA_read_stream.cc \
    #../../Libraries/cln-1.3.3/src/rational/input/cl_RA_readparsed.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_abs.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_as.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_class.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_debug.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_expt.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_expt_I.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_exptpos.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_exptpos_I.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_max.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_min.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_signum.cc \
    #../../Libraries/cln-1.3.3/src/rational/output/cl_RA_aprint.cc \
    #../../Libraries/cln-1.3.3/src/rational/output/cl_RA_bprint.cc \
    #../../Libraries/cln-1.3.3/src/rational/output/cl_RA_cprint.cc \
    #../../Libraries/cln-1.3.3/src/rational/output/cl_RA_dprint.cc \
    #../../Libraries/cln-1.3.3/src/rational/output/cl_RA_print.cc \
    #../../Libraries/cln-1.3.3/src/rational/ring/cl_RA_ring.cc \
    #../../Libraries/cln-1.3.3/src/rational/transcendental/cl_I_logp.cc \
    #../../Libraries/cln-1.3.3/src/rational/transcendental/cl_RA_logp.cc \
    #../../Libraries/cln-1.3.3/src/real/algebraic/cl_R_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/real/algebraic/cl_RA_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_F_from_R.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_F_from_R_def.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_F_from_R_f.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_R_to_DF.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_R_to_double.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_R_to_FF.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_R_to_float.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_R_to_LF.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_R_to_SF.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ceil1.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ceil12.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ceil2.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ceil22.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_fceil1.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_fceil12.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_fceil2.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_fceil22.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ffloor1.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ffloor12.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ffloor2.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ffloor22.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_floor1.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_floor12.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_floor2.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_floor22.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_fround1.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_fround12.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_fround2.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_fround22.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ftrunc1.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ftrunc12.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ftrunc2.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ftrunc22.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_mod.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_rem.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_round1.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_round12.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_round2.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_round22.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_trunc1.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_trunc12.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_trunc2.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_trunc22.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_compare.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_div.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_equal.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_minus.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_minus1.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_minusp.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_mul.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_plus.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_plus1.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_plusp.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_recip.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_square.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_uminus.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_zerop.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_cardinal.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_floatstring.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_integer.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_newroman.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_oldroman.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_ordinal.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_paddedstring.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_scaleexp.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_tens.cc \
    #../../Libraries/cln-1.3.3/src/real/input/cl_R_from_string.cc \
    #../../Libraries/cln-1.3.3/src/real/input/cl_R_read.cc \
    #../../Libraries/cln-1.3.3/src/real/input/cl_R_read_stream.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_abs.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_as.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_contagion.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_debug.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_expt.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_expt_I.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_max.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_min.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_rational.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_rationalize.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_signum.cc \
    #../../Libraries/cln-1.3.3/src/real/output/cl_R_aprint.cc \
    #../../Libraries/cln-1.3.3/src/real/output/cl_R_bprint.cc \
    #../../Libraries/cln-1.3.3/src/real/output/cl_R_cprint.cc \
    #../../Libraries/cln-1.3.3/src/real/random/cl_R_random.cc \
    #../../Libraries/cln-1.3.3/src/real/ring/cl_R_ring.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_atan.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_atan2.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_cos.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_cosh.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_coshsinh.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_cossin.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_exp.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_ln.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_log.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_sin.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_sinh.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_tan.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_tanh.cc \
    #../../Libraries/cln-1.3.3/src/vector/output/cl_GV_number_aprint.cc \
    #../../Libraries/cln-1.3.3/src/vector/output/cl_SV_aprint.cc \
    #../../Libraries/cln-1.3.3/src/vector/output/cl_SV_number_aprint.cc \
    #../../Libraries/cln-1.3.3/src/base/string/input/cl_st_get1.cc \
    #../../Libraries/cln-1.3.3/src/base/string/input/cl_st_get2.cc \
    #../../Libraries/cln-1.3.3/src/base/string/input/cl_st_getline1.cc \
    #../../Libraries/cln-1.3.3/src/base/string/input/cl_st_getline2.cc \
    #../../Libraries/cln-1.3.3/src/base/string/input/cl_st_gettoken.cc \
    ../../Libraries/cln-1.3.3/src/base/string/misc/cl_st_class.cc \
    #../../Libraries/cln-1.3.3/src/base/string/output/cl_st_print.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/division/cl_C_DF_recip.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/division/cl_C_div.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/division/cl_C_FF_recip.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/division/cl_C_LF_recip.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/division/cl_C_recip.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/division/cl_C_SF_recip.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/algebraic/cl_DF_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/conv/cl_DF_from_double.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/conv/cl_DF_to_doublej.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/conv/cl_I_to_double.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/conv/cl_RA_to_double.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/division/cl_DF_ceil22.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/division/cl_DF_fceil.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/division/cl_DF_floor22.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/division/cl_DF_recip.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/division/cl_DF_round22.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/division/cl_DF_trunc22.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_compare.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_div.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_ffloor.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_from_I.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_from_RA.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_fround.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_ftrunc.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_futrunc.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_globals.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_minus.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_minusp.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_plus.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_plusp.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_scale.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_scale_I.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_to_I.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_uminus.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_zerop.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/input/cl_DF_from_string.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_abs.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_as.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_class.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_debug.cc \
  #  ../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_decode.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_digits.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_exponent.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_idecode.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_max.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_min.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_precision.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_sign.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_signum.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/algebraic/cl_FF_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/conv/cl_FF_from_float.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/conv/cl_FF_to_floatj.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/conv/cl_I_to_float.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/conv/cl_RA_to_float.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/division/cl_FF_ceil22.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/division/cl_FF_fceil.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/division/cl_FF_floor22.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/division/cl_FF_recip.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/division/cl_FF_round22.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/division/cl_FF_trunc22.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_compare.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_div.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_ffloor.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_from_I.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_from_RA.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_fround.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_ftrunc.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_futrunc.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_globals.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_minus.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_minusp.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_plus.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_plusp.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_scale.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_scale_I.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_to_I.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_uminus.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_zerop.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/input/cl_FF_from_string.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_abs.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_as.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_class.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_debug.cc \
  #  ../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_decode.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_digits.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_exponent.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_idecode.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_max.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_min.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_precision.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_sign.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_signum.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/algebraic/cl_LF_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/division/cl_LF_ceil22.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/division/cl_LF_fceil.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/division/cl_LF_floor22.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/division/cl_LF_recip.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/division/cl_LF_round22.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/division/cl_LF_trunc22.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_I_LF_div.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_1minus.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_1plus.cc \
  #  ../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_2minus.cc \
  #  ../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_2plus.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_compare.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_div.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_ffloor.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_from_I.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_from_RA.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_fround.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_ftrunc.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_futrunc.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_globals.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_I_div.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_I_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_minus1.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_minusp.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_plus1.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_plusp.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_RA_div.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_RA_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_scale.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_scale_I.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_square.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_to_I.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_uminus.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_zerop.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_RA_LF_div.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/input/cl_LF_from_string.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_abs.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_as.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_class.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_debug.cc \
  #  ../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_decode.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_digits.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_exponent.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_extend.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_idecode.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_leninc.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_lenincx.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_max.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_min.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_precision.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_shorten.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_shortenrel.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_shortenwith.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_sign.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_signum.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_to_LF.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/algebraic/cl_SF_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/division/cl_SF_ceil22.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/division/cl_SF_fceil.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/division/cl_SF_ffloor.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/division/cl_SF_floor22.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/division/cl_SF_recip.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/division/cl_SF_round22.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/division/cl_SF_trunc22.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_compare.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_div.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_from_I.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_from_RA.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_fround.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_ftrunc.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_futrunc.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_minus.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_minusp.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_plus.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_plusp.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_scale.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_scale_I.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_to_I.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_uminus.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_zerop.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/input/cl_SF_from_string.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_abs.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_as.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_class.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_debug.cc \
  #  ../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_decode.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_digits.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_exponent.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_idecode.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_max.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_min.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_precision.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_sign.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_signum.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/combin/cl_I_binomial.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/combin/cl_I_doublefactorial.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/combin/cl_I_factorial.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/combin/cl_I_factorial_aux.cc

}

macx {
  # Mac only
  message("CLN, built for Mac")
}

unix:!macx {
  # Linux only
  message("CLN, built for Linux")

  INCLUDEPATH += \
    ../../Libraries/cln-1.3.3 \
    ../../Libraries/cln-1.3.3/autoconf \
    ../../Libraries/cln-1.3.3/include \
    ../../Libraries/cln-1.3.3/src

  # Input
  HEADERS += \
    #../../Libraries/cln-1.3.3/autoconf/cl_config.h \
    #../../Libraries/cln-1.3.3/include/cln/cln.h \
    #../../Libraries/cln-1.3.3/include/cln/complex.h \
    #../../Libraries/cln-1.3.3/include/cln/complex_class.h \
    #../../Libraries/cln-1.3.3/include/cln/complex_io.h \
    #../../Libraries/cln-1.3.3/include/cln/complex_ring.h \
    #../../Libraries/cln-1.3.3/include/cln/condition.h \
    #../../Libraries/cln-1.3.3/include/cln/config.h \
    #../../Libraries/cln-1.3.3/include/cln/dfloat.h \
    #../../Libraries/cln-1.3.3/include/cln/dfloat_class.h \
    #../../Libraries/cln-1.3.3/include/cln/dfloat_io.h \
    #../../Libraries/cln-1.3.3/include/cln/exception.h \
    #../../Libraries/cln-1.3.3/include/cln/ffloat.h \
    #../../Libraries/cln-1.3.3/include/cln/ffloat_class.h \
    #../../Libraries/cln-1.3.3/include/cln/ffloat_io.h \
    #../../Libraries/cln-1.3.3/include/cln/float.h \
    #../../Libraries/cln-1.3.3/include/cln/float_class.h \
    #../../Libraries/cln-1.3.3/include/cln/float_io.h \
    #../../Libraries/cln-1.3.3/include/cln/floatformat.h \
    #../../Libraries/cln-1.3.3/include/cln/floatparam.h \
    #../../Libraries/cln-1.3.3/include/cln/GV.h \
    #../../Libraries/cln-1.3.3/include/cln/GV_complex.h \
    #../../Libraries/cln-1.3.3/include/cln/GV_integer.h \
    #../../Libraries/cln-1.3.3/include/cln/GV_modinteger.h \
    #../../Libraries/cln-1.3.3/include/cln/GV_number.h \
    #../../Libraries/cln-1.3.3/include/cln/GV_rational.h \
    #../../Libraries/cln-1.3.3/include/cln/GV_real.h \
    #../../Libraries/cln-1.3.3/include/cln/host_cpu.h \
    #../../Libraries/cln-1.3.3/include/cln/input.h \
    #../../Libraries/cln-1.3.3/include/cln/integer.h \
    #../../Libraries/cln-1.3.3/include/cln/integer_class.h \
    #../../Libraries/cln-1.3.3/include/cln/integer_io.h \
    #../../Libraries/cln-1.3.3/include/cln/integer_ring.h \
    #../../Libraries/cln-1.3.3/include/cln/intparam.h \
    #../../Libraries/cln-1.3.3/include/cln/io.h \
    #../../Libraries/cln-1.3.3/include/cln/lfloat.h \
    #../../Libraries/cln-1.3.3/include/cln/lfloat_class.h \
    #../../Libraries/cln-1.3.3/include/cln/lfloat_io.h \
    #../../Libraries/cln-1.3.3/include/cln/malloc.h \
    #../../Libraries/cln-1.3.3/include/cln/modinteger.h \
    #../../Libraries/cln-1.3.3/include/cln/modules.h \
    #../../Libraries/cln-1.3.3/include/cln/null_ring.h \
    #../../Libraries/cln-1.3.3/include/cln/number.h \
    #../../Libraries/cln-1.3.3/include/cln/number_io.h \
    #../../Libraries/cln-1.3.3/include/cln/numtheory.h \
    #../../Libraries/cln-1.3.3/include/cln/object.h \
    #../../Libraries/cln-1.3.3/include/cln/output.h \
    #../../Libraries/cln-1.3.3/include/cln/proplist.h \
    #../../Libraries/cln-1.3.3/include/cln/random.h \
    #../../Libraries/cln-1.3.3/include/cln/rational.h \
    #../../Libraries/cln-1.3.3/include/cln/rational_class.h \
    #../../Libraries/cln-1.3.3/include/cln/rational_io.h \
    #../../Libraries/cln-1.3.3/include/cln/rational_ring.h \
    #../../Libraries/cln-1.3.3/include/cln/real.h \
    #../../Libraries/cln-1.3.3/include/cln/real_class.h \
    #../../Libraries/cln-1.3.3/include/cln/real_io.h \
    #../../Libraries/cln-1.3.3/include/cln/real_ring.h \
    #../../Libraries/cln-1.3.3/include/cln/ring.h \
    #../../Libraries/cln-1.3.3/include/cln/sfloat.h \
    #../../Libraries/cln-1.3.3/include/cln/sfloat_class.h \
    #../../Libraries/cln-1.3.3/include/cln/sfloat_io.h \
    #../../Libraries/cln-1.3.3/include/cln/string.h \
    #../../Libraries/cln-1.3.3/include/cln/SV.h \
    #../../Libraries/cln-1.3.3/include/cln/SV_complex.h \
    #../../Libraries/cln-1.3.3/include/cln/SV_integer.h \
    #../../Libraries/cln-1.3.3/include/cln/SV_number.h \
    #../../Libraries/cln-1.3.3/include/cln/SV_rational.h \
    #../../Libraries/cln-1.3.3/include/cln/SV_real.h \
    #../../Libraries/cln-1.3.3/include/cln/SV_ringelt.h \
    #../../Libraries/cln-1.3.3/include/cln/symbol.h \
    #../../Libraries/cln-1.3.3/include/cln/timing.h \
    #../../Libraries/cln-1.3.3/include/cln/types.h \
    #../../Libraries/cln-1.3.3/include/cln/univpoly.h \
    #../../Libraries/cln-1.3.3/include/cln/univpoly_complex.h \
    #../../Libraries/cln-1.3.3/include/cln/univpoly_integer.h \
    #../../Libraries/cln-1.3.3/include/cln/univpoly_modint.h \
    #../../Libraries/cln-1.3.3/include/cln/univpoly_rational.h \
    #../../Libraries/cln-1.3.3/include/cln/univpoly_real.h \
    #../../Libraries/cln-1.3.3/include/cln/V.h \
    #../../Libraries/cln-1.3.3/include/cln/version.h \
    #../../Libraries/cln-1.3.3/src/base/cl_alloca.h \
    #../../Libraries/cln-1.3.3/src/base/cl_base_config.h \
    #../../Libraries/cln-1.3.3/src/base/cl_gmpconfig.h \
    #../../Libraries/cln-1.3.3/src/base/cl_inline.h \
    #../../Libraries/cln-1.3.3/src/base/cl_inline2.h \
    #../../Libraries/cln-1.3.3/src/base/cl_iterator.h \
    #../../Libraries/cln-1.3.3/src/base/cl_low.h \
    #../../Libraries/cln-1.3.3/src/base/cl_macros.h \
    #../../Libraries/cln-1.3.3/src/base/cl_maybe_inline.h \
    #../../Libraries/cln-1.3.3/src/base/cl_N.h \
    #../../Libraries/cln-1.3.3/src/base/cl_offsetof.h \
    #../../Libraries/cln-1.3.3/src/base/cl_sysdep.h \
    #../../Libraries/cln-1.3.3/src/base/cl_xmacros.h \
    #../../Libraries/cln-1.3.3/src/complex/cl_C.h \
    #../../Libraries/cln-1.3.3/src/float/cl_F.h \
    #../../Libraries/cln-1.3.3/src/integer/cl_I.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_fix16.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_fix29.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_fix32.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_int.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_int32.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_montgom.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_pow2.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_pow2m1.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_pow2p1.h \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_std.h \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_IF.h \
    #../../Libraries/cln-1.3.3/src/polynomial/cl_UP.h \
    #../../Libraries/cln-1.3.3/src/rational/cl_RA.h \
    #../../Libraries/cln-1.3.3/src/real/cl_R.h \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_config.h \
    #../../Libraries/cln-1.3.3/src/vector/cl_GV_io.h \
    #../../Libraries/cln-1.3.3/src/vector/cl_SV_io.h \
    #../../Libraries/cln-1.3.3/src/base/digit/cl_2D.h \
    #../../Libraries/cln-1.3.3/src/base/digit/cl_D.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_2DS.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_arm.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_hppa.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_i386.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_m68k.h \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_mips.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_sparc.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_sparc64.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_endian.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_fftc.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_fftcs.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_fftm.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_fftp.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_fftp3.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_fftp3m.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_fftr.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_kara.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_kara_sqr.h \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul_nuss.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_hash.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_hash1.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_hash1weak.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_hash2.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_hash2weak.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_hashset.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_hashuniq.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_hashuniqweak.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_rcpointer2_hashweak_rcpointer.h \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_rcpointer_hashweak_rcpointer.h \
    #../../Libraries/cln-1.3.3/src/base/random/cl_random_impl.h \
    #../../Libraries/cln-1.3.3/src/base/string/cl_spushstring.h \
    #../../Libraries/cln-1.3.3/src/base/string/cl_sstring.h \
    #../../Libraries/cln-1.3.3/src/base/string/cl_st_make0.h \
    #../../Libraries/cln-1.3.3/src/float/dfloat/cl_DF.h \
    #../../Libraries/cln-1.3.3/src/float/ffloat/cl_FF.h \
    #../../Libraries/cln-1.3.3/src/float/lfloat/cl_LF.h \
    #../../Libraries/cln-1.3.3/src/float/lfloat/cl_LF_impl.h \
    #../../Libraries/cln-1.3.3/src/float/sfloat/cl_SF.h \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_catalanconst_var.h \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_eulerconst_var.h \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_exp1_var.h \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln10_var.h \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln2_var.h \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_pi_var.h \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_tran.h \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_tran.h \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_byte.h \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_log.h \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_cached_power.h \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_gcobject.h \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_gcpointer.h \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_pointer.h \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_rcobject.h \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_rcpointer.h \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hashweak_rcpointer.h \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_UP_gen.h \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_UP_GF2.h \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_UP_MI.h \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_UP_number.h \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_div_t.h \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_format.h \
    #../../Libraries/cln-1.3.3/src/integer/misc/combin/cl_I_combin.h
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_floor.cc \

  SOURCES += \
  #  ../../Libraries/cln-1.3.3/autoconf/floatparam.c \
  #  ../../Libraries/cln-1.3.3/autoconf/intparam.c \
  #  ../../Libraries/cln-1.3.3/benchmarks/timebench1.cc \
  #  ../../Libraries/cln-1.3.3/benchmarks/timebench2a.cc \
  #  ../../Libraries/cln-1.3.3/benchmarks/timebench2ap.cc \
  #  ../../Libraries/cln-1.3.3/benchmarks/timebench2b.cc \
  #  ../../Libraries/cln-1.3.3/examples/contfrac.cc \
  #  ../../Libraries/cln-1.3.3/examples/e.cc \
  #  ../../Libraries/cln-1.3.3/examples/fibonacci.cc \
  #  ../../Libraries/cln-1.3.3/examples/legendre.cc \
  #  ../../Libraries/cln-1.3.3/examples/lucaslehmer.cc \
  #  ../../Libraries/cln-1.3.3/examples/nextprime.cc \
  #  ../../Libraries/cln-1.3.3/examples/perfnum.cc \
  #  ../../Libraries/cln-1.3.3/examples/pi.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_DF_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_FF_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_gcd.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_I_sqrtp.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_LF_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_RA_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_floor.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/exam_SF_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/main.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_abs.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_ash.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_boole.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_compare.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_dpb.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_dpf.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_evenp.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_gcd.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_GV.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_ilength.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_io.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_isqrt.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_ldb.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_ldbtest.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logand.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logandc1.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logandc2.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logbitp.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logcount.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logeqv.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logior.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_lognand.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_lognor.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_lognot.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logorc1.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logorc2.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logtest.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_logxor.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_minus1.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_mkf.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_oddp.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_ord2.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_plus1.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_power2p.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_sqrtp.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_I_xgcd.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_MI.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_MI_canonhom.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_MI_div.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_MI_expt.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_MI_minus.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_MI_mul.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_MI_plus.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_MI_recip.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_nt.cc \
  #  ../../Libraries/cln-1.3.3/tests/test_nt_jacobi.cc \
  #  ../../Libraries/cln-1.3.3/tests/tests.cc \
  #  ../../Libraries/cln-1.3.3/tests/timecatalan.cc \
  #  ../../Libraries/cln-1.3.3/tests/timediv.cc \
  #  ../../Libraries/cln-1.3.3/tests/timediv2adic.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeeuler.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeexp1.cc \
  #  ../../Libraries/cln-1.3.3/tests/timefact.cc \
  #  ../../Libraries/cln-1.3.3/tests/timegcd.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFatan.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFatanh.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFcos.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFcosh.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFexp.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFln.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFRAmul.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFsin.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFsinh.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeLFsqrt.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeMImisc5.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeMIpow2div.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeMIpow2recip.cc \
  #  ../../Libraries/cln-1.3.3/tests/timemul.cc \
  #  ../../Libraries/cln-1.3.3/tests/timepi.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeprint.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeRALFdiv.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeRAtoLF.cc \
  #  ../../Libraries/cln-1.3.3/tests/timerecip2adic.cc \
  #  ../../Libraries/cln-1.3.3/tests/timesqrt.cc \
  #  ../../Libraries/cln-1.3.3/tests/timesqrtmodp.cc \
  #  ../../Libraries/cln-1.3.3/tests/timesquare.cc \
  #  ../../Libraries/cln-1.3.3/tests/timeUPMImul.cc \
  #  ../../Libraries/cln-1.3.3/tests/timezeta3.cc \
    #../../Libraries/cln-1.3.3/src/base/cl_alloca.cc \
    #../../Libraries/cln-1.3.3/src/base/cl_as_exception.cc \
    #../../Libraries/cln-1.3.3/src/base/cl_condition.cc \
    #../../Libraries/cln-1.3.3/src/base/cl_d0_exception.cc \
    #../../Libraries/cln-1.3.3/src/base/cl_debug.cc \
    ../../Libraries/cln-1.3.3/src/base/cl_debugout.cc \
    ../../Libraries/cln-1.3.3/src/base/cl_free.cc \
    #../../Libraries/cln-1.3.3/src/base/cl_immclasses.cc \
    ../../Libraries/cln-1.3.3/src/base/cl_malloc.cc \
    #../../Libraries/cln-1.3.3/src/base/cl_notreached_exception.cc \
    #../../Libraries/cln-1.3.3/src/base/cl_version.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_mips_.cc \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI.cc \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_cond_composite.cc \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_debug.cc \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_err_comp.cc \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_lshift.cc \
    #../../Libraries/cln-1.3.3/src/modinteger/cl_MI_rshift.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_IF_millerrabin.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_IF_smallprimes.cc \
  #  ../../Libraries/cln-1.3.3/src/numtheory/cl_IF_trialdiv.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_IF_trialdiv1.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_IF_trialdiv2.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_nt_cornacchia1.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_nt_cornacchia4.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_nt_isprobprime.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_nt_jacobi.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_nt_jacobi_low.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_nt_nextprobprime.cc \
    #../../Libraries/cln-1.3.3/src/numtheory/cl_nt_sqrtmodp.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_c1.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_c2.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_current.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_current2.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_d.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_dec.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_inc.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_minus.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_report.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_td_minus.cc \
    #../../Libraries/cln-1.3.3/src/timing/cl_t_td_plus.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_GV_I.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_GV_I_copy.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_GV_I_debug.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_GV_number.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_GV_number_copy.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_GV_number_debug.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_SV_copy.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_SV_number.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_SV_number_debug.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_SV_ringelt.cc \
    #../../Libraries/cln-1.3.3/src/vector/cl_SV_ringelt_debug.cc \
    #../../Libraries/cln-1.3.3/src/base/digit/cl_2D_div.cc \
    #../../Libraries/cln-1.3.3/src/base/digit/cl_2D_exptpos.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_2DS_div.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_2DS_recip.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_arm_.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_hppa_.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_i386_.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_m68k_.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_mips_.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_mipsel_.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_sparc64_.cc \
  #  ../../Libraries/cln-1.3.3/src/base/digitseq/cl_asm_sparc_.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_div.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_mul.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_random.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_recip.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_recipsqrt.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/base/digitseq/cl_DS_trandom.cc \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_rcpointer2_hashweak_rcpointer.cc \
    #../../Libraries/cln-1.3.3/src/base/hash/cl_rcpointer_hashweak_rcpointer.cc \
    #../../Libraries/cln-1.3.3/src/base/input/cl_read_bad_syntax_exception.cc \
    #../../Libraries/cln-1.3.3/src/base/input/cl_read_eof_exception.cc \
    #../../Libraries/cln-1.3.3/src/base/input/cl_read_junk_exception.cc \
    #../../Libraries/cln-1.3.3/src/base/low/cl_low_div.cc \
    #../../Libraries/cln-1.3.3/src/base/low/cl_low_isqrt.cc \
    #../../Libraries/cln-1.3.3/src/base/low/cl_low_isqrt2.cc \
    #../../Libraries/cln-1.3.3/src/base/low/cl_low_mul.cc \
    ../../Libraries/cln-1.3.3/src/base/output/cl_output_dec.cc \
    ../../Libraries/cln-1.3.3/src/base/output/cl_output_hex.cc \
    ../../Libraries/cln-1.3.3/src/base/output/cl_prin_globals.cc \
    #../../Libraries/cln-1.3.3/src/base/proplist/cl_pl_add.cc \
    ../../Libraries/cln-1.3.3/src/base/proplist/cl_pl_d.cc \
    #../../Libraries/cln-1.3.3/src/base/proplist/cl_pl_get.cc \
    ../../Libraries/cln-1.3.3/src/base/random/cl_random_def.cc \
    ../../Libraries/cln-1.3.3/src/base/random/cl_random_from.cc \
    #../../Libraries/cln-1.3.3/src/base/random/cl_UL_random.cc \
    ../../Libraries/cln-1.3.3/src/base/ring/cl_no_ring.cc \
    #../../Libraries/cln-1.3.3/src/base/ring/cl_ring_debug.cc \
    #../../Libraries/cln-1.3.3/src/base/string/cl_spushstring_append.cc \
    #../../Libraries/cln-1.3.3/src/base/string/cl_spushstring_push.cc \
    #../../Libraries/cln-1.3.3/src/base/string/cl_sstring.cc \
    ../../Libraries/cln-1.3.3/src/base/string/cl_st_c2.cc \
    #../../Libraries/cln-1.3.3/src/base/string/cl_st_concat1.cc \
    #../../Libraries/cln-1.3.3/src/base/string/cl_st_concat2.cc \
    #../../Libraries/cln-1.3.3/src/base/string/cl_st_concat3.cc \
    #../../Libraries/cln-1.3.3/src/base/string/cl_st_debug.cc \
    #../../Libraries/cln-1.3.3/src/base/string/cl_st_hashcode.cc \
    ../../Libraries/cln-1.3.3/src/base/string/cl_st_make0.cc \
    ../../Libraries/cln-1.3.3/src/base/string/cl_st_make1.cc \
    ../../Libraries/cln-1.3.3/src/base/string/cl_st_make2.cc \
    #../../Libraries/cln-1.3.3/src/base/symbol/cl_sy_hashcode.cc \
    #../../Libraries/cln-1.3.3/src/base/symbol/cl_symbol.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_C_abs.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_C_abs_aux.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_C_signum.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_C_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_DF_hypot.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_FF_hypot.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_LF_hypot.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_R_hypot.cc \
    #../../Libraries/cln-1.3.3/src/complex/algebraic/cl_SF_hypot.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_equal.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_from_R_R_complex.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_from_R_R_complex1.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_imagpart.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_minus.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_minus1.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_mul.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_plus.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_plus1.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_realpart.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_square.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_uminus.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/cl_C_zerop.cc \
    #../../Libraries/cln-1.3.3/src/complex/input/cl_N_from_string.cc \
    #../../Libraries/cln-1.3.3/src/complex/input/cl_N_read.cc \
    #../../Libraries/cln-1.3.3/src/complex/input/cl_N_read_stream.cc \
    #../../Libraries/cln-1.3.3/src/complex/misc/cl_C_class.cc \
    #../../Libraries/cln-1.3.3/src/complex/misc/cl_C_conjugate.cc \
    #../../Libraries/cln-1.3.3/src/complex/misc/cl_C_debug.cc \
    #../../Libraries/cln-1.3.3/src/complex/misc/cl_C_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/complex/misc/cl_C_expt.cc \
    #../../Libraries/cln-1.3.3/src/complex/misc/cl_C_expt_I.cc \
    #../../Libraries/cln-1.3.3/src/complex/misc/cl_N_as.cc \
    #../../Libraries/cln-1.3.3/src/complex/output/cl_N_aprint.cc \
    #../../Libraries/cln-1.3.3/src/complex/output/cl_N_bprint.cc \
    #../../Libraries/cln-1.3.3/src/complex/ring/cl_C_ring.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_acos.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_acosh.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_asin.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_asinh.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_asinh_aux.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_atan.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_atanh.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_atanh_aux.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_cis.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_cos.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_cosh.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_exp.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_expt_C.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_log.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_log2.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_phase.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_sin.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_sinh.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_tan.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_C_tanh.cc \
    #../../Libraries/cln-1.3.3/src/complex/transcendental/cl_R_cis.cc \
    #../../Libraries/cln-1.3.3/src/float/algebraic/cl_F_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/float/base/cl_F_globals.cc \
    #../../Libraries/cln-1.3.3/src/float/base/cl_F_nan_exception.cc \
    #../../Libraries/cln-1.3.3/src/float/base/cl_F_overflow_exception.cc \
    #../../Libraries/cln-1.3.3/src/float/base/cl_F_underflow_exception.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_DF_to_double.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_DF_to_FF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_DF_to_float.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_DF_to_LF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_DF_to_SF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_from_F.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_from_F_f.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_from_I.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_from_I_def.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_from_I_f.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_from_RA.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_from_RA_def.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_from_RA_f.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_to_DF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_to_double.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_to_FF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_to_float.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_to_LF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_F_to_SF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_FF_to_DF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_FF_to_double.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_FF_to_float.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_FF_to_LF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_FF_to_SF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_LF_to_DF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_LF_to_double.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_LF_to_FF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_LF_to_float.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_LF_to_SF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_SF_to_DF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_SF_to_double.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_SF_to_FF.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_SF_to_float.cc \
    #../../Libraries/cln-1.3.3/src/float/conv/cl_SF_to_LF.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_ceil1.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_ceil2.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_ceil22.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_fceil1.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_fceil2.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_ffloor1.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_ffloor2.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_floor1.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_floor2.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_floor22.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_fround1.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_fround2.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_ftrunc1.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_ftrunc2.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_round1.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_round2.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_round22.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_trunc1.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_trunc2.cc \
    #../../Libraries/cln-1.3.3/src/float/division/cl_F_trunc22.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_compare.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_div.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_I_div.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_I_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_minus.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_minusp.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_plus.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_plusp.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_RA_div.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_RA_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_recip.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_scale.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_scale_I.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_square.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_uminus.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_F_zerop.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_I_F_div.cc \
    #../../Libraries/cln-1.3.3/src/float/elem/cl_RA_F_div.cc \
    #../../Libraries/cln-1.3.3/src/float/input/cl_F_from_string.cc \
    #../../Libraries/cln-1.3.3/src/float/input/cl_F_read.cc \
    #../../Libraries/cln-1.3.3/src/float/input/cl_F_read_stream.cc \
    #../../Libraries/cln-1.3.3/src/float/input/cl_F_readparsed.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_abs.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_as.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_decode.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_digits.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_epsneg.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_epspos.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_exponent.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_extendsqrt.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_extendsqrtx.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_idecode.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_leastneg.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_leastpos.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_max.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_min.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_mostneg.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_mostpos.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_precision.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_rational.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_shortenrel.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_sign.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_sign2.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_F_signum.cc \
    #../../Libraries/cln-1.3.3/src/float/misc/cl_float_format.cc \
    #../../Libraries/cln-1.3.3/src/float/output/cl_F_aprint.cc \
    #../../Libraries/cln-1.3.3/src/float/output/cl_F_bprint.cc \
    #../../Libraries/cln-1.3.3/src/float/output/cl_F_cprint.cc \
    #../../Libraries/cln-1.3.3/src/float/output/cl_F_dprint.cc \
    #../../Libraries/cln-1.3.3/src/float/output/cl_F_printb.cc \
    #../../Libraries/cln-1.3.3/src/float/random/cl_F_random.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_atanhx.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_atanx.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_catalanconst.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_catalanconst_def.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_catalanconst_f.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_catalanconst_var.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_cos.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_cosh.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_coshsinh.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_cossin.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_eulerconst.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_eulerconst_def.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_eulerconst_f.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_eulerconst_var.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_exp.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_exp1.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_exp1_def.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_exp1_f.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_exp1_var.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_expx.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln10.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln10_f.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln10_var.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln2.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln2_f.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_ln2_var.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_lnx.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_pi.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_pi_def.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_pi_f.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_pi_var.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_roundpi.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_roundpi2.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_sin.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_sinh.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_sinhx.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_sinx.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_tan.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_tanh.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_zeta_int.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_zeta_int_def.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_F_zeta_int_f.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_atan_recip.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_atanh_recip.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_catalanconst.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_coshsinh.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_coshsinh_aux.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_cossin.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_cossin_aux.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_eulerconst.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_exp1.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_exp_aux.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ln10.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ln2.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_pi.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_a.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_ab.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_b.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_p.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_pa.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_pab.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_pb.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_pq.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_pqa.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_pqab.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_pqb.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_q.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_qa.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_qab.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratseries_qb.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratsumseries_pqcd.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratsumseries_pqcd_aux.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratsumseries_pqd.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_ratsumseries_pqd_aux.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_zeta3.cc \
    #../../Libraries/cln-1.3.3/src/float/transcendental/cl_LF_zeta_int.cc \
    #../../Libraries/cln-1.3.3/src/integer/2adic/cl_I_2adic_div.cc \
    #../../Libraries/cln-1.3.3/src/integer/2adic/cl_I_2adic_recip.cc \
    #../../Libraries/cln-1.3.3/src/integer/algebraic/cl_I_rootp.cc \
    #../../Libraries/cln-1.3.3/src/integer/algebraic/cl_I_rootp_aux.cc \
    #../../Libraries/cln-1.3.3/src/integer/algebraic/cl_I_rootp_I.cc \
    #../../Libraries/cln-1.3.3/src/integer/algebraic/cl_I_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/integer/algebraic/cl_I_sqrtp.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_ash.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_ash_exception.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_ash_I.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_boole.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_dpb.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_dpf.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_fullbyte.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_ilength.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_ldb.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_ldbtest.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_ldbx.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_ldbxtest.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_log_aux.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logand.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logandc2.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logbitp.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logbitp_I.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logcount.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logeqv.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logior.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_lognand.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_lognor.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_lognot.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logorc2.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logtest.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_logxor.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_mkf.cc \
    #../../Libraries/cln-1.3.3/src/integer/bitwise/cl_I_mkfx.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_cached_power.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_digits_need.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_digits.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_DS.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_L.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_L2.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_NDS.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_NUDS.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_Q.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_Q2.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_UDS.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_UL.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_UL2.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_from_UQ.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_mul10plus.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_to_digits.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_to_L.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_to_Q.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_to_UL.cc \
    #../../Libraries/cln-1.3.3/src/integer/conv/cl_I_to_UQ.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_ceil1.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_ceil2.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_exquo.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_exquo_exception.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_exquopos.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_floor1.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_floor2.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_mod.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_rem.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_round1.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_round2.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_trunc1.cc \
    #../../Libraries/cln-1.3.3/src/integer/division/cl_I_trunc2.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_compare.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_div.cc \
    ../../Libraries/cln-1.3.3/src/integer/elem/cl_I_equal.cc \
    ../../Libraries/cln-1.3.3/src/integer/elem/cl_I_minus.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_minus1.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_minusp.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_mul.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_plus.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_plus1.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_plusp.cc \
    ../../Libraries/cln-1.3.3/src/integer/elem/cl_I_square.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_uminus.cc \
    #../../Libraries/cln-1.3.3/src/integer/elem/cl_I_zerop.cc \
    #../../Libraries/cln-1.3.3/src/integer/gcd/cl_I_gcd.cc \
    #../../Libraries/cln-1.3.3/src/integer/gcd/cl_I_gcd_aux.cc \
    #../../Libraries/cln-1.3.3/src/integer/gcd/cl_I_gcd_aux2.cc \
    #../../Libraries/cln-1.3.3/src/integer/gcd/cl_I_lcm.cc \
    #../../Libraries/cln-1.3.3/src/integer/gcd/cl_I_xgcd.cc \
    #../../Libraries/cln-1.3.3/src/integer/gcd/cl_low_gcd.cc \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_gcobject.cc \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_gcpointer.cc \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_pointer.cc \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_rcobject.cc \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hash_rcpointer.cc \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hashcode.cc \
    #../../Libraries/cln-1.3.3/src/integer/hash/cl_I_hashweak_rcpointer.cc \
    #../../Libraries/cln-1.3.3/src/integer/input/cl_I_from_string.cc \
    #../../Libraries/cln-1.3.3/src/integer/input/cl_I_read.cc \
    #../../Libraries/cln-1.3.3/src/integer/input/cl_I_read_stream.cc \
    #../../Libraries/cln-1.3.3/src/integer/input/cl_I_readparsed.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_BN_class.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_FN_class.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_abs.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_as.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_debug.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_exptpos.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_exptpos_I.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_max.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_min.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_oddp.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_ord2.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_power2p.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/cl_I_signum.cc \
    #../../Libraries/cln-1.3.3/src/integer/output/cl_I_aprint.cc \
    #../../Libraries/cln-1.3.3/src/integer/output/cl_I_bprint.cc \
    #../../Libraries/cln-1.3.3/src/integer/output/cl_I_cprint.cc \
    #../../Libraries/cln-1.3.3/src/integer/output/cl_I_decstring.cc \
    #../../Libraries/cln-1.3.3/src/integer/output/cl_I_dprint.cc \
    #../../Libraries/cln-1.3.3/src/integer/output/cl_I_print.cc \
    #../../Libraries/cln-1.3.3/src/integer/output/cl_I_print_string.cc \
    #../../Libraries/cln-1.3.3/src/integer/random/cl_I_random.cc \
    #../../Libraries/cln-1.3.3/src/integer/random/cl_I_trandom.cc \
    #../../Libraries/cln-1.3.3/src/integer/ring/cl_0_ring.cc \
    ../../Libraries/cln-1.3.3/src/integer/ring/cl_I_ring.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_asm_GF2.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_asm_sparc_GF2.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_UP.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_UP_named.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_UP_no_ring.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/elem/cl_UP_unnamed.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/misc/cl_UP_debug.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/misc/cl_UP_deriv.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/misc/cl_UP_I_hermite.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/misc/cl_UP_I_laguerre.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/misc/cl_UP_I_tchebychev.cc \
    #../../Libraries/cln-1.3.3/src/polynomial/misc/cl_UP_RA_legendre.cc \
    #../../Libraries/cln-1.3.3/src/rational/algebraic/cl_RA_rootp.cc \
    #../../Libraries/cln-1.3.3/src/rational/algebraic/cl_RA_rootp_I.cc \
    #../../Libraries/cln-1.3.3/src/rational/algebraic/cl_RA_sqrtp.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_ceil1.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_ceil12.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_ceil2.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_ceil22.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_floor1.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_floor12.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_floor2.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_floor22.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_round1.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_round12.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_round2.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_round22.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_trunc1.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_trunc12.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_trunc2.cc \
    #../../Libraries/cln-1.3.3/src/rational/division/cl_RA_trunc22.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_compare.cc \
  #  ../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_denominator.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_div.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_equal.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_from_I_I_div.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_from_I_posI.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_from_I_posI1.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_from_I_posI_div.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_minus.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_minus1.cc \
  #  ../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_minusp.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_mul.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_numerator.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_plus.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_plus1.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_plusp.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_recip.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_square.cc \
    #../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_uminus.cc \
  #  ../../Libraries/cln-1.3.3/src/rational/elem/cl_RA_zerop.cc \
    #../../Libraries/cln-1.3.3/src/rational/input/cl_RA_from_string.cc \
    #../../Libraries/cln-1.3.3/src/rational/input/cl_RA_read.cc \
    #../../Libraries/cln-1.3.3/src/rational/input/cl_RA_read_stream.cc \
    #../../Libraries/cln-1.3.3/src/rational/input/cl_RA_readparsed.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_abs.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_as.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_class.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_debug.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_expt.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_expt_I.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_exptpos.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_exptpos_I.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_max.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_min.cc \
    #../../Libraries/cln-1.3.3/src/rational/misc/cl_RA_signum.cc \
    #../../Libraries/cln-1.3.3/src/rational/output/cl_RA_aprint.cc \
    #../../Libraries/cln-1.3.3/src/rational/output/cl_RA_bprint.cc \
    #../../Libraries/cln-1.3.3/src/rational/output/cl_RA_cprint.cc \
    #../../Libraries/cln-1.3.3/src/rational/output/cl_RA_dprint.cc \
    #../../Libraries/cln-1.3.3/src/rational/output/cl_RA_print.cc \
    #../../Libraries/cln-1.3.3/src/rational/ring/cl_RA_ring.cc \
    #../../Libraries/cln-1.3.3/src/rational/transcendental/cl_I_logp.cc \
    #../../Libraries/cln-1.3.3/src/rational/transcendental/cl_RA_logp.cc \
    #../../Libraries/cln-1.3.3/src/real/algebraic/cl_R_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/real/algebraic/cl_RA_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_F_from_R.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_F_from_R_def.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_F_from_R_f.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_R_to_DF.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_R_to_double.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_R_to_FF.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_R_to_float.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_R_to_LF.cc \
    #../../Libraries/cln-1.3.3/src/real/conv/cl_R_to_SF.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ceil1.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ceil12.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ceil2.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ceil22.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_fceil1.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_fceil12.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_fceil2.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_fceil22.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ffloor1.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ffloor12.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ffloor2.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ffloor22.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_floor1.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_floor12.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_floor2.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_floor22.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_fround1.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_fround12.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_fround2.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_fround22.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ftrunc1.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ftrunc12.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ftrunc2.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_ftrunc22.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_mod.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_rem.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_round1.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_round12.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_round2.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_round22.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_trunc1.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_trunc12.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_trunc2.cc \
    #../../Libraries/cln-1.3.3/src/real/division/cl_R_trunc22.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_compare.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_div.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_equal.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_minus.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_minus1.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_minusp.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_mul.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_plus.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_plus1.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_plusp.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_recip.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_square.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_uminus.cc \
    #../../Libraries/cln-1.3.3/src/real/elem/cl_R_zerop.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_cardinal.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_floatstring.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_integer.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_newroman.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_oldroman.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_ordinal.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_paddedstring.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_scaleexp.cc \
    #../../Libraries/cln-1.3.3/src/real/format-output/cl_fmt_tens.cc \
    #../../Libraries/cln-1.3.3/src/real/input/cl_R_from_string.cc \
    #../../Libraries/cln-1.3.3/src/real/input/cl_R_read.cc \
    #../../Libraries/cln-1.3.3/src/real/input/cl_R_read_stream.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_abs.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_as.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_contagion.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_debug.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_expt.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_expt_I.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_max.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_min.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_rational.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_rationalize.cc \
    #../../Libraries/cln-1.3.3/src/real/misc/cl_R_signum.cc \
    #../../Libraries/cln-1.3.3/src/real/output/cl_R_aprint.cc \
    #../../Libraries/cln-1.3.3/src/real/output/cl_R_bprint.cc \
    #../../Libraries/cln-1.3.3/src/real/output/cl_R_cprint.cc \
    #../../Libraries/cln-1.3.3/src/real/random/cl_R_random.cc \
    #../../Libraries/cln-1.3.3/src/real/ring/cl_R_ring.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_atan.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_atan2.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_cos.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_cosh.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_coshsinh.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_cossin.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_exp.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_ln.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_log.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_sin.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_sinh.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_tan.cc \
    #../../Libraries/cln-1.3.3/src/real/transcendental/cl_R_tanh.cc \
    #../../Libraries/cln-1.3.3/src/vector/output/cl_GV_number_aprint.cc \
    #../../Libraries/cln-1.3.3/src/vector/output/cl_SV_aprint.cc \
    #../../Libraries/cln-1.3.3/src/vector/output/cl_SV_number_aprint.cc \
    #../../Libraries/cln-1.3.3/src/base/string/input/cl_st_get1.cc \
    #../../Libraries/cln-1.3.3/src/base/string/input/cl_st_get2.cc \
    #../../Libraries/cln-1.3.3/src/base/string/input/cl_st_getline1.cc \
    #../../Libraries/cln-1.3.3/src/base/string/input/cl_st_getline2.cc \
    #../../Libraries/cln-1.3.3/src/base/string/input/cl_st_gettoken.cc \
    ../../Libraries/cln-1.3.3/src/base/string/misc/cl_st_class.cc \
    #../../Libraries/cln-1.3.3/src/base/string/output/cl_st_print.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/division/cl_C_DF_recip.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/division/cl_C_div.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/division/cl_C_FF_recip.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/division/cl_C_LF_recip.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/division/cl_C_recip.cc \
    #../../Libraries/cln-1.3.3/src/complex/elem/division/cl_C_SF_recip.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/algebraic/cl_DF_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/conv/cl_DF_from_double.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/conv/cl_DF_to_doublej.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/conv/cl_I_to_double.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/conv/cl_RA_to_double.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/division/cl_DF_ceil22.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/division/cl_DF_fceil.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/division/cl_DF_floor22.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/division/cl_DF_recip.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/division/cl_DF_round22.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/division/cl_DF_trunc22.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_compare.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_div.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_ffloor.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_from_I.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_from_RA.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_fround.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_ftrunc.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_futrunc.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_globals.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_minus.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_minusp.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_plus.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_plusp.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_scale.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_scale_I.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_to_I.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_uminus.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/elem/cl_DF_zerop.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/input/cl_DF_from_string.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_abs.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_as.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_class.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_debug.cc \
  #  ../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_decode.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_digits.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_exponent.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_idecode.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_max.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_min.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_precision.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_sign.cc \
    #../../Libraries/cln-1.3.3/src/float/dfloat/misc/cl_DF_signum.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/algebraic/cl_FF_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/conv/cl_FF_from_float.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/conv/cl_FF_to_floatj.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/conv/cl_I_to_float.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/conv/cl_RA_to_float.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/division/cl_FF_ceil22.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/division/cl_FF_fceil.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/division/cl_FF_floor22.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/division/cl_FF_recip.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/division/cl_FF_round22.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/division/cl_FF_trunc22.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_compare.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_div.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_ffloor.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_from_I.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_from_RA.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_fround.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_ftrunc.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_futrunc.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_globals.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_minus.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_minusp.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_plus.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_plusp.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_scale.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_scale_I.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_to_I.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_uminus.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/elem/cl_FF_zerop.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/input/cl_FF_from_string.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_abs.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_as.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_class.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_debug.cc \
  #  ../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_decode.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_digits.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_exponent.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_idecode.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_max.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_min.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_precision.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_sign.cc \
    #../../Libraries/cln-1.3.3/src/float/ffloat/misc/cl_FF_signum.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/algebraic/cl_LF_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/division/cl_LF_ceil22.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/division/cl_LF_fceil.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/division/cl_LF_floor22.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/division/cl_LF_recip.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/division/cl_LF_round22.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/division/cl_LF_trunc22.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_I_LF_div.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_1minus.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_1plus.cc \
  #  ../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_2minus.cc \
  #  ../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_2plus.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_compare.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_div.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_ffloor.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_from_I.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_from_RA.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_fround.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_ftrunc.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_futrunc.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_globals.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_I_div.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_I_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_minus1.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_minusp.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_plus1.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_plusp.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_RA_div.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_RA_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_scale.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_scale_I.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_square.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_to_I.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_uminus.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_LF_zerop.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/elem/cl_RA_LF_div.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/input/cl_LF_from_string.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_abs.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_as.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_class.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_debug.cc \
  #  ../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_decode.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_digits.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_exponent.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_extend.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_idecode.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_leninc.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_lenincx.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_max.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_min.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_precision.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_shorten.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_shortenrel.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_shortenwith.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_sign.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_signum.cc \
    #../../Libraries/cln-1.3.3/src/float/lfloat/misc/cl_LF_to_LF.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/algebraic/cl_SF_sqrt.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/division/cl_SF_ceil22.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/division/cl_SF_fceil.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/division/cl_SF_ffloor.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/division/cl_SF_floor22.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/division/cl_SF_recip.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/division/cl_SF_round22.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/division/cl_SF_trunc22.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_compare.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_div.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_from_I.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_from_RA.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_fround.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_ftrunc.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_futrunc.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_minus.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_minusp.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_mul.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_plus.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_plusp.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_scale.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_scale_I.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_to_I.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_uminus.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/elem/cl_SF_zerop.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/input/cl_SF_from_string.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_abs.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_as.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_class.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_debug.cc \
  #  ../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_decode.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_digits.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_eqhashcode.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_exponent.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_idecode.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_max.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_min.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_precision.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_sign.cc \
    #../../Libraries/cln-1.3.3/src/float/sfloat/misc/cl_SF_signum.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/combin/cl_I_binomial.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/combin/cl_I_doublefactorial.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/combin/cl_I_factorial.cc \
    #../../Libraries/cln-1.3.3/src/integer/misc/combin/cl_I_factorial_aux.cc


}

cross_compile {
  # Crosscompile only
  message("CLN, built for cross-compiling from Linux to Windows")
}

