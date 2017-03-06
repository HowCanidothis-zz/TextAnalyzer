#include "textanalyzer.h"
#include <getopt.h>
#include <fstream>

#include <vector>
#include <map>

using namespace std;

TextAnalyzer::ErrorState TextAnalyzer::readConsole(int argc, char *argv[], string &in, string& out)
{
    const char *optstring{"i:o:"};
    int opt;
    while((opt = getopt(argc, argv, optstring)) != -1){
        switch (opt) {
        case 'i': in = optarg;
            break;
        case 'o': out = optarg;
            break;
        default:
            break;
        }
    }
    if(in.empty() || out.empty())
        error = Error_console_args;
    return error;
}


TextAnalyzer::ErrorState TextAnalyzer::analyze()
{
    ifstream in;
    in.open(inf);

    if(!in.is_open())
    {
        error = Error_open_in_file;
        return error;
    }


    ofstream out;
    out.open(outf);
    if(!out.is_open())
    {
        error = Error_open_out_file;
        return error;
    }

    typedef map<string,int> Dictionary;
    typedef map<string,int>::iterator DictionaryI;

    Dictionary dict;
    string word;
    word.reserve(1000);
    while (in.good()) {
        char c = in.get();
        if((c > 64 && c < 91) || (c > 96 && c < 123))
            word.push_back(tolower(c));
        else
        {
            if(!word.empty()){
                DictionaryI found = dict.find(word);
                if(found != dict.end()){
                    (*found).second += 1;
                }
                else{
                    dict[word] = 1;
                }
                word.clear();
            }
        }
    }

    DictionaryI i = dict.begin();
    DictionaryI e = dict.end();
    vector<DictionaryI> one_ref_text;
    while(i != e){
        if(i->second > 1)
            out << i->second << " " << i->first << "\r\n";
        else
            one_ref_text.push_back(i);
        i++;
    }

    for(const DictionaryI& o : one_ref_text)
        out << o->second << " " << o->first << "\r\n";

    return error;
}

