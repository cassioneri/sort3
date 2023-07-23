// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 Cassio Neri <cassio.neri@gmail.com>
//
// This code is a supplementary material to:
//
//     Neri C, "Shorter and faster than Sort3AlphaDev", to appear.

#ifdef NDEBUG
#undef NDEBUG
#endif

#include "sort.h"

#include <array>
#include <cassert>
#include <cstdint>
#include <cstdio>

// Function main() exhaustively tests all flavours of sort3.
int main() {

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
    {
      test_case_t actual = test_case[0];
      Sort3AlphaDev(actual.data());
      assert(actual[0] == expected[0] && actual[1] == expected[1] && actual[2] == expected[2] &&
        "Sort3AlphaDev failed.");
    }{
      test_case_t actual = test_case[0];
      Sort3_14(actual.data());
      assert(actual[0] == expected[0] && actual[1] == expected[1] && actual[2] == expected[2] &&
        "Sort3_14 failed.");
    }{
      test_case_t actual = test_case[0];
      Sort3_15(actual.data());
      assert(actual[0] == expected[0] && actual[1] == expected[1] && actual[2] == expected[2] &&
        "Sort3_15 failed.");
    }{
      test_case_t actual = test_case[0];
      Sort3_faster(actual.data());
      assert(actual[0] == expected[0] && actual[1] == expected[1] && actual[2] == expected[2] &&
        "Sort3_faster failed.");
    }
  }

  std::puts("Tests pass.");
}
