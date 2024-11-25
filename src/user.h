#pragma once
#include<iostream>
#include<string>
using namespace std;

class MyDiary
{
    private :
    string my_password ;
    string my_name; 
    int my_key;

    public :
    MyDiary(string name = "None", string password = "0000", int key = 0){
        my_name = name;
        my_password = password;
        my_key = key ;
    }
    bool check_login(string input_PW) ;
    int get_key() ;
    string get_name();
};
