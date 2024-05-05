#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"


int main(void) {
    char word_from_file[500];
    FILE* fp = nullptr;
    trie* t = new trie();
    // const char* file_name = "a.txt";
    const char* file_name = "words.txt";
    
    fp = fopen(file_name, "r");
    if(fp == nullptr) {
        puts("Unable to open file");
        exit(0);
    }
    
    while(fgets(word_from_file, sizeof(word_from_file), fp)) {
        word_from_file[strcspn(word_from_file, "\n")] = 0;
        t->insert_word(word_from_file);
    }
    
    fclose(fp);

    fp = fopen(file_name, "r");
    
    if(fp == nullptr) {
        puts("Unable to open file");
        exit(0);
    }
    
    while(fgets(word_from_file, sizeof(word_from_file), fp)) {
        word_from_file[strcspn(word_from_file, "\n")] = 0;
        if(t->is_word_present(word_from_file) == SUCCESS)
            printf("%s word present\n", word_from_file);
        else
            printf("%s word is not present\n", word_from_file);
    }
    
    fclose(fp);

    t->print_node_count();

    trie::destroy_trie(&t);
    if(t == nullptr) {
        puts("p_trie_obj->head deleted");
    }
    
    return (0);    
}

