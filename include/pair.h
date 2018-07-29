#pragma once

#include "basic_interface.h"

typedef char* string;

struct _pair 
{
  string key;
  void *value;
};

typedef struct _pair* pair;

pair Pair(string key, void* value);
void free_pair(pair p);