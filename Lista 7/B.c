#include <stdio.h>
#include <stdlib.h>

#define GRAPH_WEIGHT_T int
#define GRAPH_WEIGHT_SUM(a, b) (a + b)
#define GRAPH_WEIGHT_LESS(a, b) (a < b)
#define GRAPH_WEIGHT_INF 2147483647

typedef struct
{
    unsigned from, to;
    GRAPH_WEIGHT_T weight;
} Edge;

typedef struct
{
    GRAPH_WEIGHT_T **edges;
    unsigned vertices;
} Graph;

Graph G_init(unsigned vertices)
{
    Graph g = {.vertices = vertices};
    g.edges = malloc(sizeof(GRAPH_WEIGHT_T *) * g.vertices);
    for (unsigned i = 0; i < g.vertices; i++)
    {
        g.edges[i] = malloc(sizeof(GRAPH_WEIGHT_T) * g.vertices);
        for (unsigned j = 0; j < g.vertices; j++)
            g.edges[i][j] = GRAPH_WEIGHT_INF;
    }
    return g;
}

void G_free(Graph g)
{
    for (unsigned i = 0; i < g.vertices; i++)
        free(g.edges[i]);
    free(g.edges);
}

void G_insert(Graph *g, Edge e)
{
    if (e.from > g->vertices || e.to > g->vertices)
        return;

    g->edges[e.from][e.to] = e.weight;
}

void G_dfs(Graph g, int start, int visited[])
{
    visited[start] = 1;
    for (unsigned i = 0; i < g.vertices; i++)
        if (g.edges[start][i] != GRAPH_WEIGHT_INF && !visited[i])
            G_dfs(g, i, visited);
}


int vi[5001];

void solve()
{
    int v;
    scanf(" %d", &v);

    Graph g = G_init(v);
    for (int from, to; scanf(" %d %d", &from, &to) == 2;)
    {
        G_insert(&g, (Edge){.from = from, .to = to});
        G_insert(&g, (Edge){.from = to, .to = from});
    }

    int ans = 0;
    for (int i = 0; i < v; i++)
        if (!vi[i])
        {
            G_dfs(g, i, vi);
            ans++;
        }

    printf("%d\n", ans);

    G_free(g);
}

int main()
{
    solve();

    return 0;
}
