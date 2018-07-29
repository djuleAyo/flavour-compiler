#include "sym_data.h"
#include "flavour.h"

struct _basic_interface basic_interface_int;
struct _basic_interface basic_interface_string;

#define MAX_STR_LEN (256)

sym_data Sym_data(type_enum t, void* var)
{
    sym_data new = malloc(sizeof(struct _sym_data));
    assert(new);
    
    switch(t)
    {
        case TYPE_ENUM_INT:
            new->bi = &basic_interface_int;
            break;
        case TYPE_ENUM_STRING:
            new->bi = &basic_interface_string;
            break;
        default:
            assert(0);
    }
    new->type_value = Basic_type_value(t, var);
    
    return new;
}

void free_sym_data(sym_data s)
{
    if(!s)
        return;
    switch(s->type_value->type)
    {
        case TYPE_ENUM_INT:
	  (s->bi->destructor)(&(s->type_value->var.num));
	  break;
        case TYPE_ENUM_STRING:
	  (s->bi->destructor)(s->type_value->var.str);
	  break;
        default:
            assert(0);
    }
    free(s);
}

string sym_dataToString(sym_data s)
{
    if(!s)
        return NULL;
    string ret_str;
    
    switch(s->type_value->type)
    {
        case TYPE_ENUM_INT:
	  ret_str = (s->bi->toString)(&(s->type_value->var.num));
	  break;
        case TYPE_ENUM_STRING:
	  ret_str = (s->bi->toString)((s->type_value->var.str));
	  break;
        default:
	  assert(0);
    }
    
    return ret_str;
}

/* int type_check(sym_data s, type_enum t) */
/* { */
/*     return s->t == t? 1:0; */
/* } */

/* int same_type(sym_data s1, sym_data s2) */
/* { */
/*     return s1->t == s2->t ? 1:0; */
/* } */

/*
int main()
{
    
    sym_data s1,s2,s3;
    
    int i =3;
    s1 = Sym_data(TYPE_ENUM_INT, &i);
    char *s = strdup("makarena");
    s2 = Sym_data(TYPE_ENUM_STRING, s);
    char *str = strdup("eeeej");
    s3 = Sym_data(TYPE_ENUM_STRING, str);
    
    init_basic_interfaces();
    
    
    char *str_sym3 = sym_dataToString(s3);
    char *str_sym2 = sym_dataToString(s2);
    
    printf("symbol: %s\nsymbol: %s\n",str_sym3,str_sym2);
    
    free(str_sym2);
    free(str_sym3);
    
    free_sym_data(s1);
    free_sym_data(s2);
    free_sym_data(s3);
    
    return 0;
}

*/
