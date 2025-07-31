#include <iostream>
#include <string>
#include <random>
#include <unistd.h>
#include <jni.h>
#include <queue>
#include <pthread.h>

using namespace std;

// 输入输出重定向机制
static queue<string> g_inputQueue;
static pthread_mutex_t g_inputMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t g_inputCond = PTHREAD_COND_INITIALIZER;

// 输出回调函数
static void (*g_outputCallback)(const char*) = nullptr;
static void (*g_errorCallback)(const char*) = nullptr;

// 随机数生成器
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dist(1, 2);

// 发送输出到 Java 层
void sendOutput(const string& text) {
    if (g_outputCallback) {
        g_outputCallback(text.c_str());
    }
}

// 发送错误到 Java 层
void sendError(const string& text) {
    if (g_errorCallback) {
        g_errorCallback(text.c_str());
    }
}

// 重定向 cout
class AndroidOutputBuffer : public streambuf {
public:
    AndroidOutputBuffer() : buffer("") {}
    
protected:
    int overflow(int c) override {
        if (c == EOF) {
            return c;
        }
        buffer.push_back(c);
        if (c == '\n') {
            sendOutput(buffer);
            buffer.clear();
        }
        return c;
    }
    
    int sync() override {
        if (!buffer.empty()) {
            sendOutput(buffer);
            buffer.clear();
        }
        return 0;
    }

private:
    string buffer;
};

// 重定向 cerr
class AndroidErrorBuffer : public streambuf {
public:
    AndroidErrorBuffer() : buffer("") {}
    
protected:
    int overflow(int c) override {
        if (c == EOF) {
            return c;
        }
        buffer.push_back(c);
        if (c == '\n') {
            sendError(buffer);
            buffer.clear();
        }
        return c;
    }
    
    int sync() override {
        if (!buffer.empty()) {
            sendError(buffer);
            buffer.clear();
        }
        return 0;
    }

private:
    string buffer;
};

// 获取输入
string getInput() {
    pthread_mutex_lock(&g_inputMutex);
    while (g_inputQueue.empty()) {
        pthread_cond_wait(&g_inputCond, &g_inputMutex);
    }
    string input = g_inputQueue.front();
    g_inputQueue.pop();
    pthread_mutex_unlock(&g_inputMutex);
    return input;
}

