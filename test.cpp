// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 Cassio Neri <cassio.neri@gmail.com>
//
// This code is a supplementary material to:
//
//     Neri, C. "Shorter and faster than Sort3AlphaDev", to appear.
//     Preprint: https://arxiv.org/abs/2307.14503.

#ifdef NDEBUG
#undef NDEBUG
#endif

#include "sort.h"

#include <array>
#include <cstdint>
#include <cstdio>

void test(void (*function)(int*), char const* name) {

  std::printf("Testing %s...\n", name);

  using test_case_t = std::array<int , 3>;

  test_case_t test_cases[][2] = {
    /* actual      expected    */
    { { 1, 2, 3 }, { 1, 2, 3 } },
    { { 1, 3, 2 }, { 1, 2, 3 } },
    { { 2, 1, 3 }, { 1, 2, 3 } },
    { { 2, 3, 1 }, { 1, 2, 3 } },
    { { 3, 1, 2 }, { 1, 2, 3 } },
    { { 3, 2, 1 }, { 1, 2, 3 } },
    { { 1, 1, 2 }, { 1, 1, 2 } },
    { { 1, 2, 1 }, { 1, 1, 2 } },
    { { 2, 1, 1 }, { 1, 1, 2 } },
    { { 2, 2, 1 }, { 1, 2, 2 } },
    { { 2, 1, 2 }, { 1, 2, 2 } },
    { { 1, 2, 2 }, { 1, 2, 2 } },
    { { 1, 1, 1 }, { 1, 1, 1 } },
  };

  for (auto& test_case : test_cases) {
    test_case_t const& expected = test_case[1];
    test_case_t actual = test_case[0];
    function(actual.data());
    if (actual[0] != expected[0] || actual[1] != expected[1] || actual[2] != expected[2]) {
      std::puts("  FAIL");
      return;
    }
  }
  std::puts("  PASS");
}

// Function main() exhaustively tests all flavours of sort3.
int main() {
  test(Sort3AlphaDev, "Sort3AlphaDev");
  test(Sort3_10     , "Sort3_10"     );
  test(Sort3_12     , "Sort3_12"     );
  test(Sort3_14     , "Sort3_14"     );
  test(Sort3_15     , "Sort3_15"     );
  test(Sort3_15_v2  , "Sort3_15_v2"  );
  test(Sort3_faster , "Sort3_faster" );
}
