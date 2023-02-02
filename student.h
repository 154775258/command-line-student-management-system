#pragma once
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<string>
#include<vector>

using namespace std;

class student {
	public:
		student();
		void pushData();//��������
		void writeData();//�����������
		void enterClass();//����༶
		void createClass();//�����༶
		void addStudentInClass(string& _class);//��༶���ѧ��
		void eraseStudentInClass(string& _class);//�Ƴ�ѧ��
		void eraseStudentInClass(string& nums,string& _class);
		void addStudent();//���ѧ����Ϣ
		void eraseStudent();//ɾ��ѧ����Ϣ
		void findStudentId();//��ѧ��ѧ�Ų��������Ϣ
		void findStudentName();//��ѧ���������������Ϣ
		void findStudentId(string& id);
		void eraseClass();//ɾ���༶
		void addDiscipline(string& _class);//��ӿ�Ŀ
		int findDiscipline(string& _class, string& a);
		void eraseClassDiscipline(string& _class);//ɾ���༶��Ŀ
		void reviseStudentScores();//�޸�ѧ���ɼ�
		int findClassId(string& id,string& tmp) {
			for (int i = 0; i < classStudentId[tmp].size(); i++) {
				if (classStudentId[tmp][i] == id)return i;
			}
			return -1;
		}

		bool check(string& a) {
			if (a.size() < 2) {
				cout << "�༶����������������\n";
				return 0;
			}
			else if (a.size() > 16) {
				cout << "�༶����������������\n";
				return 0;
			}
			else if (classStudentId.count(a)) {
				cout << "�ð༶���Ѵ�������������\n";
				return 0;
			}
			return 1;
		}
	private:
	ofstream writeFile;//�������ļ�ָ��
	ifstream putFile;//ȡ�����ļ�ָ��
	vector<string> classId;//��༶�ĵط�
	unordered_map<string, vector<string>> classStudentId;//ÿ���༶������Щѧ��
	unordered_map<string, vector<string>> classDiscipline;//ÿ���༶������Щ��Ŀ
	unordered_map<string, string> studentClass;//ÿ��ѧ�����ڰ༶
	unordered_map<string, vector<string>>studentScores;//ÿ��ѧ���ĳɼ� ѧ�Ŷ�Ӧ�ɼ�
	unordered_map<string, vector<string>>studentName;//ѧ�������Լ��������ǵ�ѧ��
	unordered_map<string, string>nameId;//ѧ�Ŷ�Ӧ����
};

student::student() {
	cout << "��ȡ������\n";
	pushData();
	while (1) {
		cout << "��ǰ�༶��:\n";
		for (int i = 0; i < classId.size(); i++) {
			cout << classId[i] << '\n';
			if (i & 1)cout << '\n';
		}
		cout << "������ѡ�����\n";
		cout << "1.����༶,          2.ʹ��ѧ��ѧ�Ų���\n";
		cout << "3.ʹ��ѧ����������,  4.�����༶\n";
		cout << "5.���治�˳�,        6���沢�˳�\n";
		cout << "7,���ѧ����Ϣ,      8.�Ƴ�ѧ����Ϣ\n";
		cout << "9,�Ƴ��༶\n";
		int nums;
		cin >> nums;
		switch (nums) {
		case 1:enterClass(); break;
		case 2:findStudentId(); break;
		case 3:findStudentName(); break;
		case 4:createClass(); break;
		case 5:writeData(); break;
		case 6:writeData(); return;
		case 7:addStudent(); break;
		case 8:eraseStudent(); break;
		case 9:eraseClass(); break;
		default:cout << "��֪����Ҫ��ɶ���Ծ���1111111�ˣ�\n"; enterClass(); break;
		}
	}
}

