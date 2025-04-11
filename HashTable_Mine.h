//
// Created by Adams Humbert on 4/10/2025.
//

#ifndef HASHTABLE_MINE_H
#define HASHTABLE_MINE_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #todo: resizing and unit tests

// hash item
typedef struct
{
    char* key;
    char* value;
} hash_item;

/* hash item functionality */

hash_item* ht_new_item(char* key, char* value);

static hash_item DELETED_ITEM = {NULL, NULL};
void delete_hash_item(hash_item* item);

inline void print_hash_item(char* key, char* value)
{
    printf("%s:%s\n", key, value);
}

/*hash table */

typedef struct
{
    hash_item** items;
    uint64_t count;
    uint64_t size;
} hash_table;

#define HASH_TABLE_CAPACITY 100
hash_table* ht_new();


void delete_hash_table(hash_table* ht);

/* core functionality of a hash table
 *insert
 *retrieve/get
 * contains
 * remove
 * size/length
 */

//Fowler–Noll–Vo hash function
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
uint64_t generate_hash_key(const char* key);
uint64_t get_hash(const char* key,uint64_t table_size,  uint64_t CollisionNumber)

void insert(hash_table* hash_table, char* key, char* value);

// returns the value
char* get(hash_table* hash_table, const char* key);

bool contains(hash_table* hash_table, const char* key);

void remove_from_hash_table();

//uint64_t size();


#endif //HASHTABLE_MINE_H
