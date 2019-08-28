#include <bits/stdc++.h>

using namespace std; 

#define MAX 10000
#define N_EXISTE -1
#define INF numeric_limits<int>::max()

typedef long long int lli;
typedef pair<long long int, long long int> ii;
typedef vector<ii> vii;

vector<vii> adj_list;

lli cost[MAX], previous[MAX];
bool visited[MAX] = {false};
lli dist[MAX][MAX];
lli n, m;
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
	printf("The cost of the MST is:	%lld\n", mst_cost);
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

		if(!visited[v_top]){
			visited[v_top] = true;
			for(j = 0; j < adj_list[v_top].size(); j++){
			aux_2 = adj_list[v_top][j];
			if(!visited[aux_2.first] && cost[aux_2.first] > aux_2.second){
				cost[aux_2.first] = aux_2.second;
				queue.push( {cost[aux_2.first], aux_2.first} );
				previous[aux_2.first] = v_top;
			}
		}
		}
		
	}
}
int main()
{
    printf("OBS: INPUT AS 'u v w' ALSO MEANS 'v u w'!\n");
	lli k, o, d, h;
	int i,j;
	printf("Insert the amount of vertices 'n' and edges 'm' (separated by space):\n");
	scanf("%lld %lld", &n, &m);
	adj_list.resize(n+5);
	
	printf("Insert the m edges with 'source destination weight' in that order (separated by space):\n\tOBS: 0 <= vertex < n\n");
	for (i = 0; i < m; ++i)
	{
		scanf("%lld %lld %lld", &o, &d, &h);
		adj_list[o].push_back( make_pair(d, h) );
		adj_list[d].push_back( make_pair(o, h) );
	}
	prim(0);
	//	ANSWER	//
	print_answer(0);

	
	return 0;
}