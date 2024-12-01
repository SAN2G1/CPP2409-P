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
string Caesar(const string& , int);
void WriteDiary(format *);
bool ExistsFile(const string& );
vector<string> FileList();
void RemoveDiary(string);
void SaveEdit(string , string, int);
void EditText(string);
string GetLine (string , int);
string EditLine(string);
void EditTag(string file_name);
