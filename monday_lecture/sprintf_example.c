#include <stdio.h>
#include <string.h>

int main(void)
{
  char response[50000];
  char *body = "<h1>Hello, World!</h1>";
  int length = strlen(body);

  sprintf(response, "HTTP/1.1 200 OK\n"
          "Content-Type: text/html\n"
          "Content-Length: %d\n"
          "Connection: close\n"
          "\n"
          "%s\n",
          length,
          body
          );

  printf("%s", response);

  return 0;
}