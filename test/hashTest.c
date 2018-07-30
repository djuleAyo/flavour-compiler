#include "hash.h"
#include "stack.h"
#include "flavour.h"



typedef struct {
  int a;
  int b;
} koordinate;


int main()
{
    hash h = make_hash();
    
    koordinate k;
    k.a=2;
    k.b=3;
    
    
    
    int i;
    for(i=0;i<10001;i++)
    {
        string key = malloc(10);
        sprintf(key,"%d",i);
        hash_add(h,key,&k);
        free(key);
    }
    
    pair p = hash_find(h, "5");
    printf("%s\n",p->key);
        
    
    koordinate uk;
    uk.a = 100;
    uk.b = 12;
    
    hash_update(h, "123", &uk);
    
    p = hash_find(h, "123");
    printf("%s %d %d\n",p->key,((koordinate*)(p->data))->a ,((koordinate*)(p->data))->b);
    
    
    p = hash_find(h, "asd");
    assert(!p);
    printf("hash_find nije nasao 'asd'\n");
    p = hash_remove(h,"123");
    p = hash_find(h,"123");
    assert(!p);
    printf("hash_find nije obrisao '123'\n");
    
    
    
    
    free_hash(h);
    
    
    return 0;
}
