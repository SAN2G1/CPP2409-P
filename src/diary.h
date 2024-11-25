#pragma once
#include <string>


using namespace std;
typedef struct format {
    string tag ;
    string str_content;

}format ;

string GetCurrentDate();
string GetCurrentDateTime();
string Caesar(const string& plaintext, int key);
void WriteDiary(format * diary_format);
bool ExistsFile(const std::string& fileName);