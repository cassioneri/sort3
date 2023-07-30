// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 Cassio Neri <cassio.neri@gmail.com>
//
// This code is a supplementary material to:
//
//     Neri, C. "Shorter and faster than Sort3AlphaDev", to appear.
//     Preprint: https://arxiv.org/abs/2307.14503.

#include "sort.h"

#include <benchmark/benchmark.h>

#include <array>
#include <cstdint>
#include <iterator>
#include <random>

std::array<int , 3> const test_cases[] = {
  { 1, 2, 3 },
  { 1, 3, 2 },
  { 2, 1, 3 },
  { 2, 3, 1 },
  { 3, 1, 2 },
  { 3, 2, 1 },
  { 1, 1, 2 },
  { 1, 2, 1 },
  { 2, 1, 1 },
  { 2, 2, 1 },
  { 2, 1, 2 },
  { 1, 2, 2 },
  { 1, 1, 1 },
};

auto ns = [](){
  std::uniform_int_distribution<unsigned> uniform_dist(0, std::size(test_cases) - 1);
  std::mt19937 rng;
  std::array<int32_t, 32768> ns;
  for (auto& n : ns)
    n = uniform_dist(rng);
  return ns;
}();

static void Scanning(benchmark::State& state) {
  for (auto _ : state)
    for (auto n : ns) {
      auto p = test_cases[n];
      benchmark::DoNotOptimize(p.data());
    }
}
BENCHMARK(Scanning);

static void Sort3AlphaDev(benchmark::State& state) {
  for (auto _ : state)
    for (auto n : ns) {
      auto p = test_cases[n];
      Sort3AlphaDev(p.data());
      benchmark::DoNotOptimize(p.data());
    }
}
BENCHMARK(Sort3AlphaDev);

static void Sort3_14(benchmark::State& state) {
  for (auto _ : state)
    for (auto n : ns) {
      auto p = test_cases[n];
      Sort3_14(p.data());
      benchmark::DoNotOptimize(p.data());
    }
}
BENCHMARK(Sort3_14);

static void Sort3_15(benchmark::State& state) {
  for (auto _ : state)
    for (auto n : ns) {
      auto p = test_cases[n];
      Sort3_15(p.data());
      benchmark::DoNotOptimize(p.data());
    }
}
BENCHMARK(Sort3_15);

static void Sort3_15_v2(benchmark::State& state) {
  for (auto _ : state)
    for (auto n : ns) {
      auto p = test_cases[n];
      Sort3_15_v2(p.data());
      benchmark::DoNotOptimize(p.data());
    }
}
BENCHMARK(Sort3_15_v2);

static void Sort3_faster(benchmark::State& state) {
  for (auto _ : state)
    for (auto n : ns) {
      auto p = test_cases[n];
      Sort3_faster(p.data());
      benchmark::DoNotOptimize(p.data());
    }
}
BENCHMARK(Sort3_faster);
