#include "../include/file_manip.hh"
#include "../include/utils.hh"
#include "../include/cal2tex.hh"

int main(int argc, char **argv)
{
try{
    if(argc != 3){
        USAGE
    }

    const std::string input_file_name{argv[1]};
    const std::string output_file_name{argv[2]};
    Cal2tex app (input_file_name, output_file_name);

    app.calculate_price(60.00);

    if(app.write_LaTeX_document_to_file()){
        std::cout << "LaTeX documents succesfully written.\n";
    }else{
        std::cerr << "Failed to write LaTeX documents\n";
        return 1;
    }
} catch(std::exception& e){
    std::cerr << e.what() << '\n';
}
    return (0);
}