void student::pushData() {
	writeFile.open("allStudent.dat", ios::app);
	writeFile.close();
	putFile.open("allStudent.dat");
	string id;
	int use = 1;
	while (!putFile.eof()) {
		putFile >> id;
		if (id == "#") {
			use++;
			continue;
		}
		if (use == 1) {
			classId.push_back(id);
		}
		else if (use == 2) {
			auto index = id.find('.');
			string tmp2 = id.substr(0, index);
			//cout << tmp2 << " "  << id << '\n';
			while (id.find('.',index+1) != string::npos) {
				auto t = index;
				index = id.find('.',index+1);
				string tmp1 = id.substr(t + 1, (index - t - 1));
				classStudentId[tmp2].push_back(tmp1);
				studentClass[tmp1] = tmp2;
				//cout << tmp2 << ' ' << tmp1 << '\n';
			}
		}
		else if (use == 3) {
			auto index = id.find('.');
			string tmp2 = id.substr(0, index);
			while (id.find('.', index + 1) != id.npos) {
				auto t = index;
				index = id.find('.', index + 1);
				classDiscipline[tmp2].push_back(id.substr(t + 1, (index - t - 1)));
			}
		}
		else if (use == 4) {
			auto index = id.find('.');
			string tmp2 = id.substr(0, index);
			while (id.find('.', index + 1) != id.npos) {
				auto t = index;
				index = id.find('.', index + 1);
				string tmp1 = id.substr(t + 1, (index - t - 1));
				studentScores[tmp2].push_back(tmp1);
			}
		}
		else if (use == 5) {
			auto index = id.find('.');
			string tmp2 = id.substr(0, index);
			while (id.find('.', index + 1) != id.npos) {
				auto t = index;
				index = id.find('.', index + 1);
				string tmp1 = id.substr(t + 1, (index - t - 1));
				//cout << index - t << '\n';
				studentName[tmp2].push_back(tmp1);
				nameId[tmp1] = tmp2;
				//cout << tmp1 << " " << tmp2 << '\n';
			}
		}
		//cout << use << '\n';
		//cout << id << '\n';
	}
	putFile.close();
	system("cls");
}

void student::writeData() {
	writeFile.open("allStudent.dat");
	for (int i = 0; i < classId.size(); i++) {
		writeFile << classId[i] << '\n';
	}
	writeFile << "#" << '\n';
	for (auto& tmp : classStudentId) {
		string t = tmp.first;
		t += '.';
		for (int i = 0; i < tmp.second.size(); i++) {
			t += tmp.second[i];
			t += '.';
		}
		writeFile << t << '\n';
	}
	writeFile << "#\n";
	for (auto& tmp : classDiscipline) {
		string t = tmp.first;
		t += '.';
		for (int i = 0; i < tmp.second.size(); i++) {
			t += tmp.second[i];
			t += '.';
		}
		writeFile << t << '\n';
	}
	writeFile << "#\n";
	for (auto& tmp : studentScores) {
		string t = tmp.first;
		t += '.';
		for (int i = 0; i < tmp.second.size(); i++) {
			t += tmp.second[i];
			t += '.';
		}
		writeFile << t << '\n';
	}
	writeFile << "#\n";
	for (auto& tmp : studentName) {
		string t = tmp.first;
		t += '.';
		for (int i = 0; i < tmp.second.size(); i++) {
			t += tmp.second[i];
			t += '.';
		}
		writeFile << t << '\n';
	}
	writeFile << "#\n";
}

void student::enterClass() {
	string tmp;
	cout << "����༶��,�˳�����0\n";
	cin >> tmp;
	if (tmp == "0")
		return;
	while (!classStudentId.count(tmp)) {
		cout << "δ���ҵ��˰༶�Ӽ�����������\n";
		cin >> tmp;
		if (tmp == "0")
			return;
	}
	for (int i = 0; i < classStudentId[tmp].size(); i++) {
		string t1 = classStudentId[tmp][i];
		cout << "ѧ��:" << t1 << " " << "����:" << nameId[t1] << " ";
		for (int j = 0; j < studentScores[t1].size(); j++) {
			cout << "��Ŀ:" << classDiscipline[tmp][j] << ":" << studentScores[t1][j] << "   ";
		}
		cout << '\n';
	}
	while (1) {
		cout << "1.��Ӱ༶��Ŀ,  2.�޸�ѧ���ɼ�\n";
		cout << "3.���ѧ��,      4,�Ƴ�ѧ��\n";
		cout << "5.ɾ���༶��Ŀ,   0�˻���һĿ¼\n";
		int nums;
		cin >> nums;
		switch (nums) {
		case 1:addDiscipline(tmp); break;
		case 2:reviseStudentScores(); break;
		case 3:addStudentInClass(tmp); break;
		case 4:eraseStudentInClass(tmp); break;
		case 5:eraseClassDiscipline(tmp); break;
		case 0:cout << "�༭�����ǵñ���!\n"; system("cls"); return;
		default:cout << "��֪����Ҫ��ɶ�Ͱ����˳������˼ǵñ���Ŷ��\n"; system("cls");  return;
		}
		system("cls");
	}
}

