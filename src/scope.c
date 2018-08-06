#include "list.h"
#include "scope.h"
#include "errors.h"

scope current_scope;
scope global_scope;

void init_scope()
{
  global_scope = make_scope(NULL, NULL);
  current_scope = global_scope;
}

void deinit_scope()
{
  free_scope(global_scope);
}


scope make_scope(scope scope_parrent, scope lambda_parrent)
{
  scope new = malloc(sizeof(struct _scope));
  assert(new);

  new->ref_count = 0;
  new->table = make_hash();
  new->lambda_parrent = lambda_parrent;
  new->scope_parrent = scope_parrent;

  return new;
}

void free_pair_object_call_back(void* p)
{
  free_object((((pair)p)->data));
  free_pair((pair)p);
}
void free_scope(scope s)
{

  unsigned i;
  for(i=0; i< s->table->volume; i++)
    {
      if(!((s->table->data)[i])) continue;

      list_iterate(((s->table->data)[i]), free_pair_object_call_back);
      free_list(&((s->table->data)[i]));
    }
  free_hash(s->table);
  free(s);
}

void free_scope_branch(scope s)
{
  if(s->ref_count)
    return;
  free_scope_branch(s->scope_parrent);
  free_scope(s);
}


object scope_find(scope s, string k, type t)
{
  object ret_val = NULL;

  if(t) goto lambda;
 not_lambda:
  {
    pair p = hash_find(s->table, k);
    if(p) return p->data;
    else goto recursion;
  }

 lambda:
  {
    int i =(int)(djb2(k) % s->table->volume);
    list l = (s->table->data)[i];
    if(!l)
      return NULL;

    while(l)
      {

        if(strcmp(((pair)(l->data))->key, k))
          {
            l = l->next;
            continue;
          }
        if(type_equals(((object)((pair)(l->data))->data)->type_val, t))
          {
            return ((object)((pair)(l->data))->data);
          }
        else
          {
            l = l->next;
          }

      }
    goto recursion;
  }

  recursion:
  {
  if(s->scope_parrent)
    {
      ret_val = scope_find(s->scope_parrent, k, t);
    }
  if(ret_val) return ret_val;

  if(s->lambda_parrent)
    {
      ret_val = scope_find(s->lambda_parrent, k, t);
    }
  return ret_val;
  }
}

object scope_assign(scope s, string k, object o)
{
  pair p = hash_find(s->table, k);
  assert(p && "Error: undeclared variable\n");

  free_object((object)(p->data));

  p->data = clone_object(o);

  return p->data;
}

object scope_add(scope s, string k, object o)
{
  int i =(int)(djb2(k) % s->table->volume);
  if(!(s->table->data)[i]) {
    hash_add(s->table,k, o);
    return o;
  }

  list l = (s->table->data)[i];
  if(o->type_val->node_type == TYPE_FUNCTION_NODE)
    {
      if(!strcmp(((pair)(l->data))->key,k))
        {
          if(type_equals(((object)(((pair)(l->data))->data))->type_val, o->type_val))
            assert(!E_SCOPE_OBJECT_EXIST);
        }
      while(l->next)
        {
          if(!strcmp(((pair)(l->next->data))->key,k))
            {
              if(type_equals(((object)((pair)(l->next->data))->data)->type_val, o->type_val))
                assert(!E_SCOPE_OBJECT_EXIST);
              else
                l = l->next;
            }
        }
      list_add_end(&l, make_pair(k, o));
    }
  else
    {
      if(!strcmp(((pair)(l->data))->key, k))
        {
          assert(!E_SCOPE_OBJECT_EXIST);
        }
      while(l->next)
        {
          if(!strcmp(((pair)(l->data))->key, k))
            assert(!E_SCOPE_OBJECT_EXIST);
          else
            l = l->next;
        }
      list_add_end(&l, make_pair(k, o));
    }
  return o;
}
