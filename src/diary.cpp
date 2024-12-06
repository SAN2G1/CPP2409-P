#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <filesystem>
#include <conio.h>
#include <cstdio>
#include "diary.h"
using namespace std;

namespace fs = std::filesystem;
const string save_directory = "2024_diary\\";
string GetCurrentDate()
{ // 날짜만
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);

    return string(buffer);
}
string GetCurrentdate_time()
{ // 날짜랑 시간까지
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);

    return string(buffer);
}
// 일기는 카이사르암호로 암호화 된다.
string Caesar(const string &plaintext, int key)
{
    string encrypted = plaintext;
    const string special_chars = "!@#$%^&*()"; // 사용할 수 있는 특수문자

    for (char &c : encrypted)
    {
        if (isalpha(c))
        {
            char base = islower(c) ? 'a' : 'A';
            c = static_cast<char>((c - base + key) % 26 + base); // cpp style 명시적 형변환
        }
        else if (isdigit(c))
        {
            c = static_cast<char>(((c - '0' + key) % 10) + '0');
        }
        else
        {
            auto pos = special_chars.find(c); // find메소드는 검색 위치의 인덱스를 반환하고 검색이 실패하면 npos를 리턴
            if (pos != string::npos)
            { //  string::npos 로 정의되는 상수
                c = special_chars[(pos + key) % special_chars.size()];
            }
        }
    }
    return encrypted;
}
bool ExistsFile(const string &file_name)
{
    return fs::exists(file_name); //(변경) 파일이 존재하면 true, 아니면 false
}

void WriteDiary(format *diary_format)
{
    string date_time = GetCurrentdate_time();
    string file_name = save_directory + "diary_" + GetCurrentDate() + ".txt"; // 일기 제목의 형식
    int counter = 1;
    while (ExistsFile(file_name))
    {
        file_name = save_directory + "diary_" + GetCurrentDate() + "_" + std::to_string(counter++) + ".txt";
    }
    ofstream diary_file(file_name, ios::app);

    if (diary_file.is_open())
    {
        diary_file << "tags: " << diary_format->tag << endl;
        diary_file << "-------------------------\n";
        diary_file << "Date & Time: " << date_time << endl;
        diary_file << "Content: " << diary_format->str_content << endl;
        diary_file << "-------------------------\n";
        diary_file.close();
        cout << "Diary entry saved successfully to " << file_name << "!" << endl;
    }
    else
    {
        cerr << "Unable to open the diary file for writing." << endl;
    }
}
vector<string> FileList()
{
    vector<string> file_list;
    fs::directory_iterator itr(fs::current_path() / save_directory);
    while (itr != fs::end(itr))
    {
        const fs::directory_entry &entry = *itr;
        file_list.push_back(entry.path().filename().string());
        itr++;
    }
    return file_list;
}
// 존재하는 file_name임을 가정
void RemoveDiary(string file_name)
{

    fs::remove(file_name);
}
//  수정된 파일을 저장하는 함수
// 0 -> 태그 , 2-> 날짜 , 3-> 내용
void SaveEdit(string file_name, string edit_line, int idx)
{
    // 파일 읽기
    ifstream file(file_name);
    vector<string> lines;
    string line = "";

    // 파일 내용을 벡터에 저장
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();

    // 기존 줄을 ':' 이후에 새로운 내용으로 편집
    line = lines[idx].substr(0, lines[idx].find(':') + 1); // ':'까지 자름
    lines[idx] = line + edit_line;

    // 파일 쓰기
    ofstream out_file(file_name, ios::out);
    for (const string &line : lines)
    {
        out_file << line << endl;
    }
    out_file.close();
}
// 일기에서 한줄 읽어와 ': '를 기준으로 자르고 내용물만 반환해주는 함수
// 0 -> 태그 , 2-> 날짜 , 3-> 내용
string GetLine(string file_name, int idx)
{
    ifstream file(file_name);
    vector<string> lines;
    string line = "";
    // 일기 내용을 읽어와 저장
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();
    line = lines[idx].substr(lines[idx].find(':') + 1); // ':'옆 공백 포함해서 자른다.
    return line;
}
// file_name의 유효성은 caller인 main함수에서 진행
// 일기 내용을 수정하는 함수
void EditText(string file_name)
{
    string line = "";
    // 일기 내용을 읽어와 저장
    line = GetLine(file_name, 3); // 일기 내용
    cout << "일기를 수정하세요! (Enetr을 누르면 종료!)" << endl;
    line = EditLine(line);
    SaveEdit(file_name, line, 3);
    cout << "completed" << endl;
}
// 태그를 수정하는 함수
void EditTag(string file_name)
{
    string line = "";
    // 일기 내용을 읽어와 저장
    line = GetLine(file_name, 0); // 태그
    cout << "태그를 수정하세요! (Enetr을 누르면 종료!)" << endl;
    line = EditLine(line);
    SaveEdit(file_name, line, 0);
    cout << "completed" << endl;
}
// string 한줄을 편집하여 반환하는 함수
string EditLine(string line)
{
    unsigned char ch;
    int cursor_point = line.size(); // 커서 끝을 문장 끝으로 설정.
    cout << line;
    cout.flush();
    while (true)
    {
        ch = _getch();
        if (ch == '\r')
            break;
        else if (ch == 8)
        { // 8은 backspace를 뜻한다.

            // erase(size_type index = 0, size_type count = npos);
            line.erase(cursor_point - 1, 1);
            cursor_point--;
        }
        else if (ch == 224)
        {                  // 화살표 키를 입력 받는다. 이때 필요인수는 2개다
            ch = _getch(); // 추가 입력 처리
            if (ch == 75 && cursor_point > 0)
                cursor_point--;
            else if (ch == 77 && cursor_point < line.size())
                cursor_point++;
        }
        else
        {
            line.insert(line.begin() + cursor_point, ch); // iterator insert(iterator pos, char ch);
            cursor_point++;
        }
        cout << string(line.size(), ' '); // 현재 줄 지우기
        cout << "\r";                     // 다시 줄 처음으로 이동
        cout << line;                     // 현재 상태 출력
        cout.flush();
    }
    return line;
}

bsTree* GetSearchTree()
{
    bsTree *root = nullptr;
    vector<string> lists = FileList();
    vector< fdata> list_data ;
    for (string list : lists)
    {   
        fdata fdata;
        fdata.file_name=list;
        sscanf(list.c_str(), "diary_%d-%d-%d", &fdata.year, &fdata.month, &fdata.day);
        list_data.push_back(fdata);
    }

    for(fdata fdata: list_data){
        root = insert(fdata, root);
    }
    return root;
}