#ifndef TEXTANALYZER_H
#define TEXTANALYZER_H
#include <string>

class TextAnalyzer
{
    std::string inf;
    std::string outf;

public:

    enum ErrorState{
        No_Error=0,
        Error_open_in_file,
        Error_open_out_file,
        Error_console_args
    };

    ErrorState error=No_Error;

    ErrorState initFromArguments(int argc, char *argv[]){
        return readConsole(argc, argv, inf, outf);
    }

    void init(const std::string& _inf, const std::string& _outf){
        inf = _inf; outf = _outf;
    }

    ErrorState analyze();
private:
    ErrorState readConsole(int argc, char *argv[], std::string &in, std::string &out);
};

#endif // TEXTANALYZER_H
