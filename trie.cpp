#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"

node::node(char* _data) {
    data = new char();
    *data = *_data;
    for (int i = 0; i < 26; i++) {
        child[i] = nullptr;
    }
}

node* trie::get_node(char* _data) {
    node* new_node = new node(_data);
    if (new_node == nullptr) {
        puts("No virtual memory");
        exit(0);
    }
    return (new_node);
}

trie::trie() {
    char head_data = '-';
    head = get_node(&head_data);
    total_char_inserted = 0;
}

status_t trie::validate_input(char* word) {
    if(word == nullptr || strlen(word) < 0) {
        return FAIL;
    }

    char* p = nullptr;
    size_t word_size = strlen(word);
    p = word;
    
    for(int i = 0; i < word_size; i++, p++) {
       *p = tolower(*p);
        if(! (int(*p) >= 97 && int(*p) <= 122)) {
            return FAIL;
        }
    }

    return SUCCESS;
}

status_t trie::insert_word(char* word) {
    size_t len = strlen(word);
    if(len < 0)     return(FAIL);

    char* cp_word = (char*)calloc(len + 1, sizeof(char));
    strcpy(cp_word, word);

    if(validate_input(cp_word) == FAIL)
        return(FAIL);
    
    status_t stat = generic_insert(cp_word);

    free(cp_word);
    cp_word = nullptr;
    return (stat);

}

status_t trie::generic_insert(char* word) {
    char *alpha = word;
    size_t word_size = strlen(word);
    node* p_run = head;

    for(int i = 0; i < word_size; i++) {
        int index = int(*alpha) - 97;
        if(p_run->child[index] == nullptr) {
            node* new_node = get_node(alpha);
            p_run->child[index] = new_node;
            total_char_inserted++;
        }

        p_run = p_run->child[index];
        alpha++;
    }

    return SUCCESS;
}

status_t trie::is_word_present(char* word) {
    size_t len = strlen(word);
    if(len < 0)     return(FAIL);

    char* cp_word = (char*)calloc(len + 1, sizeof(char));
    strcpy(cp_word, word);

    if(validate_input(cp_word) == FAIL)
        return(FAIL);
    
    char* alpha = cp_word;
    size_t word_size = len;
    node* p_run = head;

    for(int i = 0; i < word_size; i++) {
        int index = int(*alpha) - 97;
        if(p_run->child[index] == nullptr) {
            return FAIL;
        }
        
        char* x1 = p_run->child[index]->data;
        if(*x1 != *alpha) {
            puts("No word found");
            return FAIL;
        }
        p_run = p_run->child[index];
        alpha++;
    }

    free(cp_word);
    cp_word = nullptr;

    return SUCCESS;
}

void trie::print_node_count() {
    printf("Total node created : %lu\n", total_char_inserted);
}

void trie::destroy_nodes(node* node) {
    for(int i = 0; i < 26; i++) {
        if(node->child[i] != nullptr) {
            destroy_nodes(node->child[i]);
        }
    }

    // printf("deleting node->data : %c \n", *(node->data));
    delete (node);
    node = nullptr;
}

void trie::destroy_trie(trie** pp_trie_obj) {
    trie* p_trie_obj = *pp_trie_obj;

    destroy_nodes(p_trie_obj->head);

    delete *pp_trie_obj;
    *pp_trie_obj = nullptr;
}
