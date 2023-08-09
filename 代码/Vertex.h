#pragma once
#include"head.h"
/****************************************************************************************************************************
����Ŀ�е�ͼ���ڣ�������ͨͼ
����ģ�⣺���������㵼�Σ��������ɱ�ʾΪͼ������ɱ�ʾΪ���㣩
���ߣ�sixteenTang��github:https://github.com/sixteeeenTang/DataStructureCourseDesign��
****************************************************************************************************************************/
class Vertex {
private:
	int ID;					//����Ψһ��ʶID
	string name;			//��������
	string information;		//�������
	friend class Graph;		//���� Graph�� Ϊ��Ԫ��

public:
	friend ostream& operator<<(ostream& os, const Vertex& v);//���� operator<< Ϊ��Ԫ����
	Vertex(int ID = -1, string name = "NULL", string information = "NULL") :ID(ID), name(name), information(information) { ; }
	Vertex(string s);//���ļ����ݳ�ʼ��ͼʱ���ڶ�ȡ�ļ���ÿһ��ʱ��ֱ���ö�ȡ����һ�г�ʼ�� vertex
	Vertex(const Vertex& v) :ID(v.ID), name(v.name), information(v.information) { ; }
	~Vertex() { ; }
	int getID() { return ID; }
	string getName() { return name; }
	string getInformation() { return information; }
	Vertex& operator=(const Vertex& v);
};

