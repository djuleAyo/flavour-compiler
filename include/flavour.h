#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <assert.h>
#include <string.h>
#include "errors.h"
#include <stdbool.h>

#define UNUSED(x) (void)x

typedef char* string;


/* Conventions:
 * underscore notation!
 *
 * struct fields have long names
 * params use abbr
 *
 * all struct init funcs start with make_ prefix
 * all struct deinit funcs start with free_ prefix
 * both end with struct typedef name
 *
 * all data strct interfaces start with data struct typedef
 * name and action follows as sufix
 */
