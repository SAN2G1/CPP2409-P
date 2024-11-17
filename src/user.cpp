#include"user.h"

bool My_diary::check_login(string inputPass){
    if (my_password == inputPass) return true;
    else return false;
}
  
int My_diary::get_key(){
    return my_key;
}

string My_diary::get_name(){
    return my_name;
}