#include "ap.h"


// Assembler optimized but not-so-good performance WFTA routines

#if defined (USEASMGCC386)

asm (";\
    .globl _wfta2;\
    .globl _wfta3;\
    .globl _wfta4;\
    .globl _wfta5;\
/*;\
    .globl _wfta7;\
    .globl _wfta8;\
    .globl _wfta9;\
    .globl _wfta16;\
*/;\
    .globl _wftan2;\
    .globl _wftan3;\
/*;\
    .globl _wftan4;\
    .globl _wftan5;\
    .globl _wftan7;\
    .globl _wftan8;\
    .globl _wftan9;\
    .globl _wftan16;\
*/;\
;\
_wfta2:;\
    pushl %ebx;\
    pushl %ecx;\
    pushl %edx;\
    pushl %esi;\
    pushl %edi;\
;\
    movl 24(%esp), %ecx;\
    movl _modulus, %edi;\
    movl (%ecx), %eax;\
    movl 4(%ecx), %ebx;\
    movl %eax, %esi;\
;\
    addl %ebx, %esi; cmpl %edi, %esi; jb 0f; subl %edi, %esi; 0:;\
;\
    subl %ebx, %eax; jnc 0f; addl %edi, %eax; 0:;\
;\
    movl %esi, (%ecx);\
    movl %eax, 4(%ecx);\
;\
    movl 28(%esp), %ebx;\
;\
    movl $2, %esi;\
;\
    wfta2mulloop:;\
");

#if defined (USEFPU)

asm (";\
    fildl (%ecx);\
    fimull (%ebx);\
    fld %st;\
    fmul %st(2), %st;\
    fadd %st(4), %st;\
    fsub %st(4), %st;\
    fmul %st(3), %st;\
    fsubrp %st, %st(1);\
    fistpl (%ecx);\
");

#else

asm (";\
    movl (%ecx), %eax;\
    mull (%ebx);\
    divl %edi;\
    movl %edx, (%ecx);\
");

#endif

asm (";\
    addl $4, %ecx;\
    addl $4, %ebx;\
    decl %esi;\
    jnz wfta2mulloop;\
;\
    popl %edi;\
    popl %esi;\
    popl %edx;\
    popl %ecx;\
    popl %ebx;\
;\
    ret;\
;\
_wfta3:;\
    pushl %ebx;\
    pushl %ecx;\
    pushl %edx;\
    pushl %esi;\
    pushl %edi;\
;\
    movl 24(%esp), %ecx;\
    movl _modulus, %edi;\
    movl 4(%ecx), %eax;\
    movl 8(%ecx), %ebx;\
    movl %eax, %esi;\
;\
    addl %ebx, %esi; cmpl %edi, %esi; jb 0f; subl %edi, %esi; 0:;\
;\
    subl %ebx, %eax; jnc 0f; addl %edi, %eax; 0:;\
;\
    movl (%ecx), %ebx;\
    movl %esi, 4(%ecx);\
    movl %eax, 8(%ecx);\
;\
    addl %ebx, %esi; cmpl %edi, %esi; jb 0f; subl %edi, %esi; 0:;\
;\
    movl %esi, (%ecx);\
;\
    movl 28(%esp), %ebx;\
;\
    movl $3, %esi;\
;\
    wfta3mulloop:;\
");

#if defined (USEFPU)

asm (";\
    fildl (%ecx);\
    fimull (%ebx);\
    fld %st;\
    fmul %st(2), %st;\
    fadd %st(4), %st;\
    fsub %st(4), %st;\
    fmul %st(3), %st;\
    fsubrp %st, %st(1);\
    fistpl (%ecx);\
");

#else

asm (";\
    movl (%ecx), %eax;\
    mull (%ebx);\
    divl %edi;\
    movl %edx, (%ecx);\
");

#endif

