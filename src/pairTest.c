#include "pair.h"

#include "flavour.h"


typedef struct {
  int a;
  int b;
} koordinate;

#define MAX_SIZE 100

string koordinate_to_string(void* x)
{
  string ret_str = malloc(MAX_SIZE);
  assert(ret_str);

  sprintf(ret_str, "%d %d", ((koordinate*)x)->a, ((koordinate*)x)->b);

  return ret_str;
}

void dummyFree(void* v) { UNUSED(v);}

int main()
{
  koordinate x;
  x.a = 3;
  x.b = 4;

  pair p = Pair("aoeu", &x);
  
  printf("%s: %d, %d\n",p->key,((koordinate*)p->value)->a, ((koordinate*)p->value)->b);
  //free(str);
  free_pair(p);
  
  return 0;
}
