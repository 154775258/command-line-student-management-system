#pragma once
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<string>
using namespace std;


bool isIdlawful(string& Id) {
	if (Id.size() < 8 || Id.size() > 16) {
		cout << "账户或密码长度小于8或大于16\n";
		cout << "请重新输入\n";
		return 0;
	}
	return 1;
}

class ID {
	public:
		ID();//初始化
		bool usedId(string& id) {//id重复返回1不重复返回0
			return idPassword.count(id);
		}
		bool check() {
			string inId, inPassword;
			cout << "输入账号\n";
			getline(cin, inId);
			cout << "输入密码\n";
			getline(cin, inPassword);
			if (idPassword.count(inId) && idPassword[inId] == inPassword) {
				cout << "登录成功\n";
				return 0;
			}
			else {
				cout << "账号或密码有误\n";
				return 1;
			}
		}
		void pushData() {
			wirteFile.open("IDandPassword.dat", ios::app);
			wirteFile.close();
			putFile.open("IDandPassword.dat");
			string id, password;
			while (!putFile.eof()) {
				putFile >> id;
				putFile >> password;
				if (usedId(id))continue;
				else idPassword[id] = password;
			}
			putFile.close();
		}
	private:
	unordered_map<string, string> idPassword;//用哈希表存账号以及密码
	ofstream wirteFile;//存数据文件指针
	ifstream putFile;//取数据文件指针

};
ID::ID() {
	int t;
	pushData();
	cout << "1.登入   2.注册\n";
	cin >> t;
	getchar();
	if (t == 1) {
		while (check());
	}
	else if (t == 2) {
		aaaaa:
		wirteFile.open("IDandPassword.dat",ios::app);
		string idTemp,password;
		cout << "输入账号\n";
		getline(cin, idTemp); 
		while (1) { 
			if (!isIdlawful(idTemp));
			else if (usedId(idTemp)) {
				cout << "该账号已被注册\n";
				cout << "请重新输入\n";
			}
			else {
				break;
			}
			getline(cin, idTemp);
		}
		cout << "输入密码\n";
		getline(cin, password);
		while(!isIdlawful(password))getline(cin, password);
		idPassword[idTemp] = password;
		wirteFile << idTemp << '\n';
		wirteFile << password << '\n';
		wirteFile.close();
		cout << "注册成功\n";
		ID next;
	}
	else {
		cout << "虽然不知道你要干嘛但是就当你是要注册吧\n";
		goto aaaaa;
	}
}