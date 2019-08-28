#include <bits/stdc++.h>

using namespace std; 

#define MAX_V 10000
#define N_EXISTE -1
#define INF numeric_limits<long long int>::max()

typedef long long int lli;
typedef pair<long long int,long long int> ii;
typedef vector<ii> vii;
bool visitados[MAX_V] = {false};
lli pai[MAX_V];



vector<vii> adj_list;
lli s,t;
lli n_vertices, n_arestas;
lli rGraph[MAX_V][MAX_V] = {0};

bool bfs(lli s, lli t, lli pai[]){
	lli aux_c, i,j;
	ii aux;
	for(i=0;i<n_vertices;i++){
		visitados[i] = false;
	}
	queue <lli> q;
	q.push(s);
	visitados[s] = true;
	pai[s]=N_EXISTE;
	while(!q.empty()){
		lli u = q.front();
		q.pop();
		for(j=0;j<adj_list[u].size();j++){
			aux = adj_list[u][j];
			if(!visitados[aux.first] && rGraph[u][aux.first] > 0){
					q.push(aux.first);
					pai[aux.first] = u;
					visitados[aux.first] = true;
				}
			}
	}
	// RETURNS IF WE COULD REACH THE TARGET
	return (visitados[t] == true);
}

lli ford_fulkerson(lli s, lli t){	
	lli u,v,aux,aux_c,aux_d,i;
	lli max_flow = 0;

	while(bfs(s, t, pai)){
		lli path_flow = INF;
		//	SEARCH THE SMALLEST CAPACITY
		for(v=t;v!=s;v=pai[v]){
			u=pai[v];
			path_flow = min (path_flow, rGraph[u][v]);
		}
		//	ADD THE FLOW
		for(v=t;v!=s;v=pai[v]){
			u=pai[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}

		max_flow += path_flow;

	}
	return max_flow;
}

int main()
{
	lli i,j,vert_aux, count;
	lli u,v,c,d;
    printf("Insert the amount of vertices 'n' and edges 'm' (separated by space):\n");
	scanf("%lld %lld", &n_vertices, &n_arestas);
	adj_list.resize(n_vertices+5);
	memset(rGraph, 0, sizeof(rGraph));
	printf("Insert the m edges with 'source destination capacity' in that order (separated by space):\n\tOBS: 0 <= vertex < n\n");
	for(i=0;i<n_arestas;i++){
		scanf("%lld %lld %lld", &u, &v, &c);
		adj_list[u].push_back( make_pair(v, c) );
		adj_list[v].push_back( make_pair(u, 0) );
		rGraph[u][v] = c;
		rGraph[v][u] = 0;
	}
	printf("Insert the source and target (0 <= s,t < %lld):\n", n_vertices);
	scanf("%lld %lld", &s, &t);
	if(s < 0 || s >= n_vertices || t < 0 || t >= n_vertices){
		printf("%lld %lld\n", s, t);
        printf("Invalid source/target!\n");
        return 0;
    }
	//	ANSWER	//
	printf("Maximum Flow: %lld\n", ford_fulkerson(s,t));
	
	return 0;
}