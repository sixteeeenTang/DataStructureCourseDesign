#pragma once
#include"head.h"
#include"Vertex.h"
/****************************************************************************************************************************
本项目中的图基于：无向连通图
用于模拟：旅游区景点导游（旅游区可表示为图，景点可表示为顶点）
作者：sixteenTang（github:anxiaoron）
****************************************************************************************************************************/
class Graph {//无向连通图
private:
	friend ostream& operator<<(ostream& os, const Graph& p);//声明 operator<< 为友元函数
	size_t vexnum, arcnum;//图中顶点数和弧数
	vector<Vertex> vexs;//顶点向量
	int** arcs;//邻接矩阵

public:
	Graph(string vex = "景点信息.txt", string path = "路径信息.txt");
	Graph(const Graph& g);
	~Graph();
	size_t getVexnum() { return vexnum; }
	size_t getArcnum() { return arcnum; }
	Vertex find_vertex_ID(int ID);//通过 ID查找顶点
	Vertex find_vertex_name(string name);//通过 name查找顶点
	bool vex_exist(Vertex v);//通过 名称来判断此顶点是否已经存在
	bool vex_exist(int ID);//通过 ID来判断此顶点是否已经存在
	void update_Graph();//更新 图中的顶点信息和弧信息到文件中
	void add_vex(Vertex v);//添加 顶点
	void add_arc(Vertex v1, Vertex v2, int weight);//添加 弧
	void delete_vex(Vertex v);//删除 顶点
	void delete_arc(Vertex v1, Vertex v2);//删除 弧（该函数不提示弧不存在时候的错误，因为它将在 delete_vex() 中调用）
	void revise_vex_name(Vertex v, string n);//修改 顶点名称
	void revise_vex_information(Vertex v, string inf);//修改 顶点介绍
	void revise_arc(Vertex v1, Vertex v2, int weight);//修改 弧的信息
	/***********************************************************************************************************************/
	void demo_lamda(int n);
	/***********************************************************************************************************************/
	void print_nearby_vex(Vertex v);//打印 与 v 相邻的顶点
	void Dijkstra(Vertex v, int* prev, int* dist);//Dijkstra算法
	void print_all_vertex();//打印 所有顶点的信息
	void print_shortist_path(Vertex v1, Vertex v2);//打印 顶点v1与v2之间的最短路径 以及距离
	void print_all_path(Vertex v1, Vertex v2);//打印 顶点v1到v2之间的所有简单路径
	void print_recommended_path(Vertex v);//打印 以顶点v为起点遍历所有顶点
};

