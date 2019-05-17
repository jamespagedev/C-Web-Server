# cache.c

- function `struct cache_entry *alloc_entry()` needs body code block
- function `void free_entry()` needs body code block

# net.c

> `addrinfo` in `struct addrinfo hints, *servinfo, *p;` doesn't seem to be defined anywhere.

- `struct addrinfo` members:
  - `.ai_family`
  - `.ai_socktype`
  - `.ai_flags`
  - `.ai_next`
  - `.ai_protocol`
  - `.ai_addr`
  - `.ai_addrlen`

# server.c

> `response_length` argument passed in a function `int rv = send(fd, response, response_length, 0);` not defined anywhere

mime -> convert o(n) to o(1) utilizing hashtable
