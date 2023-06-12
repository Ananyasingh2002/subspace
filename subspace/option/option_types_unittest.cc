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

#include "subspace/construct/default.h"
#include "subspace/mem/relocate.h"
#include "subspace/option/option.h"
#include "subspace/test/behaviour_types.h"
#include "subspace/test/no_copy_move.h"

using sus::construct::Default;
using sus::mem::relocate_by_memcpy;
using sus::option::Option;

namespace sus::test::default_constructible {
using T = Option<sus::test::DefaultConstructible>;
using From = T;
static_assert(!std::is_trivial_v<T>);
static_assert(!std::is_aggregate_v<T>);
static_assert(std::is_standard_layout_v<T>);
static_assert(!std::is_trivially_default_constructible_v<T>);
static_assert(std::is_trivially_copy_constructible_v<T>);
static_assert(std::is_trivially_copy_assignable_v<T>);
static_assert(std::is_trivially_move_constructible_v<T>);
static_assert(std::is_trivially_move_assignable_v<T>);
static_assert(std::is_trivially_destructible_v<T>);
static_assert(std::is_copy_constructible_v<T>);
static_assert(std::is_copy_assignable_v<T>);
static_assert(std::is_move_constructible_v<T>);
static_assert(std::is_move_assignable_v<T>);
static_assert(std::is_nothrow_swappable_v<T>);
static_assert(std::is_constructible_v<T, From&&>);
static_assert(std::is_assignable_v<T, From&&>);
static_assert(std::is_constructible_v<T, const From&>);
static_assert(std::is_assignable_v<T, const From&>);
static_assert(std::is_constructible_v<T, From>);
static_assert(std::is_trivially_constructible_v<T, From>);
static_assert(std::is_assignable_v<T, From>);
static_assert(std::is_nothrow_destructible_v<T>);
static_assert(Default<T>);
static_assert(relocate_by_memcpy<T>);
}  // namespace sus::test::default_constructible

namespace sus::test::not_default_constructible {
using T = Option<sus::test::NotDefaultConstructible>;
using From = T;
static_assert(!std::is_trivial_v<T>);
static_assert(!std::is_aggregate_v<T>);
static_assert(std::is_standard_layout_v<T>);
static_assert(!std::is_trivially_default_constructible_v<T>);
static_assert(std::is_trivially_copy_constructible_v<T>);
static_assert(std::is_trivially_copy_assignable_v<T>);
static_assert(std::is_trivially_move_constructible_v<T>);
static_assert(std::is_trivially_move_assignable_v<T>);
static_assert(std::is_trivially_destructible_v<T>);
static_assert(std::is_copy_constructible_v<T>);
static_assert(std::is_copy_assignable_v<T>);
static_assert(std::is_move_constructible_v<T>);
static_assert(std::is_move_assignable_v<T>);
static_assert(std::is_nothrow_swappable_v<T>);
static_assert(std::is_constructible_v<T, From&&>);
static_assert(std::is_assignable_v<T, From&&>);
static_assert(std::is_constructible_v<T, const From&>);
static_assert(std::is_assignable_v<T, const From&>);
static_assert(std::is_constructible_v<T, From>);
static_assert(std::is_trivially_constructible_v<T, From>);
static_assert(std::is_assignable_v<T, From>);
static_assert(std::is_nothrow_destructible_v<T>);
static_assert(Default<T>);
static_assert(relocate_by_memcpy<T>);
}  // namespace sus::test::not_default_constructible

