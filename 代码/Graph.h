#pragma once
#include"head.h"
#include"Vertex.h"
/****************************************************************************************************************************
����Ŀ�е�ͼ���ڣ�������ͨͼ
����ģ�⣺���������㵼�Σ��������ɱ�ʾΪͼ������ɱ�ʾΪ���㣩
���ߣ�sixteenTang��github:https://github.com/sixteeeenTang/DataStructureCourseDesign��
****************************************************************************************************************************/
class Graph {//������ͨͼ
private:
	friend ostream& operator<<(ostream& os, const Graph& p);//���� operator<< Ϊ��Ԫ����
	size_t vexnum, arcnum;//ͼ�ж������ͻ���
	vector<Vertex> vexs;//��������
	int** arcs;//�ڽӾ���

public:
	Graph(string vex = "������Ϣ.txt", string path = "·����Ϣ.txt");
	Graph(const Graph& g);
	~Graph();
	size_t getVexnum() { return vexnum; }
	size_t getArcnum() { return arcnum; }
	Vertex find_vertex_ID(int ID);//ͨ�� ID���Ҷ���
	Vertex find_vertex_name(string name);//ͨ�� name���Ҷ���
	bool vex_exist(Vertex v);//ͨ�� �������жϴ˶����Ƿ��Ѿ�����
	bool vex_exist(int ID);//ͨ�� ID���жϴ˶����Ƿ��Ѿ�����
	void update_Graph();//���� ͼ�еĶ�����Ϣ�ͻ���Ϣ���ļ���
	void add_vex(Vertex v);//��� ����
	void add_arc(Vertex v1, Vertex v2, int weight);//��� ��
	void delete_vex(Vertex v);//ɾ�� ����
	void delete_arc(Vertex v1, Vertex v2);//ɾ�� �����ú�������ʾ��������ʱ��Ĵ�����Ϊ������ delete_vex() �е��ã�
	void revise_vex_name(Vertex v, string n);//�޸� ��������
	void revise_vex_information(Vertex v, string inf);//�޸� �������
	void revise_arc(Vertex v1, Vertex v2, int weight);//�޸� ������Ϣ
	/***********************************************************************************************************************/
	void demo_lamda(int n);
	/***********************************************************************************************************************/
	void print_nearby_vex(Vertex v);//��ӡ �� v ���ڵĶ���
	void Dijkstra(Vertex v, int* prev, int* dist);//Dijkstra�㷨
	void print_all_vertex();//��ӡ ���ж������Ϣ
	void print_shortist_path(Vertex v1, Vertex v2);//��ӡ ����v1��v2֮������·�� �Լ�����
	void print_shortist_path(Vertex v1);//��ӡ ����v�������ܵ���Ķ�������·�� �Լ�����
	void print_all_path(Vertex v1, Vertex v2);//��ӡ ����v1��v2֮������м�·��
	void print_recommended_path(Vertex v);//��ӡ �Զ���vΪ���������ж���
};


