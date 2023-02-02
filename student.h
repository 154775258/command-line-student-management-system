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
		void pushData();//读入数据
		void writeData();//输出程序数据
		void enterClass();//进入班级
		void createClass();//创建班级
		void addStudentInClass(string& _class);//向班级添加学生
		void eraseStudentInClass(string& _class);//移除学生
		void eraseStudentInClass(string& nums,string& _class);
		void addStudent();//添加学生信息
		void eraseStudent();//删除学生信息
		void findStudentId();//用学生学号查找相关信息
		void findStudentName();//用学生姓名查找相关信息
		void findStudentId(string& id);
		void eraseClass();//删除班级
		void addDiscipline(string& _class);//添加科目
		int findDiscipline(string& _class, string& a);
		void eraseClassDiscipline(string& _class);//删除班级科目
		void reviseStudentScores();//修改学生成绩
		int findClassId(string& id,string& tmp) {
			for (int i = 0; i < classStudentId[tmp].size(); i++) {
				if (classStudentId[tmp][i] == id)return i;
			}
			return -1;
		}

		bool check(string& a) {
			if (a.size() < 2) {
				cout << "班级名过短请重新输入\n";
				return 0;
			}
			else if (a.size() > 16) {
				cout << "班级名过长请重新输入\n";
				return 0;
			}
			else if (classStudentId.count(a)) {
				cout << "该班级名已存在请重新输入\n";
				return 0;
			}
			return 1;
		}
	private:
	ofstream writeFile;//存数据文件指针
	ifstream putFile;//取数据文件指针
	vector<string> classId;//存班级的地方
	unordered_map<string, vector<string>> classStudentId;//每个班级都有那些学生
	unordered_map<string, vector<string>> classDiscipline;//每个班级都有那些科目
	unordered_map<string, string> studentClass;//每个学生所在班级
	unordered_map<string, vector<string>>studentScores;//每个学生的成绩 学号对应成绩
	unordered_map<string, vector<string>>studentName;//学生姓名以及他或他们的学号
	unordered_map<string, string>nameId;//学号对应姓名
};

