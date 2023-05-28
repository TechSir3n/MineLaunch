#ifndef SHA256_HPP
#define SHA256_HPP

#include <cstring>
#include <iostream>
#include <openssl/sha.h>
#include <string_view>

std::string sha256(const std::string_view &password) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;

  SHA256_Init(&sha256);
  SHA256_Update(&sha256, password.data(), password.length());
  SHA256_Final(hash, &sha256);

  std::string result;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    char buf[3];
    sprintf(buf, "%02x", hash[i]);
    result += buf;
  }

  return result;
}

#endif
