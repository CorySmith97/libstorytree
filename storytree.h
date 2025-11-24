#ifndef STORYTREE_H
#define STORYTREE_H
/*

libstorytree is a generic DAG datastructure for divergent dialog for RPGs.

============================== HOW TO USE =====================================


.stree file type
HEADER
-------------------------------------------------
|                                                |
-------------------------------------------------
*/


#ifdef __cplusplus
extern "C" {
#endif

#define ST_API
#define _ST_PRIVATE static
#define ST_SUCCESS 0

#include <stdint.h>
#include <stdlib.h>

typedef struct st_node st_node;
typedef struct st_audio st_audio;
typedef struct st_noderesponse st_noderesponse;
typedef struct st_storytree st_storytree;
typedef struct st_allocator st_allocator;
typedef struct _st_btree _st_btree;

//
// This may not be necessary, but having audio stored as a part of the data
// for a Storytree node allows for easy playing of audio when a node is
// displayed to a player.
//
struct st_audio {
    uint8_t *data;
    uint64_t size;
    // Need more data information about audio. This can be added later.
};

//
// Dialog Responses availible for a given node. Each responses corresponds
// with a connections to another node.
//
struct st_noderesponse {
    uint8_t *reponse;
    uint64_t reponse_length;
};

//
// Basic Node type for the graph creation. Rather than use pointers to all
// the possible connections, nodes reference other nodes with in ID. These
// IDs correspond to positions within an array held within the StoryTree data
// type
//
struct st_node {
    uint32_t        id;

    uint8_t         *dialog;
    uint64_t        dialog_count;

    st_noderesponse *reponses;
    uint64_t        reponse_count;

    void(*callback)(void* context);

};

struct st_storytree {
    st_allocator *allocator;
    st_node *nodes;
    uint64_t nodes_count;
};

struct st_allocator {
    void* (*alloc_fn)(size_t size, void* usr_data);
    void* (*free_fn)(size_t size, void* usr_data);
    void* usr_data;
};

//
// Static Allocator for StoryTree. It can be overridden
//

#define alloc(st, T, s) ((T*)(st.allocator->alloc_fn)(s, st.allocator->usr_data))


// ============================================================================
// PUBLIC API
// ============================================================================

ST_API st_storytree*    st_new_story_tree();
ST_API int              st_destroy_story_tree(st_storytree*);
ST_API int              st_append_node(st_storytree*, st_node*);
ST_API int              st_remove_node(st_storytree*, uint64_t);
ST_API int              st_serialize_tree(st_storytree*, char*);
ST_API int              st_free_tree(st_storytree*, char*);

#ifdef STORYTREE_IMPL

// INTERNAL

_ST_PRIVATE void *i_st_alloc_fn(size_t size, void* usr_data);
_ST_PRIVATE void *i_st_free_fn(size_t size, void* usr_data);
_ST_PRIVATE st_storytree* i_st_new_story_tree() {
    st_storytree* st = (st_storytree*)malloc(sizeof(st_storytree));
    st->allocator->alloc_fn = i_st_alloc_fn;
    st->allocator->free_fn = i_st_free_fn;

    return st;
}

// IMPLEMENTATION

ST_API st_storytree*    st_new_story_tree() {
    return i_st_new_story_tree();
};

#endif // STORYTREE_IMPL

#ifdef __cplusplus
}
#endif

#endif /* STORYTREE_H */
