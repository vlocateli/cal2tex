#include <iostream>
#include <fstream>
#include <libical/ical.h>
#include <vector>
#include <string>
static constexpr std::string prog_name {"cal2tex"};
#define USAGE\
    std::cerr << prog_name << "<calendar_file> <output_pdf>\n";\
    return 1;

struct Cal_events{
    std::string summary;
    std::string date_start;
    std::string date_end;
    std::string location;
};
class Cal2tex{
    private:
        std::vector<Cal_events> m_events;
        std::string m_ifname;
        std::string m_ofname;
        std::ifstream m_file;
    public:
    Cal2tex(const std::string& input_file_name, 
            const std::string& output_file_name):
            m_ifname{input_file_name},
            m_ofname{output_file_name},
            m_file(m_ifname)
    {
    }
    ~Cal2tex()
    {
        m_file.close();
    }
};
int main(int argc, char **argv)
{
    if(argc != 3){
        USAGE
    }
    const std::string input_file_name{argv[1]};
    const std::string output_file_name{argv[1]};
    Cal2tex(input_file_name, output_file_name);
    return (0);
}
