#include"head.h"
#include"Vertex.h"
#include"Graph.h"

void Stringsplit(const string& str, const string& split, vector<string>& res) {// strtok �汾�� Stringsplit ֻ�ܸ����ַ����ָ�
	char* strc = new char[str.size() + 1];
	strcpy(strc, str.c_str());	//�� str ������ strc ��
	char* temp = strtok(strc, split.c_str());
	while (temp != NULL) {
		res.push_back(string(temp));
		temp = strtok(NULL, split.c_str());
	}
	delete[] strc;
}
void Stringsplit(const string& str, const char split, vector<string>& res) {//�����ϰ汾�� string ���������
	Stringsplit(str, string(1, split), res);
}
string CharToStr(char* contentChar)
{
	string tempStr;
	for (int i = 0; contentChar[i] != '\0'; i++)
	{
		tempStr += contentChar[i];
	}
	return tempStr;
}
// DelLineData �˺�������������
// void DelLineData(const char* fileName, int lineNum) {//�˺���ɾ��ָ���к󣬻������һ�����¿��У�
//	//�����ļ����ݣ�����Ҫɾ�����У�
//	ifstream in(fileName);
//	string strFileData = "";//�������ݴ����ļ������ݴ����У����㸲д
//	int line = 0;//������0��ʼ����
//	char lineData[1024] = { 0 };// getline() ÿ��������1024
//	
//	while (in.getline(lineData, sizeof(lineData))) {
//		if (line == lineNum) {
//			//strFileData += "\n";
//		}
//		else {
//			strFileData += CharToStr(lineData);
//			strFileData += "\n";//����ط������µ��ù��˺������ļ������һ��Ϊ���У�
//		}
//		line++;
//	}
//	in.close();
//	//д���ļ�
//	ofstream out(fileName);
//	out.flush();
//	out << strFileData;
//	out.close();
//}

