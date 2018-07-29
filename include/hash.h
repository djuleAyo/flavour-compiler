#pragma once

#include "flavour.h"
#include "pair.h"

#define INITIAL_HASH_VOLUME 109

//Since hash does not know what it holds it cannot free anything
//The user of the hash is responsible for dealloc.


//in case of key conflict error will occur

//=================================================================
struct _bucket
{
    pair content;
    struct _bucket *next;
};
typedef struct _bucket *bucket;

bucket Bucket(string key, void* value);
//replace
//when deleting hash table from symbol table
//first delete  pair, then delete bucket
void free_bucket(bucket b);

//=================================================================
struct _hash
{
  size_t volume;
  //hash can store as muche as needed but O(1) is no longer
  size_t size;
  bucket *data;
};
typedef struct _hash *hash;

typedef void* pair_value;
pair_value hash_find(hash h, string key);
void hash_add(hash h, string key, pair_value value);
pair_value hash_remove(hash h, string key);


hash Hash();
//TODO
hash resize_Hash(size_t volume, size_t size);

void free_hash(hash h);
