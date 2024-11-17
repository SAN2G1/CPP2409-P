#include<iostream>
#include<string>
using namespace std;

class My_diary
{
    private :
    string my_password ;
    string my_name; 
    int my_key;

    public :
    My_diary(string name = "None", string passwd = "0000", int key = 0){
        my_name = name;
        my_password = passwd;
        my_key = key ;
    }
    bool check_login(string inputPass) ;
    int get_key() ;
    string get_name();
};