void fun1() {
	Graph g;
	g.print_all_vertex();
	system("pause");
}
void fun2() {
	Graph g;
	cout << "��ѡ����Ҫ���еĲ���" << endl;
	cout << "1����Ӿ���" << endl;
	cout << "2��ɾ������" << endl;
	cout << "3�����·��" << endl;
	cout << "4��ɾ��·��" << endl;
	cout << "5���޸ľ�������" << endl;
	cout << "6���޸ľ������" << endl;
	cout << "7���޸�·������" << endl;
	cout << "����������:";
	int matching;
	do {
		cin >> matching;
		switch (matching)
		{
		case 1:
			fun2_1();
			break;
		case 2:
			fun2_2();
			break;
		case 3:
			fun2_3();
			break;
		case 4:
			fun2_4();
			break;
		case 5:
			fun2_5();
			break;
		case 6:
			fun2_6();
			break;
		case 7:
			fun2_7();
			break;

		default:
			cout << "������Ϸ����֣�" << endl;
			break;
		}
	} while (matching < 1 || matching>7);
	system("pause");
}
void fun2_1() {
	Graph g;
	cout << "����������Ҫ��ӵľ������ƣ�";
	string name;
	cin >> name;
	cout << "����������ҪΪ����������Ľ��ܣ�";
	string inf;
	cin >> inf;
	g.add_vex(Vertex(-1, name, inf));
}
void fun2_2() {
	Graph g;
	cout << "����������Ҫɾ���ľ������ƣ�";
	string name;
	cin >> name;
	g.delete_vex(g.find_vertex_name(name));
}
void fun2_3() {
	Graph g;
	cout << "����������Ҫ��ӵ�·�����������㾰�����ƣ�";
	string name1, name2;
	cin >> name1 >> name2;
	cout << "����������������֮��ľ��룺";
	int weight;
	cin >> weight;
	g.add_arc(g.find_vertex_name(name1), g.find_vertex_name(name2), weight);
}
void fun2_4() {
	Graph g;
	cout << "����������Ҫɾ����·�����������㾰�����ƣ�";
	string name1, name2;
	cin >> name1 >> name2;
	g.delete_arc(g.find_vertex_name(name1), g.find_vertex_name(name2));
}
void fun2_5() {
	Graph g;
	cout << "����������Ҫ�޸ĵľ������ƣ�";
	string name1, name2;
	cin >> name1;
	cout << "����������Ҫ�����޸�Ϊ�����ƣ�";
	cin >> name2;

	g.revise_vex_name(g.find_vertex_name(name1), name2);
}
void fun2_6() {
	Graph g;
	cout << "����������Ҫ�޸ĵľ�����ܵľ������ƣ�";
	string name, inf;
	cin >> name;
	cout << "����������Ҫ��������޸�Ϊ�����ݣ�";
	cin >> inf;
	g.revise_vex_information(g.find_vertex_name(name), inf);
}
void fun2_7() {
	Graph g;
	cout << "����������Ҫ�޸ĵľ���·�����������㾰�㣺";
	string name1, name2;
	int weight;
	cin >> name1 >> name2;
	cout << "����������Ҫ�޸ĵľ���·������Ϊ��";
	cin >> weight;

	g.revise_arc(g.find_vertex_name(name1), g.find_vertex_name(name2), weight);
}
void fun3() {
	Graph g;
	cout << "����������Ҫ��ѯ�ľ������ƣ�" << endl;
	string name;
	cin >> name;
	cout << g.find_vertex_name(name) << endl;
	g.print_nearby_vex(g.find_vertex_name(name));
	system("pause");
}
void fun4() {
	Graph g;
	cout << "����������Ҫ��ѯ�����·���ľ��㣺";
	string name;
	cin >> name;

	g.print_shortist_path(g.find_vertex_name(name));
	system("pause");
}
void fun5() {
	Graph g;
	cout << "����������Ҫ��ѯ�����·���������˵㾰�㣺";
	string name1, name2;
	cin >> name1 >> name2;

	//g.print_shortist_path(g.find_vertex_name(name1));
	g.print_shortist_path(g.find_vertex_name(name1), g.find_vertex_name(name2));
	system("pause");
}
void fun6() {
	Graph g;
	cout << "����������Ҫ��ѯ��·���������˵㾰�㣺";
	string name1, name2;
	cin >> name1 >> name2;

	g.print_all_path(g.find_vertex_name(name1), g.find_vertex_name(name2));
	system("pause");
}
void fun7() {
	Graph g;
	cout << "��������ϣ���õ����Ƽ�·�ߵ���㣺";
	string name;
	cin >> name;

	g.print_recommended_path(g.find_vertex_name(name));
	system("pause");
}
void fun8() {
	cout << "��л��ʹ�ñ�ϵͳ��" << endl;
	cout << "��ӭ���´�ʹ��o(*������*)o" << endl;
	exit(1);
}
void fun_master() {
	Graph g;
	cout << g;
	exit(0);
}

void Menu() {

	cout << "--------------------------------------------------------------------------" << endl;
	cout << "|-----------------------��ӭ�������������㵼��ϵͳ-----------------------|" << endl;
	cout << "|-----------------------����������ѡ������Ҫ�����Ĳ���-------------------|" << endl;
	cout << "|-----------------------1���鿴���о�����Ϣ------------------------------|" << endl;
	cout << "|-----------------------2���༭������Ϣ----------------------------------|" << endl;
	cout << "|-----------------------3����ѯ���徰����Ϣ------------------------------|" << endl;
	cout << "|-----------------------4����ѯ�ӵ���������������о�������·���;���--|" << endl;
	cout << "|-----------------------5����ѯ�������������·���;���----------------|" << endl;
	cout << "|-----------------------6����ѯ�������������м�·���;���------------|" << endl;
	cout << "|-----------------------7����ѯ����ָ������Ϊ�����������·��----------|" << endl;
	cout << "|-----------------------8���˳�ϵͳ--------------------------------------|" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "����������:";
	int matching;
	do {
		cin >> matching;
		switch (matching)
		{
		case 1:
			fun1();
			break;
		case 2:
			fun2();
			break;
		case 3:
			fun3();
			break;
		case 4:
			fun4();
			break;
		case 5:
			fun5();
			break;
		case 6:
			fun6();
			break;
		case 7:
			fun7();
			break;
		case 8:
			fun8();
			break;
		case 999:
			fun_master();
			break;

		default:
			cout << "������Ϸ����֣�" << endl;
			break;
		}
	} while (matching < 1 || matching>7);
	system("cls");
}
