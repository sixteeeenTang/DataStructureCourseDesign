#include"head.h"
#include"Vertex.h"

ostream& operator<<(ostream& os, const Vertex& v) {//重载输出运算符
	cout << "ID:" << v.ID << "\t名称:" << v.name << "\t介绍:" << v.information;
	return os;
}
Vertex::Vertex(string s) :ID(-1) {//此构造函数必须用在文件读取中！
	vector<string> sList;
	Stringsplit(s, ' ', sList);
	this->ID = stoi(sList[0]);//ID
	this->name = sList[1];//景点名称
	this->information = sList[2];//景点信息

}
Vertex& Vertex::operator=(const Vertex& v) {
	ID = v.ID;
	name = string(v.name);
	information = string(v.information);
	return *this;
}