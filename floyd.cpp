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


lli mat_adj[MAX][MAX];
lli dist[MAX][MAX];
lli n, m;

void print_answer(){
	lli i,j;
	printf("Printing the distance matrix:\n");
	for(i = 0; i < n; i++){
		for (j = 0; j < n; ++j)
		{
			if(dist[i][j] != INF){
				printf("%lld ", dist[i][j]);
			}else{
				printf("INF ");
			}
		}
		printf("\n");
	}
}
void floyd_warshall(){
	int i, j, k;
	for(i = 0; i <= n; i++){
		dist[i][i] = 0;
	}
	for(i=0;i<n;i++){
		for(j=0;j<adj_list[i].size();j++){
			ii aux = adj_list[i][j];
			dist[i][aux.first] = aux.second;
			
		}
	}
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			for(k=0;k<n;k++){
				if(dist[i][j] > dist[i][k] + dist[k][j]){
					dist[i][j] = dist[i][k] + dist[k][j];
				}
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
	//init dist
	for(i = 0; i <= n; i++){
		for (j = 0; j <= n; ++j)
		{
			dist[i][j] = INF;
		}
	}
	printf("Insert the m edges with 'source destination distance' in that order (separated by space):\n");
	for (i = 0; i < m; ++i)
	{
		scanf("%lld %lld %lld", &o, &d, &h);
		adj_list[o].push_back( make_pair(d, h) );
	}
	floyd_warshall();
	//RESPOSTA//
	print_answer();

	
	return 0;
}