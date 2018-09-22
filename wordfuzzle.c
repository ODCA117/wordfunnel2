#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

#define NBR_OF_WORDS 172900
#define WORD_LENGTH 30

map_int_t map;
char **words;

int findListLength(char const *word) {
    int * val = map_get(&map, word);
    if(val) {
        return *val;
    }
    else {
        return -1;
    }
}


//set the length of all the words by the use of dynamic programming
int funnel2(char word[], int i, int size, int lettersRemoved) {

    //if the word is empty
    if(size == 0) {
        return lettersRemoved -1;
    }

    //if the letter index is outofbound
    if (i >= size) {
        return lettersRemoved;
    }

    //letter not removed
    int notRemoved = 0;
    notRemoved = funnel2(word, i+1, size, lettersRemoved);

    //letter removed
    int removed = 0;
    char tmp[WORD_LENGTH];
    strcpy(tmp, word);
    memmove(&tmp[i], &tmp[i + 1], strlen(tmp) - i);

    int * val = map_get(&map, tmp);
    if(val) {
        removed = funnel2(tmp, 0, size -1, lettersRemoved + 1);
    }

    if(removed > notRemoved) {
        return removed;
    }
    else {
        return notRemoved;
    }
}

int main(int argc, char const *argv[]) {


    FILE *fp;

    const char * filename;
    const char * word;
    int checkWord;

    if(argc == 1) {
        printf("not enough args\n");
        return 1;
    }

    else if (argc == 2){
        filename = argv[1];
        checkWord = 0;
    }

    else {
        filename = argv[1];
        word = argv[2];
        checkWord = 1;
    }

    fp = fopen(filename, "r");

    //char word[WORD_LENGTH]; //word less than WORD_LENGTH letters
    words  = (char **)malloc(NBR_OF_WORDS * sizeof(char *));
    map_init(&map);


    int i;
    for(i = 0; i < NBR_OF_WORDS; i++) {
        words[i] = (char *)malloc(WORD_LENGTH * sizeof(char));
    }


    i = 0;
    while (fscanf(fp, "%s", words[i]) != EOF) {
        map_set(&map, words[i], -1);
        i++;
    }


    // int length = funnel2("gnash", 0, strlen("gnash"), 0);
    // map_set(&map, "gnash", length +1);


    int nbrWords = i;
    for(int i = 0; i < nbrWords; i++) {
        int wordLength = strlen(words[i]);
        int length = funnel2(words[i],0, wordLength, 0) +1;
        map_set(&map, words[i], length);
        if(length == 10) {
            //printf("word with 10 is %s\n", words[i] );
        }
    }

    if(checkWord) {
        int length = findListLength(word);


        printf("%s -> %d\n", word, length);

    }
    return 0;
}