// 游戏主函数
extern "C" void startGame() {
    // 初始化重定向
    static AndroidOutputBuffer outBuffer;
    static AndroidErrorBuffer errBuffer;
    cout.rdbuf(&outBuffer);
    cerr.rdbuf(&errBuffer);

    // 游戏变量
    bool LeftHandWin = false;
    bool RightHandWin = false;
    bool LeftHandWin2 = false;
    bool RightHandWin2 = false;
    bool gameRunning = true;

    sendOutput("输入start开始游戏\n");
    string GameStart = getInput();

    if (GameStart != "start") {
        sendOutput("未输入正确字符，进程结束\n");
        return;
    } else if (GameStart == "start") {
        sendOutput("游戏开始\n");
    }

    short LeftNum = 1, RightNum = 1;
    sendOutput("这是你的两个手，左、右手此时都是1\n");
    sendOutput("左：" + to_string(LeftNum) + " 右：" + to_string(RightNum) + "\n");

    short LeftNum2 = 1, RightNum2 = 1;
    sendOutput("这是你的对手（弱智ai）的左、右手\n");
    sendOutput("左：" + to_string(LeftNum2) + " 右：" + to_string(RightNum2) + "\n");

    while (gameRunning) {
        sendOutput("选择你的一只手（输入L或R）\n");
        bool ChooseLeftHand = false, ChooseRightHand = false;
        string Choice = getInput();
        char choiceChar = Choice.empty() ? ' ' : Choice[0];

        switch (choiceChar) {
            case 'L':
            case 'l': {
                if (!LeftHandWin) {
                    ChooseLeftHand = true;
                    sendOutput("你选择了左手（" + to_string(LeftNum) + ")\n");
                } else {
                    sendOutput("这只手已经赢了捏，帮你选右手了\n");
                    usleep(500000);  // 500ms 延迟
                    ChooseRightHand = true;
                    sendOutput("你选择了右手（" + to_string(RightNum) + "）\n");
                }
                break;
            }
            case 'R':
            case 'r': {
                if (!RightHandWin) {
                    ChooseRightHand = true;
                    sendOutput("你选择了右手（" + to_string(RightNum) + "）\n");
                } else {
                    sendOutput("这只手已经赢了捏，帮你选左手了\n");
                    usleep(500000);  // 500ms 延迟
                    ChooseLeftHand = true;
                    sendOutput("你选择了左手（" + to_string(LeftNum) + "）\n");
                }
                break;
            }
            default: {
                sendOutput("未输入正确字符，进程结束\n");
                return;
            }
        }

        // 选择AI的手
        sendOutput("你要加ai的哪只手（输入L或R）\n");
        string ChooseHand = getInput();
        char handChar = ChooseHand.empty() ? ' ' : ChooseHand[0];

        switch (handChar) {
            case 'L':
            case 'l': {
                if (!LeftHandWin2) {
                    if (ChooseLeftHand) {
                        sendOutput("你选择了ai的左手（" + to_string(LeftNum2) + ")\n");
                        LeftNum += LeftNum2;
                        if (LeftNum > 10) LeftNum -= 10;
                        sendOutput("计算完毕，此时你的左手是：" + to_string(LeftNum) + "\n");
                    } else if (ChooseRightHand) {
                        sendOutput("你选择了ai的左手（" + to_string(LeftNum2) + ")\n");
                        RightNum += LeftNum2;
                        if (RightNum > 10) RightNum -= 10;
                        sendOutput("计算完毕，此时你的右手是：" + to_string(RightNum) + "\n");
                    }
                } else {
                    sendOutput("AI的左手已经获胜，不能选择\n");
                }
                break;
            }
            case 'R':
            case 'r': {
                if (!RightHandWin2) {
                    if (ChooseLeftHand) {
                        sendOutput("你选择了ai的右手（" + to_string(RightNum2) + ")\n");
                        LeftNum += RightNum2;
                        if (LeftNum > 10) LeftNum -= 10;
                        sendOutput("计算完毕，此时你的左手是：" + to_string(LeftNum) + "\n");
                    } else if (ChooseRightHand) {
                        sendOutput("你选择了ai的右手（" + to_string(RightNum2) + ")\n");
                        RightNum += RightNum2;
                        if (RightNum > 10) RightNum -= 10;
                        sendOutput("计算完毕，此时你的右手是：" + to_string(RightNum) + "\n");
                    }
                } else {
                    sendOutput("AI的右手已经获胜，不能选择\n");
                }
                break;
            }
            default: {
                sendOutput("未输入正确字符，进程结束\n");
                return;
            }
        }

        // 显示状态
        sendOutput("这是你的左、右手\n");
        sendOutput("左：" + to_string(LeftNum) + " 右：" + to_string(RightNum) + "\n");
        sendOutput("这是ai的左、右手\n");
        sendOutput("左：" + to_string(LeftNum2) + " 右：" + to_string(RightNum2) + "\n");

        // AI回合
        sendOutput("ai回合\n");
        usleep(2000000);  // 2秒延迟

        short RandomSelfHandChoice = dist(gen);
        short RandomHandChoice = dist(gen);
        bool aiActionTaken = false;

        // AI选择自己的手
        if (RandomSelfHandChoice == 1 && !LeftHandWin2) {
            sendOutput("ai使用了左手（" + to_string(LeftNum2) + "）\n");
            usleep(2000000);

            // AI选择玩家的手
            if (RandomHandChoice == 1 && !LeftHandWin) {
                sendOutput("ai选择了你的左手（" + to_string(LeftNum) + "）\n");
                LeftNum2 += LeftNum;
                if (LeftNum2 > 10) LeftNum2 -= 10;
                usleep(2000000);
                sendOutput("ai此时左手的数：" + to_string(LeftNum2) + "\n");
                aiActionTaken = true;
            } else if (!RightHandWin) {
                sendOutput("ai选择了你的右手（" + to_string(RightNum) + "）\n");
                LeftNum2 += RightNum;
                if (LeftNum2 > 10) LeftNum2 -= 10;
                usleep(2000000);
                sendOutput("ai此时左手的数：" + to_string(LeftNum2) + "\n");
                aiActionTaken = true;
            }
        } else if (RandomSelfHandChoice == 2 && !RightHandWin2) {
            sendOutput("ai使用了右手（" + to_string(RightNum2) + "）\n");
            usleep(2000000);

            if (RandomHandChoice == 1 && !LeftHandWin) {
                sendOutput("ai选择了你的左手（" + to_string(LeftNum) + "）\n");
                RightNum2 += LeftNum;
                if (RightNum2 > 10) RightNum2 -= 10;
                usleep(2000000);
                sendOutput("ai此时右手的数：" + to_string(RightNum2) + "\n");
                aiActionTaken = true;
            } else if (!RightHandWin) {
                sendOutput("ai选择了你的右手（" + to_string(RightNum) + "）\n");
                RightNum2 += RightNum;
                if (RightNum2 > 10) RightNum2 -= 10;
                usleep(2000000);
                sendOutput("ai此时右手的数：" + to_string(RightNum2) + "\n");
                aiActionTaken = true;
            }
        }

        if (!aiActionTaken) {
            if (RandomSelfHandChoice == 1 && !RightHandWin2) {
                sendOutput("ai改用了右手（" + to_string(RightNum2) + "）\n");
                usleep(2000000);

                if (RandomHandChoice == 1 && !LeftHandWin) {
                    sendOutput("ai选择了你的左手（" + to_string(LeftNum) + "）\n");
                    RightNum2 += LeftNum;
                    if (RightNum2 > 10) RightNum2 -= 10;
                    usleep(2000000);
                    sendOutput("ai此时右手的数：" + to_string(RightNum2) + "\n");
                } else if (!RightHandWin) {
                    sendOutput("ai选择了你的右手（" + to_string(RightNum) + "）\n");
                    RightNum2 += RightNum;
                    if (RightNum2 > 10) RightNum2 -= 10;
                    usleep(2000000);
                    sendOutput("ai此时右手的数：" + to_string(RightNum2) + "\n");
                }
            } else if (RandomSelfHandChoice == 2 && !LeftHandWin2) {
                sendOutput("ai改用了左手（" + to_string(LeftNum2) + "）\n");
                usleep(2000000);

                if (RandomHandChoice == 1 && !LeftHandWin) {
                    sendOutput("ai选择了你的左手（" + to_string(LeftNum) + "）\n");
                    LeftNum2 += LeftNum;
                    if (LeftNum2 > 10) LeftNum2 -= 10;
                    usleep(2000000);
                    sendOutput("ai此时左手的数：" + to_string(LeftNum2) + "\n");
                } else if (!RightHandWin) {
                    sendOutput("ai选择了你的右手（" + to_string(RightNum) + "）\n");
                    LeftNum2 += RightNum;
                    if (LeftNum2 > 10) LeftNum2 -= 10;
                    usleep(2000000);
                    sendOutput("ai此时左手的数：" + to_string(LeftNum2) + "\n");
                }
            }
        }

        // 显示状态
        sendOutput("这是你的左、右手\n");
        sendOutput("左：" + to_string(LeftNum) + " 右：" + to_string(RightNum) + "\n");
        sendOutput("这是ai的左、右手\n");
        sendOutput("左：" + to_string(LeftNum2) + " 右：" + to_string(RightNum2) + "\n");

        // 获胜条件检查
        if (LeftNum == 10 && !LeftHandWin) {
            LeftHandWin = true;
            sendOutput("你的左手已获胜，将不可用\n");
            if (RightHandWin) {
                sendOutput("你已获胜\n");
                gameRunning = false;
                return;
            }
        }

        if (RightNum == 10 && !RightHandWin) {
            RightHandWin = true;
            sendOutput("你的右手已获胜，将不可用\n");
            if (LeftHandWin) {
                sendOutput("你已获胜\n");
                gameRunning = false;
                return;
            }
        }

        if (LeftNum2 == 10 && !LeftHandWin2) {
            LeftHandWin2 = true;
            sendOutput("ai的左手已获胜，将不可用\n");
            if (RightHandWin2) {
                sendOutput("你输了\n");
                gameRunning = false;
                return;
            }
        }

        if (RightNum2 == 10 && !RightHandWin2) {
            RightHandWin2 = true;
            sendOutput("ai的右手已获胜，将不可用\n");
            if (LeftHandWin2) {
                sendOutput("你输了\n");
                gameRunning = false;
                return;
            }
        }
    }
}

// JNI 接口
extern "C" {

JNIEXPORT void JNICALL
Java_com_example_handgame_MainActivity_startGame(JNIEnv *env, jobject thiz) {
    startGame();
}

JNIEXPORT void JNICALL
Java_com_example_handgame_MainActivity_sendInput(
        JNIEnv *env,
        jobject thiz,
        jstring input) {
    const char *inputStr = env->GetStringUTFChars(input, nullptr);
    pthread_mutex_lock(&g_inputMutex);
    g_inputQueue.push(string(inputStr));
    pthread_cond_signal(&g_inputCond);
    pthread_mutex_unlock(&g_inputMutex);
    env->ReleaseStringUTFChars(input, inputStr);
}

JNIEXPORT void JNICALL
Java_com_example_handgame_MainActivity_setOutputCallback(
        JNIEnv *env,
        jobject thiz,
        jobject callback) {
    // 实际实现中需要通过JNI保存回调
}

}