asm (";\
    addl $4, %ecx;\
    addl $4, %ebx;\
    decl %esi;\
    jnz wfta3mulloop;\
;\
    subl $12, %ecx;\
;\
    movl (%ecx), %eax;\
    movl 4(%ecx), %ebx;\
;\
    addl %ebx, %eax; cmpl %edi, %eax; jb 0f; subl %edi, %eax; 0:;\
;\
    movl %eax, %esi;\
    movl 8(%ecx), %ebx;\
;\
    addl %ebx, %esi; cmpl %edi, %esi; jb 0f; subl %edi, %esi; 0:;\
;\
    subl %ebx, %eax; jnc 0f; addl %edi, %eax; 0:;\
;\
    movl %esi, 4(%ecx);\
    movl %eax, 8(%ecx);\
;\
    popl %edi;\
    popl %esi;\
    popl %edx;\
    popl %ecx;\
    popl %ebx;\
;\
    ret;\
;\
_wfta4:;\
    pushl %ebx;\
    pushl %ecx;\
    pushl %edx;\
    pushl %esi;\
    pushl %edi;\
    pushl %ebp;\
;\
    movl 28(%esp), %ecx;\
    movl _modulus, %edi;\
    movl (%ecx), %eax;\
    movl 8(%ecx), %ebx;\
    movl %eax, %esi;\
;\
    addl %ebx, %esi; cmpl %edi, %esi; jb 0f; subl %edi, %esi; 0:;\
;\
    subl %ebx, %eax; jnc 0f; addl %edi, %eax; 0:;\
;\
    movl %eax, 8(%ecx);\
    movl 4(%ecx), %eax;\
    movl 12(%ecx), %ebx;\
    movl %eax, %ebp;\
;\
    addl %ebx, %ebp; cmpl %edi, %ebp; jb 0f; subl %edi, %ebp; 0:;\
;\
    subl %ebx, %eax; jnc 0f; addl %edi, %eax; 0:;\
;\
    movl %eax, 12(%ecx);\
    movl %esi, %eax;\
;\
    addl %ebp, %esi; cmpl %edi, %esi; jb 0f; subl %edi, %esi; 0:;\
;\
    subl %ebp, %eax; jnc 0f; addl %edi, %eax; 0:;\
;\
    movl %esi, (%ecx);\
    movl %eax, 4(%ecx);\
;\
    movl 32(%esp), %ebx;\
;\
    movl $4, %esi;\
;\
    wfta4mulloop:;\
");

#if defined (USEFPU)

asm (";\
    fildl (%ecx);\
    fimull (%ebx);\
    fld %st;\
    fmul %st(2), %st;\
    fadd %st(4), %st;\
    fsub %st(4), %st;\
    fmul %st(3), %st;\
    fsubrp %st, %st(1);\
    fistpl (%ecx);\
");

#else

asm (";\
    movl (%ecx), %eax;\
    mull (%ebx);\
    divl %edi;\
    movl %edx, (%ecx);\
");

#endif

asm (";\
    addl $4, %ecx;\
    addl $4, %ebx;\
    decl %esi;\
    jnz wfta4mulloop;\
;\
    subl $16, %ecx;\
;\
    movl 8(%ecx), %eax;\
    movl 12(%ecx), %ebx;\
    movl %eax, %esi;\
;\
    addl %ebx, %esi; cmpl %edi, %esi; jb 0f; subl %edi, %esi; 0:;\
;\
    subl %ebx, %eax; jnc 0f; addl %edi, %eax; 0:;\
;\
    movl 4(%ecx), %ebx;\
    movl %eax, 12(%ecx);\
    movl %esi, 4(%ecx);\
    movl %ebx, 8(%ecx);\
;\
    popl %ebp;\
    popl %edi;\
    popl %esi;\
    popl %edx;\
    popl %ecx;\
    popl %ebx;\
;\
    ret;\
;\
_wfta5:;\
    subl $24, %esp;\
    pushl %ebx;\
    pushl %ecx;\
    pushl %edx;\
    pushl %esi;\
    pushl %edi;\
    pushl %ebp;\
;\
    movl 52(%esp), %ecx;\
    movl _modulus, %edi;\
    movl 4(%ecx), %eax;\
    movl 16(%ecx), %ebx;\
    movl %eax, %esi;\
;\
    addl %ebx, %esi; cmpl %edi, %esi; jb 0f; subl %edi, %esi; 0:;\
;\
    subl %ebx, %eax; jnc 0f; addl %edi, %eax; 0:;\
;\
    movl 12(%ecx), %edx;\
    movl 8(%ecx), %ebx;\
    movl %edx, %ebp;\
;\
    addl %ebx, %ebp; cmpl %edi, %ebp; jb 0f; subl %edi, %ebp; 0:;\
;\
    subl %ebx, %edx; jnc 0f; addl %edi, %edx; 0:;\
;\
    movl %esi, %ebx;\
;\
    addl %ebp, %esi; cmpl %edi, %esi; jb 0f; subl %edi, %esi; 0:;\
;\
    movl %esi, 28(%esp);\
    movl %edx, 40(%esp);\
    movl %eax, 44(%esp);\
;\
    subl %ebp, %ebx; jnc 0f; addl %edi, %ebx; 0:;\
;\
    addl %eax, %edx; cmpl %edi, %edx; jb 0f; subl %edi, %edx; 0:;\
;\
    movl (%ecx), %eax;\
    movl %ebx, 32(%esp);\
    movl %edx, 36(%esp);\
;\
    addl %eax, %esi; cmpl %edi, %esi; jb 0f; subl %edi, %esi; 0:;\
;\
    movl %esi, 24(%esp);\
;\
    leal 24(%esp), %ecx;\
    movl 56(%esp), %ebx;\
;\
    movl $6, %esi;\
;\
    wfta5mulloop:;\
");