namespace sus::test::trivially_copyable {
using T = Option<sus::test::TriviallyCopyable>;
using From = T;
static_assert(!std::is_trivial_v<T>);
static_assert(!std::is_aggregate_v<T>);
static_assert(std::is_standard_layout_v<T>);
static_assert(!std::is_trivially_default_constructible_v<T>);
static_assert(std::is_trivially_copy_constructible_v<T>);
static_assert(std::is_trivially_copy_assignable_v<T>);
static_assert(std::is_trivially_move_constructible_v<T>);
static_assert(std::is_trivially_move_assignable_v<T>);
static_assert(std::is_trivially_destructible_v<T>);
static_assert(std::is_copy_constructible_v<T>);
static_assert(std::is_copy_assignable_v<T>);
static_assert(std::is_move_constructible_v<T>);
static_assert(std::is_move_assignable_v<T>);
static_assert(std::is_nothrow_swappable_v<T>);
static_assert(std::is_constructible_v<T, From&&>);
static_assert(std::is_assignable_v<T, From&&>);
static_assert(std::is_constructible_v<T, const From&>);
static_assert(std::is_assignable_v<T, const From&>);
static_assert(std::is_constructible_v<T, From>);
static_assert(std::is_trivially_constructible_v<T, From>);
static_assert(std::is_assignable_v<T, From>);
static_assert(std::is_nothrow_destructible_v<T>);
static_assert(Default<T>);
static_assert(relocate_by_memcpy<T>);
}  // namespace sus::test::trivially_copyable

namespace sus::test::trivially_moveable_and_relocatable {
using T = Option<sus::test::TriviallyMoveableAndRelocatable>;
using From = T;
static_assert(!std::is_trivial_v<T>);
static_assert(!std::is_aggregate_v<T>);
static_assert(std::is_standard_layout_v<T>);
static_assert(!std::is_trivially_default_constructible_v<T>);
static_assert(!std::is_trivially_copy_constructible_v<T>);
static_assert(!std::is_trivially_copy_assignable_v<T>);
static_assert(std::is_trivially_move_constructible_v<T>);
static_assert(std::is_trivially_move_assignable_v<T>);
static_assert(std::is_trivially_destructible_v<T>);
static_assert(!std::is_copy_constructible_v<T>);
static_assert(!std::is_copy_assignable_v<T>);
static_assert(std::is_move_constructible_v<T>);
static_assert(std::is_move_assignable_v<T>);
static_assert(std::is_nothrow_swappable_v<T>);
static_assert(std::is_constructible_v<T, From&&>);
static_assert(std::is_assignable_v<T, From&&>);
static_assert(!std::is_constructible_v<T, const From&>);
static_assert(!std::is_assignable_v<T, const From&>);
static_assert(std::is_constructible_v<T, From>);
static_assert(std::is_trivially_constructible_v<T, From>);
static_assert(std::is_assignable_v<T, From>);
static_assert(std::is_nothrow_destructible_v<T>);
static_assert(Default<T>);
static_assert(relocate_by_memcpy<T>);
}  // namespace sus::test::trivially_moveable_and_relocatable

namespace sus::test::trivially_copyable_not_destructible {
using T = Option<sus::test::TriviallyCopyableNotDestructible>;
using From = T;
static_assert(!std::is_trivial_v<T>);
static_assert(!std::is_aggregate_v<T>);
static_assert(std::is_standard_layout_v<T>);
static_assert(!std::is_trivially_default_constructible_v<T>);
static_assert(!std::is_trivially_copy_constructible_v<T>);
static_assert(std::is_trivially_copy_assignable_v<T>);
static_assert(!std::is_trivially_move_constructible_v<T>);
static_assert(std::is_trivially_move_assignable_v<T>);
static_assert(!std::is_trivially_destructible_v<T>);
static_assert(std::is_copy_constructible_v<T>);
static_assert(std::is_copy_assignable_v<T>);
static_assert(std::is_move_constructible_v<T>);
static_assert(std::is_move_assignable_v<T>);
static_assert(std::is_nothrow_swappable_v<T>);
static_assert(std::is_constructible_v<T, From&&>);
static_assert(std::is_assignable_v<T, From&&>);
static_assert(std::is_constructible_v<T, const From&>);
static_assert(std::is_assignable_v<T, const From&>);
static_assert(std::is_constructible_v<T, From>);
static_assert(!std::is_trivially_constructible_v<T, From>);
static_assert(std::is_assignable_v<T, From>);
static_assert(std::is_nothrow_destructible_v<T>);
static_assert(Default<T>);
static_assert(!relocate_by_memcpy<T>);
}  // namespace sus::test::trivially_copyable_not_destructible

