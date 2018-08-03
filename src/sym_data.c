#include "sym_data.h"
#include "flavour.h"

sym_data make_sym_data(type_of_sym_data t, void* data)
{
    sym_data new = malloc(sizeof(struct _sym_data));
    assert(new);
    new->type_val = t;
    switch(t)
      {
      case SYM_DATA__TYPE:
        {
          t->data_union.type_val = (type)data;
        }
        break;
      case SYM_DATA__FUNC:
        {
          assert(0);
        }
        break;
      case SYM_DATA__OBJ:
        {
          t->data_union.object_val = (object)data;
        }
        break;
      case SYM_DATA__CLASS:
        assert(0);
        break;
      default:
        assert(0);
      }
   return new;
}

void free_sym_data(sym_data s)
{
    if(!s)
        return;
    switch(s->type)
    {
    case SYM_DATA__TYPE:
	  free_type(s->type_val);
	  break;
        case SYM_DATA__OBJ:

          free_object(s->object_val);
	  break;
        default:
            assert(0);
    }
  free(s);
}

/*
string sym_dataToString(sym_data s)
{
    if(!s)
        return NULL;
    string ret_str;

    switch(t)
      {
      case SYM_DATA_TYPE:
        {
          free_type(s->data.t);;
        }
        break;
      case SYM_DATA_FUNC:
        {
          assert(0);
        }
        break;
      case SYM_DATA_OBJ:
        {
          free_object(s->data.o);
        }
        break;
      case SYM_DATA_CLASS:
        assert(0);
        break;
      default:
        assert(0);
      }
    
    return ret_str;
}
*/
