#include "GCut.h"
#include <string>

using namespace std;


GCut::GCut(const char* configname)
{
    configfile.open(configname);

    if (configfile.is_open())
    {
        string str;
        string firstWord;
        string values;

        while ( getline (configfile,str) )
        {
            string::size_type begin = str.find_first_not_of(" \f\t\v");
            if(begin == string::npos) continue;
            if(string("#").find(str[begin]) != string::npos)	continue;
            if(string("//").find(str[begin]) != string::npos)	continue;

            try {
                firstWord = str.substr(0,str.find(" "));
            }
            catch(exception& e) {
                firstWord = str.erase(str.find_first_of(" "),str.find_first_of(" "));
            }

            transform(firstWord.begin(),firstWord.end(),firstWord.begin(), ::toupper);
            firstWord.erase(firstWord.end()-1);
            values = str.substr(str.find(" ")+1,str.length());

            if (strcmp(firstWord.c_str(),string("NPhoton")) == 0)
            {
                CutNPhoton.push_back();
            }
        }
        configfile.close();
    }
}

GCut::~GCut()
{

}

void  GCut::ProcessEvent()
{

}

Bool_t  GCut::Process(const char* input_filename, const char* output_filename)
{
    if(!Open(input_filename))    return kFALSE;
    if(!OpenTagger())    return kFALSE;
    if(!OpenProtons())    return kFALSE;

    //if (configfile.is_open())
        //+	{
        //+		while ( getline (configfile,str) )
        //+		{
}