namespace sus::test::trivially_moveable_not_destructible {
using T = Option<sus::test::TriviallyMoveableNotDestructible>;
using From = T;
static_assert(!std::is_trivial_v<T>);
static_assert(!std::is_aggregate_v<T>);
static_assert(std::is_standard_layout_v<T>);
static_assert(!std::is_trivially_default_constructible_v<T>);
static_assert(!std::is_trivially_copy_constructible_v<T>);
static_assert(!std::is_trivially_copy_assignable_v<T>);
static_assert(!std::is_trivially_move_constructible_v<T>);
static_assert(std::is_trivially_move_assignable_v<T>);
static_assert(!std::is_trivially_destructible_v<T>);
static_assert(!std::is_copy_constructible_v<T>);
static_assert(!std::is_copy_assignable_v<T>);
static_assert(std::is_move_constructible_v<T>);
static_assert(std::is_move_assignable_v<T>);
static_assert(std::is_nothrow_swappable_v<T>);
static_assert(std::is_constructible_v<T, From&&>);
static_assert(std::is_assignable_v<T, From&&>);
static_assert(!std::is_constructible_v<T, const From&>);
static_assert(!std::is_assignable_v<T, const From&>);
static_assert(std::is_constructible_v<T, From>);
static_assert(!std::is_trivially_constructible_v<T, From>);
static_assert(std::is_assignable_v<T, From>);
static_assert(std::is_nothrow_destructible_v<T>);
static_assert(Default<T>);
static_assert(!relocate_by_memcpy<T>);
}  // namespace sus::test::trivially_moveable_not_destructible

namespace sus::test::not_trivially_relocatable_copyable_or_moveable {
using T = Option<sus::test::NotTriviallyRelocatableCopyableOrMoveable>;
using From = T;
static_assert(!std::is_trivial_v<T>);
static_assert(!std::is_aggregate_v<T>);
static_assert(std::is_standard_layout_v<T>);
static_assert(!std::is_trivially_default_constructible_v<T>);
static_assert(!std::is_trivially_copy_constructible_v<T>);
static_assert(!std::is_trivially_copy_assignable_v<T>);
static_assert(!std::is_trivially_move_constructible_v<T>);
static_assert(!std::is_trivially_move_assignable_v<T>);
static_assert(!std::is_trivially_destructible_v<T>);
static_assert(std::is_copy_constructible_v<T>);
static_assert(std::is_copy_assignable_v<T>);
static_assert(std::is_move_constructible_v<T>);
static_assert(std::is_move_assignable_v<T>);
static_assert(std::is_nothrow_swappable_v<T>);
static_assert(std::is_constructible_v<T, From&&>);
static_assert(std::is_assignable_v<T, From&&>);
static_assert(std::is_constructible_v<T, const From&>);
static_assert(std::is_assignable_v<T, const From&>);
static_assert(std::is_constructible_v<T, From>);
static_assert(!std::is_trivially_constructible_v<T, From>);
static_assert(std::is_assignable_v<T, From>);
static_assert(std::is_nothrow_destructible_v<T>);
static_assert(Default<T>);
static_assert(!relocate_by_memcpy<T>);
}  // namespace sus::test::not_trivially_relocatable_copyable_or_moveable

