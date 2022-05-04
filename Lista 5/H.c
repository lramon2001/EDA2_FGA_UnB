#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item
{
    char k[11], fn[101], ln[101], bd[20], pn[20];
} Item;

#define HT_SIZE 1572869u
#define key(a) (a.k)
#define less(a, b) (a < b)
#define swap(a, b) \
    {              \
        int t = a; \
        a = b;     \
        b = t;     \
    }
#define cmpswap(a, b) \
    if (less(b, a))   \
    swap(a, b)
#define eq(a, b) (!(strcmp(a.k, b.k) || strcmp(a.fn, b.fn) || strcmp(a.ln, b.ln) || strcmp(a.bd, b.bd) || strcmp(a.pn, b.pn)))

int partition(int *v, int l, int r)
{
    int pivot = v[r];
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

void quicksortM3(int *v, int l, int r)
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

void insertionsort(int *v, int l, int r)
{
    for (int i = l + 1, j; i <= r; i++)
    {
        int t = v[i];
        for (j = i; j > 0 && less(t, v[j - 1]); j--)
            v[j] = v[j - 1];
        v[j] = t;
    }
}

void quicksort(int *v, int l, int r)
{
    quicksortM3(v, l, r);
    insertionsort(v, l, r);
}

#define STRING_HASH

#ifdef STRING_HASH
#define INITIAL_HASH_VALUE 5381
#define MULT_HASH_VALUE 33
unsigned hashu(const char *x)
{
    unsigned h = INITIAL_HASH_VALUE;
    for (int i = 0; x[i] != '\0'; i++)
        h = (h * MULT_HASH_VALUE + x[i]) % HT_SIZE;
    return h;
}
#define key_t const char *
#define hash_k(k) (hashu(k))
#define eq_k(x, k) (strcmp(key(x), k) == 0)
#else
#define hash_k(k) (key(k) % HT_SIZE)
#define key_t int
#define eq_k(x, k) (key(x) == k)
#endif
#define hash(x) (hash_k(key(x)))

typedef struct LinkedItem
{
    Item item;
    struct LinkedItem *next;
} LinkedItem;

typedef struct HashTable
{
    unsigned size;
    LinkedItem **v;
} HashTable;

HashTable HT_init()
{
    HashTable ht = {.size = 0};
    ht.v = (LinkedItem **)malloc(HT_SIZE * sizeof(LinkedItem *));
    for (unsigned i = 0; i < HT_SIZE; i++)
        ht.v[i] = NULL;
    return ht;
}

void HT_free(HashTable ht)
{
    for (unsigned i; i < HT_SIZE; i++)
    {
        LinkedItem *prev = ht.v[i], *next = NULL;
        while (prev)
        {
            next = prev->next;
            free(prev);
            prev = next;
        }
    }
    free(ht.v);
}

#define HT_MACRO(k_name)                                         \
    int HT_insert##k_name(HashTable *ht, Item x)                 \
    {                                                            \
        unsigned h = hash(x);                                    \
        if (!ht->v[h])                                           \
        {                                                        \
            ht->v[h] = (LinkedItem *)malloc(sizeof(LinkedItem)); \
            *ht->v[h] = (LinkedItem){.next = NULL, .item = x};   \
            return 1;                                            \
        }                                                        \
        LinkedItem *curr = ht->v[h];                             \
        while (curr->next && !eq(curr->item, x))                 \
            curr = curr->next;                                   \
        if (eq(curr->item, x))                                   \
            return 0;                                            \
        curr->next = (LinkedItem *)malloc(sizeof(LinkedItem));   \
        *curr->next = (LinkedItem){.item = x, .next = NULL};     \
        ht->size++;                                              \
        return 1;                                                \
    }                                                            \
    int HT_remove##k_name(HashTable *ht, key_t k)                \
    {                                                            \
        unsigned h = hash_k(k);                                  \
        if (!ht->v[h])                                           \
            return 0;                                            \
        LinkedItem *curr = ht->v[h], *to_remove = NULL;          \
        if (eq_k(curr->item, k))                                 \
        {                                                        \
            ht->v[h] = curr->next;                               \
            to_remove = curr;                                    \
        }                                                        \
        else                                                     \
        {                                                        \
            while (curr->next && !eq_k(curr->next->item, k))     \
                curr = curr->next;                               \
            if (!curr->next)                                     \
                return 0;                                        \
            to_remove = curr->next;                              \
            curr->next = to_remove->next;                        \
        }                                                        \
        free(to_remove);                                         \
        return 1;                                                \
    }                                                            \
    int HT_delete##k_name(HashTable *ht, Item x)                 \
    {                                                            \
        unsigned h = hash(x);                                    \
        if (!ht->v[h])                                           \
            return 0;                                            \
        LinkedItem *curr = ht->v[h], *to_remove = NULL;          \
        if (eq(curr->item, x))                                   \
        {                                                        \
            ht->v[h] = curr->next;                               \
            to_remove = curr;                                    \
        }                                                        \
        else                                                     \
        {                                                        \
            while (curr->next && !eq(curr->next->item, x))       \
                curr = curr->next;                               \
            if (!curr->next)                                     \
                return 0;                                        \
            to_remove = curr->next;                              \
            curr->next = to_remove->next;                        \
        }                                                        \
        free(to_remove);                                         \
        return 1;                                                \
    }                                                            \
    LinkedItem *HT_search##k_name(HashTable ht, key_t k)         \
    {                                                            \
        unsigned h = hash_k(k);                                  \
        LinkedItem *curr = ht.v[h];                              \
        while (curr)                                             \
        {                                                        \
            if (eq_k(curr->item, k))                             \
                return curr;                                     \
            curr = curr->next;                                   \
        }                                                        \
        return NULL;                                             \
    }                                                            \
    int HT_contains##k_name(HashTable ht, Item x)                \
    {                                                            \
        LinkedItem *curr = ht.v[hash(x)];                        \
        while (curr)                                             \
        {                                                        \
            if (eq(curr->item, x))                               \
                return 1;                                        \
            curr = curr->next;                                   \
        }                                                        \
        return 0;                                                \
    }

#ifndef HT_K
#define HT_K
#undef key
#define key(x) (x.k)
#define hash(x) (hash_k(key(x)))
HT_MACRO(k)
#endif

#ifndef HT_FN
#define HT_FN
#undef key
#define key(x) (x.fn)
#define hash(x) (hash_k(key(x)))
HT_MACRO(fn)
#endif

#ifndef HT_LN
#define HT_LN
#undef key
#define key(x) (x.ln)
#define hash(x) (hash_k(key(x)))
HT_MACRO(ln)
#endif

#ifndef HT_BD
#define HT_BD
#undef key
#define key(x) (x.bd)
#define hash(x) (hash_k(key(x)))
HT_MACRO(bd)
#endif

#ifndef HT_PN
#define HT_PN
#undef key
#define key(x) (x.pn)
#define hash(x) (hash_k(key(x)))
HT_MACRO(pn)
#endif

typedef struct Query
{
    char field[4], value[200];
} Query;

int ans[1000], ans_size = 0;

void solve()
{
    HashTable is = HT_init(), fs = HT_init(), ls = HT_init(), bs = HT_init(), ps = HT_init();

    char command[6];
    while (scanf(" %s", command) == 1)
    {
        switch (command[0])
        {
        case 'a':
        {
            Item x;
            scanf(" %s %s %s %s %s", x.k, x.fn, x.ln, x.bd, x.pn);
            if (HT_searchk(is, x.k))
                printf("ID %s ja cadastrado.\n", x.k);
            else
            {
                HT_insertk(&is, x);
                HT_insertfn(&fs, x);
                HT_insertln(&ls, x);
                HT_insertbd(&bs, x);
                HT_insertpn(&ps, x);
            }

            break;
        }
        case 'i':
        {
            char k[11];
            scanf(" %s", k);
            LinkedItem *x = HT_searchk(is, k);
            if (!x)
                printf("ID %s nao existente.\n", k);
            else
                printf("%s %s %s %s\n", x->item.fn, x->item.ln, x->item.bd, x->item.pn);
            break;
        }
        case 'd':
        {
            char k[11];
            scanf(" %s", k);
            LinkedItem *x = HT_searchk(is, k);
            if (!x)
                printf("ID %s nao existente.\n", k);
            else
            {
                HT_deletefn(&fs, x->item);
                HT_deleteln(&ls, x->item);
                HT_deletebd(&bs, x->item);
                HT_deletepn(&ps, x->item);
                HT_deletek(&is, x->item);
            }
            break;
        }
        default:
        {
            Query qs[4];
            int qsize;

            char line[202];
            scanf(" %[^\n]s", line);
            char *q = strtok(line, " ");
            for (qsize = 0; q && qsize < 4; qsize++)
            {
                sscanf(q, " %[^:]:%s", qs[qsize].field, qs[qsize].value);
                q = strtok(NULL, " ");
            }

            for (LinkedItem *x = (qs[0].field[0] == 'f' ? HT_searchfn(fs, qs[0].value) : (qs[0].field[0] == 'l' ? HT_searchln(ls, qs[0].value) : (qs[0].field[0] == 'b' ? HT_searchbd(bs, qs[0].value) : HT_searchpn(ps, qs[0].value)))); x; x = x->next)
            {
                int ok = 1;
                for (int j = 0; j < qsize; j++)
                {
                    if (qs[j].field[0] == 'f' && strcmp(qs[j].value, x->item.fn))
                    {
                        ok = 0;
                        break;
                    }
                    else if (qs[j].field[0] == 'l' && strcmp(qs[j].value, x->item.ln))
                    {
                        ok = 0;
                        break;
                    }
                    else if (qs[j].field[0] == 'b' && strcmp(qs[j].value, x->item.bd))
                    {
                        ok = 0;
                        break;
                    }
                    else if (qs[j].field[0] == 'p' && strcmp(qs[j].value, x->item.pn))
                    {
                        ok = 0;
                        break;
                    }
                }
                if (ok)
                    ans[ans_size++] = atoi(x->item.k);
            }
            if (!ans_size)
                printf("\n");
            else
            {
                quicksort(ans, 0, ans_size - 1);
                for (int i = 0; i < ans_size; i++)
                    printf("%d%c", ans[i], " \n"[i == ans_size - 1]);
                ans_size = 0;
            }
        }
        }
    }

    HT_free(is);
    HT_free(bs);
    HT_free(fs);
    HT_free(ls);
    HT_free(ps);
}

int main()
{
    solve();

    return 0;
}
