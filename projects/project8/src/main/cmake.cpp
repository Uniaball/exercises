#include "include.h"
#include <fstream>

bool writeCMakeLists_project(){
    string projectName;
    string cmakeMinimumRequired;
    cout << "输入项目名称：";
    cin >> projectName;

    cout << "输入要求的CMake最低版本（输入0则默认为3.10）" << endl;
    cin >> cmakeMinimumRequired;
    if (cmakeMinimumRequired == "0"){
        cmakeMinimumRequired = "3.10";
    }
    ofstream write("CMakeLists.txt", ios::out);
    write << "cmake_minimum_required(VERSION " << cmakeMinimumRequired << ")" << endl;
    write << "\n";
    write << "project(" << projectName << endl;

    again:
    string projectLang;
    cout << "选择语言（输入CXX或C）" << endl;
    cin >> projectLang;

    if (projectLang == "CXX"){
        write << "    LANGUAGES CXX" << endl;
        write << ")" << endl;
        write.close();
        return false;
    }
    else if (projectLang == "C"){
        write << "    LANGUAGES C" << endl;
        write << ")" << endl;
        write.close();
        return true;
    }
    else{
        goto again;
    }
}
void writeCMakeLists_langVersion(bool choice){
    ofstream write("CMakeLists.txt", ios::app);
    string projectLangVersion;
    cout << "输入标准版本" << endl;
    cin >> projectLangVersion;

    if (!choice){
        write << "set(CMAKE_CXX_STANDARD " << projectLangVersion << ")" << endl;
    }
    else{
        write << "set(CMAKE_C_STANDARD " << projectLangVersion << ")" << endl;
    }
    again:
    char required;
    cout << "是否开启 CMAKE_C(XX)_STANDARD_REQUIRED ？（输入1为开启，2为关闭，0为默认）" << endl;
    cin >> required;

    switch (required){
        case '1':{
            if (!choice)
                write << "set(CMAKE_CXX_STANDARD_REQUIRED ON)" << endl;
            else
                write << "set(CMAKE_C_STANDARD_REQUIRED ON)" << endl;
            break;
        }
        case '2':{
            if (!choice)
                write << "set(CMAKE_CXX_STANDARD_REQUIRED OFF)" << endl;
            else
                write << "set(CMAKE_C_STANDARD_REQUIRED OFF)" << endl;
            break;
        }
        case '0':{
            break;
        }
        default:{
            goto again;
        }
    }
    write << "\n";
    write.close();
}
string writeCMakeLists_addExecutable(){
    ofstream write("CMakeLists.txt", ios::app);
    string appName;
    cout << "输入程序名：";
    cin >> appName;
    write << "add_executable(" << appName << endl;
    int num;
    cout << "需要构建的文件数：";
    cin >> num;

    vector<string> fileNameList;
    string fileName;

    cout << "源文件名称:" << endl;
    for (int i = 0;i < num;i++){
        cin >> fileName;
        fileNameList.push_back(fileName);
    }

    for (int i = 0;i < fileNameList.size();i++){
        write << "    " << fileNameList[i] << endl;
    }
    write << ")" << endl;
    write.close();
    cout << "CMakeLists生成完毕" << endl;
    return appName;
}
string makeFile(){
    system("mkdir -p build");
    again:
    short buildType;
    cout << "输入构建类型（1为Release，2为Debug）" << endl;
    cin >> buildType;
    string command;
    if (buildType == 1){
        command = "cmake -B build -DCMAKE_BUILD_TYPE=Release";
    }
    else if (buildType == 2){
        command = "cmake -B build -DCMAKE_BUILD_TYPE=Debug";
    }
    else{
        goto again;
    }
    again1:
    char choice;
    cout << "是否需要输入额外指令（0/1）：";
    cin >> choice;
    switch(choice){
        case '0':{
            break;
        }
        case '1':{
            short num;
            cout << "需要输入多少指令：";
            cin >> num;
            vector<string> commandList;
            string extraCommand;
            cout << "输入额外指令（如-DANDROID_ABI）：" << endl;
            for (int i = 0;i < num;i++){
                cin >> extraCommand;
                commandList.push_back(extraCommand);
            }
            string commands;
            for (int i = 0;i < commandList.size();i++){
                commands += " " + commandList[i];
            }
            command += commands;
            break;
        }
        default:{
            goto again1;
        }
    }
    system(command.c_str());
    cout << "构建文件生成完毕" << endl;
    string returnBuildType;
    if (buildType == 1){
        returnBuildType = "Release";
    }
    else if(buildType == 2){
        returnBuildType = "Debug";
    }
    return returnBuildType;
}
void build(string buildType, string appName){
    string parallel;
    string command;
    cout << "需要调用的核心数（输入MAX调用所有核心）：";
    cin >> parallel;
    if (parallel == "MAX"){
        command = "cmake --build build --config " + buildType + " --parallel $(nproc)";
    }
    else {
        command = "cmake --build build --config " + buildType + " --parallel " + parallel;
    }
    system(command.c_str());
    string command2 = "mv -f build/" + appName + " .";
    system(command2.c_str());
    system("rm -rf build/");
    cout << "操作执行完成" << endl;
}