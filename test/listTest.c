#include "list.h"
#include "flavour.h"

bool order(void *x, void* y)
{
  return *(int*)x == *(int*)y;
}

int main()
{
  list l = make_list();

  int dva = 2;
  int pet = 5;
  int sedam = 7;
  int k = 100;

  for(int i = 0; i < 5000; i++)
    list_add_end(&l, &dva);

  for(int i = 0; i < 3; i++)
    list_add_start(&l, &pet);

  list_add_end(&l, &sedam);

  int* n = list_find(l, &sedam, order);
  printf("%d\n", *n);

  int* n2 = list_find(l, &k, order);
  printf("%s\n", n2? "ima" : "nema");

  //skida prvi
  list_remove(&l, &pet, order);
  int* n1 = list_find(l, &pet, order);

  //skida poslednji
  list_remove(&l, &sedam, order);


  list_remove(&l, &pet, order);
  list_remove(&l, &pet, order);

  n2 = list_find(l, &pet, order);
  printf("%s\n", n2? "ima" : "nema");

  list_remove(&l, &dva, order);
  list_remove(&l, &dva, order);
  list_remove(&l, &dva, order);

  //assert(!l);
    

  free_list(&l);


}
