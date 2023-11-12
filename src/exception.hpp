#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>

struct ExportException : public std::runtime_error {
  ExportException(std::string text) : std::runtime_error(text) {}
};

#endif // EXCEPTION_HPP
