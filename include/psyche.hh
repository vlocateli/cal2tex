#ifndef PSYCHE
#define PSYCHE 1
#include <iostream>
#include <fstream>
#include <libical/ical.h>
#include <vector>
#include <string>
#include <regex>
#include <unordered_map>
#include "../include/cal_events.hh"
#include "../include/file_manip.hh"
#include "../include/utils.hh"
static const std::string prog_name {"psyche"};
#define USAGE\
    std::cerr << prog_name << " <calendar_file> <output_pdf>\n";\
    return 1;
#define IS_CURRENT_NULLPTR\
 current_event != nullptr ? current_event : "";
// TODO list:
//          1) Write parser[ ]
//          2) Move file to different class[ ]
//          3) Save "CPF" in a GPG file[ ]
//          4) Make GUI[ ]
class Psyche{
    private:
        std::vector<Cal_events>                m_events;
        std::string                            m_ifname;
        std::string                            m_ofname;
        //std::ifstream                          m_ifile;
        //std::ofstream                          m_ofile;
        manipulation::File                     m_ifile;
        std::vector<std::string>               m_filenames;
        std::vector<std::ofstream>             m_tex_ofiles;
        std::vector<std::string>               m_ics_days;
        std::string                            m_ics_month;
        std::string                            m_ics_year;
        std::unordered_map<std::string, float> m_summary_price_map;
        bool parse_ics();
        void get_ics_days();
        void get_ics_month();
        void get_ics_year();
     
    public:
    Psyche(const std::string& input_file_name, 
            const std::string& output_file_name):
            m_ifname{input_file_name},
            m_ofname{output_file_name},
            m_ifile(m_ifname, std::ios_base::in)
    {
            parse_ics();

    }
    ~Psyche()
    {
    }
    bool write_LaTeX_document_to_file();
    void calculate_price(const float &price) ;
};
bool Psyche::parse_ics() {


    auto file_content = m_ifile.slurp_file();
    auto pos  {std::size_t(0)};
    auto pos2 {std::size_t(0)};
    auto delimiter{std::string("\n")};
    std::vector<std::string> delimiters {"SUMMARY"};
    while(( pos = file_content.find(delimiter)) != std::string::npos){
            auto token = file_content.substr(0, pos);
            for(auto &d: delimiters){
                pos2 = token.find(d);
                auto str = token.substr(0, pos2);
                std::cout << str << '\n';
                token.erase(0, pos2 + d.length());
            }
            file_content.erase(0, pos + delimiter.length());
    }
#if 0
    const char *current_event {};
    if(!m_ifile.is_open()){
        std::cerr << "[ERROR]: Could not open " << m_ifname << '\n';
        std::exit(1);
    }
    // load the file into a buffer
    std::string content((std::istreambuf_iterator<char>(m_ifile)),
                         std::istreambuf_iterator<char>());
    if(content.empty()){
        std::cerr << "[ERROR]: File  " << m_ifname << " content is empty\n";
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
        m_events.push_back(e);
    }
    icalcomponent_free(calendar);
    return;
#endif
    return true;
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

bool Psyche::write_LaTeX_document_to_file() {
    if(m_summary_price_map.empty()){
        std::cerr << "[ERROR]: Summary price map is empty\n";
        return false;
    }
    for(const auto& pair: m_summary_price_map){
        const std::string& person = pair.first;
        const float& value  = pair.second;
        std::string filename = person + ".tex";
        m_filenames.push_back(filename);
        std::ofstream outfile(filename);
        if(!outfile.is_open()){
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
         << "    \\noindent Recebemos de " + std::string(person) + ", portador do CPF: CPF de " + std::string(person) +" a quantia de "
         <<      value
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
void Psyche::calculate_price(const float& price) {
    std::string current_word{};
    for(const auto& event: m_events){
        current_word = event.summary;
        m_summary_price_map[current_word] += price;
    }
}
void Psyche::get_ics_days(){
    for(auto& event: m_events){
        if(!event.date_start.empty()){
            std::cout << event.summary << " " << event.date_start << '\n';
        }
    }
}
#endif // PSYCHE