student::student() {
	cout << "读取数据中\n";
	pushData();
	while (1) {
		cout << "当前班级有:\n";
		for (int i = 0; i < classId.size(); i++) {
			cout << classId[i] << '\n';
			if (i & 1)cout << '\n';
		}
		cout << "输入编号选择操作\n";
		cout << "1.进入班级,          2.使用学生学号查找\n";
		cout << "3.使用学生姓名查找,  4.创建班级\n";
		cout << "5.保存不退出,        6保存并退出\n";
		cout << "7,添加学生信息,      8.移除学生信息\n";
		cout << "9,移除班级\n";
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
		default:cout << "不知道你要干啥所以就是1111111了！\n"; enterClass(); break;
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
	cout << "输入班级名,退出输入0\n";
	cin >> tmp;
	if (tmp == "0")
		return;
	while (!classStudentId.count(tmp)) {
		cout << "未查找到此班级从检查后重新输入\n";
		cin >> tmp;
		if (tmp == "0")
			return;
	}
	for (int i = 0; i < classStudentId[tmp].size(); i++) {
		string t1 = classStudentId[tmp][i];
		cout << "学号:" << t1 << " " << "姓名:" << nameId[t1] << " ";
		for (int j = 0; j < studentScores[t1].size(); j++) {
			cout << "科目:" << classDiscipline[tmp][j] << ":" << studentScores[t1][j] << "   ";
		}
		cout << '\n';
	}
	while (1) {
		cout << "1.添加班级科目,  2.修改学生成绩\n";
		cout << "3.添加学生,      4,移除学生\n";
		cout << "5.删除班级科目,   0退回上一目录\n";
		int nums;
		cin >> nums;
		switch (nums) {
		case 1:addDiscipline(tmp); break;
		case 2:reviseStudentScores(); break;
		case 3:addStudentInClass(tmp); break;
		case 4:eraseStudentInClass(tmp); break;
		case 5:eraseClassDiscipline(tmp); break;
		case 0:cout << "编辑结束记得保存!\n"; system("cls"); return;
		default:cout << "不知道你要干啥就帮您退出界面了记得保存哦！\n"; system("cls");  return;
		}
		system("cls");
	}
}

void student::addDiscipline(string& _class) {
	string Discipline;
	cout << "输入你要添加的科目名称\n";
	cin >> Discipline;
	while (findDiscipline(_class, Discipline) != -1) {
		cout << "您输入的科目名称已存在\n";
		cout << "请重新输入\n";
		cin >> Discipline;
	}
	classDiscipline[_class].push_back(Discipline);
	cout << classDiscipline[_class].back() << '\n';
	for (int i = 0; i < classStudentId[_class].size(); i++) {
		studentScores[classStudentId[_class][i]].push_back("-1");
	}
	cout << "添加成功\n";
}

void student::createClass() {
	cout << "输入班级名\n";
	string tmp;
	cin >> tmp;
	while (!check(tmp))cin >> tmp;
	classId.push_back(tmp);
	classStudentId[tmp].push_back("text");
	cout << "添加成功\n";
}

void student::addStudentInClass(string& _class) {
	string nums,name;
	cout << "输入学生学号\n";
	cin >> nums;
	while (!nameId.count(nums) || findClassId(nums,_class) != -1) {
		cout << "在本学校内未查找到该学号是否未添加或输入错误或该学生已存在与该班级\n";
		cout << "请重新输入 退出输入0\n";
		cin >> nums;
		if (nums == "0")return;
	}
	if (classStudentId[_class][0] == "text")classStudentId[_class][0] = nums;
	else
	classStudentId[_class].push_back(nums);
	//cout << classStudentId[_class][0] << '\n';
	studentClass[nums] = _class;
	studentScores[_class].resize(classDiscipline[_class].size(), "-1");
	cout << "添加成功\n";
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
	cout << "输入你要移除学生的学号\n";
	cin >> id;
	while (findClassId(id, _class) == -1){
		cout << "该班级没有此学号学生，请检查是否输入正确\n";
		cout << "请重新输入\n";
		cout << "请重新输入 退出输入0\n";
		cin >> id;
		if (id == "0")return;
	}
	auto it = classStudentId[_class].begin();
	it += findClassId(id, _class);
	classStudentId[_class].erase(it);
	studentScores.erase(id);
	studentClass.erase(id);
	cout << "删除成功\n";
}

void student::addStudent() {
	string nums,name;
	cout << "输入学生学号\n";
	cin >> nums;
	while (nameId.count(nums)) {
		cout << "该学号已存在\n请重新输入\n";
		cout << "退出输入0\n";
		cin >> nums;
		if (nums == "0")return;
	}
	first:
	cout << "输入学生姓名\n";
	cin >> name;
	cout << "姓名是否输入正确 正确输入 1 不正确输入 0 并重新输入\n";
	int t;
	cin >> t;
	if (t == 0)goto first;
	nameId[nums] = name;
	studentName[name].push_back(nums);
	cout << "添加成功\n";
}

void student::eraseStudent() {
	string id;
	cout << "请输入要移除学生的学号\n";
	cin >> id;
	while (!nameId.count(id)) {
		cout << "寻找不到该学号请检查是否有误并重新输入\n";
		cout << "退出输入0\n";
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
	cout << "删除成功\n";
}

void student::findStudentId() {
	string id;
	cout << "输入要查找的学号\n";
	cin >> id;
	while (!nameId.count(id)) {
		cout << "系统中没有此学号请确认是否输入正确\n";
		cout << "请重新输入 退出输入0\n";
		cin >> id;
		if (id == "0")return;
	}
	cout << "学号: " << id << ' ';
	if (studentClass.count(id)) {
		cout << "班级：";
		cout << studentClass[id] << "   ";
	}
	else {
		cout << "该学生暂无班级   ";
	}
	cout << "姓名: " << nameId[id] << ' ';
	cout << "成绩:\n";
	for (int i = 0; i < studentScores[id].size(); i++) {
		cout << classDiscipline[studentClass[id]][i] << ":" << studentScores[id][i] << '\n';
	}
}

void student::findStudentName() {
	string name;
	cout << "输入你要查找的名字\n";
	cin >> name;
	while (!studentName.count(name)) {
		cout << "该系统内未包含此姓名\n";
		cout << "请重新输入 退出输入0\n";
		cin >> name;
		if (name == "0")return;
	}
	for (int i = 0; i < studentName[name].size(); i++) {
		findStudentId(studentName[name][i]);
		cout << '\n';
	}
}

void student::findStudentId(string& id) {
	cout << "学号: " << id << ' ';
	if (studentClass.count(id)) {
		cout << studentClass[id] << "   ";
	}
	else {
		cout << "该学生暂无班级   ";
	}
	cout << "姓名: " << nameId[id] << ' ';
	cout << "成绩:\n";
	for (int i = 0; i < studentScores[id].size(); i++) {
		cout << classDiscipline[studentClass[id]][i] << ":" << studentScores[id][i] << '\n';
	}
}

void student::eraseClass() {
	string _class;
	cout << "输入要移除的班级\n";
	cin >> _class;
	while (!classStudentId.count(_class)) {
		cout << "未找到你要移除的班级\n";
		cout << "请重新输入 退出输入0\n";
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
	cout << "删除成功\n";
}

int student::findDiscipline(string& _class,string& a) {
	for (int i = 0; i < classDiscipline[_class].size(); i++) {
		if (classDiscipline[_class][i] == a)return i;
	}
	return -1;
}

void student::eraseClassDiscipline(string& _class) {
	string Discipline;
	cout << "输入你要删除的科目名称\n";
	cin >> Discipline;
	while (findDiscipline(_class, Discipline) == -1) {
		cout << "您输入的科目名称不存在\n";
		cout << "请重新输入 退出输入0\n";
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
	cout << "删除成功\n";
}

void student::reviseStudentScores() {
	string id;
	cout << "输入你要修改成绩的学生学号\n";
	cin >> id;
	while (!nameId.count(id)) {
		cout << "未查找到您输入的学号是否是输入错误\n";
		cout << "请重新输入 退出输入0\n";
		cin >> id;
		if (id == "0")return;
	}
	cout << "科目有：\n";
	for (int i = 0; i < classDiscipline[studentClass[id]].size(); i++) {
		cout << classDiscipline[studentClass[id]][i] << '\n';
	}
	string Discipline;
	cout << "输入你要修改的学生科目\n";
	cin >> Discipline;
	while (findDiscipline(studentClass[id], Discipline) == -1) {
		cout << "未找到您要修改的科目\n";
		cout << "请重新输入 退出输入0\n";
		cin >> Discipline;
		if (Discipline == "0")return;
	}
	int t = findDiscipline(studentClass[id], Discipline);
	auto it = studentScores[id].begin();
	it += t;
	string nums1 = "-1", nums2 = "0";
	while (nums1 != nums2) {
		cout << "输入修改后的分数\n";
		cin >> nums1;
		cout << "确定修改后的分数\n";
		cin >> nums2;
		if (nums1 != nums2) {
			cout << "两次输入不一样请重新输入\n";
			cout << "退出请输入两次 -1\n";
		}
		if (nums1 == "-1" && nums2 == "-1")return;
	}
	*it = nums1;
	cout << "修改成功\n";
}