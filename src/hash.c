#include "hash.h"
//pair is dependancie

#include "flavour.h"

//TODO hash resize_Hash(size_t volume, size_t size);


//when bucket is created key will be duplicated in memory
//this dupicated key will be removed by bucket_free function
//user is responisble for freeing passed key argument

hash make_hash()
{
  hash new = malloc(sizeof(struct _hash));
  assert(new);

  //must allocate data to NULL
  new->data = calloc(sizeof(list), INITIAL_HASH_VOLUME);
  assert(new->data);

  new->size = 0;
  new->volume = INITIAL_HASH_VOLUME;

  return new;
}

void free_hash(hash h)
{
    if(!h)
        return;
    unsigned i = 0;
    for(i = 0; i < h->volume; i++)
    {
        if((h->data)[i])
        {
            list_iterate((h->data)[i], free_pair);
            free_list(&((h->data)[i]));
        }
    } 
    free(h->data);
    free(h);
}

unsigned djb2(string key)
{
  unsigned long hash = 5381;
  int c;
  while ((c = *key++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}

pair hash_find(hash h, string k)
{
  int index =(int)(djb2(k) % h->volume);
  pair p = (pair)list_find((h->data)[index], k , pair_has_key);
  return p;
}


//new lists are stored at the end of data list because we want
//to check all previous keys for no duplicates
void* hash_add(hash h, string k, void* v)
{
  //TODO resize of hash when average list length is greater then 2

    /* pair p = hash_find(h, k); */
    /* if(p) */
    /*     assert(!E_HASH_DUPLICATE_KEY); */
    
  int index =(int)(djb2(k) % h->volume);
  if(!((h->data)[index]))
  {
    list_add_start(&((h->data)[index]), make_pair(k,v));
    return v;
  }
  
  list_add_end(&((h->data)[index]), make_pair(k,v));
  return v;
}

void* hash_remove(hash h, string k)
{
  int index =(int)(djb2(k) % h->volume);
  
  if(!((h->data)[index]))
    return NULL;
  pair p = list_remove(&((h->data)[index]),k, pair_has_key);
  void *tmp = p->data;
  free_pair(p);
  return tmp;
}

void* hash_update(hash h, string k, void *v)
{
    pair p = hash_find(h,k);
    if(!p)
        assert(!E_HASH_NOENT_UPDATE);
    void *tmp = p->data;
    p->data = v;
    return tmp;
}
