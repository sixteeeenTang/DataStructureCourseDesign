#include"head.h"
#include"Vertex.h"

ostream& operator<<(ostream& os, const Vertex& v) {//������������
	cout << "ID:" << v.ID << "\t����:" << v.name << "\t����:" << v.information;
	return os;
}
Vertex::Vertex(string s) :ID(-1) {//�˹��캯�����������ļ���ȡ�У�
	vector<string> sList;
	Stringsplit(s, ' ', sList);
	this->ID = stoi(sList[0]);//ID
	this->name = sList[1];//��������
	this->information = sList[2];//������Ϣ

}
Vertex& Vertex::operator=(const Vertex& v) {
	ID = v.ID;
	name = string(v.name);
	information = string(v.information);
	return *this;
}