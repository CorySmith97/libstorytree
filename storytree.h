#ifndef STORYTREE_H
#define STORYTREE_H
/*
libstorytree is a generic DAG datastructure for divergent dialog for RPGs.

    === HOW TO USE ===
*/


#include <cstdint>
#ifdef __cplusplus
extern "C" {
#endif

#define ST_API extern
#define ST_SUCCESS 0

#include <stdint.h>

typedef struct ST_Node ST_Node;
typedef struct ST_Audio ST_Audio;
typedef struct ST_NodeResponse ST_NodeResponse;
typedef struct ST_StoryTree ST_StoryTree;

//
// This may not be necessary, but having audio stored as a part of the data
// for a Storytree node allows for easy playing of audio when a node is
// displayed to a player.
//
struct ST_Audio {
    uint8_t *data;
    uint64_t size;
    // Need more data information about audio. This can be added later.
};

//
// Dialog Responses availible for a given node. Each responses corresponds
// with a connections to another node.
//
struct ST_NodeResponse {
    uint8_t *reponse;
    uint64_t reponse_length;
};

//
// Basic Node type for the graph creation. Rather than use pointers to all
// the possible connections, nodes reference other nodes with in ID. These
// IDs correspond to positions within an array held within the StoryTree data
// type
//
struct ST_Node {
    uint32_t        id;

    uint8_t         *dialog;
    uint64_t        dialog_count;

    ST_NodeResponse *reponses;
    uint64_t        reponse_count;

};

struct ST_StoryTree {
    ST_Node *nodes;
    uint64_t nodes_count;
};

// ============================================================================
// PUBLIC API
// ============================================================================

ST_API ST_StoryTree*    ST_new_story_tree();
ST_API int              ST_destroy_story_tree(ST_StoryTree*);
ST_API int              ST_append_node(ST_StoryTree*, ST_Node*);
ST_API int              ST_remove_node(ST_StoryTree*, uint64_t);
ST_API int              ST_serialize_tree(ST_StoryTree*, char*);

#ifdef __cplusplus
}
#endif

#endif /* STORYTREE_H */
