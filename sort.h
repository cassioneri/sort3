// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 Cassio Neri <cassio.neri@gmail.com>
//
// This code is a supplementary material to:
//
//     Neri, C. "Shorter and faster than Sort3AlphaDev", to appear.
//     Preprint: https://arxiv.org/abs/2307.14503.

#include <cstdint>

#if defined(__clang__)

// Original Sort3AlphaDev from [1].
// [1] https://github.com/deepmind/alphadev/blob/1a6eac1544c1075ef27814f09f9223cb84537c59/sort_functions_test.cc#L23
void Sort3AlphaDev(int* buffer) {
  asm volatile(
      "mov 0x4(%0), %%eax            \n"
      "mov 0x8(%0), %%ecx            \n"
      "cmp %%eax, %%ecx              \n"
      "mov %%eax, %%edx              \n"
      "cmovl %%ecx, %%edx            \n"
      "mov (%0), %%r8d               \n"
      "cmovg %%ecx, %%eax            \n"
      "cmp %%r8d, %%eax              \n"
      "mov %%r8d, %%ecx              \n"
      "cmovl %%eax, %%ecx            \n"
      "cmovle %%r8d, %%eax           \n"
      "mov %%eax, 0x8(%0)            \n"
      "cmp %%ecx, %%edx              \n"
      "cmovle %%edx, %%r8d           \n"
      "mov %%r8d, (%0)               \n"
      "cmovg %%edx, %%ecx            \n"
      "mov %%ecx, 0x4(%0)            \n"
      : "+r"(buffer)
      :
      : "eax", "ecx", "edx", "r8d", "memory");
}

#else

// Adapted from [1] for gcc. ("rd8" is replaced with "esi" for the compilation to succeed.)
void Sort3AlphaDev(int* buffer) {
  asm volatile(
      "mov 0x4(%0), %%eax            \n"
      "mov 0x8(%0), %%ecx            \n"
      "cmp %%eax, %%ecx              \n"
      "mov %%eax, %%edx              \n"
      "cmovl %%ecx, %%edx            \n"
      "mov (%0), %%esi               \n"
      "cmovg %%ecx, %%eax            \n"
      "cmp %%esi, %%eax              \n"
      "mov %%esi, %%ecx              \n"
      "cmovl %%eax, %%ecx            \n"
      "cmovle %%esi, %%eax           \n"
      "mov %%eax, 0x8(%0)            \n"
      "cmp %%ecx, %%edx              \n"
      "cmovle %%edx, %%esi           \n"
      "mov %%esi, (%0)               \n"
      "cmovg %%edx, %%ecx            \n"
      "mov %%ecx, 0x4(%0)            \n"
      : "+r"(buffer)
      :
      : "eax", "ecx", "edx", "esi", "memory");
}
#endif

// Author: Bernhard Kauer.
void Sort3_beat(int* buffer) {
  asm volatile(
      "mov 0x8(%0), %%eax            \n"
      "cmp %%eax, 0x4(%0)            \n"
      "mov %%eax, %%edx              \n"
      "cmovl 0x4(%0), %%edx          \n"
      "cmovg 0x4(%0), %%eax          \n"
      "cmp (%0), %%eax               \n"
      "mov %%eax, %%ecx              \n"
      "cmovl (%0), %%eax             \n"
      "cmovg (%0), %%ecx             \n"
      "cmp %%ecx, %%edx              \n"
      "cmovg %%edx,%%ecx             \n"
      "cmovg (%0), %%edx             \n"
      "mov %%eax, 0x8(%0)            \n"
      "mov %%edx, (%0)               \n"
      "mov %%ecx, 0x4(%0)            \n"
      : "+r"(buffer)
      :
      : "eax", "ecx", "edx", "esi", "memory");
}

void Sort3_14(int* buffer) {
  int a, b, c;
  asm volatile (
    "mov (%[p]), %[a]           \n\t" // int a = buffer[0];
    "mov 4(%[p]), %[b]          \n\t" // int b = buffer[1];
    "loop_start%=:              \n\t" // for(;;) {
    "mov %[a], %[c]             \n\t" //   int c = a;
    "cmp %[b], %[a]             \n\t" //   bool flag = b < a;
    "cmovg %[b], %[a]           \n\t" //   a = flag ? b : a;
    "cmovg %[c], %[b]           \n\t" //   b = flag ? c : b;
    "cmp 8(%[p]), %[b]          \n\t" //   flag = buffer[2] < b;
    "jle loop_end%=             \n\t" //   if (!flag) break;
    "mov %[b], %[c]             \n\t" //   c = b;
    "mov 8(%[p]), %[b]          \n\t" //   b = buffer[2];
    "mov %[c], 8(%[p])          \n\t" //   buffer[2] = c;
    "jmp loop_start%=           \n\t" // }
    "loop_end%=:                \n\t" //
    "mov %[a], (%[p])           \n\t" // buffer[0] = a;
    "mov %[b], 4(%[p])              " // buffer[1] = b;
    : [a]"=r"(a), [b]"=r"(b), [c]"=r"(c), [p]"+r"(buffer)
    : : "memory");
}

char dest[] = {
  1, 2, 9, 2, 0, 9, 0, 1,
  0, 0, 9, 1, 1, 9, 2, 2,
  2, 1, 9, 0, 2, 9, 1, 0
};

