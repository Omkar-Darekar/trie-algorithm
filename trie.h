#ifndef __TRIE_H__
#define __TRIE_H__

#define SUCCESS     1
#define FAIL        0
#define status_t    int

class node {
    friend class trie;
    private:
        char* data;
        node* child[26];
        node(char* _data);
};

class trie {
    private:
        unsigned long int total_char_inserted;
        node* head;
        node* get_node(char* _data);
        status_t validate_input(char* word);
        status_t generic_insert(char* word); 
        static void destroy_nodes(node* node);
    public:
        trie();
        status_t insert_word(char* alpha);
        status_t is_word_present(char* word);
        static void destroy_trie(trie** pp_trie_obj);
        void print_node_count();
};

#endif //__TRIE_H__