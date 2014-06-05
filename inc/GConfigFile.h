#ifndef __GConfigFile_h__
#define __GConfigFile_h__


#include <string>
#include <iostream>
#include <TROOT.h>


class  GConfigFile
{
private:
    std::string	global_config_file;

protected:

public:
    GConfigFile();
    GConfigFile(const Char_t* config_file);
    virtual ~GConfigFile();

            void    SetConfigFile(const Char_t* config_file)	{global_config_file = config_file;}
    const   Char_t* GetConfigFile() const                       {}

    std::string	ReadConfig(const std::string& key_in, const Int_t instance, const Char_t* configname);
    std::string	ReadConfig(const std::string& key_in, const Int_t instance)                             {return ReadConfig(key_in, instance, global_config_file.c_str());}
    std::string	ReadConfig(const std::string& key_in)                                                   {/*std::cout << "il: " << global_config_file << std::endl;*/ return ReadConfig(key_in, 0, global_config_file.c_str());}
};

#endif
