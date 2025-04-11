//
// Created by Adams Humbert on 4/10/2025.
//

#include "HashTable_Mine.h"


/*
*algorithm fnv-1a is
    hash := FNV_offset_basis

    for each byte_of_data to be hashed do
        hash := hash XOR byte_of_data
        hash := hash × FNV_prime

    return hash
 */

// for 64 bits
#define FNV_offset_basis 14695981039346656037
#define FNV_prime 1099511628211

hash_item* ht_new_item(char* key, char* value)
{
    // create new memory for the items
    hash_item* new_item = malloc(sizeof(hash_item));
    // _strdup copies pointer and pointer size
    new_item->key = _strdup(key);
    new_item->value = _strdup(value);
    return new_item;
}

void delete_hash_item(hash_item* item)
{
    if (item != NULL)
    {
        free(item->key);
        free(item->value);
        free(item);
    }
}

hash_table* ht_new()
{
    hash_table* new_hash_table = malloc(sizeof(hash_table));
    new_hash_table->count = 0;
    new_hash_table->size = HASH_TABLE_CAPACITY;
    new_hash_table->items = calloc((size_t) new_hash_table->size, sizeof(hash_item *));
    return new_hash_table;
}

void delete_hash_table(hash_table* ht)
{
    for (int i = 0; i < ht->size; i++)
    {
        hash_item* item = ht->items[i];
        if (item != NULL)
        {
            hash_item (item);
        }
    }
    free(ht->items);
    free(ht);
}

uint64_t generate_hash_key(const char* key)
{
    uint64_t hash = FNV_offset_basis;

    // iterate over the byte size of the key
    for (const char* p = key; *p; p++)
    {
        //bitwise XOR (^)operation (^= bitwise or with assignment)
        // bitwise XOR sets bits on when they are the same, and off otherwise
        hash ^= (uint64_t) (unsigned char) (*p);
        hash *= FNV_prime;
    }


    //handle collision using open addressing / double hashing

    return hash;
}

uint64_t get_hash(const char* key, uint64_t table_size, uint64_t CollisionNumber)
{
    const uint64_t hash_a = generate_hash_key(key);
    const uint64_t hash_b = generate_hash_key(key);
    return (hash_a + (CollisionNumber * (hash_b + 1))) % table_size;
}


void insert(hash_table* hash_table, char* key, char* value)
{
    // create new hash item
    hash_item* new_item = ht_new_item(key, value);
    // generate a hash key
    uint64_t hash_index = get_hash(key, hash_table->size, 0);
    // map the hash to the index
    hash_item* cur_item = hash_table->items[hash_index];
    uint64_t i = 1;
    while (cur_item != NULL)
    {
        if (cur_item != &DELETED_ITEM)
        {
            // in the event that we already have a value in the hash, we want to overwrite it
            if (strcmp(cur_item->key, key) == 0)
            {
                delete_hash_item(cur_item);
                hash_table->items[hash_index] = cur_item;
                return;
            }
        }
        hash_index = get_hash(new_item->key, hash_table->size, i);
        cur_item = hash_table->items[hash_index];
        i++;
    }
    hash_table->items[hash_index] = new_item;

    // increase count
    hash_table->count++;
}

char* get(hash_table* hash_table, const char* key)
{
    // get the hash key
    uint64_t hash_index = get_hash(key, hash_table->size, 0);
    hash_item* cur_item = hash_table->items[hash_index];
    // since we might have mapped a hash index that had a collision, we want to iterate through all possible indexes
    int i = 1;
    while (cur_item != NULL)
    {
        if (cur_item != &DELETED_ITEM)
        {
            // if we find a match return the value
            if (strcmp(cur_item->key, key) == 0)
            {
                return cur_item->value;
            }
        }
        // if we dont find the value, keep iterating until we reach a valid one or a null one
        hash_index = get_hash(key, hash_table->size, i);
        cur_item = hash_table->items[hash_index];
        i++;
    }
    return NULL;
}


bool contains(hash_table* hash_table, const char* key)
{
    //very similar to the get function, but without returing the value

    // get the hash key
    uint64_t hash_index = get_hash(key, hash_table->size, 0);
    hash_item* cur_item = hash_table->items[hash_index];
    // since we might have mapped a hash index that had a collision, we want to iterate through all possible indexes
    int i = 1;
    while (cur_item != NULL)
    {
        if (cur_item != &DELETED_ITEM)
        {
            // if we find a match return true
            if (strcmp(cur_item->key, key) == 0)
            {
                return true;
            }
        }
        // if we dont find the value, keep iterating until we reach a valid one or a null one
        hash_index = get_hash(key, hash_table->size, i);
        cur_item = hash_table->items[hash_index];
        i++;
    }
    // we have not found a valid item
    return false;
}


void remove_from_hash_table(hash_table* hash_table, const char* key)
{
    // get a valid index, similar thing as the prev functions

    // get the hash key
    uint64_t hash_index = get_hash(key, hash_table->size, 0);
    hash_item* cur_item = hash_table->items[hash_index];
    // since we might have mapped a hash index that had a collision, we want to iterate through all possible indexes
    int i = 1;
    while (cur_item != NULL)
    {
        // make sure we are not checking against an empty item, and that we have a valid item
        if (cur_item != &DELETED_ITEM)
        {
            // if we find a match, we want to delete the function
            if (strcmp(cur_item->key, key) == 0)
            {
                // free the item, and clear the value in the hash table
                delete_hash_item(cur_item);
                hash_table->items[hash_index] = &DELETED_ITEM;
            }
        }
        // if we dont find the value, keep iterating until we reach a valid one for deletion or nothing happens
        hash_index = get_hash(key, hash_table->size, i);
        cur_item = hash_table->items[hash_index];
        i++;
    }
    hash_table->count--;
}