void student::addDiscipline(string& _class) {
	string Discipline;
	cout << "������Ҫ��ӵĿ�Ŀ����\n";
	cin >> Discipline;
	while (findDiscipline(_class, Discipline) != -1) {
		cout << "������Ŀ�Ŀ�����Ѵ���\n";
		cout << "����������\n";
		cin >> Discipline;
	}
	classDiscipline[_class].push_back(Discipline);
	cout << classDiscipline[_class].back() << '\n';
	for (int i = 0; i < classStudentId[_class].size(); i++) {
		studentScores[classStudentId[_class][i]].push_back("-1");
	}
	cout << "��ӳɹ�\n";
}

void student::createClass() {
	cout << "����༶��\n";
	string tmp;
	cin >> tmp;
	while (!check(tmp))cin >> tmp;
	classId.push_back(tmp);
	classStudentId[tmp].push_back("text");
	cout << "��ӳɹ�\n";
}

void student::addStudentInClass(string& _class) {
	string nums,name;
	cout << "����ѧ��ѧ��\n";
	cin >> nums;
	while (!nameId.count(nums) || findClassId(nums,_class) != -1) {
		cout << "�ڱ�ѧУ��δ���ҵ���ѧ���Ƿ�δ��ӻ����������ѧ���Ѵ�����ð༶\n";
		cout << "���������� �˳�����0\n";
		cin >> nums;
		if (nums == "0")return;
	}
	if (classStudentId[_class][0] == "text")classStudentId[_class][0] = nums;
	else
	classStudentId[_class].push_back(nums);
	//cout << classStudentId[_class][0] << '\n';
	studentClass[nums] = _class;
	studentScores[_class].resize(classDiscipline[_class].size(), "-1");
	cout << "��ӳɹ�\n";
}

void student::eraseStudentInClass(string& id,string& _class) {
	auto it = classStudentId[_class].begin();
	if (findClassId(id, _class) != -1) {
		it += findClassId(id, _class);
		classStudentId[_class].erase(it);
		//cout << "!!!\n";
	}
}

void student::eraseStudentInClass(string& _class) {
	string id;
	cout << "������Ҫ�Ƴ�ѧ����ѧ��\n";
	cin >> id;
	while (findClassId(id, _class) == -1){
		cout << "�ð༶û�д�ѧ��ѧ���������Ƿ�������ȷ\n";
		cout << "����������\n";
		cout << "���������� �˳�����0\n";
		cin >> id;
		if (id == "0")return;
	}
	auto it = classStudentId[_class].begin();
	it += findClassId(id, _class);
	classStudentId[_class].erase(it);
	studentScores.erase(id);
	studentClass.erase(id);
	cout << "ɾ���ɹ�\n";
}

void student::addStudent() {
	string nums,name;
	cout << "����ѧ��ѧ��\n";
	cin >> nums;
	while (nameId.count(nums)) {
		cout << "��ѧ���Ѵ���\n����������\n";
		cout << "�˳�����0\n";
		cin >> nums;
		if (nums == "0")return;
	}
	first:
	cout << "����ѧ������\n";
	cin >> name;
	cout << "�����Ƿ�������ȷ ��ȷ���� 1 ����ȷ���� 0 ����������\n";
	int t;
	cin >> t;
	if (t == 0)goto first;
	nameId[nums] = name;
	studentName[name].push_back(nums);
	cout << "��ӳɹ�\n";
}

void student::eraseStudent() {
	string id;
	cout << "������Ҫ�Ƴ�ѧ����ѧ��\n";
	cin >> id;
	while (!nameId.count(id)) {
		cout << "Ѱ�Ҳ�����ѧ�������Ƿ�������������\n";
		cout << "�˳�����0\n";
		cin >> id;
		if (id == "0")return;
	}
	string name = nameId[id];
	nameId.erase(id);
	auto it = studentName[name].begin();
	for (; it != studentName[name].end(); ++it)
		if (*it == id)break;
	studentName[name].erase(it);
	//cout << 1 << '\n';
	if(studentClass.count(id))
	eraseStudentInClass(id, studentClass[id]);
	studentScores.erase(id);
	studentClass.erase(id);
	cout << "ɾ���ɹ�\n";
}

void student::findStudentId() {
	string id;
	cout << "����Ҫ���ҵ�ѧ��\n";
	cin >> id;
	while (!nameId.count(id)) {
		cout << "ϵͳ��û�д�ѧ����ȷ���Ƿ�������ȷ\n";
		cout << "���������� �˳�����0\n";
		cin >> id;
		if (id == "0")return;
	}
	cout << "ѧ��: " << id << ' ';
	if (studentClass.count(id)) {
		cout << "�༶��";
		cout << studentClass[id] << "   ";
	}
	else {
		cout << "��ѧ�����ް༶   ";
	}
	cout << "����: " << nameId[id] << ' ';
	cout << "�ɼ�:\n";
	for (int i = 0; i < studentScores[id].size(); i++) {
		cout << classDiscipline[studentClass[id]][i] << ":" << studentScores[id][i] << '\n';
	}
}

