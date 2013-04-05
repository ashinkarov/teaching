#include <stdlib.h>
#include <string.h>

#include "mystring.h"


static char *
string_length_min (char * l, char *r)
{
  if (strlen (l) < strlen (r))
    return l;
  else
    return r;
}

/* -1  ==> l <  r
    0  ==> l == r
    1  ==> l >  r
*/
int
string_compare (char * l, char * r)
{
  size_t i;
  char * min = string_length_min (l, r);

  for (i = 0; i < strlen (min); i++)
    {
      if (l[i] < r[i])
	return -1;
      else if (l[i] > r[i])
        return 1;
    }

  if (strlen (l) == strlen (r))
    return 0;

  if (min == l)
    return -1;

  return 1;
}


