#include <iostream>
#include <textanalyzer.h>

using namespace std;

int main(int argc, char *argv[])
{
    TextAnalyzer analyzer;
    if(analyzer.initFromArguments(argc, argv) == TextAnalyzer::Error_console_args)
    {
        cout << "Not correct parameters.\n"
                "Use follow parameters:\n"
                "[-i] input file name\n"
                "[-o] output file name\n";
    }
    switch (analyzer.analyze()) {
    case TextAnalyzer::Error_open_in_file:
        cout << "Cannot open input file.\n";
        break;
    case TextAnalyzer::Error_open_out_file:
        cout << "Cannot open output file.\n";
        break;
    default:
        cout << "done.";
        break;
    }

    return 0;
}

