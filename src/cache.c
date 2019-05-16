#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "cache.h"

/**
 * Allocate a cache entry
 */
struct cache_entry *alloc_entry(char *path, char *content_type, void *content, int content_length)
{
    ///////////////////
    // IMPLEMENT ME! //
    ///////////////////
    struct cache_entry *ce = malloc(sizeof(struct cache_entry));
    ce->path = strdup(path);
    ce->content_type = strdup(content_type);
    ce->content_length = content_length;
    ce->content = malloc(content_length * sizeof(int));
    memcpy(ce->content, content, content_length);
    ce->next = NULL;
    ce->prev = NULL;

    return ce;
}

/**
 * Deallocate a cache entry
 */
void free_entry(struct cache_entry *entry)
{
    ///////////////////
    // IMPLEMENT ME! //
    ///////////////////
    free(entry->path);
    entry->path = NULL;
    free(entry->content_type);
    entry->content_type = NULL;
    free(entry->content);
    entry->content = NULL;
    free(entry->next);
    entry->next = NULL;
    free(entry->prev);
    entry->prev = NULL;
    free(entry);
    entry = NULL;
}

/**
 * Insert a cache entry at the head of the linked list
 */
void dllist_insert_head(struct cache *cache, struct cache_entry *ce)
{
    // Insert at the head of the list
    if (cache->head == NULL) {
        cache->head = cache->tail = ce;
        ce->prev = ce->next = NULL;
    } else {
        cache->head->prev = ce;
        ce->next = cache->head;
        ce->prev = NULL;
        cache->head = ce;
    }
}

/**
 * Move a cache entry to the head of the list
 */
void dllist_move_to_head(struct cache *cache, struct cache_entry *ce)
{
    if (ce != cache->head) {
        if (ce == cache->tail) {
            // We're the tail
            cache->tail = ce->prev;
            cache->tail->next = NULL;

        } else {
            // We're neither the head nor the tail
            ce->prev->next = ce->next;
            ce->next->prev = ce->prev;
        }

        ce->next = cache->head;
        cache->head->prev = ce;
        ce->prev = NULL;
        cache->head = ce;
    }
}


/**
 * Removes the tail from the list and returns it
 *
 * NOTE: does not deallocate the tail
 */
struct cache_entry *dllist_remove_tail(struct cache *cache)
{
    struct cache_entry *oldtail = cache->tail;

    cache->tail = oldtail->prev;
    cache->tail->next = NULL;

    cache->cur_size--;

    return oldtail;
}

/**
 * Create a new cache
 *
 * max_size: maximum number of entries in the cache
 * hashsize: hashtable size (0 for default)
 */
struct cache *cache_create(int max_size, int hashsize)
{
    ///////////////////
    // IMPLEMENT ME! //
    ///////////////////
    // instantiate cache
    struct cache *c = malloc(sizeof(struct cache));

    // instantiate the hash table and assign cache hashtable pointer to new hash table
    struct hashtable *index = hashtable_create(hashsize, NULL);
    c->index = index;

    // instantiate the cache_entry(s) -> tail and head
    c->head = NULL;
    c->tail = NULL;

    // instantiate the max_size
    c->max_size = max_size;

    // instantiate the cur_size
    c->cur_size = 0;

    return c;
}

void cache_free(struct cache *cache)
{
    struct cache_entry *cur_entry = cache->head;

    hashtable_destroy(cache->index);

    while (cur_entry != NULL) {
        struct cache_entry *next_entry = cur_entry->next;

        free_entry(cur_entry);

        cur_entry = next_entry;
    }

    free(cache);
}

/**
 * Store an entry in the cache
 *
 * This will also remove the least-recently-used items as necessary.
 *
 * NOTE: doesn't check for duplicate cache entries
 */
void cache_put(struct cache *cache, char *path, char *content_type, void *content, int content_length)
{
    ///////////////////
    // IMPLEMENT ME! //
    ///////////////////
    // Allocate a new cache entry with the passed parameters.
    //    use alloc_entry() from cache.c
    struct cache_entry *ce = alloc_entry(path, content_type, content, content_length);

    // Insert the entry at the head of the doubly-linked list.
    //    use dllist_insert_head() from cache.c
    dllist_insert_head(cache, ce);

    // Store the entry in the hashtable as well, indexed by the entry's path.
    //    use hashtable_put(cache->index, path, ??) from hashtable.c
    hashtable_put(cache->index, path, ce);

    // Increment the current size of the cache.
    //    cache->cur_size++
    cache->cur_size++;

    // If the cache size is greater than the max size:
    //    cache->cur_size > cache->max_size
    if (cache->cur_size > cache->max_size){
      printf("content_type = %s\n", content_type);
      //    Remove the cache entry at the tail of the linked list.
      //      use dllist_remove_tail() from cache.c
      struct cache_entry *ce_old_tail = dllist_remove_tail(cache); // lru

      //    Remove that same entry from the hashtable, using the entry's path and the hashtable_delete function.
      //      use hashtable_delete() from hashtable.c
      hashtable_delete(cache->index, ce_old_tail->path);

      //    Free the old tail cache entry.
      //      use free_entry() from cache.c
      free_entry(ce_old_tail);

      //  Ensure the size counter for the number of entries in the cache is correct.
      //    i dunnno you, you tell me what the entries are and how to make sure they are correct????
      //    also, what do i do or how should I handle the entries if they are not correct????
      if (cache->cur_size > cache->max_size){
        printf("cache is unstable\n");
      }
    }

}

/**
 * Retrieve an entry from the cache
 */
struct cache_entry *cache_get(struct cache *cache, char *path)
{
    ///////////////////
    // IMPLEMENT ME! //
    ///////////////////
    // Attempt to find the cache entry pointer by path in the hash table.
    //    use hashtable_get() from hashtable.c to check if it returns null

    // If not found, return NULL.
    if (hashtable_get(cache->index, path) == NULL)
    {
      return NULL;
    }

    // Move the cache entry to the head of the doubly-linked list.
    //    use dllist_move_to_head() from cache.c
    dllist_move_to_head(cache, hashtable_get(cache->index, path)); // most recently used cache_entry

    // Return the cache entry pointer.
    //    cache->head
    return cache->head;
}
