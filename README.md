# Sort3

This repository contains the supplementary material to the paper below with
later [contributions](https://github.com/cassioneri/sort3/pull/1) from
[Bernhard Kauer](https://github.com/vmmon).

Neri, C. "Shorter and faster than *Sort3AlphaDev*", to appear.
([Preprint](https://arxiv.org/abs/2307.14503).)


## Introduction

The following DeepMind's work

Mankowitz, D.J., Michi, A., Zhernov, A. et al. "Faster sorting algorithms
discovered using deep reinforcement learning." Nature 618, 257–263 (2023).
doi.org/10.1038/s41586-023-06004-9

presents new implementations of sorting algorithms found through deep
reinforcement learning that work on a small number of numeric inputs. For 3
numbers, the published implementation contains 17 assembly instructions, and
the authors state that no shorter program exists. However, the following
response:

Neri, C. "Shorter and faster than *Sort3AlphaDev*", to appear.
([Preprint](https://arxiv.org/abs/2307.14503).)

presents two counterexamples for this claim and a straightforward C/C++
implementation that is faster than DeepMind's.

## Table of Contents

**[Errata](#errata)**<br>
**[Live tests and benchmarks](#live-tests-and-benchmarks)**<br>
**[Building with CMake](#building-with-cmake)**<br>

  * **[Command line](#command-line)**
  * **[Visual Studio Code](#visual-studio-code)**

**[Executables](#executables)**<br>
**[Dependencies](#dependencies)**<br>

# Errata

1. The preprint fails to mention that *Sort_15* only works for non-negative numbers,
so the following sentence must be added at the end of section "Shorter than
*Sort3AlphaDev*".

> Unfortunately, *Sort_15* imposes the extra condition that the three numbers are
> non-negative.

# Live tests and benchmarks

Readers are encouraged to checkout this repository for building and running
tests and benchmarks on their own platforms but thanks to
[Compiler explorer](https://godbolt.org) and
[quick-bench](https://quick-bench.com), live versions cane be seen at:

1. [godbolt.org/z/3TqG6Tbjv](https://godbolt.org/z/3TqG6Tbjv);
1. [quick-bench.com/q/ndRd9bDMaprBk-rL00CCimNMVJQ](https://quick-bench.com/q/ndRd9bDMaprBk-rL00CCimNMVJQ).

# Building with CMake

**Only Linux builds are supported.**

## Command line

A list of CMakePresets is available. For instance, the preset
`gcc.release.make` builds in `release` mode using `gcc` and `make`. In general,
preset names have the form *compiler*.*mode*.*builder* where

* *compiler* is one of `clang` or `gcc`;
* *mode* is one of `debug`, `release` or `release-symbols`;
* *builder* is one of `make` or `ninja`.

Tip: `cmake --list-presets` shows the complete list available presets.

To build everything, on the top level directory, run:
```
$ cmake --preset <preset-name>
$ cmake --build build/<preset-name>
```

## Visual Studio Code

Simply open the top level folder and select one of the available presets.

# Executables

They are created in the `build/<preset-name>/bin` directory and the
instructions below assumes this is the current working directory.

| Name   | Description                                                   |
|--------|---------------------------------------------------------------|
|`test`  | Exhaustive test for *Sort3_14*, *Sort3_15* and *Sort3_faster* |
|`bench` | Benchmarks various implementations of Sort3                   |

# Dependencies

[Google Benchmark](https://github.com/google/benchmark) is automatically
downloaded and built as part of sort3's build.
