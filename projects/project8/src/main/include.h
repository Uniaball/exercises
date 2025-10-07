#pragma once
#include <iostream>
#include <vector>
#ifdef _WIN32
    #define clear cls
#endif

using namespace std;
namespace compile{
    void cpp();
    void c();
}
namespace wrap{
    void staticLib();
    void dynamicLib();
    void cpp();
    void c_staticLib();
    void c_dynamicLib();
    void c();
}
bool help();