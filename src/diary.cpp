#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "diary.h"
using namespace std;

string GetCurrentDate() { // 날짜만
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);

    return string(buffer);
}
string GetCurrentdate_time() { // 날짜랑 시간까지
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);

    return string(buffer);
}
// 일기는 카이사르암호로 암호화 된다.
string Caesar(const string& plaintext, int key) {
    string encrypted = plaintext;
    const string special_chars = "!@#$%^&*()";  //사용할 수 있는 특수문자

    for (char& c : encrypted) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = static_cast<char>((c - base + key) % 26 + base); // cpp style 명시적 형변환
        } else if (isdigit(c)) {
            c = static_cast<char>(((c - '0' + key) % 10) + '0');
        } else {
            auto pos = special_chars.find(c); //find메소드는 검색 위치의 인덱스를 반환하고 검색이 실패하면 npos를 리턴
            if (pos != string::npos) {  //  string::npos 로 정의되는 상수
                c = special_chars[(pos + key) % special_chars.size()]; 
            }
        }
    }
    return encrypted;
}
bool ExistsFile(const string& file_name) { // 파일이 존재하는지 검색하는 함수
    ifstream file(file_name);
    return file.good(); //정상적 으로 파일이 열리면 true를 반환...
}

void WriteDiary(format * diary_format) {
    string date_time = GetCurrentdate_time();
    string file_name = "2024_diary/diary_" + GetCurrentDate() + ".txt"; //일기 제목의 형식
    int counter = 1;
    while (ExistsFile(file_name)) {
        file_name = "2024_diary/diary_" + GetCurrentDate() + "_" + std::to_string(counter++) + ".txt";
    }
    ofstream diary_file(file_name, ios::app);

    if (diary_file.is_open()) {
        diary_file << "tags: " << diary_format -> tag << endl;
        diary_file << "-------------------------\n";
        diary_file << "Date & Time: " << date_time << endl;
        diary_file << "Content: " << diary_format -> str_content << endl;
        diary_file << "-------------------------\n";
        diary_file.close();
        cout << "Diary entry saved successfully to " << file_name << "!" << endl;
    } else {
        cerr << "Unable to open the diary file for writing." << endl;
    }
}