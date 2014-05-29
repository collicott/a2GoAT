#ifndef __GConfigFile_h__
#define __GConfigFile_h__


#include <string>
#include <TROOT.h>


class  GConfigFile
{
private:
    Char_t*		global_config_file;

protected:
    std::string config;

public:
    GConfigFile();
    virtual ~GConfigFile();

    void 	SetConfigFile(Char_t* config_file)	{global_config_file = config_file;}
    Char_t* GetConfigFile()	{return global_config_file;}

    std::string	ReadConfig(const std::string& key_in, Int_t instance, Char_t* configname);
    std::string	ReadConfig(const std::string& key_in, Int_t instance)                       {return ReadConfig(key_in, instance, global_config_file);}
    std::string	ReadConfig(const std::string& key_in)                                       {return ReadConfig(key_in, 0, global_config_file);}
};

#endif
