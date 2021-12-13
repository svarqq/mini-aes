#include <iostream>
#include <string>

#include "aux.h"
#include "crypto.h"


int main(int argc, char **argv) {
    // check for legal arguments
    std::string aes_process;
    std::string aes_target;
    if (argc == 3) {
        if (((std::string)"encrypt").compare(argv[1]) == 0 || 
                ((std::string)"decrypt").compare(argv[1]) == 0) {
            aes_process = argv[1];
            aes_target = argv[2];
        } else {
            throw std::invalid_argument("First arguments must be either 'encrypt' or 'decrypt'\n"
                    "\t\tmini_aes [encrypt|decrypt] [text|filepath]");
        }
    } else {
        throw std::invalid_argument("Two arguments must be provided to mini_aes\n"
                "\t\tmini_aes [encrypt|decrypt] [text|filepath]");
    }

    // load text either as file input or argument input
    std::string intext;
    std::ifstream infile(aes_target);
    bool file_input = false;
    if (infile.is_open()) {
        file_input = true;
        intext = get_filetext(infile);
        infile.close();
    } else {
        intext = aes_target;
    }

    // encrypt or decrypt text depending on provided argument
    std::string outtext;
    if (aes_process.compare("encrypt") == 0) {
        outtext = encrypt(intext);
    } else if (aes_process.compare("decrypt") == 0) {
        outtext = decrypt(intext);
    }


    if (file_input) {
        std::string out_fname;
        int directory_idx = aes_target.rfind("/");
        int extension_idx = aes_target.rfind(".");
        if (aes_process.compare("encrypt") == 0) {
            out_fname += "encrypted/";
            out_fname += aes_target.substr(directory_idx + 1, extension_idx-directory_idx-1);
            out_fname += ".enc";
        } else if (aes_process.compare("decrypt") == 0) {
            out_fname += "decrypted/";
            out_fname += aes_target.substr(directory_idx + 1, extension_idx-directory_idx-1);
            out_fname += ".dec";
        }
        write_file(out_fname, outtext);
        std::cout << aes_process << "ed text of '" << aes_target 
            << "' written to file '" << out_fname << "'.\n";
    } else {
        print_formatted_result(intext, outtext);
    }

    return 0;
}
