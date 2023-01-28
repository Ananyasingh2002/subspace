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

#include "subdoc/tests/subdoc_test.h"

TEST_F(SubDocTest, MarkdownParagraph) {
  auto result = run_code(R"(
    /// Comment headline
    ///
    /// Next Paragraph
    /// Next Line
    void f() {}
    )");
  ASSERT_TRUE(result.is_ok());
  subdoc::Database db = sus::move(result).unwrap();
  EXPECT_TRUE(has_function_comment(
      db, "2:5", "<p>Comment headline</p><p>Next Paragraph Next Line</p>"));
}

TEST_F(SubDocTest, MarkdownCodeBlock) {
  auto result = run_code(R"(
    /// Comment headline
    ///
    /// Before code
    /// ```
    /// Code 1
    /// Code 2
    /// ```
    /// After code
    void f() {}
    )");
  ASSERT_TRUE(result.is_ok());
  subdoc::Database db = sus::move(result).unwrap();
  EXPECT_TRUE(
      has_function_comment(db, "2:5",
                           "<p>Comment headline</p>"
                           "<p>Before code</p>"
                           "<pre><code>Code 1\nCode 2\n</code></pre>"
                           "<p>After code</p>"));
}