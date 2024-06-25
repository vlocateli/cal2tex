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

#include "../include/cal_events.hh"
#include "../include/file_manip.hh"

#include <fstream>
#include <iostream>
#include <libical/ical.h>
#include <string>
#include <vector>
#include <unordered_map>

static const std::string prog_name{"cal2tex"};
static const std::string author{"Victor Locateli"};
static const std::string year{"2024"};
#define DEBUG 1
#define USAGE                                                      \
  std::cerr                                                        \
      << "cal2tex Copyright (C) " << year << " " << author << '\n' \
      << "This program comes with ABSOLUTELY NO WARRANTY;\n"       \
<< "This is free software, and you are welcome to redistribute it  \
under certain "                                                    \
<< " conditions.\n";                                               \
return 1;
#define IS_CURRENT_NULLPTR current_event != nullptr ? current_event : "";
// TODO list:
//          1) Parse the file to get fields: SUMMARY, DTSTART and DTEND[ ]
//          2) Move file to different class[X]
//          3) Save "CPF" in a GPG file[ ]
//          4) Make GUI[ ]

namespace calendar{
    class Cal2tex {
    private:
      std::vector<Cal_events> m_events;
      std::string m_ifname;
      std::string m_ofname;
      manipulation::File m_ifile;
      std::vector<std::string> m_filenames;
      std::vector<std::ofstream> m_tex_ofiles;
      std::vector<std::string> m_ics_days;
      std::string m_ics_month;
      std::string m_ics_year;
      std::unordered_map<std::string, float> m_summary_price_map;
      bool parse_ics();

    public:
      Cal2tex(const std::string &input_file_name,
              const std::string &output_file_name)
          : m_ifname{input_file_name}, m_ofname{output_file_name},
            m_ifile(m_ifname, std::ios_base::in) {
            parse_ics();
      }
      ~Cal2tex() {}
      bool write_LaTeX_document_to_file();
      void calculate_price(const float &price);
    };
}
