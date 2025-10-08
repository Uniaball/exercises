#include "include.h"
#include <fstream>
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
static void main_cmake(){
    again:
    string receiveMakeFileReturnValue;
    string appName;
    again1:
    short input;
    cout << "选择要执行的操作" << endl;
    cout << "1：生成CMakeLists.txt" << endl;
    cout << "2：生成构建文件" << endl;
    cout << "3：构建" << endl;
    cin >> input;
    system("clear");
    switch(input){
        case 1:{
            if (!writeCMakeLists_project()){
                writeCMakeLists_langVersion(false);
                appName = writeCMakeLists_addExecutable();
            }
            else {
                writeCMakeLists_langVersion(true);
                appName = writeCMakeLists_addExecutable();
            }
            goto again1;
            break;
        }
        case 2:{
            ifstream checkCMakeLists("CMakeLists.txt", ios::in);
            if (!checkCMakeLists.is_open()){
                cout << "还没有创建CMakeLists！" << endl;
                goto again;
            }
            checkCMakeLists.close();
            receiveMakeFileReturnValue = makeFile();
            goto again1;
            break;
        }
        case 3:{
            if (receiveMakeFileReturnValue.empty()){
                cout << "还没有生成构建文件！" << endl;
            }
            else{
                build(receiveMakeFileReturnValue, appName);
            }
            break;
        }
        default:{
            goto again;
        }
    }
}
int main(){
    again:
    short input;
    cout << "选择要执行的操作" << endl;
    cout << "1：编译" << endl;
    cout << "2：打包" << endl;
    cout << "3：使用CMake构建项目" << endl;
    cout << "4：注意事项" << endl;
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
            system("clear");
            main_cmake();
            break;
        }
        case 4:{
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