namespace sus::test::trivial_abi_relocatable {
using T = Option<sus::test::TrivialAbiRelocatable>;
using From = T;
static_assert(!std::is_trivial_v<T>);
static_assert(!std::is_aggregate_v<T>);
static_assert(std::is_standard_layout_v<T>);
static_assert(!std::is_trivially_default_constructible_v<T>);
static_assert(!std::is_trivially_copy_constructible_v<T>);
static_assert(!std::is_trivially_copy_assignable_v<T>);
static_assert(!std::is_trivially_move_constructible_v<T>);
static_assert(std::is_trivially_move_assignable_v<T>);
static_assert(!std::is_trivially_destructible_v<T>);
static_assert(!std::is_copy_constructible_v<T>);
static_assert(!std::is_copy_assignable_v<T>);
static_assert(std::is_move_constructible_v<T>);
static_assert(std::is_move_assignable_v<T>);
static_assert(std::is_nothrow_swappable_v<T>);
static_assert(std::is_constructible_v<T, From&&>);
static_assert(std::is_assignable_v<T, From&&>);
static_assert(!std::is_constructible_v<T, const From&>);
static_assert(!std::is_assignable_v<T, const From&>);
static_assert(std::is_constructible_v<T, From>);
static_assert(!std::is_trivially_constructible_v<T, From>);
static_assert(std::is_assignable_v<T, From>);
static_assert(std::is_nothrow_destructible_v<T>);
static_assert(Default<T>);
static_assert(relocate_by_memcpy<T>);
}  // namespace sus::test::trivial_abi_relocatable

namespace sus::test::reference {
using T = Option<NoCopyMove&>;
using From = T;
static_assert(!std::is_trivial_v<T>);
static_assert(!std::is_aggregate_v<T>);
static_assert(std::is_standard_layout_v<T>);
static_assert(!std::is_trivially_default_constructible_v<T>);
static_assert(std::is_trivially_copy_constructible_v<T>);
static_assert(std::is_trivially_copy_assignable_v<T>);
static_assert(std::is_trivially_move_constructible_v<T>);
static_assert(std::is_trivially_move_assignable_v<T>);
static_assert(std::is_trivially_destructible_v<T>);
static_assert(std::is_copy_constructible_v<T>);
static_assert(std::is_copy_assignable_v<T>);
static_assert(std::is_move_constructible_v<T>);
static_assert(std::is_move_assignable_v<T>);
static_assert(std::is_nothrow_swappable_v<T>);
static_assert(std::is_constructible_v<T, From&&>);
static_assert(std::is_assignable_v<T, From&&>);
static_assert(std::is_constructible_v<T, const From&>);
static_assert(std::is_assignable_v<T, const From&>);
static_assert(std::is_constructible_v<T, From>);
static_assert(std::is_trivially_constructible_v<T, From>);
static_assert(std::is_assignable_v<T, From>);
static_assert(std::is_nothrow_destructible_v<T>);
static_assert(Default<T>);
static_assert(relocate_by_memcpy<T>);
}  // namespace sus::test::default_constructible

namespace sus::test::const_reference {
using T = Option<const NoCopyMove&>;
using From = T;
static_assert(!std::is_trivial_v<T>);
static_assert(!std::is_aggregate_v<T>);
static_assert(std::is_standard_layout_v<T>);
static_assert(!std::is_trivially_default_constructible_v<T>);
static_assert(std::is_trivially_copy_constructible_v<T>);
static_assert(std::is_trivially_copy_assignable_v<T>);
static_assert(std::is_trivially_move_constructible_v<T>);
static_assert(std::is_trivially_move_assignable_v<T>);
static_assert(std::is_trivially_destructible_v<T>);
static_assert(std::is_copy_constructible_v<T>);
static_assert(std::is_copy_assignable_v<T>);
static_assert(std::is_move_constructible_v<T>);
static_assert(std::is_move_assignable_v<T>);
static_assert(std::is_nothrow_swappable_v<T>);
static_assert(std::is_constructible_v<T, From&&>);
static_assert(std::is_assignable_v<T, From&&>);
static_assert(std::is_constructible_v<T, const From&>);
static_assert(std::is_assignable_v<T, const From&>);
static_assert(std::is_constructible_v<T, From>);
static_assert(std::is_trivially_constructible_v<T, From>);
static_assert(std::is_assignable_v<T, From>);
static_assert(std::is_nothrow_destructible_v<T>);
static_assert(Default<T>);
static_assert(relocate_by_memcpy<T>);
}  // namespace sus::test::default_constructible
