#include <iostream>
#include <Windows.h>
#include <random>
#include <conio.h>
#include "main.h"

using namespace std;
random_device rd;                                    //搞随机用的捏
mt19937 gen(rd());
uniform_int_distribution<int> dist(1, 3);


int main() {
	//开始游戏检测（人机测试）
	string StartGame;
	cout << "输入start开始游戏" << endl;
	cin >> StartGame;
	if (StartGame == "start") {
		cout << "输入正确字符，游戏开始" << endl;
		Sleep(2000);
		system("cls");  

		GameSum();  //废话函数调用

		Sleep(3000);
		system("cls");

		Start();  //选择函数调用
	}
	else {
		cout << "未输入正确字符，进程将以代码1退出" << endl;
		return 1;
	}

	system("pause");
	return 0;
}






void GameSum() { //废话函数
	cout << "本游戏就是一个石头剪刀布捏,同时来练练我的函数水平" << endl;
	cout << "你的对手仍然是那个弱智ai捏" << endl;
}


short Start() {
	char s, j, b;
	cout << "你要出什么（石头按“S”，剪刀按“J”，布按“B”）：" << endl;                               //bzl同款的侦测键盘函数
	switch (_getche()) {
	case 's': {
		cout << "\n";
		cout << "你选择了石头" << endl;
		cout << "等待ai选择" << endl;
		s = 's';
		j = 'N';
		b = 'N';
		Keyboard(s, j, b);  ///
		break;
	}
	case 'j': {
		cout << "\n";
		cout << "你选择了剪刀" << endl;
		cout << "等待ai选择" << endl;
		s = 'N';
		j = 'j';
		b = 'N';
		Keyboard(s, j, b);  ///
		break;
	}
	case 'b': {
		cout << "\n";
		cout << "你选择了布" << endl;
		cout << "等待ai选择" << endl;
		s = 'N';
		j = 'N';
		b = 'b';
		Keyboard(s, j, b);  ///
		break;
	}
	default: {
		cout << "\n";
		cout << "你牛魔的按啥捏" << endl;
		cout << "给你崩了" << endl;
		return 1;
	}
	}
	
	//system("pause");
}


short Keyboard(char s, char j, char b) {    
	short AiRandomChoose = dist(gen);                      //负责处理对应键、ai回合及游戏胜负
	if (s == 's') {   //玩家选择石头
		switch (AiRandomChoose) {
		case 1: {          //石头
			Sleep(2000);
			cout << "ai选择了石头" << endl;
			Sleep(500);
			cout << "你们平局" << endl;
			Sleep(500);
			cout << "请重新选择" << endl;
			Start();       //重新执行start函数
			break;
		}
		case 2: {         //剪刀
			Sleep(2000);
			cout << "ai选择了剪刀" << endl;
			Sleep(500);
			cout << "你赢了" << endl;
			Sleep(500);
			cout << "游戏将以代码0退出" << endl;
			return 0;
			break;
		}
		case 3: {         //布
			Sleep(2000);
			cout << "ai选择了布" << endl;
			Sleep(500);
			cout << "你输了" << endl;
			Sleep(500);
			cout << "游戏将以代码2退出" << endl;
			return 2;
			break;
		}
		}
	}
	else if (j == 'j') {        //玩家选择剪刀
		switch (AiRandomChoose) {
		case 1: {          //石头
			Sleep(2000);
			cout << "ai选择了石头" << endl;
			Sleep(500);
			cout << "你输了" << endl;
			Sleep(500);
			cout << "游戏将以代码2退出" << endl;
			return 2;   
			break;
		}
		case 2: {         //剪刀
			Sleep(2000);
			cout << "ai选择了剪刀" << endl;
			Sleep(500);
			cout << "你们平局" << endl;
			Sleep(500);
			cout << "请重新选择" << endl;
			Start();          //重新执行start函数
			break;
		}
		case 3: {         //布
			Sleep(2000);
			cout << "ai选择了布" << endl;
			Sleep(500);
			cout << "你赢了" << endl;
			Sleep(500);
			cout << "游戏将以代码0退出" << endl;
			return 0;
			break;
		}
		}
	}
	else if (b == 'b') {        //玩家选择布
		switch (AiRandomChoose) {
		case 1: {          //石头
			Sleep(2000);
			cout << "ai选择了石头" << endl;
			Sleep(500);
			cout << "你赢了" << endl;
			Sleep(500);
			cout << "游戏将以代码0退出" << endl;
			return 0;
			break;
		}
		case 2: {         //剪刀
			Sleep(2000);
			cout << "ai选择了剪刀" << endl;
			Sleep(500);
			cout << "你输了" << endl;
			Sleep(500);
			cout << "游戏将以代码2退出" << endl;
			return 2;
			break;
		}
		case 3: {         //布
			Sleep(2000);
			cout << "ai选择了布" << endl;
			Sleep(500);
			cout << "你们平局" << endl;
			Sleep(500);
			cout << "请重新选择" << endl;
			Start();          //重新执行start函数
			break;
		}
		}
	}
	//system("pause");
}