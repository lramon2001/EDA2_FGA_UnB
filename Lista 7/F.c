#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    unsigned V, E;
} Graph;

Graph G_init(unsigned numberOfVertices)
{
    Graph g = {.V = numberOfVertices, .E = 0};
    g.edges = malloc(sizeof(GRAPH_WEIGHT_T *) * g.V);
    for (unsigned i = 0; i < g.V; i++)
    {
        g.edges[i] = malloc(sizeof(GRAPH_WEIGHT_T) * g.V);
        for (unsigned j = 0; j < g.V; j++)
            g.edges[i][j] = GRAPH_WEIGHT_INF;
    }
    return g;
}

void G_free(Graph g)
{
    for (unsigned i = 0; i < g.V; i++)
        free(g.edges[i]);
    free(g.edges);
}

void G_insert(Graph *g, Edge e)
{
    if (e.from > g->V || e.to > g->V)
        return;

    g->E += (g->edges[e.from][e.to] == GRAPH_WEIGHT_INF);
    g->edges[e.from][e.to] = e.weight;
}

int G_numberOfEdges(Graph g)
{
    return g.E;
}

int G_numberOfVertices(Graph g)
{
    return g.V;
}

void G_components(Graph g, int start, int components[])
{
    if (components[start] < 0)
        components[start] = start;
    for (unsigned i = 0; i < g.V; i++)
        if (g.edges[start][i] != GRAPH_WEIGHT_INF && components[i] < 0)
        {
            int mn = ((int)i < components[start] ? (int)i : components[start]);
            components[start] = mn;
            components[i] = mn;
            G_components(g, i, components);
        }
}

int co[5001], freq[5001];
char s[5001][32];

void solve()
{
    int v, c;
    scanf(" %d %d", &v, &c);
    if (!v && !c)
        return;

    for (int i = 0; i < v; i++)
        co[i] = -1, freq[i] = 0;

    for (int i = 0; i < v; i++)
        scanf(" %s", s[i]);

    Graph g = G_init(v);

    for (int i = 0; i < c; i++)
    {
        char a[32], b[32];
        scanf(" %s %s", a, b);
        int ai = -1, bi = -1;
        for (int j = 0; j < v && (ai == -1 || bi == -1); j++)
        {
            if (ai == -1 && strcmp(s[j], a) == 0)
                ai = j;
            else if (bi == -1 && strcmp(s[j], b) == 0)
                bi = j;
        }
        G_insert(&g, (Edge){.from = bi, .to = ai, .weight = 1});
        G_insert(&g, (Edge){.from = ai, .to = bi, .weight = 1});
    }

    for (int i = 0; i < v; i++)
        G_components(g, i, co);
    G_free(g);

    int ans = 0;
    for (int i = 0; i < v; i++)
        if (++freq[co[i]] > ans)
            ans = freq[co[i]];

    printf("%d\n", ans);

    solve();
}

int main()
{
    solve();

    return 0;
}
