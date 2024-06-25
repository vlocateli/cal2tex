#include "../include/cal2tex.hh"



std::ostream &operator<<(std::ostream &stream, const Cal_events &cal_events) {
  stream << cal_events.summary << '\n';
  stream << cal_events.date_start << '\n';
  stream << cal_events.date_end << '\n';
  stream << cal_events.location << '\n';
  return stream;
}

bool calendar::Cal2tex::write_LaTeX_document_to_file() {
  if (m_summary_price_map.empty()) {
    std::cerr << "[ERROR]: Summary price map is empty\n";
    return false;
  }
  for (const auto &pair : m_summary_price_map) {
    const std::string &person = pair.first;
    const float &value = pair.second;
    std::string filename = person + ".tex";
    m_filenames.push_back(filename);
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
      std::cerr << "[ERROR]: Can't open " << filename << '\n';
    }
    outfile << "\\documentclass[12pt]{article}\n"
            << "\\usepackage[portuguese]{babel}\n"
            << "\\usepackage{titleps}\n"
            << "\\usepackage{titling}\n"
            << "\\usepackage{fancyhdr}\n"
            << "\\usepackage{background}\n"
            << "\\pagestyle{fancy}\n"
            << "\\fancyhf{}\n"
            << "\\fancyhead[L]{\\(\\Psi\\)}\n"
            << "\\fancyhead[C]{\\textbf{Sigmund Freud}}\n"
            << "\\fancyfoot[C]{\\textbf{Rua dos psicólogos - 1234}}\n"
            << "\\fancyhead[R]{\\(\\Psi\\)}\n"
            << "\\renewcommand{\\footrulewidth}{0.4pt}\n"
            << "\\newcommand{\\bottomphrase}{São Paulo, \\today}\n"
            << "\\backgroundsetup{\n"
            << "    scale=50,\n"
            << "    color=black,\n"
            << "    opacity=0.1,\n"
            << "    angle=360,\n"
            << "    position=current page.center,\n"
            << "    nodeanchor=west,\n"
            << "    hshift=-4pt,\n"
            << "    contents={\\(\\Psi\\)}\n"
            << "}\n"
            << "\\begin{document}\n"
            << "    \\sloppy\n"
            << "    \\noindent Recebemos de " + std::string(person) +
                   ", portador do CPF: CPF de " + std::string(person) +
                   " a quantia de "
            << value
            << "    \\ proveniente de Serviços de Psicoterapia, realizados em\n"
            << "    de de .\n"
            << "    Para clareza firmamos o presente recibo.\n"
            << "    \\newline\n"
            << "    \\newline\n"
            << "    \\noindent \\bottomphrase\n"
            << "\\end{document}\n";
  }
  return true;
}
void calendar::Cal2tex::calculate_price(const float &price) {
  std::string current_word{};
  for (const auto &event : m_events) {
    current_word = event.summary;
    m_summary_price_map[current_word] += price;
  }
}

bool calendar::Cal2tex::parse_ics() {
  std::string file_content;
  try {
    file_content = m_ifile.slurp_file();
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return false;
  }
  const std::vector<std::string> delimiters{":", "\n"};
  std::vector<std::string> tokens;
  tokenize<std::string>(file_content, delimiters, tokens);
  dbg::print(tokens);
  return true;
}

