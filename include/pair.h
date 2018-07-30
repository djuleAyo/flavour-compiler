#ifndef _PAIR_H
#define _PAIR_H

#include "flavour.h"

struct _pair 
{
  string key;
  void *data;
};

typedef struct _pair* pair;

pair make_pair(string key, void* value);
void free_pair(pair p);

bool pair_has_key(pair p, string k);

#endif
