#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Push__(a,b)  {top++; stack[top].from=a; stack[top].to=b;}
#define Pop__(a,b)  {a=stack[top].from; b=stack[top].to; top--;}
#define StakNotEmpty (top>=0?1:0)////
#define HasEdge(i,j)  (g->adj[(i)*g->n+(j)]==1)

struct Graph {
	int n;
	char** vetex;
	int* adj;
};
struct Edge {
	int from;
	int to;
};

Graph* Graph_Create(int n);
void Graph_Free(Graph* g);
int Graph_DepthFirst(Graph*g, int start, Edge* tree);

Graph* Graph_Create(int n)
{
    Graph* g=(Graph*)malloc(sizeof(Graph));
    g->n=n;
    g->vetex=(char**)malloc(sizeof(char*)*n);
    int i;
    for (i=0; i<n; i++) g->vetex[i] = NULL;
    g->adj=(int*)malloc(sizeof(int)*n*n);
    int j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            g->adj[i*n+j]=0;
        }
    }
    return g;
}
void Graph_Free(Graph* g)
{
    free(g->adj);
    int i;
    for (i=0; i<g->n; i++) free(g->vetex[i]);
    free(g->vetex);
    free(g);
}
int Graph_DepthFirst(Graph*g, int start, Edge* tree)

{
    const int MAX=1000;
    Edge stack[MAX];
    int top=-1;

    char* visited=(char*)malloc(sizeof(char)*g->n);
    memset(visited, 0, sizeof(char)*g->n);
    int parent=-1;
    int curr=start;
    Push__(parent, curr);
    int k=0;
    while (StakNotEmpty) {
        Pop__(parent, curr);
        if (visited[curr]) continue;
        visited[curr]=1;
        tree[k].from=parent; tree[k].to=curr; k++;
        int j;
        for (j=g->n-1; j>=0; j--) {
            if (HasEdge(curr,j) && !visited[j]) Push__(curr,j);
        }
    }
    free(visited);
    return k;
}

int main()
{
	int n;
	scanf("%d", &n);
	Graph* g=Graph_Create(n);
	char name[100];
	int i;
	for (i=0; i<n; i++) {
		scanf("%s",name);
		int len=0;
		while(name[len]!=0) len++;
		g->vetex[i]=(char*)malloc(sizeof(char)*(len+1));
		memcpy(g->vetex[i], name, len+1);
	}
	while(true) {
		char c;
		scanf(" %c",&c,1);
		if(c=='x') break;

		int j;
		scanf("%d",&i);
		scanf("%d",&j);
		scanf(" %c",&c,1);

		g->adj[i*g->n+j]=1;
		if(c==')') g->adj[j*g->n+i] =1;
	}
	int start;
	scanf("%d",&start);
	int k;
	Edge* tree=(Edge*)malloc(sizeof(Edge)*n*n);
	k=Graph_DepthFirst(g,start,tree);
	printf("tree edges: ");

	printf("<-1,%s> ",g->vetex[tree[0].to]);
	for(i=1; i<k; i++) {
		printf("<%s,%s> ",g->vetex[tree[i].from],g->vetex[tree[i].to]);
	}
	printf("\nvisit sequence: ");
	for(i=0; i<k; i++) {
		printf("%s ",g->vetex[tree[i].to]);
	}
	printf("\n");

	free(tree);
	Graph_Free(g);
    return 0;

}
