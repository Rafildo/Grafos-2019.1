#include <bits/stdc++.h>

using namespace std; 

#define MAX 10000
#define INF numeric_limits<long long int>::max()
#define N_EXISTE -1


typedef long long int lli;
typedef pair<long long int,long long int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

lli v,e;
bool visitados[MAX] = {false};
lli pai[MAX];
lli dist[MAX];

vector<vii> adj_list;

long long int minn(lli a, lli b){
    return (a<b)?a:b;
}

long long int maxx(lli a, lli b){
    return (a>b)?a:b;
}

void print_answer(lli s, lli t){
    lli answer[MAX];
    lli i, answer_size = 0;;
    for(i = t; i != N_EXISTE; i=pai[i]){
        answer[answer_size++] = i;
    }
    printf("Path:\n");
    for(i=answer_size-1;i>=0;i--){
        if(i == 0){
            printf("%lld\n", answer[i]);
        }
        else{
            printf("%lld ---> ", answer[i]);
        }
    }
    printf("Distance: %lld\n", dist[t]);
}

void dijkstra(lli s){
    lli i, i_w;
    //ESSA FILA COLOCA OS MENORES PESOS NA FRENTE
    priority_queue<ii,vii,greater<ii>> queue;

    dist[s] = 0;
    pai[s] = N_EXISTE;
    queue.push( {dist[s],s} );

    while(!queue.empty()){
        lli v_top = queue.top().second;
        queue.pop();

        if(!visitados[v_top]){
            visitados[v_top] = true;

            for(i=0;i<adj_list[v_top].size();i++){
                ii aux = adj_list[v_top][i];

                if(dist[v_top] + aux.second < dist[aux.first]){

                    dist[aux.first] = dist[v_top] + aux.second;
                    queue.push( {dist[aux.first], aux.first});
                    pai[aux.first] = v_top;
                }
            }
        }
    }
}

int main()
{
    printf("OBS: INPUT AS 'u v w' ALSO MEANS 'v u w'!\n");
    lli i,j;
    lli aux_ori,aux_dest,aux_peso, s, t;
    printf("Insert the amount of vertices 'n' and edges 'm' (separated by space):\n");
    scanf("%lld %lld", &v, &e); 
    adj_list.resize(v+5);

    printf("Insert the m edges with 'source destination distance' in that order (separated by space):\n\tOBS: 0 <= vertex < n\n");
    for(i = 0; i < e; i++){
        scanf("%lld %lld %lld", &aux_ori, &aux_dest, &aux_peso);
        adj_list[aux_ori].push_back( make_pair(aux_dest, aux_peso) );
        adj_list[aux_dest].push_back( make_pair(aux_ori, aux_peso) );
    }
    printf("Insert the source and target wanted (0 <= s,t < %lld)\n", v);
    scanf("%lld %lld", &s, &t);
    if(s < 0 || s >= v || t < 0 || t >= v){
        printf("Invalid source/target!\n");
        return 0;
    }
    for (i = 0; i <= v; ++i)
    {
        pai[i] = -1;
        dist[i] = INF;
        visitados[i] = false;
    }
    dijkstra(s);
    print_answer(s, t);
    
    return 0;
}
