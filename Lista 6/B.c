#include <stdio.h>
#include <stdlib.h>

#define min(a, b) (a < b ? a : b)
#define max(a, b) (b < a ? a : b)
// #define Item int
#define key(x) (x->value)
#define less(a, b) (key(a) > key(b))
#define swap(a, b)  \
    {               \
        Item t = a; \
        a = b;      \
        b = t;      \
    }
#define cmpswap(a, b) \
    if (less(b, a))   \
    swap(a, b)

struct Item
{
    int heap_idx, value;
};

typedef struct Item *Item;

Item NULL_ITEM = NULL;

typedef struct
{
    Item *heap;
    size_t size, capacity;
} PriorityQueue;

void HEAP_fixup(Item *heap, int i)
{
    for (; i > 1 && less(heap[i / 2], heap[i]); i /= 2)
    {
        swap(heap[i], heap[i / 2]);
        heap[i]->heap_idx = i;
        heap[i / 2]->heap_idx = i / 2;
    }
}

void HEAP_fixdown(Item *heap, size_t size, int i)
{
    for (int larger = i * 2; i * 2 <= size; i = larger, larger = i * 2)
    {
        if (larger < size && less(heap[larger], heap[larger + 1]))
            larger++;

        if (!less(heap[i], heap[larger]))
            break;

        swap(heap[i], heap[larger]);
        heap[i]->heap_idx = i;
        heap[larger]->heap_idx = larger;
    }
}

PriorityQueue PQ_init(size_t capacity)
{
    PriorityQueue pq = {.capacity = capacity, .size = 0};
    pq.heap = malloc((capacity + 1) * sizeof(Item));
    return pq;
}

void PQ_free(PriorityQueue pq)
{
    free(pq.heap);
}

int PQ_isEmpty(PriorityQueue pq)
{
    return pq.size == 0;
}

void PQ_ensureCapacity(PriorityQueue *pq, size_t newCapacity)
{
    if (newCapacity <= pq->capacity)
        return;

    pq->capacity *= 4;
    pq->heap = realloc(pq->heap, (pq->capacity + 1) * sizeof(Item));
}

void PQ_insert(PriorityQueue *pq, Item x)
{
    PQ_ensureCapacity(pq, pq->size + 1);
    pq->heap[++pq->size] = x;
    x->heap_idx = pq->size;
    HEAP_fixup(pq->heap, pq->size);
}

Item PQ_getTop(PriorityQueue pq)
{
    return pq.heap[1];
}

Item PQ_extractTop(PriorityQueue *pq)
{
    if (PQ_isEmpty(*pq))
        return NULL_ITEM;

    Item top = PQ_getTop(*pq);
    pq->heap[1] = pq->heap[pq->size--];
    HEAP_fixdown(pq->heap, pq->size, 1);
    return top;
}

Item PQ_remove(PriorityQueue *pq, int i)
{
    if (i < 1 || i > pq->size)
        return NULL_ITEM;

    Item removed = pq->heap[i];
    pq->heap[i] = pq->heap[pq->size--];
    HEAP_fixdown(pq->heap, pq->size, i);
    return removed;
}

void solve()
{
    int n, k;
    scanf(" %d %d\n", &n, &k);
    if (n == 0 && k == 0)
        return;

    Item v = malloc(n * sizeof(struct Item));
    for (int i = 0; i < n; i++)
        scanf(" %d", &v[i].value);

    PriorityQueue pq = PQ_init(k);
    for (int i = 0; i < k - 1; i++)
        PQ_insert(&pq, &v[i]);

    for (int i = k - 1; i < n; i++)
    {
        PQ_insert(&pq, &v[i]);
        printf("%d%c", PQ_getTop(pq)->value, " \n"[i == n-1]);
        PQ_remove(&pq, v[i - k + 1].heap_idx);
    }

    PQ_free(pq);
    solve();
}

int main()
{
    solve();

    return 0;
}
