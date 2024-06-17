#ifndef FILE_MANIP_HH
#define FILE_MANIP_HH 1
#include <fstream>
#include <iostream>
#include <vector>
#include "../include/utils.hh"

#define KB 1024
#ifdef KB
#define MB 1024 * KB 
#endif


// TODO: Use File system constructor from C++17
namespace manipulation{
class File
{
    private:
        std::fstream             m_file;
        std::ofstream            m_ofile;
        std::string              m_ifname;
        std::ios_base::openmode  m_openmode;
        std::streamsize          m_file_size;
    public:
        explicit File(const std::string& input_name, const std::ios_base::openmode& openmode)
            : m_openmode{openmode}
           
        {
            if(input_name.empty()){
                throw(std::logic_error("[ERROR]: input file name is empty\n"));
            }
            m_ifname = input_name;
            m_file   = std::fstream(m_ifname, m_openmode);
        }
        inline std::string slurp_file();
        ~File()
        {
            m_file.close();
        }
        friend class Psyche;
};
    std::string File::slurp_file(){
        static constexpr auto buff_size =  std::size_t {1 * MB} ;
        m_file.exceptions(std::ios_base::badbit);
        auto out = std::string();
        auto buff = std::string(buff_size, '\0');

        if(m_file.is_open()){
            while(m_file.read(buff.data(), buff_size)){
                out.append(buff, 0, m_file.gcount());
            }
            out.append(buff, 0, m_file.gcount());
            return buff;
        }
        throw std::logic_error("[ERROR] File: " + m_ifname + " isn't opened\n");
        return buff;
    }
    
}
#endif // FILE_MANIP_HH
