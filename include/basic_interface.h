#pragma once

#include "flavour.h"

struct _basic_interface
{
  string (*toString)(void*);
  void (*destructor)(void*);
};

typedef struct _basic_interface* basic_interface;

//static since these are needed during runtime of the compiler
extern struct _basic_interface basic_interface_int;
extern struct _basic_interface basic_interface_string;

void init_basic_interfaces();
