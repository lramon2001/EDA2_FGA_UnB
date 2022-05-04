#include <stdio.h>
#include <stdlib.h>

#define QUEUE_T int

typedef struct Q_I
{
    QUEUE_T val;
    struct Q_I *next;
} QueueItem;

typedef struct
{
    size_t size;
    QueueItem *head;
    QueueItem *tail;
} Queue;

Queue Q_init()
{
    return (Queue){.head = NULL, .tail = NULL, .size = 0};
}

int Q_empty(Queue q)
{
    return q.size == 0;
}

QUEUE_T Q_front(Queue q)
{
    QUEUE_T front;
    if (!Q_empty(q))
        front = q.head->val;
    return front;
}

QUEUE_T Q_back(Queue q)
{
    QUEUE_T back;
    if (!Q_empty(q))
        back = q.tail->val;
    return back;
}

void Q_push(Queue *q, QUEUE_T value)
{
    QueueItem *qi = malloc(sizeof(QueueItem));
    qi->val = value;
    qi->next = NULL;

    if (Q_empty(*q))
    {
        q->head = qi;
        q->tail = qi;
    }
    else
    {
        q->tail->next = qi;
        q->tail = qi;
    }
    q->size++;
}

QUEUE_T Q_pop(Queue *q)
{
    QUEUE_T value = Q_front(*q);
    if (!Q_empty(*q))
    {
        QueueItem *toRemove = q->head;
        q->head = toRemove->next;
        if (!q->head)
            q->tail = NULL;
        free(toRemove);
        q->size--;
    }
    return value;
}

void Q_clear(Queue *q)
{
    while (!Q_empty(*q))
        Q_pop(q);
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

short G_bestPathBF(Graph g, int start, GRAPH_WEIGHT_T *dist)
{
    short *onQueue = malloc(sizeof(short) * g.V);
    for (unsigned i = 0; i < g.V; i++)
        dist[i] = GRAPH_WEIGHT_INF, onQueue[i] = 0;
    dist[start] = 0;

    Queue q = Q_init();
    Q_push(&q, start);
    onQueue[start] = 1;

    const int sentinel = g.V;
    unsigned k = 0;
    Q_push(&q, sentinel);

    while (!Q_empty(q))
    {
        int v = Q_pop(&q);
        if (v < sentinel)
        {
            for (unsigned i = 0; i < g.V; i++)
            {
                if (g.edges[v][i] == GRAPH_WEIGHT_INF)
                    continue;

                if (GRAPH_WEIGHT_LESS(GRAPH_WEIGHT_SUM(dist[v], g.edges[v][i]), dist[i]))
                {
                    dist[i] = k == g.V ? GRAPH_WEIGHT_INF : GRAPH_WEIGHT_SUM(dist[v], g.edges[v][i]);
                    if (!onQueue[i])
                    {
                        Q_push(&q, i);
                        onQueue[i] = 1;
                    }
                }
            }
        }
        else
        {
            if (Q_empty(q))
                return 1;
            if (++k >= g.V + 1)
                return 0;
            Q_push(&q, v);
            for (unsigned i = 0; i < g.V; i++)
                onQueue[i] = 0;
        }
    }

    Q_clear(&q);
    free(onQueue);
    return 1;
}

int distX[2001][2001], distS[2001][2001], tc[2001][2001], negative_cycles[2001];

void solve()
{
    int v;
    scanf(" %d", &v);

    Graph gX = G_init(v), gS = G_init(v);
    for (int f, t, c, d; scanf(" %d %d %d %d", &f, &t, &c, &d) == 4 && (f | t | c | d);)
    {
        G_insert(&gS, (Edge){.from = f, .to = t, .weight = c});
        if (d == 0)
            G_insert(&gS, (Edge){.from = t, .to = f, .weight = c});

        if (d == 1)
            continue;

        G_insert(&gX, (Edge){.from = f, .to = t, .weight = c});
        G_insert(&gX, (Edge){.from = t, .to = f, .weight = c});
    }

    for (int i = 0; i < G_numberOfVertices(gS); i++)
    {
        if (!G_bestPathBF(gS, i, distS[i]))
            negative_cycles[i] = 1;
        G_bestPathBF(gX, i, distX[i]);
    }

    G_transitiveClosure(gS, tc);

    G_free(gX);
    G_free(gS);

    for (int t, x; scanf(" %d %d", &t, &x) == 2;)
    {
        int ans = distS[t][x] != GRAPH_WEIGHT_INF && distX[t][x] != GRAPH_WEIGHT_INF;
        if (negative_cycles[t])
        {
            for (int i = 0; i < v && ans; i++)
                if (distS[t][i] == GRAPH_WEIGHT_INF && (tc[i][t] || tc[i][x]))
                    ans = 0;
        }

        if (ans)
            printf("%d %d\n", distX[t][x], distS[t][x]);
        else
            printf("Impossibru\n");
    }
}

int main()
{
    solve();

    return 0;
}
