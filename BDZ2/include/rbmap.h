#ifndef RBMAP_H
#define RBMAP_H

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    void *key;
    void *value;
    Color color;
    struct RBNode *left, *right, *parent;
} RBNode;

typedef struct {
    RBNode *root;
    int (*cmp)(void *, void *);
} RBMap;

RBMap *rbmap_create(int (*cmp)(const void *, const void *));
void rbmap_insert(RBMap *map, void *key, void *value);
void *rbmap_get(RBMap *map, void *key);
void rbmap_destroy(RBMap *map, void (*free_func)(void *, void *));

#endif // RBMAP_H