// Precondition: buffer[0] >= 0 && buffer[1] >= 0 && buffer[2] >= 0.
void Sort3_15(int* buffer) {
  int a, b, c;
  int64_t i, j;
  asm volatile (
    "mov (%[p]), %[a]           \n\t" // int a = buffer[0];
    "mov 4(%[p]), %[b]          \n\t" // int b = buffer[1];
    "mov 8(%[p]), %[c]          \n\t" // int c = buffer[2];
    "cmp %[a], %[b]             \n\t" // bool flag = b < a;
    "sbb %[i], %[i]             \n\t" // int i = flag ? -1 : 0;
    "cmp %[b], %[c]             \n\t" // flag = c < b;
    "adc %[i], %[i]             \n\t" // i = 2 * i + flag;
    "cmp %[a], %[c]             \n\t" // flag = c < a;
    "adc %[i], %[i]             \n\t" // i = 2 * i + flag;
    "movsb dest+4(%[i]), %[j]   \n\t" // int j = dest[i + 4];
    "mov %[a], (%[p],%[j],4)    \n\t" // buffer[j] = a;
    "movsb dest+12(%[i]), %[j]  \n\t" // j = dest[i + 12];
    "mov %[b], (%[p],%[j],4)    \n\t" // buffer[j] = b;
    "movsb dest+20(%[i]), %[j]  \n\t" // j = dest[i + 20];
    "mov %[c], (%[p],%[j],4)        " // buffer[j] = c;
    : [a]"=r"(a), [b]"=r"(b), [c]"=r"(c), [i]"=r"(i), [j]"=r"(j),
    [p]"+r"(buffer) : "g"(dest) : "memory");
  return;
}

// Precondition: buffer[0] >= 0 && buffer[1] >= 0 && buffer[2] >= 0.
// Faster than the Sort3_15, this implementation also does not use a look-up
// table and thus, compiler switches "-fno-pie -no-pie" are unnecessary.
void Sort3_15_v2(int* buffer) {
  int a, b, c;
  int64_t i, j;
  asm volatile (
    "mov (%[p]), %[a]         \n\t" // int a = buffer[0];
    "mov 4(%[p]), %[b]        \n\t" // int b = buffer[1];
    "mov 8(%[p]), %[c]        \n\t" // int c = buffer[2];
    "cmp %[a], %[b]           \n\t" // int flag = b < a;
    "sbb %[j], %[j]           \n\t" // int j = -flag;       // = - (b < a)
    "blsi %[j], %[i]          \n\t" // int i = -j;          // = (b < a)
    "cmp %[a], %[c]           \n\t" // flag = c < a;
    "adc $0, %[i]             \n\t" // i = i + (0 + flag);  // = (b < a) + (c < a)
    "mov %[a], (%[p],%[i],4)  \n\t" // buffer[i] = a;
    "cmp %[c], %[b]           \n\t" // flag = b < c;
    "sbb $-2, %[j]            \n\t" // j = j - (-2 + flag); // = 2 - (b < a) - (b < c) = (a <= b) + (c <= b)
    "mov %[b], (%[p],%[j],4)  \n\t" // buffer[j] = b;
    "add %[j], %[i]           \n\t" // i = i + j;
    "xor $3, %[i]             \n\t" // i = 3 - i;
    "mov %[c], (%[p],%[i],4)      " // buffer[i] = c;
    : [a]"=r"(a), [b]"=r"(b), [c]"=r"(c), [i]"=r"(i), [j]"=r"(j),
    [p]"+r"(buffer) : : "memory");
  return;
}

void Sort3_faster(int* buffer) {

  int a = buffer[0];
  int b = buffer[1];
  int c = buffer[2];

  bool flag = c < b;
  int d = b;
  b = flag ? c : b;
  c = flag ? d : c;

  flag = c < a;
  d = a;
  a = flag ? c : a;
  c = flag ? d : c;
  buffer[2] = c;

  flag = b < a;
  d = a;
  a = flag ? b : a;
  b = flag ? d : b;
  buffer[0] = a;
  buffer[1] = b;

  return;
}

// Author: Bernhard Kauer.
// Bubble sort.
void Sort3_10(int* buffer) {
  asm volatile (
    "mov $2, %%esi;"
    "0: "
    "mov %%esi, %%ecx;"
    "mov (%[p], %%rsi, 4), %%eax;"
    "1: "
    "cmp %%eax, -4(%[p], %%rcx, 4);"
    "jl 2f;"
    "xchg %%eax, -4(%[p], %%rcx, 4);"
    "2:"
    "loop 1b;"
    "mov %%eax, (%[p], %%rsi, 4);"
    "dec %%esi;"
    "jnz 0b"
    : [p]"+r"(buffer) : : "memory", "esi", "eax", "ecx");
}

// Author: Bernhard Kauer.
// Precondition: buffer[0] >= 0 && buffer[1] >= 0 && buffer[2] >= 0.
void Sort3_12(int* buffer) {
  asm volatile (
    "mov (%%rdi), %%eax;"
    "cmp %%eax, 4(%%rdi);"
    "sbb  %%rcx, %%rcx;"
    "xchg %%eax, 4(%%rdi, %%rcx, 4);"

    "cmp 8(%%rdi), %%eax;"
    "sbb  %%rcx, %%rcx;"
    "xchg %%eax, 8(%%rdi, %%rcx, 4);"
    "mov %%eax, (%%rdi);"

    "cmp 4(%%rdi), %%eax;"
    "sbb  %%rcx, %%rcx;"
    "xchg %%eax, 4(%%rdi, %%rcx, 4);"
    "mov %%eax, (%%rdi);"
    : : "rdi"(buffer) : "memory", "esi", "eax", "ecx");
}
