#include"user.h"

bool MyDiary::check_login(string input_PW){
    if (my_password == input_PW) return true;
    else return false;
}
  
int MyDiary::get_key(){
    return my_key;
}

string MyDiary::get_name(){
    return my_name;
}