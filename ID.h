#pragma once
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<string>
using namespace std;


bool isIdlawful(string& Id) {
	if (Id.size() < 8 || Id.size() > 16) {
		cout << "�˻������볤��С��8�����16\n";
		cout << "����������\n";
		return 0;
	}
	return 1;
}

class ID {
	public:
		ID();//��ʼ��
		bool usedId(string& id) {//id�ظ�����1���ظ�����0
			return idPassword.count(id);
		}
		bool check() {
			string inId, inPassword;
			cout << "�����˺�\n";
			getline(cin, inId);
			cout << "��������\n";
			getline(cin, inPassword);
			if (idPassword.count(inId) && idPassword[inId] == inPassword) {
				cout << "��¼�ɹ�\n";
				return 0;
			}
			else {
				cout << "�˺Ż���������\n";
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
	unordered_map<string, string> idPassword;//�ù�ϣ����˺��Լ�����
	ofstream wirteFile;//�������ļ�ָ��
	ifstream putFile;//ȡ�����ļ�ָ��

};
ID::ID() {
	int t;
	pushData();
	cout << "1.����   2.ע��\n";
	cin >> t;
	getchar();
	if (t == 1) {
		while (check());
	}
	else if (t == 2) {
		aaaaa:
		wirteFile.open("IDandPassword.dat",ios::app);
		string idTemp,password;
		cout << "�����˺�\n";
		getline(cin, idTemp); 
		while (1) { 
			if (!isIdlawful(idTemp));
			else if (usedId(idTemp)) {
				cout << "���˺��ѱ�ע��\n";
				cout << "����������\n";
			}
			else {
				break;
			}
			getline(cin, idTemp);
		}
		cout << "��������\n";
		getline(cin, password);
		while(!isIdlawful(password))getline(cin, password);
		idPassword[idTemp] = password;
		wirteFile << idTemp << '\n';
		wirteFile << password << '\n';
		wirteFile.close();
		cout << "ע��ɹ�\n";
		ID next;
	}
	else {
		cout << "��Ȼ��֪����Ҫ���ﵫ�Ǿ͵�����Ҫע���\n";
		goto aaaaa;
	}
}