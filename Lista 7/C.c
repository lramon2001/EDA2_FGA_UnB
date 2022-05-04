#include <stdio.h>
#include <stdlib.h>

#define Item int
#define key(x) (x)
#define less(a, b) (a < b)
#define swap(a, b)  \
    {               \
        Item t = a; \
        a = b;      \
        b = t;      \
    }
#define cmpswap(a, b) \
    if (less(b, a))   \
    swap(a, b)

int partition(Item *v, int l, int r)
{
    Item pivot = v[r];
    int j = l;
    for (int k = l; k < r; k++)
        if (less(v[k], pivot))
        {
            swap(v[k], v[j]);
            j++;
        }
    swap(v[j], v[r]);
    return j;
}

void quicksortM3(Item *v, int l, int r)
{
    if (r - l <= 32)
        return;

    swap(v[(l + r) / 2], v[r - 1]);
    cmpswap(v[l], v[r - 1]);
    cmpswap(v[l], v[r]);
    cmpswap(v[r - 1], v[r]);

    int m = partition(v, l, r);
    quicksortM3(v, l, m - 1);
    quicksortM3(v, m + 1, r);
}

void insertionsort(Item *v, int l, int r)
{
    for (int i = l + 1, j; i <= r; i++)
    {
        Item t = v[i];
        for (j = i; j > 0 && less(t, v[j - 1]); j--)
            v[j] = v[j - 1];
        v[j] = t;
    }
}

void quicksort(Item *v, int l, int r)
{
    quicksortM3(v, l, r);
    insertionsort(v, l, r);
}

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

int co[5001];

void solve()
{
    int v, s;
    scanf(" %d %d", &v, &s);

    Graph g = G_init(v);
    for (int f, t; scanf(" %d %d", &f, &t) == 2;)
    {
        G_insert(&g, (Edge){.from = f, .to = t});
        G_insert(&g, (Edge){.from = t, .to = f});
    }

    for (int i = 0; i < v; i++)
        co[i] = -1;

    for (int i = 0; i < v; i++)
        G_components(g, i, co);

    G_free(g);

    int *freq = malloc(sizeof(int) * v);
    for (int i = 0; i < v; i++)
        freq[i] = 0;

    int ans = v - 1;
    for (int i = v - 1; i >= 0; i--)
    {
        if (++freq[co[i]] > freq[ans] || (freq[co[i]] == freq[ans] && ans != co[s] && co[i] < ans))
            ans = co[i];
    }
    free(freq);

    if (ans == co[s] && G_numberOfEdges(g) == 0)
        printf("Fique em casa\n");
    else if (ans == co[s])
        printf("Bora pra estrada\n");
    else
        printf("Vamos para %d\n", ans);
}

int main()
{
    solve();

    return 0;
}
