#pragma once
#include"head.h"
/****************************************************************************************************************************
本项目中的图基于：无向连通图
用于模拟：旅游区景点导游（旅游区可表示为图，景点可表示为顶点）
作者：sixteenTang（github:anxiaoron）
****************************************************************************************************************************/
class Vertex {
private:
	int ID;					//景点唯一标识ID
	string name;			//景点名称
	string information;		//景点介绍
	friend class Graph;		//声明 Graph类 为友元类

public:
	friend ostream& operator<<(ostream& os, const Vertex& v);//声明 operator<< 为友元函数
	Vertex(int ID = -1, string name = "NULL", string information = "NULL") :ID(ID), name(name), information(information) { ; }
	Vertex(string s);//用文件内容初始化图时，在读取文件的每一行时，直接用读取到的一行初始化 vertex
	Vertex(const Vertex& v) :ID(v.ID), name(v.name), information(v.information) { ; }
	~Vertex() { ; }
	int getID() { return ID; }
	string getName() { return name; }
	string getInformation() { return information; }
	//void out_print();
	Vertex& operator=(const Vertex& v);
};

