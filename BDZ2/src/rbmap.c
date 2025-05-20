#include "rbmap.h"
#include <stdio.h>


static RBNode *create_node(void *key, void *value, Color color) {
    RBNode *node = malloc(sizeof(RBNode));
    node->key = key;
    node->value = value;
    node->color = color;
    node->left = node->right = node->parent = NULL;
    return node;
}

static void left_rotate(RBMap *map, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) map->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

static void right_rotate(RBMap *map, RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent) map->root = x;
    else if (y == y->parent->right) y->parent->right = x;
    else y->parent->left = x;
    x->right = y;
    y->parent = x;
}

static void insert_fixup(RBMap *map, RBNode *z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode *y = z->parent->parent->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(map, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(map, z->parent->parent);
            }
        } else {
            RBNode *y = z->parent->parent->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(map, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(map, z->parent->parent);
            }
        }
    }
    map->root->color = BLACK;
}

void rbmap_insert(RBMap *map, void *key, void *value) {
    RBNode *z = create_node(key, value, RED);
    RBNode *y = NULL;
    RBNode *x = map->root;

    while (x) {
        y = x;
        int cmp = map->cmp(key, x->key);
        if (cmp == 0) {
            x->value = value; // заменить значение
            free(z);
            return;
        }
        x = (cmp < 0) ? x->left : x->right;
    }

    z->parent = y;
    if (!y) map->root = z;
    else if (map->cmp(key, y->key) < 0) y->left = z;
    else y->right = z;

    insert_fixup(map, z);
}

void *rbmap_get(RBMap *map, void *key) {
    RBNode *current = map->root;
    while (current) {
        int cmp = map->cmp(key, current->key);
        if (cmp == 0) return current->value;
        current = (cmp < 0) ? current->left : current->right;
    }
    return NULL; // ключ не найден
}

static void destroy_node(RBNode *node, void (*free_func)(void *, void *)) {
    if (!node) return;
    destroy_node(node->left, free_func);
    destroy_node(node->right, free_func);
    if (free_func) free_func(node->key, node->value);
    free(node);
}

void rbmap_destroy(RBMap *map, void (*free_func)(void *, void *)) {
    destroy_node(map->root, free_func);
    free(map);
}

RBMap *rbmap_create(int (*cmp)(const void *, const void *)) {
    RBMap *map = malloc(sizeof(RBMap));
    map->root = NULL;
    map->cmp = cmp;
    return map;
}
