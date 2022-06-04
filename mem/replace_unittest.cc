// Copyright 2022 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "mem/replace.h"

#include <type_traits>

#include "assertions/builtin.h"
#include "mem/__private/relocate.h"
#include "third_party/googletest/googletest/include/gtest/gtest.h"

namespace sus::mem {
namespace {

TEST(Replace, ConstexprTrivialRelocate) {
  using T = int;
  static_assert(__private::relocate_one_by_memcpy_v<T>, "");

  auto i = []() constexpr {
    T i(2);
    T j(::sus::mem::replace(i, T(5)));
    return i;
  };
  auto j = []() constexpr {
    T i(2);
    T j(::sus::mem::replace(i, T(5)));
    return j;
  };
  static_assert(i() == T(5), "");
  static_assert(j() == T(2), "");
}

TEST(Replace, ConstexprTrivialAbi) {
  struct [[clang::trivial_abi]] S {
    constexpr S(int n) : num(n) {}
    constexpr S(S&& other) : num(other.num), assigns(other.assigns) {}
    constexpr void operator=(S&& other) {
      num = other.num;
      assigns = other.assigns + 1;
    }
    int num;
    int assigns = 0;
  };
  // This means `S` is only "trivially relocatable" if achieved through
  // [[clang::trivial_abi]].
  static_assert(!std::is_trivially_move_constructible_v<S>, "");
  static_assert(__private::relocate_one_by_memcpy_v<S> ==
                    __has_extension(trivially_relocatable),
                "");

  auto i = []() constexpr {
    S i(2);
    S j(::sus::mem::replace(i, S(5)));
    return i;
  };
  auto j = []() constexpr {
    S i(2);
    S j(::sus::mem::replace(i, S(5)));
    return j;
  };
  static_assert(i().num == 5, "");
  static_assert(j().num == 2, "");
  // The replace was done by move operations, since memcpy is not constexpr.
  static_assert(i().assigns == 1, "");
}

TEST(Replace, ConstexprNonTrivial) {
  struct S {
    constexpr S(int n) : num(n) {}
    constexpr S(S&& other) : num(other.num), assigns(other.assigns) {}
    constexpr void operator=(S&& other) {
      num = other.num;
      assigns = other.assigns + 1;
    }
    int num;
    int assigns = 0;
  };
  static_assert(!__private::relocate_one_by_memcpy_v<S>, "");

  auto i = []() constexpr {
    S i(2);
    S j(::sus::mem::replace(i, S(5)));
    return i;
  };
  auto j = []() constexpr {
    S i(2);
    S j(::sus::mem::replace(i, S(5)));
    return j;
  };
  static_assert(i().num == 5, "");
  static_assert(j().num == 2, "");
  // The replace was done by move operations, since memcpy is not constexpr.
  static_assert(i().assigns == 1, "");
}

TEST(Replace, TrivialRelocate) {
  using T = int;
  static_assert(__private::relocate_one_by_memcpy_v<T>, "");

  T i(2);
  T j(::sus::mem::replace(i, T(5)));
  EXPECT_EQ(i, T(5));
  EXPECT_EQ(j, T(2));
}

TEST(Replace, TrivialAbi) {
  struct [[clang::trivial_abi]] S {
    constexpr S(int n) : num(n) {}
    constexpr S(S&& other) : num(other.num), assigns(other.assigns) {}
    constexpr void operator=(S&& other) {
      num = other.num;
      assigns = other.assigns + 1;
    }
    int num;
    int assigns = 0;
  };
  // This means `S` is only "trivially relocatable" if achieved through
  // [[clang::trivial_abi]].
  static_assert(!std::is_trivially_move_constructible_v<S>, "");
  static_assert(__private::relocate_one_by_memcpy_v<S> ==
                    __has_extension(trivially_relocatable),
                "");

  S i(2);
  S j(::sus::mem::replace(i, S(5)));
  EXPECT_EQ(i.num, 5);
  EXPECT_EQ(j.num, 2);
#if __has_extension(trivially_relocatable)
  // The replace was done by memcpy.
  EXPECT_EQ(0, i.assigns);
#else
  // The replace was done by move operations.
  EXPECT_EQ(1, i.assigns);
#endif
}

TEST(Replace, NonTrivial) {
  struct S {
    constexpr S(int n) : num(n) {}
    constexpr S(S&& other) : num(other.num), assigns(other.assigns) {}
    constexpr void operator=(S&& other) {
      num = other.num;
      assigns = other.assigns + 1;
    }
    int num;
    int assigns = 0;
  };
  static_assert(!__private::relocate_one_by_memcpy_v<S>, "");

  S i(2);
  S j(::sus::mem::replace(i, S(5)));
  EXPECT_EQ(i.num, 5);
  EXPECT_EQ(j.num, 2);
  // The replace was done by move operations.
  EXPECT_EQ(1, i.assigns);
}

}  // namespace
}  // namespace sus::mem