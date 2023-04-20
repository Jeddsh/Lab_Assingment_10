#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trie{
    int flag;
    struct Trie *next[26];
}Trie;

//ppTrie acts like root
//practice: try this with recursion!
void insert(struct Trie **ppTrie, char *word){
    if(*ppTrie == NULL) return;

    Trie* temp = *ppTrie;
    int len = strlen(word);
    for(int i  = 0; i < len; i++){
        int index = word[i] - 'a';
        if(temp->next[index] == NULL)
            temp->next[index] = (Trie*) calloc(1,sizeof(Trie));
        temp = temp->next[index];
    }
    temp->flag++;
}
int numberOfOccurances(struct Trie *pTrie, char *word){
    if(pTrie == NULL) return 0;

    Trie* temp = pTrie;
    int len = strlen(word);
    for(int i = 0; i < len;i++){
        int index = word[i] - 'a';
        if(temp->next[index]==NULL){
            return 0;
        }
        temp = temp->next[index];
    }
    return temp->flag;
}

struct Trie *deallocateTrie(struct Trie *pTrie){
    if(pTrie==NULL){ 
        free(pTrie);
        return &pTrie;
    }

    Trie* temp = pTrie;
    for(int i = 0; i < 26; i++){
        deallocateTrie(temp->next[i]);
    }
    free(pTrie);
    return &pTrie;
}

int main(void)
{
    struct Trie *trie = (Trie *) calloc(1,sizeof(Trie));
    
      //read the number of the words in the dictionary
      // parse line  by line, and insert each word to the trie data structure
      char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
      for (int i=0;i<5;i++)
      {
        insert(&trie,pWords[i]);
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
     }
    trie = deallocateTrie(trie);
    if (trie != NULL)
       printf("There is an error in this program\n");
    return 0;
}