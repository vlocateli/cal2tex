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
#include "../include/utils.hh"
#include <fstream>
#include <iostream>
#include <vector>

#define KB 1024
#ifdef KB
#define MB 1024 * KB
#endif

// TODO: Use File system constructor from C++17
namespace manipulation {
struct File {
  explicit File(const std::string &input_name,
                const std::ios_base::openmode &openmode)
      : m_openmode{openmode}

  {
    if (input_name.empty()) {
      throw(std::logic_error("[ERROR]: input file name is empty\n"));
    }
    m_ifname = input_name;
    m_file = std::fstream(m_ifname, m_openmode);
  }
  inline std::string slurp_file();
  ~File() { m_file.close(); }
  std::fstream m_file;
  std::ofstream m_ofile;
  std::string m_ifname;
  std::ios_base::openmode m_openmode;
  std::streamsize m_file_size;
};
std::string File::slurp_file() {
  static constexpr auto buff_size = std::size_t{1 * MB};
  m_file.exceptions(std::ios_base::badbit);
  auto out = std::string();
  auto buff = std::string(buff_size, '\0');

  if (m_file.is_open()) {
    while (m_file.read(buff.data(), buff_size)) {
      out.append(buff, 0, m_file.gcount());
    }
    out.append(buff, 0, m_file.gcount());
    return out;
  }
  throw std::logic_error("[ERROR] File: " + m_ifname + " isn't opened\n");
}
} // namespace manipulation
