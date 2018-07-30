#include "hash.h"
#include "stack.h"
#include "flavour.h"



int main()
{
    /*
    bucket b = Bucket("key","vrednost");
    
    free_bucket(b);
    
    
    hash h = Hash();
    char *value = strdup("vrednost");
    
    hash_add(h,"key", value);
    //hash_remove(h,"key");
    printf("%s\n",(char*)hash_remove(h,"key"));
    free_hash(h);
    free(value);
    
    
    
    */
    hash h = Hash();
    
    stack s1 = Stack();
    stack s2 = Stack();
    stack s3 = Stack();
    
    hash_add(h, "s1", s1);
    hash_add(h, "s2", s2);
    hash_add(h, "s3", s3);
    
    
    //printf("%s\n", hash_find(h,"s1") == hash_remove(h, "s1") ? "ok":"not ok");
    
    printf("s1: %ld == %ld\n", s1, hash_find(h, "s1"));
    printf("s2: %ld == %ld\n", s2, hash_find(h, "s2"));
    printf("s3: %ld == %ld\n", s3, hash_find(h, "s3"));

    free_stack(s1);
    free_stack(s2);
    free_stack(s3);

    hash_remove(h, "s1");
    hash_remove(h, "s3");
    hash_remove(h, "s2");
    
    free_hash(h);
    
    return 0;
}