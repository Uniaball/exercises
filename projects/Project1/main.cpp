#include <iostream>     //此文件有部分由AI修正
#include <string>
#include <random>
#include <windows.h>

using namespace std;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dist(1, 2);

int main()
{
    //全局变量初始化区
    //bool Game = 0;
    bool LeftHandWin = 0;
    bool RightHandWin = 0;
    bool LeftHandWin2 = 0;
    bool RightHandWin2 = 0;
    //游戏开始

    string GameStart;
    cout << "输入start开始游戏" << endl;
    cin >> GameStart;

    if (GameStart != "start") {
        cout << "未输入正确字符，进程结束" << endl;
        return 1;
    }
    else if (GameStart == "start") {
        cout << "游戏开始" << endl;
    }
    //初始化左右手
    //for (;;) {  //游戏主循环

        short LeftNum = 1, RightNum = 1;
        cout << "这是你的两个手，左、右手此时都是1" << endl;
        cout << "左：" << LeftNum << " 右：" << RightNum << endl;

        short LeftNum2 = 1, RightNum2 = 1;
        cout << "这是你的对手（弱智ai）的左、右手" << endl;
        cout << "左：" << LeftNum2 << " 右：" << RightNum2 << endl;

        //选择自己出的手
        for (;;) {

            cout << "选择你的一只手（输入L或R）" << endl;
            bool ChooseLeftHand = 0, ChooseRightHand = 0;
            char Choice;
            cin >> Choice;
            switch (Choice) {
            case 'L': {
                if (LeftHandWin != 1) {  // 修正：只检查是否获胜，不检查数值
                    ChooseLeftHand = 1;
                    cout << "你选择了左手（" << LeftNum << ")" << endl;
                }
                else {
                    cout << "这只手已经赢了捏，帮你选右手了" << endl;
                    ChooseRightHand = 1;
                    Sleep(500);
                    cout << "你选择了右手（" << RightNum << "）" << endl;
                }
                break;
            }
            case 'R': {
                if (RightHandWin != 1) {  // 修正：只检查是否获胜，不检查数值
                    ChooseRightHand = 1;
                    cout << "你选择了右手（" << RightNum << "）" << endl;
                }
                else {
                    cout << "这只手已经赢了捏，帮你选左手了" << endl;
                    ChooseLeftHand = 1;
                    Sleep(500);
                    cout << "你选择了左手（" << LeftNum << "）" << endl;
                }
                break;
            }
            default: {
                cout << "未输入正确字符，进程结束" << endl;
                return 1;
            }
            }
            //加ai哪只手
            char ChooseHand;
            cout << "你要加ai的哪只手（输入L或R）";
            cin >> ChooseHand;
            switch (ChooseHand) {
            case 'L': {
                if (LeftHandWin2 != 1) {  // 修正：检查AI的手是否获胜
                    if (ChooseLeftHand == 1) {
                        cout << "你选择了ai的左手（" << LeftNum2 << ")" << endl;
                        LeftNum += LeftNum2;
                        if (LeftNum > 10) {
                            LeftNum -= 10;
                        }
                        cout << "计算完毕，此时你的左手是：" << LeftNum << endl;
                    }
                    else if (ChooseRightHand == 1) {
                        cout << "你选择了ai的左手（" << LeftNum2 << ")" << endl;
                        RightNum += LeftNum2;
                        if (RightNum > 10) {
                            RightNum -= 10;
                        }
                        cout << "计算完毕，此时你的右手是：" << RightNum << endl;
                    }
                }
                else {
                    cout << "AI的左手已经获胜，不能选择" << endl;
                }
                break;
            }

            case 'R': {
                if (RightHandWin2 != 1) {  // 修正：检查AI的手是否获胜
                    if (ChooseLeftHand == 1) {
                        cout << "你选择了ai的右手（" << RightNum2 << ")" << endl;
                        LeftNum += RightNum2;
                        if (LeftNum > 10) {
                            LeftNum -= 10;
                        }
                        cout << "计算完毕，此时你的左手是：" << LeftNum << endl;
                    }
                    else if (ChooseRightHand == 1) {
                        cout << "你选择了ai的右手（" << RightNum2 << ")" << endl;
                        RightNum += RightNum2;
                        if (RightNum > 10) {
                            RightNum -= 10;
                        }
                        cout << "计算完毕，此时你的右手是：" << RightNum << endl;
                    }
                }
                else {
                    cout << "AI的右手已经获胜，不能选择" << endl;
                }
                break;
            }

            default: {
                cout << "未输入正确字符，进程结束" << endl;
                return 1;
            }
            }

            //显示左右手
            cout << "这是你的左、右手" << endl;
            cout << "左：" << LeftNum << " 右：" << RightNum << endl;

            cout << "这是ai的左、右手" << endl;
            cout << "左：" << LeftNum2 << " 右：" << RightNum2 << endl;

            ///////////////////////////////////////////////////////////////////////////////////////ai回合
            short RandomSelfHandChoice = dist(gen);
            short RandomHandChoice = dist(gen);
            cout << "ai回合" << endl;
            Sleep(2000);

            // 重构AI回合逻辑
            bool aiActionTaken = false;

            // AI选择自己的手
            if (RandomSelfHandChoice == 1 && LeftHandWin2 != 1) {
                cout << "ai使用了左手（" << LeftNum2 << "）" << endl;
                Sleep(2000);

                // AI选择玩家的手
                if (RandomHandChoice == 1 && LeftHandWin != 1) {
                    cout << "ai选择了你的左手（" << LeftNum << "）" << endl;
                    LeftNum2 += LeftNum;
                    if (LeftNum2 > 10) {
                        LeftNum2 -= 10;
                    }
                    Sleep(2000);
                    cout << "ai此时左手的数：" << LeftNum2 << endl;
                    aiActionTaken = true;
                }
                else if (RightHandWin != 1) {
                    cout << "ai选择了你的右手（" << RightNum << "）" << endl;
                    LeftNum2 += RightNum;
                    if (LeftNum2 > 10) {
                        LeftNum2 -= 10;
                    }
                    Sleep(2000);
                    cout << "ai此时左手的数：" << LeftNum2 << endl;
                    aiActionTaken = true;
                }
            }
            else if (RandomSelfHandChoice == 2 && RightHandWin2 != 1) {
                cout << "ai使用了右手（" << RightNum2 << "）" << endl;
                Sleep(2000);

                // AI选择玩家的手
                if (RandomHandChoice == 1 && LeftHandWin != 1) {
                    cout << "ai选择了你的左手（" << LeftNum << "）" << endl;
                    RightNum2 += LeftNum;
                    if (RightNum2 > 10) {
                        RightNum2 -= 10;
                    }
                    Sleep(2000);
                    cout << "ai此时右手的数：" << RightNum2 << endl;
                    aiActionTaken = true;
                }
                else if (RightHandWin != 1) {
                    cout << "ai选择了你的右手（" << RightNum << "）" << endl;
                    RightNum2 += RightNum;
                    if (RightNum2 > 10) {
                        RightNum2 -= 10;
                    }
                    Sleep(2000);
                    cout << "ai此时右手的数：" << RightNum2 << endl;
                    aiActionTaken = true;
                }
            }

            // 如果AI没有执行动作（因为选择的手不可用），尝试另一只手
            if (!aiActionTaken) {
                if (RandomSelfHandChoice == 1 && RightHandWin2 != 1) {
                    cout << "ai改用了右手（" << RightNum2 << "）" << endl;
                    Sleep(2000);

                    if (RandomHandChoice == 1 && LeftHandWin != 1) {
                        cout << "ai选择了你的左手（" << LeftNum << "）" << endl;
                        RightNum2 += LeftNum;
                        if (RightNum2 > 10) {
                            RightNum2 -= 10;
                        }
                        Sleep(2000);
                        cout << "ai此时右手的数：" << RightNum2 << endl;
                    }
                    else if (RightHandWin != 1) {
                        cout << "ai选择了你的右手（" << RightNum << "）" << endl;
                        RightNum2 += RightNum;
                        if (RightNum2 > 10) {
                            RightNum2 -= 10;
                        }
                        Sleep(2000);
                        cout << "ai此时右手的数：" << RightNum2 << endl;
                    }
                }
                else if (RandomSelfHandChoice == 2 && LeftHandWin2 != 1) {
                    cout << "ai改用了左手（" << LeftNum2 << "）" << endl;
                    Sleep(2000);

                    if (RandomHandChoice == 1 && LeftHandWin != 1) {
                        cout << "ai选择了你的左手（" << LeftNum << "）" << endl;
                        LeftNum2 += LeftNum;
                        if (LeftNum2 > 10) {
                            LeftNum2 -= 10;
                        }
                        Sleep(2000);
                        cout << "ai此时左手的数：" << LeftNum2 << endl;
                    }
                    else if (RightHandWin != 1) {
                        cout << "ai选择了你的右手（" << RightNum << "）" << endl;
                        LeftNum2 += RightNum;
                        if (LeftNum2 > 10) {
                            LeftNum2 -= 10;
                        }
                        Sleep(2000);
                        cout << "ai此时左手的数：" << LeftNum2 << endl;
                    }
                }
            }

            // 如果AI仍然没有执行动作，说明所有选择都不可用
            if (!aiActionTaken) {
                cout << "ai无法行动，跳过回合" << endl;
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////显示左右手
            cout << "这是你的左、右手" << endl;
            cout << "左：" << LeftNum << " 右：" << RightNum << endl;

            cout << "这是ai的左、右手" << endl;
            cout << "左：" << LeftNum2 << " 右：" << RightNum2 << endl;

            //获胜条件及单手
            if (LeftNum == 10 && !LeftHandWin) {
                LeftHandWin = 1;
                cout << "你的左手已获胜，将不可用" << endl;
                if (RightHandWin == 1) {
                    cout << "你已获胜，进程将以代码0退出" << endl;
                    return 0;
                }
            }

            if (RightNum == 10 && !RightHandWin) {
                RightHandWin = 1;
                cout << "你的右手已获胜，将不可用" << endl;
                if (LeftHandWin == 1) {
                    cout << "你已获胜，进程将以代码0退出" << endl;
                    return 0;
                }
            }

            if (LeftNum2 == 10 && !LeftHandWin2) {
                LeftHandWin2 = 1;
                cout << "ai的左手已获胜，将不可用" << endl;
                if (RightHandWin2 == 1) {
                    cout << "你输了，进程将以代码2退出" << endl;
                    return 2;
                }
            }

            if (RightNum2 == 10 && !RightHandWin2) {
                RightHandWin2 = 1;
                cout << "ai的右手已获胜，将不可用" << endl;
                if (LeftHandWin2 == 1) {
                    cout << "你输了，进程将以代码2退出" << endl;
                    return 2;
                }
            }

        }

        //Game = 1;
    //}//最外围for的扩回

    system("pause");
    return 0;
}