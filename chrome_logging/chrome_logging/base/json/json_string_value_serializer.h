// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_JSON_JSON_STRING_VALUE_SERIALIZER_H_
#define BASE_JSON_JSON_STRING_VALUE_SERIALIZER_H_

#include <string>

#include "base/base_export.h"
#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/strings/string_piece.h"
#include "base/values.h"

class BASE_EXPORT JSONStringValueSerializer : public base::ValueSerializer {
 public:
  // |json_string| is the string that will be source of the deserialization
  // or the destination of the serialization.  The caller of the constructor
  // retains ownership of the string. |json_string| must not be null.
  explicit JSONStringValueSerializer(std::string* json_string);

  // This version allows initialization with a StringPiece for deserialization
  // only. Retains a reference to the contents of |json_string|, so the data
  // must outlive the JSONStringValueSerializer.
  explicit JSONStringValueSerializer(const base::StringPiece& json_string);

  ~JSONStringValueSerializer() override;

  // Attempt to serialize the data structure represented by Value into
  // JSON.  If the return value is true, the result will have been written
  // into the string passed into the constructor.
  bool Serialize(const base::Value& root) override;

  // Equivalent to Serialize(root) except binary values are omitted from the
  // output.
  bool SerializeAndOmitBinaryValues(const base::Value& root);

  // Attempt to deserialize the data structure encoded in the string passed
  // in to the constructor into a structure of Value objects.  If the return
  // value is null, and if |error_code| is non-null, |error_code| will
  // contain an integer error code (a JsonParseError in this case).
  // If |error_message| is non-null, it will be filled in with a formatted
  // error message including the location of the error if appropriate.
  // The caller takes ownership of the returned value.
  base::Value* Deserialize(int* error_code,
                           std::string* error_message) override;

  void set_pretty_print(bool new_value) { pretty_print_ = new_value; }
  bool pretty_print() { return pretty_print_; }

  void set_allow_trailing_comma(bool new_value) {
    allow_trailing_comma_ = new_value;
  }

 private:
  bool SerializeInternal(const base::Value& root, bool omit_binary_values);

  // String for writing. Owned by the caller of the constructor. Will be null if
  // the serializer was initialized with a const string.
  std::string* json_string_;
  // String for reading. Data is owned by the caller of the constructor. If
  // |json_string_| is non-null, this is a view onto |json_string_|.
  base::StringPiece json_string_readonly_;
  bool pretty_print_;  // If true, serialization will span multiple lines.
  // If true, deserialization will allow trailing commas.
  bool allow_trailing_comma_;

  DISALLOW_COPY_AND_ASSIGN(JSONStringValueSerializer);
};

#endif  // BASE_JSON_JSON_STRING_VALUE_SERIALIZER_H_

