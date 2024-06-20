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
#include "../include/cal2tex.hh"
#include "../include/file_manip.hh"
#include "../include/utils.hh"

int main(int argc, char **argv) {
  try {
    if (argc != 3) {
      USAGE
    }

    const std::string input_file_name{argv[1]};
    const std::string output_file_name{argv[2]};
    Cal2tex app(input_file_name, output_file_name);

    app.calculate_price(60.00);

    if (app.write_LaTeX_document_to_file()) {
      std::cout << "LaTeX documents succesfully written.\n";
    } else {
      std::cerr << "Failed to write LaTeX documents\n";
      return 1;
    }
  } catch (std::exception &e) {
    std::cerr << e.what() << '\n';
  }
  return (0);
}
