#include <string.h>
#include <ctype.h>
#include "mime.h"
#include "hashtable.h"

#define DEFAULT_MIME_TYPE "application/octet-stream"

/**
 * Lowercase a string
 */
char *strlower(char *s)
{
    for (char *p = s; *p != '\0'; p++) {
        *p = tolower(*p);
    }

    return s;
}

/**
 * Return a MIME type for a given filename
 */
char *mime_type_get(char *filename)
{
    char *ext = strrchr(filename, '.');

    if (ext == NULL) {
        return DEFAULT_MIME_TYPE;
    }

    ext++;

    strlower(ext);

    // TODO: this is O(n) and it should be O(1)
    struct hashtable *ht = hashtable_create(10, NULL);

    hashtable_put(ht, "html", "text/html");
    hashtable_put(ht, "htm", "text/html");
    hashtable_put(ht, "jpeg", "image/jpg");
    hashtable_put(ht, "jpg", "image/jpg");
    hashtable_put(ht, "css", "text/css");
    hashtable_put(ht, "js", "application/javascript");
    hashtable_put(ht, "json", "application/json");
    hashtable_put(ht, "txt", "text/plain");
    hashtable_put(ht, "gif", "image/gif");
    hashtable_put(ht, "png", "image/png");

    if (hashtable_get(ht, ext) != NULL)
    {
      return hashtable_get(ht, ext);
    }

    // if (strcmp(ext, "html") == 0 || strcmp(ext, "htm") == 0) { return "text/html"; }
    // else if (strcmp(ext, "jpeg") == 0 || strcmp(ext, "jpg") == 0) { return "image/jpg"; }
    // else if (strcmp(ext, "css") == 0) { return "text/css"; }
    // else if (strcmp(ext, "js") == 0) { return "application/javascript"; }
    // else if (strcmp(ext, "json") == 0) { return "application/json"; }
    // else if (strcmp(ext, "txt") == 0) { return "text/plain"; }
    // else if (strcmp(ext, "gif") == 0) { return "image/gif"; }
    // else if (strcmp(ext, "png") == 0) { return "image/png"; }

    return DEFAULT_MIME_TYPE;
}