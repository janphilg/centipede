// Copyright 2022 Google LLC.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <openssl/sha.h>  // IWYU pragma: keep

#include <cstddef>
#include <string>

#include "./defs.h"
#include "./util.h"

namespace centipede {

std::string Hash(const ByteArray &ba) {
  // Compute SHA1.
  unsigned char sha1[SHA_DIGEST_LENGTH];
  SHA1(ba.data(), ba.size(), sha1);
  // Convert SHA1 to text.
  static_assert(kHashLen == 2 * SHA_DIGEST_LENGTH);
  char sha1_hex_text[kHashLen];
  static const char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                               '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  for (size_t i = 0; i < SHA_DIGEST_LENGTH; i++) {
    sha1_hex_text[i * 2 + 0] = hex[sha1[i] / 16];
    sha1_hex_text[i * 2 + 1] = hex[sha1[i] % 16];
  }
  return std::string(sha1_hex_text, sha1_hex_text + kHashLen);
}

}  // namespace centipede
