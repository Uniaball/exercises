#include "include.h"
using namespace std;
void wrap::staticLib(){
    vector<string> fileNameList;
    int num;
    cout << "需要打包的文件个数：";
    cin >> num;
    cin.ignore();
    string fileName;
    cout << "源文件名称：" << endl;
    for (int i = 0;i < num;i++){
        cin >> fileName;
        fileNameList.push_back(fileName);
    }
    string fileNames;
    for (int i = 0;i < fileNameList.size();i++){
        fileNames += " " + fileNameList[i];
    }

    string version;
    string command;
    cout << "输入语言版本（输入：11或其他版本，输入“默认”即为默认版本，不要输入奇怪的东西）" << endl;
    cin >> version;
    if (version == "默认"){
        command = "g++ -c " + fileNames;
    }
    else{
        command = "g++ -c " + fileNames + " -std=c++" + version;
    }
    system(command.c_str());

    string suffix = ".cpp";
    size_t suffix_length = suffix.length();
    for (auto& file : fileNameList){
        if (file.ends_with(suffix)){
            file.erase(file.size() - suffix_length);
        }
    }

    string libName;
    cout << "输入库的名称" << endl;
    cin >> libName;
    
    string o_fileNames;
    for (int i = 0;i < fileNameList.size();i++){
        o_fileNames += " " + fileNameList[i] + ".o";
    }
    string command2 = "ar rcs " + libName + o_fileNames;
    system(command2.c_str());
}

void wrap::dynamicLib(){
    vector<string> fileNameList;
    int num;
    cout << "需要打包的文件个数：";
    cin >> num;
    cin.ignore();
    string fileName;
    cout << "源文件名称：" << endl;
    for (int i = 0;i < num;i++){
        cin >> fileName;
        fileNameList.push_back(fileName);
    }
    string fileNames;
    for (int i = 0;i < fileNameList.size();i++){
        fileNames += " " + fileNameList[i];
    }

    string version;
    string command;
    cout << "输入语言版本（输入：11或其他版本，输入“默认”即为默认版本，不要输入奇怪的东西）" << endl;
    cin >> version;
    if (version == "默认"){
        command = "g++ -fPIC -c " + fileNames;
    }
    else{
        command = "g++ -fPIC -c " + fileNames + " -std=c++" + version;
    }
    system(command.c_str());

    string suffix = ".cpp";
    size_t suffix_length = suffix.length();
    for (auto& file : fileNameList){
        if (file.ends_with(suffix)){
            file.erase(file.size() - suffix_length);
        }
    }

    string libName;
    cout << "输入库的名称" << endl;
    cin >> libName;
    
    string o_fileNames;
    for (int i = 0;i < fileNameList.size();i++){
        o_fileNames += " " + fileNameList[i] + ".o";
    }

    string command2 = "g++ -shared -o " + libName + o_fileNames;
    system(command2.c_str());
}

void wrap::cpp(){
    again:
    short input;
    cout << "你要打包什么库（1：静态库 2：动态库）" << endl;
    cin >> input;
    switch (input){
    case 1:{
        wrap::staticLib();
        break;
    }
    case 2:{
        wrap::dynamicLib();
        break;
    }
    default:{
        system("clear");
        goto again;
    }
    }
}


void wrap::c_staticLib(){
    vector<string> fileNameList;
    int num;
    cout << "需要打包的文件个数：";
    cin >> num;
    cin.ignore();
    string fileName;
    cout << "源文件名称：" << endl;
    for (int i = 0;i < num;i++){
        cin >> fileName;
        fileNameList.push_back(fileName);
    }
    string fileNames;
    for (int i = 0;i < fileNameList.size();i++){
        fileNames += " " + fileNameList[i];
    }
    
    string version;
    string command;
    cout << "输入语言版本（输入：11或其他版本，输入“默认”即为默认版本，不要输入奇怪的东西）" << endl;
    cin >> version;
    if (version == "默认"){
        command = "gcc -c " + fileNames;
    }
    else{
        command = "gcc -c " + fileNames + " -std=c" + version;
    }
    system(command.c_str());

    string suffix = ".c";
    size_t suffix_length = suffix.length();
    for (auto& file : fileNameList){
        if (file.ends_with(suffix)){
            file.erase(file.size() - suffix_length);
        }
    }

    string libName;
    cout << "输入库的名称" << endl;
    cin >> libName;
    
    string o_fileNames;
    for (int i = 0;i < fileNameList.size();i++){
        o_fileNames += " " + fileNameList[i] + ".o";
    }

    string command2 = "ar rcs " + libName + o_fileNames;
    system(command2.c_str());
}

void wrap::c_dynamicLib(){
    vector<string> fileNameList;
    int num;
    cout << "需要打包的文件个数：";
    cin >> num;
    cin.ignore();
    string fileName;
    cout << "源文件名称：" << endl;
    for (int i = 0;i < num;i++){
        cin >> fileName;
        fileNameList.push_back(fileName);
    }
    string fileNames;
    for (int i = 0;i < fileNameList.size();i++){
        fileNames += " " + fileNameList[i];
    }
    
    string version;
    string command;
    cout << "输入语言版本（输入：11或其他版本，输入“默认”即为默认版本，不要输入奇怪的东西）" << endl;
    cin >> version;
    if (version == "默认"){
        command = "gcc -fPIC -c " + fileNames;
    }
    else{
        command = "gcc -fPIC -c " + fileNames + " -std=c" + version;
    }
    system(command.c_str());

    string suffix = ".c";
    size_t suffix_length = suffix.length();
    for (auto& file : fileNameList){
        if (file.ends_with(suffix)){
            file.erase(file.size() - suffix_length);
        }
    }

    string libName;
    cout << "输入库的名称" << endl;
    cin >> libName;
    
    string o_fileNames;
    for (int i = 0;i < fileNameList.size();i++){
        o_fileNames += " " + fileNameList[i] + ".o";
    }

    string command2 = "gcc -shared -o " + libName + o_fileNames;
    system(command2.c_str());
}

void wrap::c(){
    again:
    short input;
    cout << "你要打包什么库（1：静态库 2：动态库）" << endl;
    cin >> input;
    switch (input){
    case 1:{
        c_staticLib();
        break;
    }
    case 2:{
        c_dynamicLib();
        break;
    }
    default:{
        system("clear");
        goto again;
    }
    }
}