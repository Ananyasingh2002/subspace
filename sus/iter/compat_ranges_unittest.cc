// Copyright 2023 Google LLC
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

#include "sus/iter/compat_ranges.h"

#include <concepts>
#include <iterator>
#include <ranges>
#include <vector>

#include "googletest/include/gtest/gtest.h"
#include "sus/containers/vec.h"
#include "sus/iter/empty.h"
#include "sus/iter/iterator.h"
#include "sus/prelude.h"

namespace {

using CompatRange = sus::iter::IteratorRange<sus::iter::Empty<i32>>;

static_assert(std::ranges::range<CompatRange>);
static_assert(std::ranges::viewable_range<CompatRange>);
static_assert(std::ranges::input_range<CompatRange>);

TEST(CompatRanges, ViewableRange) {
  sus::Vec<i32> vec = sus::vec(1, 2, 3, 4, 5, 6);
  // all() requires a `std::ranges::viewable_range`.
  auto view = std::ranges::views::all(sus::move(vec).into_iter().range());
  i32 e = 1;
  for (i32 i : view) {
    EXPECT_EQ(e, i);
    e += 1;
  }
  EXPECT_EQ(e, 7);
}

TEST(CompatRanges, InputRange) {
  sus::Vec<i32> vec = sus::vec(1, 2, 3, 4, 5, 6);
  // filter() requires a `std::ranges::input_range`.
  auto filter = std::ranges::views::filter(sus::move(vec).into_iter().range(),
                                           [](const i32& i) { return i > 3; });
  i32 e = 4;
  for (i32 i : filter) {
    EXPECT_EQ(e, i);
    e += 1;
  }
  EXPECT_EQ(e, 7);
}

TEST(CompatRanges, FromRange) {
  {
    auto v = std::vector<i32>({1, 2, 3});
    auto it = sus::iter::from_range(v);
    static_assert(sus::iter::Iterator<decltype(it), i32&>);
    static_assert(sus::iter::DoubleEndedIterator<decltype(it), i32&>);
    static_assert(sus::iter::ExactSizeIterator<decltype(it), i32&>);
    static_assert(sus::mem::Move<decltype(it)>);
    static_assert(!sus::mem::Copy<decltype(it)>);
    static_assert(sus::mem::Clone<decltype(it)>);
    static_assert(sus::mem::relocate_by_memcpy<decltype(it)>);
  }

  // Mutable use of vector.
  {
    auto v = std::vector<i32>({1, 2, 3});
    sus::iter::Iterator<i32&> auto it = sus::iter::from_range(v);
    static_assert(sus::iter::DoubleEndedIterator<decltype(it), i32&>);
    static_assert(sus::iter::ExactSizeIterator<decltype(it), i32&>);

    EXPECT_EQ(it.size_hint(), sus::iter::SizeHint(3u, sus::some(3u)));
    EXPECT_EQ(it.exact_size_hint(), 3u);

    EXPECT_EQ(&it.next().unwrap(), &v[0]);
    EXPECT_EQ(it.size_hint(), sus::iter::SizeHint(2u, sus::some(2u)));
    EXPECT_EQ(it.exact_size_hint(), 2u);

    EXPECT_EQ(&it.next().unwrap(), &v[1]);
    EXPECT_EQ(it.size_hint(), sus::iter::SizeHint(1u, sus::some(1u)));
    EXPECT_EQ(it.exact_size_hint(), 1u);

    EXPECT_EQ(&it.next().unwrap(), &v[2]);
    EXPECT_EQ(it.size_hint(), sus::iter::SizeHint(0u, sus::some(0u)));
    EXPECT_EQ(it.exact_size_hint(), 0u);

    EXPECT_EQ(it.next(), sus::none());
    EXPECT_EQ(it.size_hint(), sus::iter::SizeHint(0u, sus::some(0u)));
    EXPECT_EQ(it.exact_size_hint(), 0u);
  }
  // Const use of vector.
  {
    const auto v = std::vector<i32>({1, 2, 3});
    sus::iter::Iterator<const i32&> auto it = sus::iter::from_range(v);
    static_assert(sus::iter::DoubleEndedIterator<decltype(it), const i32&>);
    static_assert(sus::iter::ExactSizeIterator<decltype(it), const i32&>);

    EXPECT_EQ(it.size_hint(), sus::iter::SizeHint(3u, sus::some(3u)));
    EXPECT_EQ(it.exact_size_hint(), 3u);

    EXPECT_EQ(&it.next().unwrap(), &v[0]);
    EXPECT_EQ(it.size_hint(), sus::iter::SizeHint(2u, sus::some(2u)));
    EXPECT_EQ(it.exact_size_hint(), 2u);

    EXPECT_EQ(&it.next().unwrap(), &v[1]);
    EXPECT_EQ(it.size_hint(), sus::iter::SizeHint(1u, sus::some(1u)));
    EXPECT_EQ(it.exact_size_hint(), 1u);

    EXPECT_EQ(&it.next().unwrap(), &v[2]);
    EXPECT_EQ(it.size_hint(), sus::iter::SizeHint(0u, sus::some(0u)));
    EXPECT_EQ(it.exact_size_hint(), 0u);

    EXPECT_EQ(it.next(), sus::none());
    EXPECT_EQ(it.size_hint(), sus::iter::SizeHint(0u, sus::some(0u)));
    EXPECT_EQ(it.exact_size_hint(), 0u);
  }
  // next_back().
  {
    const auto v = std::vector<i32>({1, 2, 3});
    sus::iter::Iterator<const i32&> auto it = sus::iter::from_range(v);

    EXPECT_EQ(it.size_hint(), sus::iter::SizeHint(3u, sus::some(3u)));
    EXPECT_EQ(it.exact_size_hint(), 3u);

    EXPECT_EQ(&it.next_back().unwrap(), &v[2]);
    EXPECT_EQ(it.size_hint(), sus::iter::SizeHint(2u, sus::some(2u)));
    EXPECT_EQ(it.exact_size_hint(), 2u);

    EXPECT_EQ(&it.next().unwrap(), &v[0]);
    EXPECT_EQ(it.size_hint(), sus::iter::SizeHint(1u, sus::some(1u)));
    EXPECT_EQ(it.exact_size_hint(), 1u);

    EXPECT_EQ(&it.next_back().unwrap(), &v[1]);
    EXPECT_EQ(it.size_hint(), sus::iter::SizeHint(0u, sus::some(0u)));
    EXPECT_EQ(it.exact_size_hint(), 0u);

    EXPECT_EQ(it.next_back(), sus::none());
    EXPECT_EQ(it.size_hint(), sus::iter::SizeHint(0u, sus::some(0u)));
    EXPECT_EQ(it.exact_size_hint(), 0u);
  }
  // rvalues are moved from the range.
  {
    auto v = std::vector<i32>({1, 2, 3});
    sus::iter::Iterator<i32> auto it = sus::iter::from_range(sus::move(v));
    EXPECT_EQ(sus::move(it).sum(), 1 + 2 + 3);

    EXPECT_EQ(sus::iter::from_range(std::vector<i32>({1, 2, 3})).sum(),
              1 + 2 + 3);
  }
}

TEST(CompatRanges, FromRange_Example) {
  {
    // An input_iterator by reference.
    const auto v = std::vector<i32>({1, 2, 3});
    sus::check(sus::iter::from_range(v).copied().sum() == 1 + 2 + 3);
  }
  {
    // An input_iterator by value.
    auto v = std::vector<i32>({1, 2, 3});
    sus::check(sus::iter::from_range(sus::move(v)).sum() == 1 + 2 + 3);
  }
}

}  // namespace