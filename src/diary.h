#pragma once
#include <string>
#include <vector>
using namespace std;
extern const string save_directory; 
typedef struct format {
    string tag ;
    string str_content;

}format ;

string GetCurrentDate();
string GetCurrentDateTime();
string Caesar(const string& plaintext, int key);
void WriteDiary(format * diary_format);
bool ExistsFile(const std::string& file_name);
vector<string> FileList();
void RemoveDiary(std::string file_name);