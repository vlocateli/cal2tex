#include "../include/cal2tex.hh"
int main(int argc, char **argv)
{
    if(argc != 3){
        USAGE
    }
    const std::string input_file_name{argv[1]};
    const std::string output_file_name{argv[2]};
    Cal2tex cal2tex (input_file_name, output_file_name);
    cal2tex.calculate_price(60.00);
    if(cal2tex.write_LaTeX_document_to_file()){
        std::cout << "LaTeX documents succesfully written.\n";
    }else{
        std::cerr << "Failed to write LaTeX documents\n";
        return 1;
    }
    return (0);
}
