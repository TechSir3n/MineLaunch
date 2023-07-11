#pragma once

#include <exception>
#include <iostream>

class NullPointerException : public std::runtime_error {
public:
  NullPointerException(const std::string &strErr)
      : std::runtime_error(strErr) {}
};

class OpenFileException : public std::runtime_error {
public:
  OpenFileException(const std::string &strErr) : std::runtime_error(strErr) {}
};

class OpenDirectoryException : public std::runtime_error {
  public:
  OpenDirectoryException(const std::string &strErr)
      : std::runtime_error(strErr) {}
};

class ErrorCalculateHash : public std::runtime_error {
  public:
  ErrorCalculateHash(const std::string &strErr) : std::runtime_error(strErr) {}
};
