package com.uniaball.project1_android;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ScrollView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("handgame");
    }

    private TextView consoleOutput;
    private EditText inputField;
    private Button sendButton;
    private ScrollView scrollView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        consoleOutput = findViewById(R.id.console_output);
        inputField = findViewById(R.id.input_field);
        sendButton = findViewById(R.id.send_button);
        scrollView = findViewById(R.id.scroll_view);

        sendButton.setOnClickListener(v -> {
            String input = inputField.getText().toString().trim();
            if (!input.isEmpty()) {
                // 添加用户输入到控制台
                appendToConsole("> " + input + "\n");
                
                // 发送输入到原生代码
                sendInput(input);
                
                // 清空输入框
                inputField.setText("");
            }
        });

        // 启动游戏线程
        new Thread(() -> {
            try {
                Thread.sleep(1000); // 等待UI初始化
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            startGame();
        }).start();
    }

    // 原生方法声明
    private native void startGame();
    private native void sendInput(String input);
    private native void setOutputCallback(Object callback);

    // 在控制台输出文本
    public void appendToConsole(final String text) {
        runOnUiThread(() -> {
            consoleOutput.append(text);
            // 自动滚动到底部
            scrollView.post(() -> scrollView.fullScroll(View.FOCUS_DOWN));
        });
    }

    // 原生代码调用此方法来输出文本
    public void nativeOutput(String text) {
        appendToConsole(text);
    }
}