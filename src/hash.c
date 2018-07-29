#include "flavour.h"
#include "hash.h"
//pair is dependancie
#include "pair.h"

unsigned long djb2(string  s);

//when bucket is created key will be duplicated in memory
//this dupicated key will be removed by bucket_free function
//user is responisble for freeing passed key argument
bucket Bucket(string key, void* value)
{
  bucket new = malloc(sizeof(struct _bucket));
  assert(new);

  new->content = Pair(key, value);
  new->next = NULL;

  return new;
}

void free_bucket(bucket b)
{
    if(!b)
        return;
    free_pair(b->content);
    free(b);
}


//================================================================

hash Hash()
{
  hash new = malloc(sizeof(struct _hash));
  assert(new);

  //must allocate data to NULL
  new->data = calloc(sizeof(void*), INITIAL_HASH_VOLUME);
  assert(new->data);

  new->size = 0;
  new->volume = INITIAL_HASH_VOLUME;

  return new;
}

unsigned long djb2(string  str)
{
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}

pair_value hash_find(hash h, string key)
{
  int index =(int)(djb2(key) % h->volume);
  if((h->data)[index])
  {
    bucket tmp = (h->data)[index];
    while(tmp)
    {
      if(!strcmp(tmp->content->key, key))
        return tmp->content;
      else
        tmp = tmp->next;
    }
  }
  return NULL;
}


//new buckets are stored at the end of bucket list because we want
//to check all previous keys for no duplicates
void hash_add(hash h, string key, pair_value value)
{
  //TODO resize of hash when average list length is greater then 2

  int index =(int)(djb2(key) % h->volume);
  if(!((h->data)[index]))
  {
    (h->data)[index] = Bucket(key, value);
    return;
  }
  
  bucket tmp = (h->data)[index];
  if(!strcmp(tmp->content->key, key))
      assert(0);
  while(tmp->next)
  {
    if(!strcmp(tmp->content->key, key))
      assert(0);
    else
      tmp = tmp->next;
  }
  tmp->next = Bucket(key, value);
}

pair_value hash_remove(hash h, string key)
{
  int index =(int)(djb2(key) % h->volume);
  
  if(!((h->data)[index]))
    return NULL;
  
  //if key was first in list of buckets
  bucket tmp = (h->data)[index];
  pair ret_val;
  if(!strcmp(tmp->content->key, key))
  {
    (h->data)[index] = tmp->next;
    ret_val = tmp->content->value;
    free_bucket(tmp);
    return ret_val;
  }
  //otherwise
  while(tmp->next)
  {
    if(!strcmp(tmp->next->content->key, key))
    {
      bucket del_tmp = tmp->next;
      tmp->next = tmp->next->next;
      ret_val = tmp->next->content->value;
      free_bucket(del_tmp);
      return ret_val;
    }
    tmp = tmp->next;
  }
  return NULL;
}

void free_hash(hash h)
{
  free(h->data);
  free(h);
}
