/*
Cal2tex - Convert ical files to tex and generate PDF.
Copyright (C) 2024 Victor Locateli

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#define DEBUG 1
#include <iostream>
#include <vector>
template <typename T>
std::ostream &operator<<(std::ostream &stream, const std::vector<T> &v) {
  for (auto &e : v) {
    stream << e;
  }
  return stream;
}
#ifdef DEBUG
namespace dbg{
template<typename T, typename... Ts>
constexpr void print(T&& first, Ts&&... rest) noexcept {
    if constexpr (sizeof... (Ts) == 0) {
        std::cerr << first;
    } else {
        std::cerr << first << " ";
        print(std::forward<Ts>(rest)...);
    }
}
}
#endif // DEBUG
void tokenize(const std::string &s, const std::string &delimiters,
        std::vector<std::string> &tokens); 
