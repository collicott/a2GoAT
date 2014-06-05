#include "GConfigFile.h"
#include <algorithm>
#include <fstream>
#include <iostream>


GConfigFile::GConfigFile()  :
    global_config_file()
{
}

GConfigFile::GConfigFile(const Char_t* config_file)  :
    global_config_file(config_file)
{
}

GConfigFile::~GConfigFile()
{

}



std::string GConfigFile::ReadConfig(const std::string& key_in, const Int_t instance, const Char_t* configname)
{
    Int_t string_instance = 0;
    std::string key = key_in;
    std::transform(key.begin(), key.end(),key.begin(), ::toupper);

    std::string str;
    std::string values;

    ifstream configfile;

    configfile.open(configname);
    //std::cout << "config: " << configname << std::endl;

    if (configfile.is_open())
    {
        while ( getline (configfile,str) )
        {
            std::string::size_type begin = str.find_first_not_of(" \f\t\v");
            if(begin == std::string::npos) continue;
            if(std::string("#").find(str[begin]) != std::string::npos)	continue;
            if(std::string("//").find(str[begin]) != std::string::npos)	continue;

            std::string firstWord;

            try {
                firstWord = str.substr(0,str.find(":"));
            }
            catch(std::exception& e) {
                firstWord = str.erase(str.find_first_of(":"),str.find_first_of(":"));
            }
            std::transform(firstWord.begin(),firstWord.end(),firstWord.begin(), ::toupper);

            values = str.substr(str.find(":")+1,str.length());

            if (strcmp(firstWord.c_str(),key.c_str()) == 0)
            {
                if (string_instance == instance)
                {
                    configfile.close();
                    return values;
                }
                else string_instance++;
            }
        }
        configfile.close();
    }

    return "nokey";
}
