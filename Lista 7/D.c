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

void G_transitiveClosure(Graph g, int transitive[][2001])
{
    for (unsigned i = 0; i < g.V; i++)
    {
        for (unsigned j = 0; j < g.V; j++)
            transitive[i][j] = g.edges[i][j] != GRAPH_WEIGHT_INF;
        transitive[i][i] = 1;
    }

    for (unsigned i = 0; i < g.V; i++)
        for (unsigned j = 0; j < g.V; j++)
            if (transitive[j][i] == 1)
                for (unsigned k = 0; k < g.V; k++)
                    if (transitive[i][k] == 1)
                        transitive[j][k] = 1;
}

int tc[2001][2001];

void solve()
{
    int v;
    scanf(" %d", &v);

    Graph g = G_init(v);
    for (int f, t, d; scanf(" %d %d %d", &f, &t, &d) == 3 && d;)
    {
        G_insert(&g, (Edge){.from = f, .to = t, .weight = 1});
        if (d == 2)
            G_insert(&g, (Edge){.from = t, .to = f, .weight = 1});
    }

    G_transitiveClosure(g, tc);
    G_free(g);

    for (int t, x; scanf(" %d %d", &t, &x) == 2;)
        printf("%s\n", (tc[t][x] && tc[x][t] ? "Ida e Volta" : (tc[t][x] ? "Apenas Ida" : (tc[x][t] ? "Apenas Volta" : "Impossibru"))));
}

int main()
{
    solve();

    return 0;
}
