//#include<cstdio>
//#include<cstring>
//#include<algorithm>
//using namespace std;
//#pragma warning(disable : 4996)
//const int maxV = 510;
//const int INF = 1000000000;
////n为顶点数，m为边数，G为邻接矩阵，w[]记录最大权值之和
////num[]记录最短路径条数，weight为点权，d[]最短距离
////st和ed分别为起点和终点
//int n, m, st, ed, G[maxV][maxV], weight[maxV];
//int d[maxV], w[maxV], num[maxV];
//bool vis[maxV] = { false };
//void Dijkstra(int s) {
//	fill(d, d + maxV, INF);
//	memset(num, 0, sizeof(num));
//	memset(w, 0, sizeof(w));
//	d[s] = 0;
//	w[s] = weight[s];
//	num[s] = 1;
//	for (int i = 0; i < n; i++) {
//		int u = -1, min = INF;
//		for (int j = 0; j < n; j++) {
//			if (vis[j] == false && d[j] < min) {
//				u = j;
//				min = d[j];
//			}
//		}
//		if (u == -1) return;
//		vis[u] = true;
//		for (int v = 0; v < n; v++) {
//			if (vis[v] == false && G[u][v] != INF) {
//				if (d[u] + G[u][v] < d[v]) {
//					d[v] = d[u] + G[u][v];
//					w[v] = w[u] + weight[v];
//					num[v] = num[u];
//				}
//				else if (d[u] + G[u][v] == d[v]) {
//					if (w[u] + weight[v] > w[v]) {
//						w[v] = w[u] + weight[v];
//					}
//					num[v] += num[u];
//				}
//			}
//		}
//	}
//}
//int main() {
//	scanf("%d%d%d%d", &n, &m, &st, &ed);
//	for (int i = 0; i < n; i++) {
//		scanf("%d", &weight[i]);//读入点权
//	}
//	int u, v;
//	fill(G[0], G[0] + maxV * maxV, INF);
//	for (int i = 0; i < m; i++) {
//		scanf("%d%d", &u, &v);
//		scanf("%d", &G[u][v]);//读入边权
//		G[v][u] = G[u][v];//无向图
//	}
//	Dijkstra(st);
//	printf("%d %d\n", num[ed], w[ed]);
//	return 0;
//}


////////Bellman-Ford算法
#include<cstdio>
#include<cstring>
#include<vector>
#include<set>
#include<queue>
#include<algorithm>
using namespace std;
#pragma warning(disable : 4996)
const int maxV = 510;
const int INF =0x3fffffff;
struct Node {
	int v, dis;//v为邻接边的目标顶点
	Node(int _v,int _dis):v(_v),dis(_dis) {}
};
/*vector<Node> Adj[maxV]*/;
//weight[]用来记录点权，num[]记录最短路径条数
//int n, m, st, ed, weight[maxV];
//int d[maxV], w[maxV], num[maxV];
set<int> pre[maxV];//前驱
void Bellman(int s) {
	fill(d, d + maxV, INF);
	memset(num, 0, sizeof(num));
	memset(w, 0, sizeof(w));
	d[s] = 0;
	w[s] = weight[s];
	num[s] = 1;
//	//以下是求解数组d部分
//	for (int i = 0; i < n - 1; i++) {   //执行n-1轮操作，n为顶点数
//		for (int u = 0; u < n; u++) {   //每轮操作都遍历所有的边
//			for (int j = 0; j < Adj[u].size(); j++) {
//				int v = Adj[u][j].v;//邻接边的顶点
//				int dis = Adj[u][j].dis;
//				if (d[u] + dis < d[v]) {
//					d[v] = d[u] + dis;
//					w[v] = w[u] + weight[v];
//					num[v] = num[u];
//					pre[v].clear();
//					pre[v].insert(u);
//				}
//				else if (d[u] + dis == d[v]) {
//					if (w[u] + weight[v] > w[v]) {
//						w[v] = w[u] + weight[v];
//					}
//					pre[v].insert(u);
//					num[v] = 0;
//					set<int>::iterator it;
//					for (it = pre[v].begin(); it != pre[v].end(); it++) {
//						num[v] += num[*it];
//					}
//				}
//			}
//		}
//	}
//}
	////SPFA算法
	vector<Node> Adj[maxV];
	int n, d[maxV], num[maxV];//num数组记录顶点的入队次数
	bool inq[maxV];//顶点是否在队列中
	bool SPFA(int s) {
		memset(inq, false, sizeof(inq));
		memset(num, 0, sizeof(num));
		fill(d, d + maxV, INF);
		//源点入队部分
		queue<int> Q;
		Q.push(s);
		inq[s] = true;
		num[s]++;
		d[s] = 0;
		//主体部分
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			inq[u] = false;
			//遍历u的所有邻接边v
			for (int j = 0; j < Adj[u].size(); j++) {
				int v = Adj[u][j].v;
				int dis = Adj[u][j].dis;
				if (d[u] + dis < d[v]) {
					d[v] = d[u] + dis;
					if (!inq[v]) {   //如果V不在队列中
						Q.push(v);
						inq[v] = true;
						num[v]++;
						if (num[v] >= n) return false;//有可能出现负环
					}
				}
			}
		}
		return true;//无可达负环
	}
int main() {
	scanf("%d%d%d%d", &n, &m, &st, &ed);
		for (int i = 0; i < n; i++) {
			scanf("%d", &weight[i]);//读入点权
		}
		int u, v, wt;
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", &u, &v, &wt);
			Adj[u].push_back(Node(v, wt));
			Adj[u].push_back(Node(v, wt));
		}
		Bellman(st);
		printf("%d %d\n", num[ed], w[ed]);
		return 0;
}
