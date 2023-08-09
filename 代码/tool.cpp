#include"head.h"
#include"Vertex.h"
#include"Graph.h"

void Stringsplit(const string& str, const string& split, vector<string>& res) {// strtok 版本的 Stringsplit 只能根据字符来分割
	char* strc = new char[str.size() + 1];
	strcpy(strc, str.c_str());	//将 str 拷贝到 strc 中
	char* temp = strtok(strc, split.c_str());
	while (temp != NULL) {
		res.push_back(string(temp));
		temp = strtok(NULL, split.c_str());
	}
	delete[] strc;
}
void Stringsplit(const string& str, const char split, vector<string>& res) {//避免上版本中 string 引发的误解
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
// DelLineData 此函数被我弃用了
// void DelLineData(const char* fileName, int lineNum) {//此函数删除指定行后，会在最后一行留下空行！
//	//复制文件内容（除了要删除的行）
//	ifstream in(fileName);
//	string strFileData = "";//将内容暂存在文件内容暂存其中，方便覆写
//	int line = 0;//行数从0开始计数
//	char lineData[1024] = { 0 };// getline() 每次最多读入1024
//	
//	while (in.getline(lineData, sizeof(lineData))) {
//		if (line == lineNum) {
//			//strFileData += "\n";
//		}
//		else {
//			strFileData += CharToStr(lineData);
//			strFileData += "\n";//这个地方将导致调用过此函数的文件的最后一行为空行！
//		}
//		line++;
//	}
//	in.close();
//	//写入文件
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
	cout << "请选择您要进行的操作" << endl;
	cout << "1、添加景点" << endl;
	cout << "2、删除景点" << endl;
	cout << "3、添加路径" << endl;
	cout << "4、删除路径" << endl;
	cout << "5、修改景点名称" << endl;
	cout << "6、修改景点介绍" << endl;
	cout << "7、修改路径距离" << endl;
	cout << "请输入数字:";
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
			cout << "请输入合法数字！" << endl;
			break;
		}
	} while (matching < 1 || matching>7);
	system("pause");
}
void fun2_1() {
	Graph g;
	cout << "请输入您想要添加的景点名称：";
	string name;
	cin >> name;
	cout << "请输入您想要为该新增景点的介绍：";
	string inf;
	cin >> inf;
	g.add_vex(Vertex(-1, name, inf));
}
void fun2_2() {
	Graph g;
	cout << "请输入您想要删除的景点名称：";
	string name;
	cin >> name;
	g.delete_vex(g.find_vertex_name(name));
}
void fun2_3() {
	Graph g;
	cout << "请输入您想要添加的路径的两个顶点景点名称：";
	string name1, name2;
	cin >> name1 >> name2;
	cout << "请输入这两个景点之间的距离：";
	int weight;
	cin >> weight;
	g.add_arc(g.find_vertex_name(name1), g.find_vertex_name(name2), weight);
}
void fun2_4() {
	Graph g;
	cout << "请输入您想要删除的路径的两个顶点景点名称：";
	string name1, name2;
	cin >> name1 >> name2;
	g.delete_arc(g.find_vertex_name(name1), g.find_vertex_name(name2));
}
void fun2_5() {
	Graph g;
	cout << "请输入您想要修改的景点名称：";
	string name1, name2;
	cin >> name1;
	cout << "请输入您想要将其修改为的名称：";
	cin >> name2;

	g.revise_vex_name(g.find_vertex_name(name1), name2);
}
void fun2_6() {
	Graph g;
	cout << "请输入您想要修改的景点介绍的景点名称：";
	string name, inf;
	cin >> name;
	cout << "请输入您想要将其介绍修改为的内容：";
	cin >> inf;
	g.revise_vex_information(g.find_vertex_name(name), inf);
}
void fun2_7() {
	Graph g;
	cout << "请输入您想要修改的景点路径的两个顶点景点：";
	string name1, name2;
	int weight;
	cin >> name1 >> name2;
	cout << "请输入您想要修改的景点路径距离为：";
	cin >> weight;

	g.revise_arc(g.find_vertex_name(name1), g.find_vertex_name(name2), weight);
}
void fun3() {
	Graph g;
	cout << "请输入您想要查询的景点名称：" << endl;
	string name;
	cin >> name;
	cout << g.find_vertex_name(name) << endl;
	g.print_nearby_vex(g.find_vertex_name(name));
	system("pause");
}
void fun4() {
	Graph g;
	cout << "请输入您想要查询的最短路径的景点：";
	string name;
	cin >> name;

	g.print_shortist_path(g.find_vertex_name(name));
	system("pause");
}
void fun5() {
	Graph g;
	cout << "请输入您想要查询的最短路径的两个端点景点：";
	string name1, name2;
	cin >> name1 >> name2;

	//g.print_shortist_path(g.find_vertex_name(name1));
	g.print_shortist_path(g.find_vertex_name(name1), g.find_vertex_name(name2));
	system("pause");
}
void fun6() {
	Graph g;
	cout << "请输入您想要查询的路径的两个端点景点：";
	string name1, name2;
	cin >> name1 >> name2;

	g.print_all_path(g.find_vertex_name(name1), g.find_vertex_name(name2));
	system("pause");
}
void fun7() {
	Graph g;
	cout << "请输入您希望得到的推荐路线的起点：";
	string name;
	cin >> name;

	g.print_recommended_path(g.find_vertex_name(name));
	system("pause");
}
void fun8() {
	cout << "感谢您使用本系统！" << endl;
	cout << "欢迎您下次使用o(*￣▽￣*)o" << endl;
	exit(1);
}
void fun_master() {
	Graph g;
	cout << g;
	exit(0);
}

void Menu() {

	cout << "--------------------------------------------------------------------------" << endl;
	cout << "|-----------------------欢迎来到旅游区景点导游系统-----------------------|" << endl;
	cout << "|-----------------------请输入数字选择您想要继续的操作-------------------|" << endl;
	cout << "|-----------------------1、查看所有景点信息------------------------------|" << endl;
	cout << "|-----------------------2、编辑景点信息----------------------------------|" << endl;
	cout << "|-----------------------3、查询具体景点信息------------------------------|" << endl;
	cout << "|-----------------------4、查询从单个景点出发到所有景点的最短路径和距离--|" << endl;
	cout << "|-----------------------5、查询两个景点间的最短路径和距离----------------|" << endl;
	cout << "|-----------------------6、查询两个景点间的所有简单路径和距离------------|" << endl;
	cout << "|-----------------------7、查询以您指定景点为起点的最佳游览路线----------|" << endl;
	cout << "|-----------------------8、退出系统--------------------------------------|" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "请输入数字:";
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
			cout << "请输入合法数字！" << endl;
			break;
		}
	} while (matching < 1 || matching>7);
	system("cls");
}
