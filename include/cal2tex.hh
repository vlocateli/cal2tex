#ifndef CAL2TEX
#define CAL2TEX 1
#include <iostream>
#include <fstream>
#include <libical/ical.h>
#include <vector>
#include <string>
#include <unordered_map>
#include "../include/cal_events.hh"
static const std::string prog_name {"cal2tex"};
#define USAGE\
    std::cerr << prog_name << " <calendar_file> <output_pdf>\n";\
    return 1;
#define IS_CURRENT_NULLPTR\
 current_event != nullptr ? current_event : "";
class Cal2tex{
    private:
        std::vector<Cal_events> m_events;
        std::string m_ifname;
        std::string m_ofname;
        std::ifstream m_ifile;
        std::ofstream m_ofile;
        std::unordered_map<std::string, float> m_summary_price_map;
        std::vector<Cal_events> parse_ics() ;
    public:
    Cal2tex(const std::string& input_file_name, 
            const std::string& output_file_name):
            m_ifname{input_file_name},
            m_ofname{output_file_name},
            m_ifile(m_ifname),
            m_ofile(m_ofname)
    {
    }
    ~Cal2tex()
    {
        m_ifile.close();
    }
    template<typename T>
    friend std::ostream& operator<<(std::ostream& stream,
                                    std::vector<T> &v);
    int run_program(int argc, char **argv);
    bool write_LaTeX_document_to_file();
    void calculate_price(const float &price) ;
};
std::vector<Cal_events> Cal2tex::parse_ics() {
    std::vector<Cal_events> events;
    const char *current_event {};
    if(!m_ifile.is_open()){
        std::cerr << "[ERROR]: Could not open " << m_ifname << '\n';
        std::exit(1);
    }
    // load the file into a buffer
    std::string content((std::istreambuf_iterator<char>(m_ifile)),
                         std::istreambuf_iterator<char>());
    if(content.empty()){
        std::cerr << "[ERROR]: File content is empty\n";
        std::exit(1);
    }
    icalcomponent *calendar = icalparser_parse_string(content.c_str());
    if(!calendar){
        std::cerr << "[ERROR]: Could not parse string content into ical component\n";
        std::exit(1);
    }
    for(icalcomponent *event = icalcomponent_get_first_component(calendar,
                                                                 ICAL_VEVENT_COMPONENT); event != nullptr; event = icalcomponent_get_next_component(calendar, ICAL_VEVENT_COMPONENT)){
        Cal_events e;
        current_event = icalcomponent_get_summary(event);
        e.summary =    IS_CURRENT_NULLPTR 
        current_event = icaltime_as_ical_string(icalcomponent_get_dtstart(event));
        e.date_start = IS_CURRENT_NULLPTR 
        current_event = icaltime_as_ical_string(icalcomponent_get_dtend(event));
        e.date_end  = IS_CURRENT_NULLPTR 
        current_event = icalcomponent_get_location(event);
        e.location = IS_CURRENT_NULLPTR 
        events.push_back(e);
    }
    icalcomponent_free(calendar);
    return events;
}
template<typename T>
std::ostream& operator<<(std::ostream& stream,
                                    std::vector<T>&v){
    if(v.empty()){
        return stream;
    }

    for(auto &elem : v){
        stream << ' ' << elem;
    }

    return stream;
}
std::ostream& operator<< (std::ostream& stream,
                          const Cal_events &cal_events) {
    stream << cal_events.summary     << '\n';
    stream << cal_events.date_start  << '\n';
    stream << cal_events.date_end    << '\n';
    stream << cal_events.location    << '\n';
    return stream;
}

bool Cal2tex::write_LaTeX_document_to_file() {
    if(!m_ofile.is_open()){
        std::cerr << "[ERROR]: Can't open " << m_ofname << '\n';
        return false;
    }
    auto events = parse_ics();
    if(events.empty()){
        std::cerr << "[ERROR]: events empty\n";
        std::abort();
    }

    // Write the LaTeX document content to the stream
    m_ofile << "\\documentclass[12pt]{article}\n";
    m_ofile << "\\usepackage[portuguese]{babel}\n";
    m_ofile << "\\usepackage{titleps}\n";
    m_ofile << "\\usepackage{titling}\n";
    m_ofile << "\\usepackage{fancyhdr}\n";
    m_ofile << "\\usepackage{background}\n";
    m_ofile << "\\pagestyle{fancy}\n";
    m_ofile << "\\fancyhf{}\n";
    m_ofile << "\\fancyhead[L]{\\(\\Psi\\)}\n";
    m_ofile << "\\fancyhead[C]{\\textbf{Sigmund Freud}}\n";
    m_ofile << "\\fancyfoot[C]{\\textbf{Rua dos psicólogos - 1234}}\n";
    m_ofile << "\\fancyhead[R]{\\(\\Psi\\)}\n";
    m_ofile << "\\renewcommand{\\footrulewidth}{0.4pt}\n";
    m_ofile << "\\newcommand{\\bottomphrase}{São Paulo, \\today}\n";
    m_ofile << "\\backgroundsetup{\n";
    m_ofile << "    scale=50,\n";
    m_ofile << "    color=black,\n";
    m_ofile << "    opacity=0.1,\n";
    m_ofile << "    angle=360,\n";
    m_ofile << "    position=current page.center,\n";
    m_ofile << "    nodeanchor=west,\n";
    m_ofile << "    hshift=-4pt,\n";
    m_ofile << "    contents={\\(\\Psi\\)}\n";
    m_ofile << "}\n";
    m_ofile << "\\begin{document}\n";
    m_ofile << "    \\sloppy\n";
    m_ofile << "    \\noindent Recebemos de , portador do CPF: a quantia de proveniente de Serviços de Psicoterapia, realizados em\n";
    m_ofile << "    de de .\n";
    m_ofile << "    Para clareza firmamos o presente recibo.\n";
    m_ofile << "    \\newline\n";
    m_ofile << "    \\newline\n";
    m_ofile << "    \\noindent \\bottomphrase\n";
    m_ofile << "\\end{document}\n";

    // Return the constructed LaTeX document string
    return true;
}
void Cal2tex::calculate_price(const float& price) {
    std::string current_word{};
    auto events = parse_ics();
#if 0
    for(auto& event : events){
        current_word = event.summary;
        word_count[current_word]++; 
    }

    std::unordered_map<std::string, std::vector<float>> prices_map;

    for(auto& pair: word_count){
        prices_map[pair.first].push_back(pair.second);
    }
    for(auto& pair : prices_map){
        for(auto& value : pair.second){
            std::cout << value * price << '\n';
        }
    }
#endif
    for(const auto& event: events){
        current_word = event.summary;
        m_summary_price_map[current_word] += price;
    }
}
int Cal2tex::run_program(int argc, char** argv){
    if(argc != 3){
        USAGE
        return 1;
    }
    const std::string input_file_name{argv[1]};
    const std::string output_file_name{argv[2]};
    
    Cal2tex cal2tex(input_file_name, output_file_name);
    cal2tex.calculate_price(60.0); 
    cal2tex.write_LaTeX_document_to_file();
    return 0;
}
#endif // CAL2TEX
