#include"Graph.h"

ostream& operator<<(ostream& os, const Graph& g) {//����������������ӡ�ڽӾ���
	Graph gg(g);//���뿽���ſ��Է��� gg.vexs
	cout << "��ǰͼ�о��еĶ�������Ϊ��" << gg.vexnum << endl;
	cout << "��ǰͼ�о��еĻ�����Ϊ��" << gg.arcnum << endl;
	cout << "ͼ���ڽӾ����ʾΪ��" << endl;
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
	//��ʼ���ڽӾ���
	arcs = new int* [MAX_VERTEX_NUM];
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		arcs[i] = new int[MAX_VERTEX_NUM]();//��ʼ��Ϊ 999999
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			arcs[i][j] = INF;
		}
		arcs[i][i] = 0;
	}
	//���ļ�
	ifstream inf_vex(vex);
	ifstream inf_path(path);
	if (!inf_vex.is_open()) {
		cout << "������Ϣ�ļ���ʧ�ܣ�ͼ��ʼ��ʧ�ܣ�" << endl;
	}
	if (!inf_path.is_open()) {
		cout << "·����Ϣ�ļ���ʧ�ܣ�ͼ��ʼ��ʧ�ܣ�" << endl;
	}
	//¼�뾰����Ϣ
	string s1;
	while (getline(inf_vex, s1)) {
		if (s1.empty()) {//�������
			break;
		}
		vexnum++;
		vexs.push_back(Vertex(s1));//��������Ϣ¼�붥��������
	}
	//¼��·����Ϣ
	string s2;
	while (getline(inf_path, s2)) {
		if (s2.empty()) {//�������
			break;
		}
		vector<string> pathList;//�ݴ��һ�е�·����Ϣ string��
		Stringsplit(s2, '-', pathList);//�ָ�ÿһ��·����Ϣ string��
		try {
			//���·�����Ƿ���ڷǷ�����ID
			if (!vex_exist(stoi(pathList[0])) || !vex_exist(stoi(pathList[1]))) {
				throw "·���ļ��д��ڷǷ�·�������޸ģ�";
			}
			arcs[stoi(pathList[0])][stoi(pathList[1])] = stoi(pathList[2]);//��·����Ϣ��ŵ��ڽӾ�����
			arcs[stoi(pathList[1])][stoi(pathList[0])] = stoi(pathList[2]);
			arcnum++;
		}
		catch (const char* msg) {
			cerr << msg << endl;
			exit(-1);
		}

	}
	//�ر��ļ�
	inf_vex.close();
	inf_path.close();
}
Graph::Graph(const Graph& g) :vexnum(g.vexnum), arcnum(g.arcnum) {
	//������������
	this->vexs.assign(g.vexs.begin(), g.vexs.end());
	//��ʼ���ڽӾ���
	arcs = new int* [MAX_VERTEX_NUM];
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		arcs[i] = new int[MAX_VERTEX_NUM]();//��ʼ��Ϊ 999.99
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			arcs[i][j] = INF;
		}
		arcs[i][i] = 0;
	}
	//�����ڽӾ���
	/*copy(&g.arcs[0][0], &g.arcs[0][0] + MAX_VERTEX_NUM * MAX_VERTEX_NUM, &arcs[0][0]);*/
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			arcs[i][j] = g.arcs[i][j];
		}
	}
	//������ ʮ����
}
Graph::~Graph() {
	//�����ڽӾ���
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		delete[]arcs[i];
	}
	delete[]arcs;
	//cout << "~Graph()��������" << endl;
	//������ ʮ����
}
Vertex Graph::find_vertex_ID(int ID) {//ͨ�� ID���Ҷ���
	for (int i = 0; i < vexnum; i++) {
		if (ID == vexs[i].getID()) {
			return vexs[i];
		}
	}
	cout << "���޴�ID��" << endl;
	return Vertex();
}
Vertex Graph::find_vertex_name(string name) {//ͨ�� name���Ҷ���
	for (int i = 0; i < vexnum; i++) {
		if (name == vexs[i].getName()) {
			return vexs[i];
		}
	}
	cout << "���޴�name��" << endl;
	return Vertex();
}
bool Graph::vex_exist(Vertex v) {//ͨ�� �������жϴ˶����Ƿ��Ѿ�����
	for (int i = 0; i < vexnum; i++) {
		if (v.getName() == this->vexs[i].getName()) {
			return true;
		}
	}
	return false;
}
bool Graph::vex_exist(int ID) {//ͨ�� ID���жϴ˶����Ƿ��Ѿ�����
	for (int i = 0; i < vexnum; i++) {
		if (ID == this->vexs[i].getID()) {
			return true;
		}
	}
	return false;
}
void Graph::update_Graph() {//���� ͼ�еĶ�����Ϣ�ͻ���Ϣ���ļ���
	ofstream out_vex("������Ϣ.txt");
	if (!out_vex.is_open()) {
		cout << "������Ϣ�ļ���ʧ�ܣ�" << endl;
	}
	ofstream out_arc("·����Ϣ.txt");
	if (!out_arc.is_open()) {
		cout << "·����Ϣ�ļ���ʧ�ܣ�" << endl;
	}
	//д�뾰����Ϣ
	for (int i = 0; i < vexnum; i++) {
		out_vex << this->vexs[i].ID << " " << this->vexs[i].name << " " << this->vexs[i].information << "\n";
	}
	//д��·����Ϣ
	for (int i = 0; i < vexnum; i++) {
		for (int j = 0; j <= i; j++) {
			if ((this->arcs[i][j] != INF) && (this->arcs[i][j] != 0)) {
				out_arc << i << "-" << j << "-" << this->arcs[i][j] << "\n";
			}
		}
	}
	//�ر��ļ�
	out_vex.close();
	out_arc.close();
}
void Graph::add_vex(Vertex v) {//��� ����
	//���жϴ˶����Ƿ��Ѿ�����
	if (this->vex_exist(v)) {
		cout << "����Ϊ\"" << v.name << "\"�Ķ����Ѿ����ڣ��޷���Ӷ��㣡" << endl;
		return;
	}
	//��Ӷ��� push_back��vexs��󣬲����޸Ĵ˶����ID
	v.ID = this->vexnum;
	this->vexs.push_back(v);
	vexnum++;
	//���� �ļ�
	update_Graph();
}
void Graph::add_arc(Vertex v1, Vertex v2, int weight) {//��� ��
	if (weight == INF) {
		cout << INF << "��ʾû�л�����˲����Խ�����Ϊ�޸ĵĻ���Ϣ��" << endl;
		return;
	}
	if (weight == 0) {
		cout << 0 << "��ʾ�����غϣ���˲����Խ�����Ϊ�޸ĵĻ���Ϣ��" << endl;
		return;
	}
	if (weight < 0) {
		cout << "�������и�Ȩֵ��" << endl;
		return;
	}
	//���ж϶����Ƿ����
	if ((!this->vex_exist(v1)) || (!this->vex_exist(v2))) {
		cout << "�ж��㲻����ͼ�У��޷���ӻ���" << endl;
		return;
	}
	//�жϻ��Ƿ��Ѿ����� �Ѿ���������ʾ����
	if ((this->arcs[v1.ID][v2.ID] != INF) || (this->arcs[v2.ID][v1.ID] != INF)) {
		cout << "��\"" << v1.name << "\"��\"" << v2.name << "\"�Ļ��Ѿ����ڣ��޷���ӻ���" << endl;
		return;
	}
	//��ӻ�
	arcnum++;
	this->arcs[v1.getID()][v2.getID()] = weight;
	this->arcs[v2.getID()][v1.getID()] = weight;
	//���� �ļ�
	update_Graph();
}
void Graph::delete_vex(Vertex v) {//ɾ�� �ö����Լ��ö��������еĻ�
	//���жϴ˶����Ƿ��Ѿ�����
	if (!this->vex_exist(v)) {
		cout << "�˶��㲻���ڣ��޷�ɾ�����㣡" << endl;
		return;
	}
	//ɾ������ ��ɾ���������������л�Ȼ��ɾ���ö���
	for (int i = 0; i < this->vexnum; i++) {
		if (i == v.ID) {//���������Լ������ʱ������
			continue;
		}
		this->delete_arc(this->vexs[i], v);
	}
	auto iter = this->vexs.erase(this->vexs.begin() + v.ID);
	this->vexnum--;
	for (int i = 0; i < vexnum; i++) {
		this->vexs[i].ID = i;
	}
	//���� �ļ�
	update_Graph();
}
void Graph::delete_arc(Vertex v1, Vertex v2) {//ɾ�� �����ú�������ʾ�������ڣ���������Ϊ INF��ʱ��ġ����󡱣���Ϊ������ delete_vex() �е��ã�
	//���ж϶����Ƿ����
	if ((!this->vex_exist(v1)) || (!this->vex_exist(v2))) {
		cout << "�ж��㲻����ͼ�У��޷�ɾ������" << endl;
		return;
	}
	//����������ͬ������ɾ��
	if (v1.name == v2.name) {
		cout << "����������ͬ��������ɾ����" << endl;
		return;
	}
	//ɾ����
	if ((arcs[v1.getID()][v2.getID()] != INF) && (arcs[v2.getID()][v1.getID()] != INF)) {
		this->arcnum--;
		this->arcs[v1.getID()][v2.getID()] = INF;
		this->arcs[v2.getID()][v1.getID()] = INF;
	}

	//���� �ļ�
	update_Graph();
}
void Graph::revise_vex_name(Vertex v, string n) {//�޸� ��������
	if (!vex_exist(v)) {
		cout << "�ö��㲻���ڣ�" << endl;
		return;
	}
	//�޸Ķ�������
	this->vexs[v.ID].name = n;
	//���� �ļ�
	update_Graph();
}
void Graph::revise_vex_information(Vertex v, string inf) {//�޸� �������
	if (!vex_exist(v)) {
		cout << "�ö��㲻���ڣ�" << endl;
		return;
	}
	//�޸Ķ�������
	this->vexs[v.ID].information = inf;
	//���� �ļ�
	update_Graph();
}
void Graph::revise_arc(Vertex v1, Vertex v2, int weight) {//�޸� ������Ϣ
	//���ж϶����Ƿ����
	if (weight == INF) {
		cout << INF << "��ʾû�л�����˲����Խ�����Ϊ�޸ĵĻ���Ϣ��" << endl;
		return;
	}
	if (weight == 0) {
		cout << 0 << "��ʾ�����غϣ���˲����Խ�����Ϊ�޸ĵĻ���Ϣ��" << endl;
		return;
	}
	if (weight < 0) {
		cout << "�������и�Ȩֵ��" << endl;
		return;
	}
	if ((!this->vex_exist(v1)) || (!this->vex_exist(v2))) {
		cout << "�ж��㲻����ͼ�У��޷��޸Ļ���" << endl;
		return;
	}
	//�жϻ��Ƿ���� ����������ʾ����
	if ((this->arcs[v1.ID][v2.ID] == INF) || (this->arcs[v2.ID][v1.ID] == INF)) {
		cout << "��\"" << v1.name << "\"��\"" << v2.name << "\"�Ļ������ڣ��޷��޸Ļ���������ӻ���" << endl;
		return;
	}
	//�޸Ļ�
	this->arcs[v1.ID][v2.ID] = weight;
	this->arcs[v2.ID][v1.ID] = weight;
	//���� �ļ�
	update_Graph();
}
/***********************************************************************************************************************/
/*���������븶�ѹۿ�����*/
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
void Graph::print_nearby_vex(Vertex v) {//��ӡ �� v ���ڵĶ���
	if (!vex_exist(v)) {
		cout << "�˶��㲻���ڣ��޷���ѯ��" << endl;
		return;
	}
	cout << "��\"" << v.name << "\"���ڵĶ����У�" << endl;
	//���ڽӾ����в�ѯ
	for (int i = 0; i < this->vexnum; i++) {
		if (this->arcs[v.ID][i] != INF && this->arcs[v.ID][i] != 0) {
			cout << this->vexs[i];
			cout << "��\t\t\"" << v.name << "\"��\"" << this->vexs[i].name << "\"�ľ���Ϊ:" << this->arcs[v.ID][i] << endl;
		}
	}
}
void Graph::Dijkstra(Vertex v, int* prev, int* dist) {
	if (!vex_exist(v)) {
		cout << "�˶��㲻���ڣ��޷���ѯ��" << endl;
		return;
	}
	int* vis = new int[this->vexnum]();//��ʼ���������� �жϸõ��Ƿ������·��
	int i, j, k;
	int min, tmp;
	//��ʼ��
	for (i = 0; i < this->vexnum; i++) {
		vis[i] = 0;//���ж����δ�����·��
		prev[i] = v.ID;//���ж����ǰ������Ϊ v.ID
		dist[i] = this->arcs[v.ID][i];//���·��ֵ
	}
	//����� v ��������ݳ�ʼ��
	vis[v.ID] = 1;
	dist[v.ID] = 0;
	//���� vexnum-1 �Σ�ÿ���ҳ�һ����������·��
	for (i = 1; i < this->vexnum; i++) {
		//Ѱ�ҵ�ǰ��С��·������δ��ȡ���·���Ķ����У��ҵ������ v ����Ķ��� k
		min = INF;//��ʼΪ INF ���������Сֵ
		for (j = 0; j < this->vexnum; j++) {
			if (vis[j] == 0 && dist[j] < min) {
				min = dist[j];
				k = j;
			}
		}
		//��� ����k Ϊ�Ѿ���ȡ�����·��
		vis[k] = 1;

		//���� δ��ȡ���·���Ķ�������·����ǰ������
		for (j = 0; j < this->vexnum; j++) {
			tmp = (this->arcs[k][j] == INF ? INF : (min + this->arcs[k][j]));//��ֹ���
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
void Graph::print_shortist_path(Vertex v1, Vertex v2) {//��ӡ ����v1��v2֮������·���Լ����룬Ĭ��v1Ϊ��㣬v2Ϊ�յ�
	//���ж϶����Ƿ����
	if ((!this->vex_exist(v1)) || (!this->vex_exist(v2))) {
		cout << "���������ж��㲻����ͼ�У��޷���ӡ��������֮������·����" << endl;
		return;
	}
	//����Dijkstra()
	int* prev = new int[this->vexnum];
	int* dist = new int[this->vexnum];
	this->Dijkstra(v2, prev, dist);
	//�������v1��v2�����·���Լ�����
	cout << "��\"" << v1.name << "\"��\"" << v2.name << "\"�����·��Ϊ��\t";
	for (int i = v1.ID; i != v2.ID; i = prev[i]) {
		if (i == v1.ID) {
			cout << (this->find_vertex_ID(i)).name;
		}
		else {
			cout << "->" << (this->find_vertex_ID(i)).name;
		}
	}
	cout << "->" << v2.name;
	cout << "\t\t\t����Ϊ��" << dist[v1.ID] << endl;
}
void Graph::print_shortist_path(Vertex v) {//��ӡ ����v�������ܵ���Ķ�������·�� �Լ�����
	//���ж϶����Ƿ����
	if (!this->vex_exist(v)) {
		cout << "���㲻����ͼ�У��޷���ӡ���·����" << endl;
		return;
	}
	for (int i = 0; i < vexnum; i++) {
		if (i == v.ID) {
			continue;
		}
		this->print_shortist_path(find_vertex_ID(i), v);
	}
}
void Graph::print_all_path(Vertex v1, Vertex v2) {//��ӡ �Ӷ���v1��v2֮������м�·��
	if ((!this->vex_exist(v1)) || (!this->vex_exist(v2))) {
		cout << "���������ж��㲻����ͼ�У��޷���ӡ��������֮���·����" << endl;
		return;
	}
	int start = v1.ID, dest = v2.ID;
	int path_list_num = 1;
	int distance = 0;//��ʼ������Ϊ0
	int* vis = new int[this->vexnum]();//��Ƕ����Ƿ����
	int* stack = new int[this->vexnum]();//ģ��ջ
	int top = -1;//ջ��ָ��

	//�˴���΢ѧϰ��ʹ����lamda���ʽ
	const auto& DFS = [&](const int& start) {
		function<void(const int&)>ddffss;//����ͨ�� function���ú���ָ��ķ�ʽ���뺯���ݹ�
		ddffss = [&](const int& now) {
			vis[now] = 1;
			stack[++top] = now;
			/************************************************************************************************/
			/*�˲���Ϊ�ݹ����*/
			if (now == dest) {
				//��ӡ·��
				cout << "��\"" << v1.name << "\"��\"" << v2.name << "\"�ĵ�" << path_list_num++ << "��·Ϊ:\t";
				for (int j = 0; j < top; j++) {
					cout << this->find_vertex_ID(stack[j]).name << "->";
				}
				cout << this->find_vertex_ID(stack[top]).name << "\t\t\t����Ϊ��" << distance << endl;
			}
			/************************************************************************************************/
			for (int i = 0; i < this->vexnum; i++) {
				if (vis[i] == 0 && this->arcs[now][i] < INF) {//�������ж��㣬������δ�������Ҹö��������֮��û��ֱ��·��ʱ������ݹ�
					distance += this->arcs[now][i];
					ddffss(i);
					distance -= this->arcs[now][i];
				}
			}
			top--;
			vis[now] = 0;
		};
		ddffss(start);//���� ddffss()
	};
	DFS(start);//���� DFS()

	//����Ҫ�ҳ�������֮������·���;���
	this->print_shortist_path(v1, v2);
}
void Graph::print_recommended_path(Vertex v) {//��ӡ �Զ���vΪ���������ж���
	if (!vex_exist(v)) {
		cout << "�˶��㲻���ڣ��޷���ѯ��" << endl;
		return;
	}
	int* vis = new int[this->vexnum]();//��Ƕ����Ƿ����
	vis[v.ID] = 1;
	//�ж��Ƿ��Ѿ����������ж���
	const auto& ifend = [=]() {
		for (int i = 0; i < vexnum; i++) {
			if (vis[i] == 0) {
				return 0;
			}
		}
		return 1;
	};

	vector<int> path_list;
	path_list.push_back(v.ID);//�Ƚ�������
	for (int i = v.ID; !ifend(); ) {
		int* prev = new int[this->vexnum]();
		int* dist = new int[this->vexnum]();
		vis[i] = 1;//��ǰ�����ѱ�����
		int next_vex;
		for (int j = 0; j < vexnum; j++) {//��ʼ�� next_vex
			if (!vis[j]) {
				next_vex = j;
			}
		}
		this->Dijkstra(this->find_vertex_ID(i), prev, dist);//�Ե�ǰ����������� Dijkstra()

		for (int j = 0; j < this->vexnum; j++) {
			if (!vis[j]) {
				next_vex = dist[j] < dist[next_vex] ? j : next_vex;//�ҳ��뵱ǰ������������Ķ��� next_vex
			}
		}
		if (ifend()) {
			break;
		}
		//�ҳ�·������ path_list ��
		vector<int> temp;
		for (int j = next_vex; j != i; j = prev[j]) {
			temp.insert(temp.begin(), j);//��ͷ����ʼ�ĵط�����
		}
		path_list.insert(path_list.end(), temp.begin(), temp.end());//�� temp �е�Ԫ�طŵ� path_list �ĺ���
		// i ����
		i = next_vex;
	}
	//���·��
	cout << "��\"" << v.name << "\"Ϊ�����������������������Ƽ�·��Ϊ��";
	for (int i = 0; i < path_list.size() - 1; i++) {
		cout << this->find_vertex_ID(path_list[i]).name << "->";
	}
	cout << this->find_vertex_ID(path_list[path_list.size() - 1]).name << endl;
}
/***********************************************************************************************************************/