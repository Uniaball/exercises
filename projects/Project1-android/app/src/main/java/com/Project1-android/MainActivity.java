package com.example.yourgame;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import jackpal.androidterm.emulatorview.TermSession;
import jackpal.androidterm.emulatorview.EmulatorView;
import jackpal.androidterm.util.SessionList;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("game");
    }

    private EmulatorView terminal;
    private NativeSession session;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        terminal = findViewById(R.id.terminal);
        session = new NativeSession();
        
        SessionList sessions = new SessionList();
        sessions.add(session);
        terminal.attachSession(session);
        
        new Thread(this::startNativeGame).start();
    }

    private native void startNativeGame();

    private class NativeSession extends TermSession {
        public NativeSession() {
            super();
            setProcessExitMessage("Game exited");
        }

        @Override
        public void initializeEmulator(int columns, int rows) {
            // 初始化终端
        }

        @Override
        public void onProcessExit() {
            // 游戏退出处理
        }
        
        // 从 C++ 接收输出
        public void receiveOutput(String text) {
            write(text.toCharArray(), 0, text.length());
        }
    }
}