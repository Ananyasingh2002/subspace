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

#include "subdoc/lib/gen/generate_record.h"

#include <sstream>

#include "subdoc/lib/database.h"
#include "subdoc/lib/gen/files.h"
#include "subdoc/lib/gen/generate_head.h"
#include "subdoc/lib/gen/html_writer.h"
#include "subdoc/lib/gen/options.h"
#include "subspace/prelude.h"

namespace subdoc::gen {

namespace {

void generate_record_overview(HtmlWriter::OpenDiv& record_div,
                              const RecordElement& element) {
  auto section_div = record_div.open_div();
  section_div.add_class("section");
  section_div.add_class("overview");

  {
    auto record_header_div = section_div.open_div();
    record_header_div.add_class("section-header");
    {
      auto record_type_span = record_header_div.open_span();
      record_type_span.write_text(
          friendly_record_type_name(element.record_type, true));
    }
    {
      auto name_anchor = record_header_div.open_a();
      name_anchor.add_href("#");
      name_anchor.add_class("type-name");
      name_anchor.write_text(element.name);
    }
  }
  {
    auto type_sig_div = section_div.open_div();
    type_sig_div.add_class("type-signature");
    {
      auto record_type_span = type_sig_div.open_span();
      std::string record_type_name =
          friendly_record_type_name(element.record_type, false);
      record_type_span.add_class(record_type_name);
      record_type_span.write_text(record_type_name);
    }
    {
      auto name_span = type_sig_div.open_span();
      name_span.add_class("type-name");
      name_span.write_text(element.name);
    }
    {
      auto record_body_div = type_sig_div.open_div();
      record_body_div.add_class("record-body");
      record_body_div.write_text("{ ... };");
    }
  }
  {
    auto desc_div = section_div.open_div();
    desc_div.add_class("description");
    desc_div.write_text(element.comment.raw_text);
  }
}

void generate_record_fields(
    HtmlWriter::OpenDiv& record_div, const RecordElement& element,
    bool static_fields,
    sus::Slice<const sus::Tuple<std::string_view, UniqueSymbol>> fields) {
  if (fields.is_empty()) return;

  auto section_div = record_div.open_div();
  section_div.add_class("section");
  section_div.add_class("fields");
  section_div.add_class(static_fields ? "static" : "nonstatic");

  {
    auto fields_header_div = section_div.open_div();
    fields_header_div.add_class("section-header");
    fields_header_div.write_text(static_fields ? "Static Data Members"
                                               : "Data Members");
  }
  {
    for (auto&& [name, field_unique_symbol] : fields) {
      const FieldElement& fe = element.fields.at(field_unique_symbol);

      auto field_div = section_div.open_div();
      field_div.add_class("section-item");

      if (static_fields) {
        auto static_span = field_div.open_span();
        static_span.add_class("static");
        static_span.write_text("static");
      }
      if (fe.is_const) {
        auto field_type_span = field_div.open_span();
        field_type_span.add_class("const");
        field_type_span.write_text("const");
      }
      if (fe.is_volatile) {
        auto field_type_span = field_div.open_span();
        field_type_span.add_class("volatile");
        field_type_span.write_text("volatile");
      }
      {
        auto field_type_span = field_div.open_span();
        field_type_span.add_class("type-name");
        field_type_span.write_text(fe.type_name);
      }
      {
        auto field_name_anchor = field_div.open_a();
        std::ostringstream anchor;
        anchor << "field.";
        anchor << (static_fields ? "static." : "");
        anchor << fe.name;
        field_name_anchor.add_name(anchor.str());
        field_name_anchor.add_href(std::string("#") + anchor.str());
        field_name_anchor.add_class("field-name");
        field_name_anchor.write_text(fe.name);
      }
      {
        auto desc_div = field_div.open_div();
        desc_div.add_class("description");
        if (fe.has_comment()) {
          desc_div.write_text(fe.comment.raw_text);
        }
      }
    }
  }
}

void generate_record_methods(
    HtmlWriter::OpenDiv& record_div, const RecordElement& element,
    bool static_methods,
    sus::Slice<const sus::Tuple<std::string_view, const FunctionId&>> methods) {
  if (methods.is_empty()) return;

  auto section_div = record_div.open_div();
  section_div.add_class("section");
  section_div.add_class("methods");
  section_div.add_class(static_methods ? "static" : "nonstatic");

  {
    auto methods_header_div = section_div.open_div();
    methods_header_div.add_class("section-header");
    methods_header_div.write_text(static_methods ? "Static Methods"
                                                 : "Methods");
  }
  {
    for (auto&& [name, method_id] : methods) {
      const FunctionElement& fe = element.methods.at(method_id);

      auto method_div = section_div.open_div();
      method_div.add_class("section-item");

      for (const FunctionOverload& overload : fe.overloads) {
        auto overload_div = method_div.open_div();
        overload_div.add_class("overload");

        if (static_methods) {
          auto static_span = overload_div.open_span();
          static_span.add_class("static");
          static_span.write_text("static");
        }
        {
          auto return_type_span = overload_div.open_span();
          return_type_span.add_class("type-name");
          return_type_span.write_text(fe.return_type_name);
        }
        {
          auto method_name_anchor = overload_div.open_a();
          std::ostringstream anchor;
          anchor << "method.";
          anchor << (static_methods ? "static." : "");
          anchor << fe.name;
          method_name_anchor.add_name(anchor.str());
          method_name_anchor.add_href(std::string("#") + anchor.str());
          method_name_anchor.add_class("method-name");
          method_name_anchor.write_text(fe.name);
        }
        {
          auto params_span = overload_div.open_span();
          params_span.add_class("method-params");
          // TODO: Write params.
          params_span.write_text("()");
        }
        if (overload.method->is_volatile) {
          auto volatile_span = overload_div.open_span();
          volatile_span.add_class("volatile");
          volatile_span.write_text("volatile");
        }
        {
          switch (overload.method->qualifier) {
            case MethodQualifier::Const: {
              auto qualifier_span = overload_div.open_span();
              qualifier_span.add_class("const");
              qualifier_span.write_text("const");
              break;
            }
            case MethodQualifier::ConstLValue: {
              auto qualifier_span = overload_div.open_span();
              qualifier_span.add_class("const");
              qualifier_span.add_class("ref");
              qualifier_span.write_text("const&");
              break;
            }
            case MethodQualifier::ConstRValue: {
              auto qualifier_span = overload_div.open_span();
              qualifier_span.add_class("const");
              qualifier_span.add_class("rref");
              qualifier_span.write_text("const&&");
              break;
            }
            case MethodQualifier::Mutable: {
              break;
            }
            case MethodQualifier::MutableLValue: {
              auto qualifier_span = overload_div.open_span();
              qualifier_span.add_class("mutable");
              qualifier_span.add_class("ref");
              qualifier_span.write_text("&");
              break;
            }
            case MethodQualifier::MutableRValue: {
              auto qualifier_span = overload_div.open_span();
              qualifier_span.add_class("mutable");
              qualifier_span.add_class("rref");
              qualifier_span.write_text("&&");
              break;
            }
          }
        }
      }
      {
        auto desc_div = method_div.open_div();
        desc_div.add_class("description");
        if (fe.has_comment()) {
          desc_div.write_text(fe.comment.raw_text);
        }
      }
    }
  }
}

}  // namespace

void generate_record(const RecordElement& element,
                     const Options& options) noexcept {
  const std::filesystem::path path = construct_html_file_path(
      options.output_root, element.namespace_path.as_ref(),
      element.class_path.as_ref(), element.name);
  std::filesystem::create_directories(path.parent_path());
  auto html = HtmlWriter(open_file_for_writing(path).unwrap());

  generate_head(html, element.name, options);

  auto body = html.open_body();

  auto record_div = body.open_div();
  record_div.add_class("type");
  record_div.add_class("record");
  record_div.add_class(friendly_record_type_name(element.record_type, false));
  generate_record_overview(mref(record_div), element);

  sus::Vec<sus::Tuple<std::string_view, UniqueSymbol>> sorted_static_fields;
  sus::Vec<sus::Tuple<std::string_view, UniqueSymbol>> sorted_fields;
  for (const auto& [symbol, field_element] : element.fields) {
    switch (field_element.is_static) {
      case FieldElement::Static:
        sorted_static_fields.push(sus::tuple(field_element.name, symbol));
        break;
      case FieldElement::NonStatic:
        sorted_fields.push(sus::tuple(field_element.name, symbol));
        break;
    }
  }
  sorted_static_fields.sort_unstable_by(
      [](const sus::Tuple<std::string_view, UniqueSymbol>& a,
         const sus::Tuple<std::string_view, UniqueSymbol>& b) {
        return a.get_ref<0>() <=> b.get_ref<0>();
      });
  sorted_fields.sort_unstable_by(
      [](const sus::Tuple<std::string_view, UniqueSymbol>& a,
         const sus::Tuple<std::string_view, UniqueSymbol>& b) {
        return a.get_ref<0>() <=> b.get_ref<0>();
      });

  generate_record_fields(mref(record_div), element, true,
                         sorted_static_fields.as_ref());
  generate_record_fields(mref(record_div), element, false,
                         sorted_fields.as_ref());

  sus::Vec<sus::Tuple<std::string_view, const FunctionId&>> sorted_static_methods;
  sus::Vec<sus::Tuple<std::string_view, const FunctionId&>> sorted_methods;
  for (const auto& [method_id, method_element] : element.methods) {
    if (method_id.is_static) {
      sorted_static_methods.push(sus::tuple(method_element.name, method_id));
    } else {
      sorted_methods.push(sus::tuple(method_element.name, method_id));
    }
  }
  sorted_static_methods.sort_unstable_by(
      [](const sus::Tuple<std::string_view, const FunctionId&>& a,
         const sus::Tuple<std::string_view, const FunctionId&>& b) {
        return a.get_ref<0>() <=> b.get_ref<0>();
      });
  sorted_methods.sort_unstable_by(
      [](const sus::Tuple<std::string_view, const FunctionId&>& a,
         const sus::Tuple<std::string_view, const FunctionId&>& b) {
        return a.get_ref<0>() <=> b.get_ref<0>();
      });

  generate_record_methods(mref(record_div), element, true,
                          sorted_static_methods.as_ref());
  generate_record_methods(mref(record_div), element, false,
                          sorted_methods.as_ref());
}

}  // namespace subdoc::gen