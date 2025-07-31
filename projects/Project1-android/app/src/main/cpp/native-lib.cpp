#include <jni.h>
#include "main.cpp"

extern "C" JNIEXPORT void JNICALL
Java_com_example_yourgame_MainActivity_startNativeGame(JNIEnv* env, jobject thiz) {
    // 初始化输出重定向
    static AndroidStream outBuf(sendOutput);
    static AndroidStream errBuf(sendError);
    cout.rdbuf(&outBuf);
    cerr.rdbuf(&errBuf);
    
    startGame();
}

// 从 Java 接收输入
extern "C" JNIEXPORT void JNICALL
Java_com_example_yourgame_MainActivity_00024NativeSession_sendInput(
    JNIEnv* env, jobject thiz, jstring input
) {
    const char* chars = env->GetStringUTFChars(input, nullptr);
    // 将输入传递给游戏（需实现输入队列）
    // ...
    env->ReleaseStringUTFChars(input, chars);
}

// 发送输出到 Java
void sendOutput(const char* text) {
    // 通过 JNI 调用 Java 的 receiveOutput 方法
}