#include <iostream>
#include <exception>
#include "user.h"
#include "diary.h"
using namespace std;
// 사용자 정의 예외 클래스
class NullPointerException : public exception {
public:
    const char* what() const noexcept override {
        return "File list is NULL";
    }
};
void PrintMain();
void PrintMenu();
bool IsYes();

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
        cin >> get_num;
        if (get_num > 0 && get_num < 6)
        {
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
                try
                {
                    bsTree *root = GetSearchTree();
                    // 폴더에 일기가 없으면 예외를 던진다.
                    if(root == nullptr) throw NullPointerException(); 
                    cout<<"complete"<<endl;
                }
                catch(const NullPointerException& e){
                    cout << "empty file list : "<< e.what()<<endl;
                    continue;
                }

    
            }
            else if (get_num == 5)
            {
                PrintMain();
                cout << "END END END END END";

                return 0;
            }
            else
            {
                cout << "indexErr";
                return 0;
            }
        }
        else
            cout << "Please input (1~5)" << endl;
    }

    return 0;
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
    cout << "5. Exit" << endl;
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