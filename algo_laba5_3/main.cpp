#include <iostream>
#include <cstring>

struct node
{
    char key[21];
    char value[21];
    node* bucket_next;
    node* bucket_prev;
    node* next;
    node* prev;
};

struct bucket
{
    node* head;
    node* tail;
};

bucket* hashTable;
const int size = 100003;
const int p = 31;
node* tail = NULL;

unsigned int hash(char x[21])
{
    unsigned int h = 0;
    for (int i = 0; i < 21; i++)
    {
        if (x[i] == '\0')
        {
            break;
        }
        h += x[i];
    }
    return h % size;
}

node* get(char x[21])
{
    unsigned int num = hash(x);
    bucket b = hashTable[num];

    if (b.head == NULL)
    {
        return NULL;
    }

    node* n = b.head;
    do
    {
        if (strcmp(n->key, x) == 0)
        {
            return n;
        }
        n = n->bucket_next;
    } while (n != NULL);

    return NULL;
}

void put(char x[21], char y[21])
{
    node* n = get(x);
    if (n != NULL)
    {
        strcpy(n->value, y);
        return;
    }

    unsigned int num = hash(x);
    bucket* b = &hashTable[num];
    node* newNode = new node;
    strcpy(newNode->key, x);
    strcpy(newNode->value, y);
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->bucket_next = NULL;

    if (b->head == NULL)
    {
        b->head = newNode;
        newNode->bucket_prev = NULL;
    }
    else
    {
        b->tail->bucket_next = newNode;
        newNode->bucket_prev = b->tail;
    }

    b->tail = newNode;

    if (tail != NULL)
    {
        tail->next = newNode;
        newNode->prev = tail;
    }
    tail = newNode;
}

void del(char x[21])
{
    node* n = get(x);

    if (n != NULL)
    {
        unsigned int num = hash(x);
        bucket* b = &hashTable[num];
        if (n->bucket_next != NULL)
        {
            n->bucket_next->bucket_prev = n->bucket_prev;
        }
        if (n->bucket_prev != NULL)
        {
            n->bucket_prev->bucket_next = n->bucket_next;
        }

        if (b->head == n)
        {
            b->head = n->bucket_next;
        }

        if (b->tail == n)
        {
            b->tail = n->bucket_prev;
        }

        if (tail == n)
        {
            tail = tail->prev;
        }

        if (n->prev != NULL)
        {
            n->prev->next = n->next;
        }

        if (n->next != NULL)
        {
            n->next->prev = n->prev;
        }

        delete(n);
    }
}

node* next(char x[21])
{
    node* n = get(x);
    if (n != NULL)
    {
        return n->next;
    }
    return NULL;
}

node* prev(char x[21])
{
    node* n = get(x);
    if (n != NULL)
    {
        return n->prev;
    }
    return NULL;
}

int main() {
    FILE* fin = fopen("linkedmap.in", "r");
    FILE* fout = fopen("linkedmap.out", "w");

    char* command = new char[21];
    hashTable = new bucket[size];
    for (int i = 0; i < size; i++)
    {
        hashTable[i].head = NULL;
        hashTable[i].tail = NULL;
    }

    char x[21];
    char y[21];

    while (true)
    {
        if (fscanf(fin, "%s", command) == -1)
        {
            break;
        }

        if (strcmp(command, "put") == 0)
        {
            fscanf(fin, "%s %s", x, y);
            put(x, y);
        }
        else if (strcmp(command, "delete") == 0)
        {
            fscanf(fin, "%s", x);
            del(x);
        }
        else if (strcmp(command, "get") == 0)
        {
            fscanf(fin, "%s", x);
            node* res = get(x);
            if (res == NULL)
            {
                fprintf(fout, "none\n");
            }
            else
            {
                fprintf(fout, "%s\n", res->value);
            }
        }
        else if (strcmp(command, "next") == 0)
        {
            fscanf(fin, "%s", x);
            node* res = next(x);
            if (res == NULL)
            {
                fprintf(fout, "none\n");
            }
            else
            {
                fprintf(fout, "%s\n", res->value);
            }
        }
        else if (strcmp(command, "prev") == 0)
        {
            fscanf(fin, "%s", x);
            node* res = prev(x);
            if (res == NULL)
            {
                fprintf(fout, "none\n");
            }
            else
            {
                fprintf(fout, "%s\n", res->value);
            }
        }
    }
    return 0;
}