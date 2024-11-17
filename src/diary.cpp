#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "diary.h"
using namespace std;

string getCurrentDate() { // 날짜만
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);

    return string(buffer);
}
string getCurrentDateTime() { // 날짜랑 시간까지
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);

    return string(buffer);
}
// 일기는 카이사르암호로 암호화 된다.
string caesar(const string& plaintext, int key) {
    string encrypted = plaintext;
    const string specialChars = "!@#$%^&*()";  //사용할 수 있는 특수문자

    for (char& c : encrypted) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = static_cast<char>((c - base + key) % 26 + base); // cpp style 명시적 형변환
        } else if (isdigit(c)) {
            c = static_cast<char>(((c - '0' + key) % 10) + '0');
        } else {
            auto pos = specialChars.find(c); //find메소드는 검색 위치의 인덱스를 반환하고 검색이 실패하면 npos를 리턴
            if (pos != string::npos) {  //  string::npos 로 정의되는 상수
                c = specialChars[(pos + key) % specialChars.size()]; 
            }
        }
    }
    return encrypted;
}
bool fileExists(const string& fileName) { // 파일이 존재하는지 검색하는 함수
    ifstream file(fileName);
    return file.good(); //정상적으로 파일이 열리면 true를 반환...
}

void writediary(format * diaryFormat) {
    string dateTime = getCurrentDateTime();
    string fileName = "2024_diary/diary_" + getCurrentDate() + ".txt"; //일기 제목의 형식
    int counter = 1;
    while (fileExists(fileName)) {
        fileName = "2024_diary/diary_" + getCurrentDate() + "_" + std::to_string(counter++) + ".txt";
    }
    ofstream diaryFile(fileName, ios::app);

    if (diaryFile.is_open()) {
        diaryFile << "tags: " << diaryFormat -> tag << endl;
        diaryFile << "-------------------------\n";
        diaryFile << "Date & Time: " << dateTime << endl;
        diaryFile << "Content: " << diaryFormat -> strContent << endl;
        diaryFile << "-------------------------\n";
        diaryFile.close();
        cout << "Diary entry saved successfully to " << fileName << "!" << endl;
    } else {
        cerr << "Unable to open the diary file for writing." << endl;
    }
}