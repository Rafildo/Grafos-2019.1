#include <stdio.h>
#include <utility> 
#include <vector>  
#include <queue> 
#include <cstring>
#include <limits>

using namespace std; 

#define MAX 1000
#define N_EXISTE -1
#define INF std::numeric_limits<int>::max()

typedef long long int lli;
typedef pair<long long int, long long int> ii;
typedef vector<ii> vii;

vector<vii> adj_list;

lli cost[MAX], previous[MAX];
bool visited[MAX] = {false};
lli mat_adj[MAX][MAX];
lli dist[MAX][MAX];
lli n, m;

/*
void prim_func(lli u, priority_queue<ii,vii,greater<ii>>& queue){
	lli j;
	ii aux;
	visited[u] = true;
	for(j = 0; j < adj_list[u].size(); j++){
		aux = adj_list[u][j];
		if(!visited[aux.first]){
			queue.push( {aux.second, aux.first} ); //PUTS THE WEIGHT FIRST BECAUSE WILL BE USED TO SORT THE HEAP
		}
	}
}

lli prim(lli s){
	memset(visited, false, sizeof(visited));
	priority_queue<ii,vii,greater<ii>> queue;
	prim_func(s, queue);
	lli mst_cost = 0;
	while(!queue.empty()){
		ii aux = queue.top();
		queue.pop();
		//printf("%lld\n", aux.first);

		if(!visited[aux.second]){
			mst_cost += aux.first;
			prim_func(aux.second, queue);
		}
	}
	return mst_cost;

}*/
void print_mst(lli s){
	lli i;
	for(i = 0; i < n; i++){
		if(i != s){
			printf("%lld --(%lld)--> %lld\n", previous[i], cost[i], i);
		}
	}

}

void print_answer(lli s){
	lli i, mst_cost = 0;
	printf("Printing the edges of the MST:\n");
	print_mst(s);
	for(i = 0; i < n; i++){
		if(i != s){
			mst_cost += cost[i];
		}
	}
	printf("The cos of the MST is:	%lld\n", mst_cost);
}



void prim(lli s){
	lli u, j;
	ii aux, aux_2;
	for(u = 0; u < n; u++){
		cost[u] = INF;
		previous[u] = N_EXISTE;
	}
	cost[s] = 0;
	priority_queue<ii,vii,greater<ii>> queue;
	queue.push( {cost[s], s} );
	while(!queue.empty()){
		lli v_top = queue.top().second;
		queue.pop();
		for(j = 0; j < adj_list[v_top].size(); j++){
			aux_2 = adj_list[v_top][j];
			if(cost[aux_2.first] > aux_2.second){//cost[z] > w(v,z)
				cost[aux_2.first] = aux_2.second;
				queue.push( {cost[aux_2.first], aux_2.first} );
				previous[aux_2.first] = v_top;
			}
		}
	}
}
int main()
{
	lli k, o, d, h;
	int i,j;
	printf("Insert the amount of vertices and edges (separated by space):\n");
	scanf("%lld %lld", &n, &m);
	adj_list.resize(n+5);
	
	printf("Insert the m edges with 'source destination weight' in that order (separated by space):\n");
	for (i = 0; i < m; ++i)
	{
		scanf("%lld %lld %lld", &o, &d, &h);
		adj_list[o].push_back( make_pair(d, h) );
		adj_list[d].push_back( make_pair(o, h) );
	}
	printf("Insert the source of the PRIM algorithm:\n");
	scanf("%lld", &k);
	prim(k);
	//RESPOSTA//
	print_answer(k);

	
	return 0;
}