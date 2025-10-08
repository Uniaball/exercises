#include "include.h"

void compile::cpp(){
    vector<string> fileNameList;
    int num;
    cout << "需要编译的文件个数：";
    cin >> num;
    cin.ignore();
    string fileName;
    cout << "源文件名称：" << endl;
    for (int i = 0;i < num;i++){
        cin >> fileName;
        fileNameList.push_back(fileName);
    }
    string fileNames;
    for (int a = 0;a < fileNameList.size();a++){
        fileNames += " " + fileNameList[a];
    }
    string appName;
    cout << "输入程序名：";
    cin >> appName;
    
    string version;
    string command;
    cout << "输入语言版本（输入：11或其他版本，输入“默认”即为默认版本，不要输入奇怪的东西）" << endl;
    cin >> version;
    if (version == "默认"){
        command = "g++" + fileNames + " " + "-o " + appName;
    }
    else {
        command = "g++" + fileNames + " " + "-o " + appName + " -std=c++" + version;
    }
    system(command.c_str());
}
void compile::c(){
    vector<string> fileNameList;
    int num;
    cout << "需要编译的文件个数：";
    cin >> num;
    cin.ignore();
    string fileName;
    cout << "源文件名称" << endl;
    for (int i = 0;i < num;i++){
        cin >> fileName;
        fileNameList.push_back(fileName);
    }
    string fileNames;
    for (int a = 0;a < fileNameList.size();a++){
        fileNames += " " + fileNameList[a];
    }
    string appName;
    cout << "输入程序名：";
    cin >> appName;

    string version;
    string command;
    cout << "输入语言版本（输入：11或其他版本，输入“默认”即为默认版本，不要输入奇怪的东西）" << endl;
    cin >> version;
    if (version == "默认"){
        command = "gcc" + fileNames + " " + "-o " + appName;
    }
    else {
        command = "gcc" + fileNames + " " + "-o " + appName + " -std=c" + version;
    }
    system(command.c_str());
}