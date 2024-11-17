#include <iostream>
#include "user.h"
#include "diary.h"
using namespace std;
void print_main();
void print_menu();
bool yn_choice();

int main()
{
    My_diary admin("admin", "1234", 4);
    string passwd = "";
    while (1)
    { // 로그인 화면
        print_main();
        cout << "If you want to exit, please enter the password 'exit'." << endl;
        cout << "Please enter password >> ";
        cin >> passwd;
        if (passwd == "exit")
        { // 종료 여부를 검사한다.
            cout << "Exit my diary";
            return 0;
        }
        if (admin.check_login(passwd))
            break; // 유저의 페스워드가 맞으면 다음 화면으로 넘어간다.
        else
            cout << "Incorrect password" << endl;
    }

    int get_num = 0;
    while (1)
    {
        print_menu(); // menu를 프린트한다.
        cout << "HELLO " << admin.get_name() << ". Have a nice day." << endl;
        cout << "Select Number >> " ;
        cin >> get_num ;
        if (get_num > 0 && get_num < 6) {
            if(get_num == 1) { // write
                format this_diary = {"",""};
                // 일기 작성
                cin.ignore();
                cout << "WRITE : " ;
                getline(cin, this_diary.strContent);
                // tag 추가
                cout << "tag (whitespace-separated) :" ;
                getline(cin, this_diary.tag);
                if(this_diary.tag == "" || this_diary.tag == "\n" ) this_diary.tag = "NONE";
                // 일기 암호화 여부
                cout << "Would you like to encrypt the diary content? " ;
                if(yn_choice()) { // 대답이 yes면 내용을 암호화 시킨다.
                this_diary.strContent = caesar(this_diary.strContent, admin.get_key());
                } 
                writediary(&this_diary);
            }
            else if(get_num == 2) {

            }
            else if(get_num == 3){

            }
            else if(get_num == 4){

            }
            else if(get_num == 5){
                print_main();
                cout << "END END END END END";

                return 0;

            }
            else {cout<<"indexErr" ; return 0;}
            
        }
        else cout << "Please input (1~5)" << endl; 

    }

    return 0;
}

void print_main()
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
void print_menu(){
    cout << "\n\n";
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    cout << "1. Write a diary" << endl;
    cout << "2. Delete a diary" << endl;
    cout << "3. Edit a diary" << endl ;
    cout << "4. Search a diary" <<endl;
    cout << "5. Exit" << endl ;
    cout << "---------------------------------------------------------------------------------------------------" << endl;

}

bool yn_choice(){
    char choice ;
    while(1){
    cout << "Please answer y(yes) or n(no) : " ;
    cin >> choice;
    if(choice == 'y') return true;
    else if(choice == 'n') return false;

    }
}