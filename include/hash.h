#ifndef _HASH_H
#define _HASH_H
#include "flavour.h"

//DEPENDENCIES
#include "list.h"
#include "pair.h"

#define INITIAL_HASH_VOLUME 109

//Since hash does not know what it holds it cannot free anything
//The user of the hash is responsible for dealloc.

/*Hash is using chaining for resolving collisions */

//in case of key conflict error will occur
//to update element use hash_update

//list in hash must contain pair as data

struct _hash
{
  size_t volume;
  //hash can store as muche as needed but O(1) is no longer
  size_t size;
  list *data;
};
typedef struct _hash *hash;

hash make_hash();
void free_hash(hash h);

pair hash_find(hash h, string k);
void* hash_add(hash h, string k, void* v);
//since hash cannot free value we return it to a caller
void* hash_remove(hash h, string k);
//return old value to a caller so it can be freed
void* hash_update(hash h, string k, void* v);


unsigned djb2(string key);

#endif
