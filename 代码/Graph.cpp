#include"Graph.h"

ostream& operator<<(ostream& os, const Graph& g) {//重载输出运算符，打印邻接矩阵
	Graph gg(g);//必须拷贝才可以访问 gg.vexs
	cout << "当前图中具有的顶点数量为：" << gg.vexnum << endl;
	cout << "当前图中具有的弧数量为：" << gg.arcnum << endl;
	cout << "图的邻接矩阵表示为：" << endl;
	for (int i = 0; i < gg.vexnum; i++) {
		cout << "\t\t" << gg.vexs[i].getName();
	}
	cout << endl;
	for (int i = 0; i < gg.vexnum; i++) {
		cout << gg.vexs[i].getName();
		for (int j = 0; j < gg.vexnum; j++) {
			if (gg.arcs[i][j] == INF) {
				cout << "\t\t" << "INF";
			}
			else {
				cout << "\t\t" << gg.arcs[i][j];
			}
		}
		cout << endl << endl;
	}

	return os;
}
Graph::Graph(string vex, string path) :vexnum(0), arcnum(0), arcs(nullptr) {
	//初始化邻接矩阵
	arcs = new int* [MAX_VERTEX_NUM];
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		arcs[i] = new int[MAX_VERTEX_NUM]();//初始化为 999999
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			arcs[i][j] = INF;
		}
		arcs[i][i] = 0;
	}
	//打开文件
	ifstream inf_vex(vex);
	ifstream inf_path(path);
	if (!inf_vex.is_open()) {
		cout << "景点信息文件打开失败！图初始化失败！" << endl;
	}
	if (!inf_path.is_open()) {
		cout << "路径信息文件打开失败！图初始化失败！" << endl;
	}
	//录入景点信息
	string s1;
	while (getline(inf_vex, s1)) {
		if (s1.empty()) {//处理空行
			break;
		}
		vexnum++;
		vexs.push_back(Vertex(s1));//将顶点信息录入顶点向量中
	}
	//录入路径信息
	string s2;
	while (getline(inf_path, s2)) {
		if (s2.empty()) {//处理空行
			break;
		}
		vector<string> pathList;//暂存放一行的路径信息 string类
		Stringsplit(s2, '-', pathList);//分割每一行路径信息 string类
		try {
			//检查路径中是否存在非法景点ID
			if (!vex_exist(stoi(pathList[0])) || !vex_exist(stoi(pathList[1]))) {
				throw "路径文件中存在非法路径，请修改！";
			}
			arcs[stoi(pathList[0])][stoi(pathList[1])] = stoi(pathList[2]);//将路径信息存放到邻接矩阵中
			arcs[stoi(pathList[1])][stoi(pathList[0])] = stoi(pathList[2]);
			arcnum++;
		}
		catch (const char* msg) {
			cerr << msg << endl;
			exit(-1);
		}

	}
	//关闭文件
	inf_vex.close();
	inf_path.close();
}
Graph::Graph(const Graph& g) :vexnum(g.vexnum), arcnum(g.arcnum) {
	//顶点向量拷贝
	this->vexs.assign(g.vexs.begin(), g.vexs.end());
	//初始化邻接矩阵
	arcs = new int* [MAX_VERTEX_NUM];
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		arcs[i] = new int[MAX_VERTEX_NUM]();//初始化为 999.99
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			arcs[i][j] = INF;
		}
		arcs[i][i] = 0;
	}
	//拷贝邻接矩阵
	/*copy(&g.arcs[0][0], &g.arcs[0][0] + MAX_VERTEX_NUM * MAX_VERTEX_NUM, &arcs[0][0]);*/
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			arcs[i][j] = g.arcs[i][j];
		}
	}
	//作者是 十六躺
}
Graph::~Graph() {
	//析构邻接矩阵
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		delete[]arcs[i];
	}
	delete[]arcs;
	//cout << "~Graph()被调用了" << endl;
	//作者是 十六躺
}
Vertex Graph::find_vertex_ID(int ID) {//通过 ID查找顶点
	for (int i = 0; i < vexnum; i++) {
		if (ID == vexs[i].getID()) {
			return vexs[i];
		}
	}
	cout << "查无此ID！" << endl;
	return Vertex();
}
Vertex Graph::find_vertex_name(string name) {//通过 name查找顶点
	for (int i = 0; i < vexnum; i++) {
		if (name == vexs[i].getName()) {
			return vexs[i];
		}
	}
	cout << "查无此name！" << endl;
	return Vertex();
}
bool Graph::vex_exist(Vertex v) {//通过 名称来判断此顶点是否已经存在
	for (int i = 0; i < vexnum; i++) {
		if (v.getName() == this->vexs[i].getName()) {
			return true;
		}
	}
	return false;
}
bool Graph::vex_exist(int ID) {//通过 ID来判断此顶点是否已经存在
	for (int i = 0; i < vexnum; i++) {
		if (ID == this->vexs[i].getID()) {
			return true;
		}
	}
	return false;
}
void Graph::update_Graph() {//更新 图中的顶点信息和弧信息到文件中
	ofstream out_vex("景点信息.txt");
	if (!out_vex.is_open()) {
		cout << "景点信息文件打开失败！" << endl;
	}
	ofstream out_arc("路径信息.txt");
	if (!out_arc.is_open()) {
		cout << "路径信息文件打开失败！" << endl;
	}
	//写入景点信息
	for (int i = 0; i < vexnum; i++) {
		out_vex << this->vexs[i].ID << " " << this->vexs[i].name << " " << this->vexs[i].information << "\n";
	}
	//写入路径信息
	for (int i = 0; i < vexnum; i++) {
		for (int j = 0; j <= i; j++) {
			if ((this->arcs[i][j] != INF) && (this->arcs[i][j] != 0)) {
				out_arc << i << "-" << j << "-" << this->arcs[i][j] << "\n";
			}
		}
	}
	//关闭文件
	out_vex.close();
	out_arc.close();
}
void Graph::add_vex(Vertex v) {//添加 顶点
	//先判断此顶点是否已经存在
	if (this->vex_exist(v)) {
		cout << "名称为\"" << v.name << "\"的顶点已经存在，无法添加顶点！" << endl;
		return;
	}
	//添加顶点 push_back到vexs最后，并且修改此顶点的ID
	v.ID = this->vexnum;
	this->vexs.push_back(v);
	vexnum++;
	//更新 文件
	update_Graph();
}
void Graph::add_arc(Vertex v1, Vertex v2, int weight) {//添加 弧
	if (weight == INF) {
		cout << INF << "表示没有弧，因此不可以将其作为修改的弧信息！" << endl;
		return;
	}
	if (weight == 0) {
		cout << 0 << "表示顶点重合，因此不可以将其作为修改的弧信息！" << endl;
		return;
	}
	if (weight < 0) {
		cout << "不可以有负权值！" << endl;
		return;
	}
	//先判断顶点是否存在
	if ((!this->vex_exist(v1)) || (!this->vex_exist(v2))) {
		cout << "有顶点不存在图中，无法添加弧！" << endl;
		return;
	}
	//判断弧是否已经存在 已经存在则提示错误！
	if ((this->arcs[v1.ID][v2.ID] != INF) || (this->arcs[v2.ID][v1.ID] != INF)) {
		cout << "从\"" << v1.name << "\"到\"" << v2.name << "\"的弧已经存在，无法添加弧！" << endl;
		return;
	}
	//添加弧
	arcnum++;
	this->arcs[v1.getID()][v2.getID()] = weight;
	this->arcs[v2.getID()][v1.getID()] = weight;
	//更新 文件
	update_Graph();
}
void Graph::delete_vex(Vertex v) {//删除 该顶点以及该顶点所具有的弧
	//先判断此顶点是否已经存在
	if (!this->vex_exist(v)) {
		cout << "此顶点不存在，无法删除顶点！" << endl;
		return;
	}
	//删除顶点 先删除与其相连的所有弧然后删除该顶点
	for (int i = 0; i < this->vexnum; i++) {
		if (i == v.ID) {//当遍历到自己顶点的时候跳过
			continue;
		}
		this->delete_arc(this->vexs[i], v);
	}
	auto iter = this->vexs.erase(this->vexs.begin() + v.ID);
	this->vexnum--;
	for (int i = 0; i < vexnum; i++) {
		this->vexs[i].ID = i;
	}
	//更新 文件
	update_Graph();
}
void Graph::delete_arc(Vertex v1, Vertex v2) {//删除 弧（该函数不提示弧不存在（即弧长度为 INF）时候的“错误”，因为它将在 delete_vex() 中调用）
	//先判断顶点是否存在
	if ((!this->vex_exist(v1)) || (!this->vex_exist(v2))) {
		cout << "有顶点不存在图中，无法删除弧！" << endl;
		return;
	}
	//两个顶点相同不可以删除
	if (v1.name == v2.name) {
		cout << "两个顶点相同，不可以删除！" << endl;
		return;
	}
	//删除弧
	if ((arcs[v1.getID()][v2.getID()] != INF) && (arcs[v2.getID()][v1.getID()] != INF)) {
		this->arcnum--;
		this->arcs[v1.getID()][v2.getID()] = INF;
		this->arcs[v2.getID()][v1.getID()] = INF;
	}

	//更新 文件
	update_Graph();
}
void Graph::revise_vex_name(Vertex v, string n) {//修改 顶点名称
	if (!vex_exist(v)) {
		cout << "该顶点不存在！" << endl;
		return;
	}
	//修改顶点名称
	this->vexs[v.ID].name = n;
	//更新 文件
	update_Graph();
}
void Graph::revise_vex_information(Vertex v, string inf) {//修改 顶点介绍
	if (!vex_exist(v)) {
		cout << "该顶点不存在！" << endl;
		return;
	}
	//修改顶点名称
	this->vexs[v.ID].information = inf;
	//更新 文件
	update_Graph();
}
void Graph::revise_arc(Vertex v1, Vertex v2, int weight) {//修改 弧的信息
	//先判断顶点是否存在
	if (weight == INF) {
		cout << INF << "表示没有弧，因此不可以将其作为修改的弧信息！" << endl;
		return;
	}
	if (weight == 0) {
		cout << 0 << "表示顶点重合，因此不可以将其作为修改的弧信息！" << endl;
		return;
	}
	if (weight < 0) {
		cout << "不可以有负权值！" << endl;
		return;
	}
	if ((!this->vex_exist(v1)) || (!this->vex_exist(v2))) {
		cout << "有顶点不存在图中，无法修改弧！" << endl;
		return;
	}
	//判断弧是否存在 不存在则提示错误！
	if ((this->arcs[v1.ID][v2.ID] == INF) || (this->arcs[v2.ID][v1.ID] == INF)) {
		cout << "从\"" << v1.name << "\"到\"" << v2.name << "\"的弧不存在，无法修改弧！请先添加弧！" << endl;
		return;
	}
	//修改弧
	this->arcs[v1.ID][v2.ID] = weight;
	this->arcs[v2.ID][v1.ID] = weight;
	//更新 文件
	update_Graph();
}
/***********************************************************************************************************************/
/*以下内容请付费观看诶嘿*/
void Graph::demo_lamda(int n) {
	const auto& DFS = [](const int& n) {
		function<int(const int&)>x;
		x = [&](const int& n) {
			return n == 1 ? 1 : n + x(n - 1);
		};
		return x(n);
	};
	cout << DFS(n);
}
/***********************************************************************************************************************/
void Graph::print_nearby_vex(Vertex v) {//打印 与 v 相邻的顶点
	if (!vex_exist(v)) {
		cout << "此顶点不存在，无法查询！" << endl;
		return;
	}
	cout << "与\"" << v.name << "\"相邻的顶点有：" << endl;
	//在邻接矩阵中查询
	for (int i = 0; i < this->vexnum; i++) {
		if (this->arcs[v.ID][i] != INF && this->arcs[v.ID][i] != 0) {
			cout << this->vexs[i];
			cout << "。\t\t\"" << v.name << "\"与\"" << this->vexs[i].name << "\"的距离为:" << this->arcs[v.ID][i] << endl;
		}
	}
}
void Graph::Dijkstra(Vertex v, int* prev, int* dist) {
	if (!vex_exist(v)) {
		cout << "此顶点不存在，无法查询！" << endl;
		return;
	}
	int* vis = new int[this->vexnum]();//初始化辅助数组 判断该点是否有最短路径
	int i, j, k;
	int min, tmp;
	//初始化
	for (i = 0; i < this->vexnum; i++) {
		vis[i] = 0;//所有顶点均未有最短路径
		prev[i] = v.ID;//所有顶点的前驱顶点为 v.ID
		dist[i] = this->arcs[v.ID][i];//最短路径值
	}
	//对起点 v 的相关数据初始化
	vis[v.ID] = 1;
	dist[v.ID] = 0;
	//遍历 vexnum-1 次；每次找出一个顶点的最短路径
	for (i = 1; i < this->vexnum; i++) {
		//寻找当前最小的路径，在未获取最短路径的顶点中，找到离起点 v 最近的顶点 k
		min = INF;//初始为 INF 方便更新最小值
		for (j = 0; j < this->vexnum; j++) {
			if (vis[j] == 0 && dist[j] < min) {
				min = dist[j];
				k = j;
			}
		}
		//标记 顶点k 为已经获取到最短路径
		vis[k] = 1;

		//更新 未获取最短路径的顶点的最短路径和前驱顶点
		for (j = 0; j < this->vexnum; j++) {
			tmp = (this->arcs[k][j] == INF ? INF : (min + this->arcs[k][j]));//防止溢出
			if (vis[j] == 0 && (tmp < dist[j])) {
				dist[j] = tmp;
				prev[j] = k;
			}
		}
	}

}
void Graph::print_all_vertex() {
	for (int i = 0; i < this->vexnum; i++) {
		cout << this->find_vertex_ID(i) << endl;
	}
}
void Graph::print_shortist_path(Vertex v1, Vertex v2) {//打印 顶点v1与v2之间的最短路径以及距离，默认v1为起点，v2为终点
	//先判断顶点是否存在
	if ((!this->vex_exist(v1)) || (!this->vex_exist(v2))) {
		cout << "两个点中有顶点不存在图中，无法打印两个顶点之间的最短路径！" << endl;
		return;
	}
	//调用Dijkstra()
	int* prev = new int[this->vexnum];
	int* dist = new int[this->vexnum];
	this->Dijkstra(v2, prev, dist);
	//输出顶点v1与v2的最短路径以及距离
	cout << "从\"" << v1.name << "\"到\"" << v2.name << "\"的最短路径为：\t";
	for (int i = v1.ID; i != v2.ID; i = prev[i]) {
		if (i == v1.ID) {
			cout << (this->find_vertex_ID(i)).name;
		}
		else {
			cout << "->" << (this->find_vertex_ID(i)).name;
		}
	}
	cout << "->" << v2.name;
	cout << "\t\t\t距离为：" << dist[v1.ID] << endl;
}
void Graph::print_shortist_path(Vertex v) {//打印 顶点v到所有能到达的顶点的最短路径 以及距离
	//先判断顶点是否存在
	if (!this->vex_exist(v)) {
		cout << "顶点不存在图中，无法打印最短路径！" << endl;
		return;
	}
	for (int i = 0; i < vexnum; i++) {
		if (i == v.ID) {
			continue;
		}
		this->print_shortist_path(find_vertex_ID(i), v);
	}
}
void Graph::print_all_path(Vertex v1, Vertex v2) {//打印 从顶点v1到v2之间的所有简单路径
	if ((!this->vex_exist(v1)) || (!this->vex_exist(v2))) {
		cout << "两个点中有顶点不存在图中，无法打印两个顶点之间的路径！" << endl;
		return;
	}
	int start = v1.ID, dest = v2.ID;
	int path_list_num = 1;
	int distance = 0;//初始化距离为0
	int* vis = new int[this->vexnum]();//标记顶点是否访问
	int* stack = new int[this->vexnum]();//模拟栈
	int top = -1;//栈顶指针

	//此处稍微学习并使用了lamda表达式
	const auto& DFS = [&](const int& start) {
		function<void(const int&)>ddffss;//必须通过 function来用函数指针的方式进入函数递归
		ddffss = [&](const int& now) {
			vis[now] = 1;
			stack[++top] = now;
			/************************************************************************************************/
			/*此部分为递归结束*/
			if (now == dest) {
				//打印路径
				cout << "从\"" << v1.name << "\"到\"" << v2.name << "\"的第" << path_list_num++ << "条路为:\t";
				for (int j = 0; j < top; j++) {
					cout << this->find_vertex_ID(stack[j]).name << "->";
				}
				cout << this->find_vertex_ID(stack[top]).name << "\t\t\t距离为：" << distance << endl;
			}
			/************************************************************************************************/
			for (int i = 0; i < this->vexnum; i++) {
				if (vis[i] == 0 && this->arcs[now][i] < INF) {//遍历所有顶点，当顶点未被访问且该顶点与起点之间没有直达路径时，进入递归
					distance += this->arcs[now][i];
					ddffss(i);
					distance -= this->arcs[now][i];
				}
			}
			top--;
			vis[now] = 0;
		};
		ddffss(start);//调用 ddffss()
	};
	DFS(start);//调用 DFS()

	//还需要找出两个点之间的最短路径和距离
	this->print_shortist_path(v1, v2);
}
void Graph::print_recommended_path(Vertex v) {//打印 以顶点v为起点遍历所有顶点
	if (!vex_exist(v)) {
		cout << "此顶点不存在，无法查询！" << endl;
		return;
	}
	int* vis = new int[this->vexnum]();//标记顶点是否访问
	vis[v.ID] = 1;
	//判断是否已经遍历了所有顶点
	const auto& ifend = [=]() {
		for (int i = 0; i < vexnum; i++) {
			if (vis[i] == 0) {
				return 0;
			}
		}
		return 1;
	};

	vector<int> path_list;
	path_list.push_back(v.ID);//先将起点放入
	for (int i = v.ID; !ifend(); ) {
		int* prev = new int[this->vexnum]();
		int* dist = new int[this->vexnum]();
		vis[i] = 1;//当前顶点已被访问
		int next_vex;
		for (int j = 0; j < vexnum; j++) {//初始化 next_vex
			if (!vis[j]) {
				next_vex = j;
			}
		}
		this->Dijkstra(this->find_vertex_ID(i), prev, dist);//对当前所处顶点调用 Dijkstra()

		for (int j = 0; j < this->vexnum; j++) {
			if (!vis[j]) {
				next_vex = dist[j] < dist[next_vex] ? j : next_vex;//找出离当前所处顶点最近的顶点 next_vex
			}
		}
		if (ifend()) {
			break;
		}
		//找出路径放入 path_list 中
		vector<int> temp;
		for (int j = next_vex; j != i; j = prev[j]) {
			temp.insert(temp.begin(), j);//从头部开始的地方插入
		}
		path_list.insert(path_list.end(), temp.begin(), temp.end());//将 temp 中的元素放到 path_list 的后面
		// i 迭代
		i = next_vex;
	}
	//输出路径
	cout << "以\"" << v.name << "\"为起点出发游览整个旅游区，推荐路径为：";
	for (int i = 0; i < path_list.size() - 1; i++) {
		cout << this->find_vertex_ID(path_list[i]).name << "->";
	}
	cout << this->find_vertex_ID(path_list[path_list.size() - 1]).name << endl;
}
/***********************************************************************************************************************/