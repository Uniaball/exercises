#include "include.h"
using namespace std;
static void main_compile(){
    again:
    short lang;
    cout << "你要编译什么语言（1：C++ 2：C语言）" << endl;
    cin >> lang;
    if (lang == 1){
        compile::cpp();
    }
    else if (lang == 2){
        compile::c();
    }
    else {
        system("clear");
        goto again;
    }
}
static void main_wrap(){
    again:
    short lang;
    cout << "你要打包什么语言（1：C++ 2：C语言）" << endl;
    cin >> lang;
    if (lang == 1){
        wrap::cpp();
    }
    else if (lang == 2){
        wrap::c();
    }
    else {
        system("clear");
        goto again;
    }
}
int main(){
    again:
    short input;
    cout << "选择要执行的操作" << endl;
    cout << "1：编译" << endl;
    cout << "2：打包" << endl;
    cout << "3：注意事项" << endl;
    cin >> input;
    switch(input){
        case 1:{
            main_compile();
            break;
        }
        case 2:{
            main_wrap();
            break;
        }
        case 3:{
            if (!help()){
                system("clear");
                goto again;
            }
            break;
        }
        default:{
            system("clear");
            goto again;
        }
    }
}