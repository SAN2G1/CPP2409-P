#include <iostream>
#include <exception>
#include <limits> // numeric_limits가 정의된 헤더

#include "user.h"
#include "diary.h"
using namespace std;
// 사용자 정의 예외 클래스
class NullPointerException : public exception
{
public:
    const char *what() const noexcept override
    {
        return "File list is NULL";
    }
};
class OutOfOption : public exception
{
public:
    const char *what() const noexcept override
    {
        return "It's out of range";
    }
};
void PrintMain();
void PrintMenu();
bool IsYes();
void DateInputHandler(bsTree *);
void PrintResult(const vector<string> &);
int main()
{
    MyDiary admin("admin", "1234", 4);
    string password = "";
    while (1)
    { // 로그인 화면
        PrintMain();
        cout << "If you want to exit, please enter the password 'exit'." << endl;
        cout << "Please enter password >> ";
        cin >> password;
        if (password == "exit")
        { // 종료 여부를 검사한다.
            cout << "Exit my diary";
            return 0;
        }
        if (admin.check_login(password))
            break; // 유저의 페스워드가 맞으면 다음 화면으로 넘어간다.
        else
            cout << "Incorrect password" << endl;
    }

    int get_num = 0;
    while (1)
    {
        PrintMenu(); // menu를 프린트한다.
        cout << "HELLO " << admin.get_name() << ". Have a nice day." << endl;
        cout << "Select Number >> ";
        try
        {
            cin >> get_num;
            if (cin.fail())
                throw OutOfOption();

            if (get_num == 1)
            { // write
                format this_diary = {"", ""};
                // 일기 작성
                cin.ignore();
                cout << "WRITE : ";
                getline(cin, this_diary.str_content);
                // tag 추가
                cout << "tag (whitespace-separated) :";
                getline(cin, this_diary.tag);
                if (this_diary.tag == "" || this_diary.tag == "\n")
                    this_diary.tag = "NONE";
                // 일기 암호화 여부
                cout << "Would you like to encrypt the diary content? ";
                if (IsYes())
                { // 대답이 yes면 내용을 암호화 시킨다.
                    this_diary.str_content = Caesar(this_diary.str_content, admin.get_key());
                }
                WriteDiary(&this_diary);
            }
            else if (get_num == 2)
            {
                vector<string> file_list = FileList();
                int i = 0;
                string rm_file = "";
                cout << "FILE LIST : " << endl;
                for (string file_name : file_list)
                {
                    cout << "[" << ++i << "] : " << file_name << std::endl;
                }
                cout << endl;
                cout << "Which files should be removed? " << endl;
                cout << "If you enter \"No\" nothing will be removed :";
                cin >> rm_file;
                rm_file = save_directory + rm_file;
                while (!ExistsFile(rm_file))
                {
                    if (rm_file == save_directory + "No")
                        break;
                    cout << "Please enter the correct file name :";
                    cin >> rm_file;
                    rm_file = save_directory + rm_file;
                }
                if (rm_file == save_directory + "No")
                    continue;
                cout << "Are you sure you want to delete [" << rm_file << "] file? : " << endl;
                if (IsYes())
                    RemoveDiary(rm_file);
                else
                    continue;
                cout << "REMOVED!!!!" << endl;
            }
            else if (get_num == 3)
            {
                string file_name = "";
                vector<string> file_list = FileList();
                int i = 0;
                string edit_file = "";
                cout << "FILE LIST : " << endl;
                for (string file_name : file_list)
                {
                    cout << "[" << ++i << "] : " << file_name << std::endl;
                }
                cout << endl;
                cout << "Which files should be changed? " << endl;
                cout << "If you enter \"No\" nothing will be edited :";
                cin >> edit_file;
                edit_file = save_directory + edit_file;
                while (!ExistsFile(edit_file))
                {
                    if (edit_file == save_directory + "No")
                        break;
                    cout << "Please enter the correct file name :";
                    cin >> edit_file;
                    edit_file = save_directory + edit_file;
                }
                if (edit_file == save_directory + "No")
                    continue;
                int input = 0;
                cout << "Which should I modify, tag (1) or diary (2):";
                cin >> input;
                while (true)
                {
                    if (input == 1)
                    {
                        EditTag(edit_file);
                        break;
                    }
                    else if (input == 2)
                    {
                        EditText(edit_file);
                        break;
                    }
                    else
                    {
                        cout << "1과 2중 하나로만 입력해주세요";
                        cin >> input;
                    }
                }
            }
            else if (get_num == 4)
            {
                cout << "Searching" << endl;

                bsTree *root = GetSearchTree();
                // 폴더에 일기가 없으면 예외를 던진다.
                if (root == nullptr)
                    throw NullPointerException();
                cout << "complete" << endl;

                string choice;
                cout << "day or tag : ";
                cin >> choice;
                if (choice == "day")
                {
                    DateInputHandler(root);
                }
                else if (choice == "tag")
                {
                    PrintAllTags(BuildTagFileMap());
                }
                else
                    cout << "Invalid input." << endl;
                if (root != nullptr)
                {
                    DeleteTree(root);
                    root = nullptr;
                }
            }
            else if (get_num == 5)
            {
                string select;
                string file_name;
                cout << "Encryption OR Decryption FILE!!!" << endl;
                cout << "Please input \"enc\" or \"dec\" >> ";
                cin >> select;
                if (select == "enc")
                {
                    cout << "Input file name : ";
                    cin >> file_name;
                    file_name = save_directory + file_name;
                    if (!ExistsFile(file_name))
                    {
                        cout << file_name << " does not exist" << endl;
                        continue;
                    }
                    string context = GetLine(file_name, 3);
                    string enc_text = Caesar(context, admin.get_key());
                    SaveEdit(file_name, enc_text, 3);
                    cout << "it's completed" << endl;
                }
                else if (select == "dec")
                {
                    cout << "Input file name : ";
                    cin >> file_name;
                    file_name = save_directory + file_name;
                    if (!ExistsFile(file_name))
                    {
                        cout << file_name << " does not exist" << endl;
                        continue;
                    }
                    string enc_text = GetLine(file_name, 3);
                    string dec_text = Caesar(enc_text, -(admin.get_key()));
                    SaveEdit(file_name, dec_text, 3);
                    cout << "it's completed" << endl;
                }
                else
                    throw OutOfOption();
            }
            else if (get_num == 6)
            {
                PrintMain();
                cout << "END END END END END";

                return 0;
            }
            else
            {
                throw OutOfOption();
            }
        }
        catch (const NullPointerException &e)
        {
            cout << "empty file list : " << e.what() << endl;
            continue;
        }
        catch (const OutOfOption &e)
        {
            cout << "Not in the options : " << e.what() << endl;
            cin.clear();                                         // 스트림 상태 플래그 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 잘못된 입력 비우기
            continue;                                            // 메뉴 다시 출력
        }
    }
    // 입력 버퍼 초기화
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return 0;
}
void DateInputHandler(bsTree *root)
{
    int year = -1, month = -1, day = -1;

    cout << "Enter year: ";
    cin >> year;

    cout << "Enter month (or -1 to skip): ";
    cin >> month;

    cout << "Enter day (or -1 to skip): ";
    cin >> day;
    vector<string> result;
    // 입력값에 따라 함수 호출
    if (month == -1)
    {
        result = Search(year, root); // 년도만 입력
        PrintResult(result);
    }
    else if (day == -1)
    {
        result = Search(year, month, root); // 년도와 월 입력
        PrintResult(result);
    }
    else
    {
        result = Search(year, month, day, root); // 년도, 월, 일 모두 입력
        PrintResult(result);
    }
}
// 결과를 출력하는 함수(스트링 벡터)
void PrintResult(const vector<string> &results)
{
    if (results.empty())
    {
        cout << "No results found." << endl;
    }
    else
    {
        cout << "Results:" << endl;
        for (const string &result : results)
        {
            cout << result << endl;
        }
    }
}

void PrintMain()
{
    cout << "\n\n";
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    cout << "       ###       ###   ##      ##   ########     ########       ####        #######     ##      ##" << endl;
    cout << "       ## #     # ##    ##    ##    ##     ##       ##         ##  ##       ##    ##     ##    ##" << endl;
    cout << "       ##  #   #  ##     ##  ##     ##      ##      ##        ##    ##      #######       ##  ##" << endl;
    cout << "       ##   # #   ##      ##        ##     ##       ##       ## #### ##     ##    ##       ##" << endl;
    cout << "       ##    #    ##      ##        ########     ########   ##        ##    ##     ##      ##" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;
}
void PrintMenu()
{
    cout << "\n\n";
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    cout << "1. Write a diary" << endl;
    cout << "2. Delete a diary" << endl;
    cout << "3. Edit a diary" << endl;
    cout << "4. Search a diary" << endl;
    cout << "5. Encryption OR Decryption" << endl;
    cout << "6. Exit" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;
}

bool IsYes()
{
    char choice;
    while (1)
    {
        cout << "Please answer y(yes) or n(no) : ";
        cin >> choice;
        if (choice == 'y')
            return true;
        else if (choice == 'n')
            return false;
    }
}