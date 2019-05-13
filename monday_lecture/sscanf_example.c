#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
GET /foobar HTTP/1.1
Host: www.example.com
Connection: close
X-Header: whatever
*/

int main (void)
{
  char method[8]; // REST verb
  char path[8192];

  char *s = "GET /foobar HTTP/1.1\nHost: www.example.com\nConnection: close\nX-Header: whatever\n\n";

  sscanf(s, "%s %s", method, path);

  printf("method: \"%s\"\n", method);
  printf("path: \"%s\"\n", path);
}