#if defined (USEFPU)

asm (";\
    fildl (%ecx);\
    fimull (%ebx);\
    fld %st;\
    fmul %st(2), %st;\
    fadd %st(4), %st;\
    fsub %st(4), %st;\
    fmul %st(3), %st;\
    fsubrp %st, %st(1);\
    fistpl (%ecx);\
");

#else

asm (";\
    movl (%ecx), %eax;\
    mull (%ebx);\
    divl %edi;\
    movl %edx, (%ecx);\
");

#endif

asm (";\
    addl $4, %ecx;\
    addl $4, %ebx;\
    decl %esi;\
    jnz wfta5mulloop;\
;\
    movl 24(%esp), %eax;\
    movl 28(%esp), %ebx;\
;\
    addl %ebx, %eax; cmpl %edi, %eax; jb 0f; subl %edi, %eax; 0:;\
;\
    movl 32(%esp), %ebx;\
    movl %eax, %esi;\
;\
    addl %ebx, %esi; cmpl %edi, %esi; jb 0f; subl %edi, %esi; 0:;\
;\
    subl %ebx, %eax; jnc 0f; addl %edi, %eax; 0:;\
;\
    movl 36(%esp), %ebx;\
    movl 40(%esp), %ebp;\
    movl 44(%esp), %ecx;\
    movl %ebx, %edx;\
;\
    addl %ecx, %ebx; cmpl %edi, %ebx; jb 0f; subl %edi, %ebx; 0:;\
;\
    subl %ebp, %edx; jnc 0f; addl %edi, %edx; 0:;\
;\
    movl %esi, %ebp;\
    movl 52(%esp), %ecx;\
;\
    addl %edx, %esi; cmpl %edi, %esi; jb 0f; subl %edi, %esi; 0:;\
;\
    subl %edx, %ebp; jnc 0f; addl %edi, %ebp; 0:;\
;\
    movl %esi, 4(%ecx);\
    movl %ebp, 16(%ecx);\
    movl %eax, %esi;\
;\
    addl %ebx, %esi; cmpl %edi, %esi; jb 0f; subl %edi, %esi; 0:;\
;\
    subl %ebx, %eax; jnc 0f; addl %edi, %eax; 0:;\
;\
    movl 24(%esp), %edx;\
    movl %esi, 8(%ecx);\
    movl %eax, 12(%ecx);\
    movl %edx, (%ecx);\
;\
    popl %ebp;\
    popl %edi;\
    popl %esi;\
    popl %edx;\
    popl %ecx;\
    popl %ebx;\
    addl $24, %esp;\
;\
    ret;\
;\
_wftan2:;\
    pushl %ebx;\
    pushl %ecx;\
    pushl %edx;\
    pushl %esi;\
    pushl %edi;\
    pushl %ebp;\
;\
    movl 28(%esp), %ecx;\
    movl 36(%esp), %esi;\
    movl _modulus, %edi;\
    leal (%ecx, %esi, 4), %edx;\
;\
    wftan2loop1:;\
    movl -4(%ecx, %esi, 4), %eax;\
    movl -4(%edx, %esi, 4), %ebx;\
;\
    addl %eax, %ebx; addl %eax, %eax;\
    subl %ebx, %eax; jnc 0f; addl %edi, %eax; 0:;\
    cmpl %edi, %ebx; jb 0f; subl %edi, %ebx; 0:;\
;\
    movl %eax, -4(%edx, %esi, 4);\
    movl %ebx, -4(%ecx, %esi, 4);\
;\
    decl %esi;\
    jnz wftan2loop1;\
;\
    movl 40(%esp), %ebx;\
    movl 44(%esp), %ecx;\
    movl 36(%esp), %esi;\
    movl (%ebx), %ebx;\
;\
    cmpl %ebx, %esi;\
    jne wftan2nblock;\
;\
    movl _wftas(, %ebx, 4), %ebx;\
    movl 32(%esp), %edx;\
    movl 28(%esp), %edi;\
    shll $2, %ecx;\
    shll $2, %esi;\
    pushl %edx;\
    pushl %edi;\
;\
    addl %ecx, %edx;\
    addl %esi, %edi;\
    pushl %edx;\
    pushl %edi;\
;\
    call *%ebx;\
    addl $8, %esp;\
;\
    call *%ebx;\
    addl $8, %esp;\
;\
    jmp wftan2end;\
;\
    wftan2nblock:;\
;\
    movl %esi, %eax;\
    xorl %edx, %edx;\
    divw %bx;\
    movl %eax, %ebp;\
;\
    movl 48(%esp), %edi;\
    movl %ecx, %eax;\
    xorl %edx, %edx;\
    divw (%edi);\
;\
    movl _wftan(, %ebx, 4), %ebx;\
    shll $2, %ecx;\
    shll $2, %esi;\
    movl 28(%esp), %edi;\
    movl 32(%esp), %edx;\
;\
    addl $4, 48(%esp);\
    addl $4, 40(%esp);\
;\
    pushl 48(%esp);\
    pushl %eax;\
    pushl 48(%esp)              # 40(esp) but esp changed;\
    pushl %ebp;\
    pushl %edx;\
    pushl %edi;\
;\
    addl %esi, %edi;\
    addl %ecx, %edx;\
    pushl 72(%esp)              # 48(esp) but esp changed;\
    pushl %eax;\
    pushl 72(%esp)              # 40(esp) but esp changed;\
    pushl %ebp;\
    pushl %edx;\
    pushl %edi;\
;\
    call *%ebx;\
    addl $24, %esp;\
;\
    call *%ebx;\
    addl $24, %esp;\
;\
    wftan2end:;\
;\
    popl %ebp;\
    popl %edi;\
    popl %esi;\
    popl %edx;\
    popl %ecx;\
    popl %ebx;\
;\
    ret;\
;\
_wftan3:;\
    pushl %ebx;\
    pushl %ecx;\
    pushl %edx;\
    pushl %esi;\
    pushl %edi;\
    pushl %ebp;\
;\
    movl 28(%esp), %ecx;\
    movl 36(%esp), %esi;\
    movl _modulus, %edi;\
    leal (%ecx, %esi, 4), %edx;\
    leal (%ecx, %esi, 8), %ebp;\
;\
    wftan3loop1:;\
    movl -4(%edx, %esi, 4), %eax;\
    movl -4(%ebp, %esi, 4), %ebx;\
;\
    addl %eax, %ebx; addl %eax, %eax;\
    subl %ebx, %eax; jnc 0f; addl %edi, %eax; 0:;\
    cmpl %edi, %ebx; jb 0f; subl %edi, %ebx; 0:;\
;\
    movl %eax, -4(%ebp, %esi, 4);\
    movl -4(%ecx, %esi, 4), %eax;\
    movl %ebx, -4(%edx, %esi, 4);\
;\
    addl %eax, %ebx; cmpl %edi, %ebx; jb 0f; subl %edi, %ebx; 0:;\
;\
    movl %ebx, -4(%ecx, %esi, 4);\
;\
    decl %esi;\
    jnz wftan3loop1;\
;\
    movl 40(%esp), %ebx;\
    movl 44(%esp), %ecx;\
    movl 36(%esp), %esi;\
    movl (%ebx), %ebx;\
;\
    cmpl %ebx, %esi;\
    jne wftan3nblock;\
;\
    movl _wftas(, %ebx, 4), %ebx;\
    movl 32(%esp), %edx;\
    movl 28(%esp), %edi;\
    shll $2, %ecx;\
    shll $2, %esi;\
    pushl %edx;\
    pushl %edi;\
;\
    addl %ecx, %edx;\
    addl %esi, %edi;\
    pushl %edx;\
    pushl %edi;\
;\
    addl %ecx, %edx;\
    addl %esi, %edi;\
    pushl %edx;\
    pushl %edi;\
;\
    call *%ebx;\
    addl $8, %esp;\
;\
    call *%ebx;\
    addl $8, %esp;\
;\
    call *%ebx;\
    addl $8, %esp;\
;\
    jmp wftan3end;\
;\
    wftan3nblock:;\
;\
    movl %esi, %eax;\
    xorl %edx, %edx;\
    divw %bx;\
    movl %eax, %ebp;\
;\
    movl 48(%esp), %edi;\
    movl %ecx, %eax;\
    xorl %edx, %edx;\
    divw (%edi);\
;\
    movl _wftan(, %ebx, 4), %ebx;\
    shll $2, %ecx;\
    shll $2, %esi;\
    movl 28(%esp), %edi;\
    movl 32(%esp), %edx;\
;\
    addl $4, 48(%esp);\
    addl $4, 40(%esp);\
;\
    pushl 48(%esp);\
    pushl %eax;\
    pushl 48(%esp)              # 40(esp) but esp changed;\
    pushl %ebp;\
    pushl %edx;\
    pushl %edi;\
;\
    addl %esi, %edi;\
    addl %ecx, %edx;\
    pushl 72(%esp)              # 48(esp) but esp changed;\
    pushl %eax;\
    pushl 72(%esp)              # 40(esp) but esp changed;\
    pushl %ebp;\
    pushl %edx;\
    pushl %edi;\
;\
    addl %esi, %edi;\
    addl %ecx, %edx;\
    pushl 96(%esp)              # 48(esp) but esp changed;\
    pushl %eax;\
    pushl 96(%esp)              # 40(esp) but esp changed;\
    pushl %ebp;\
    pushl %edx;\
    pushl %edi;\
;\
    call *%ebx;\
    addl $24, %esp;\
;\
    call *%ebx;\
    addl $24, %esp;\
;\
    call *%ebx;\
    addl $24, %esp;\
;\
    wftan3end:;\
;\
    movl 28(%esp), %ecx;\
    movl 36(%esp), %esi;\
    movl _modulus, %edi;\
    leal (%ecx, %esi, 4), %edx;\
    leal (%ecx, %esi, 8), %ebp;\
;\
    wftan3loop2:;\
    movl -4(%ecx, %esi, 4), %eax;\
    movl -4(%edx, %esi, 4), %ebx;\
;\
    addl %ebx, %eax; cmpl %edi, %eax; jb 0f; subl %edi, %eax; 0:;\
;\
    movl -4(%ebp, %esi, 4), %ebx;\
;\
    addl %eax, %ebx; addl %eax, %eax;\
    subl %ebx, %eax; jnc 0f; addl %edi, %eax; 0:;\
    cmpl %edi, %ebx; jb 0f; subl %edi, %ebx; 0:;\
;\
    movl %eax, -4(%ebp, %esi, 4);\
    movl %ebx, -4(%edx, %esi, 4);\
;\
    decl %esi;\
    jnz wftan3loop2;\
;\
    popl %ebp;\
    popl %edi;\
    popl %esi;\
    popl %edx;\
    popl %ecx;\
    popl %ebx;\
;\
    ret;\
");

#endif
