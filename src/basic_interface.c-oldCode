#include "basic_interface.h"

#define INT_MAX_STR_LEN 12

string intToString(void* x)
{
  string str = malloc(INT_MAX_STR_LEN);
  assert(str);

  sprintf(str, "%d", *(int*)x);

  return str;
}

void intDestructor(void* x)
{
  //ints types are stored on stack
  UNUSED(x);
}

//str to str makes a copy so the original stays
string stringToString(void* s)
{
  string str = malloc(strlen((string)s) + 3);
  assert(str);

  sprintf(str, "\"%s\"", (string)s);
  
  return str;
}

void stringDestructor(void* s)
{
  free((string)s);
}

struct _basic_interface basic_interface_int;
struct _basic_interface basic_interface_string;

void init_basic_interfaces()
{
  basic_interface_string.toString = stringToString;
  basic_interface_string.destructor = stringDestructor;

  basic_interface_int.toString = intToString;
  basic_interface_int.destructor = intDestructor;
  
}