void student::findStudentName() {
	string name;
	cout << "������Ҫ���ҵ�����\n";
	cin >> name;
	while (!studentName.count(name)) {
		cout << "��ϵͳ��δ����������\n";
		cout << "���������� �˳�����0\n";
		cin >> name;
		if (name == "0")return;
	}
	for (int i = 0; i < studentName[name].size(); i++) {
		findStudentId(studentName[name][i]);
		cout << '\n';
	}
}

void student::findStudentId(string& id) {
	cout << "ѧ��: " << id << ' ';
	if (studentClass.count(id)) {
		cout << studentClass[id] << "   ";
	}
	else {
		cout << "��ѧ�����ް༶   ";
	}
	cout << "����: " << nameId[id] << ' ';
	cout << "�ɼ�:\n";
	for (int i = 0; i < studentScores[id].size(); i++) {
		cout << classDiscipline[studentClass[id]][i] << ":" << studentScores[id][i] << '\n';
	}
}

void student::eraseClass() {
	string _class;
	cout << "����Ҫ�Ƴ��İ༶\n";
	cin >> _class;
	while (!classStudentId.count(_class)) {
		cout << "δ�ҵ���Ҫ�Ƴ��İ༶\n";
		cout << "���������� �˳�����0\n";
		cin >> _class;
		if (_class == "0")return;
	}
	auto it = classId.begin();
	for (; it != classId.end(); it++)
		if (*it == _class)break;
	classId.erase(it);
	classDiscipline.erase(_class);
	for (auto& q : classStudentId[_class]) {
		studentClass.erase(q);
	}
	classStudentId.erase(_class);
	cout << "ɾ���ɹ�\n";
}

int student::findDiscipline(string& _class,string& a) {
	for (int i = 0; i < classDiscipline[_class].size(); i++) {
		if (classDiscipline[_class][i] == a)return i;
	}
	return -1;
}

void student::eraseClassDiscipline(string& _class) {
	string Discipline;
	cout << "������Ҫɾ���Ŀ�Ŀ����\n";
	cin >> Discipline;
	while (findDiscipline(_class, Discipline) == -1) {
		cout << "������Ŀ�Ŀ���Ʋ�����\n";
		cout << "���������� �˳�����0\n";
		cin >> Discipline;
		if (Discipline == "0")return;
	}
	int t = findDiscipline(_class, Discipline);
	auto it = classDiscipline[_class].begin();
	it += t;
	classDiscipline[_class].erase(it);
	for (int i = 0; i < classStudentId[_class].size(); i++) {
		it = studentScores[classStudentId[_class][i]].begin();
		it += t;
		studentScores[classStudentId[_class][i]].erase(it);
	}
	cout << "ɾ���ɹ�\n";
}

void student::reviseStudentScores() {
	string id;
	cout << "������Ҫ�޸ĳɼ���ѧ��ѧ��\n";
	cin >> id;
	while (!nameId.count(id)) {
		cout << "δ���ҵ��������ѧ���Ƿ����������\n";
		cout << "���������� �˳�����0\n";
		cin >> id;
		if (id == "0")return;
	}
	cout << "��Ŀ�У�\n";
	for (int i = 0; i < classDiscipline[studentClass[id]].size(); i++) {
		cout << classDiscipline[studentClass[id]][i] << '\n';
	}
	string Discipline;
	cout << "������Ҫ�޸ĵ�ѧ����Ŀ\n";
	cin >> Discipline;
	while (findDiscipline(studentClass[id], Discipline) == -1) {
		cout << "δ�ҵ���Ҫ�޸ĵĿ�Ŀ\n";
		cout << "���������� �˳�����0\n";
		cin >> Discipline;
		if (Discipline == "0")return;
	}
	int t = findDiscipline(studentClass[id], Discipline);
	auto it = studentScores[id].begin();
	it += t;
	string nums1 = "-1", nums2 = "0";
	while (nums1 != nums2) {
		cout << "�����޸ĺ�ķ���\n";
		cin >> nums1;
		cout << "ȷ���޸ĺ�ķ���\n";
		cin >> nums2;
		if (nums1 != nums2) {
			cout << "�������벻һ������������\n";
			cout << "�˳����������� -1\n";
		}
		if (nums1 == "-1" && nums2 == "-1")return;
	}
	*it = nums1;
	cout << "�޸ĳɹ�\n";
}