#include "include.h"
using namespace std;
bool help(){
    cout << "注意事项：" << endl;
    cout << "1.编译和打包时源文件不能有空格（中文可以）" << endl;
    cout << "2.不要在要求输入时进行一些作死行为（如将文件名写成格机指令）" << endl;
    cout << "3.文件拓展名只能为.cpp或.c，不要搞一些奇怪的东西进来" << endl;
    cout << "4.库拓展名最好为.a或.so，否则后果自负" << endl;
    cout << "5.需要先自行下载gcc和g++，不然无法构建" << endl;
    cout << "6.进行打包和编译时请将本程序置于源代码相同目录中" << endl;
    cout << "7.文件名最好不要带有路径" << endl;
    cout << "8.本程序对非程序以外的报错不作任何处理，请自己想办法解决" << endl;
    again:
    short input;
    cout << "输入0退出" << endl;
    cin >> input;
    if (input == 0){
        return 0;
    }
    else
        goto again;
}