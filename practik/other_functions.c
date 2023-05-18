#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "structures.h"


void getcharLock(int loops){
    for(int i = 0; i < loops; i++ ) getchar();
}

void clearscreen(){
    printf("\n"); system("cls");
}

int filenlines(const char *filename)
{
    FILE *in = fopen(filename, "r");
    if(!in) {
        printf("Error... File '%s' not found!\nPress any key to continue...\n", filename);
        getcharLock(2); return 0;
    }
    int file_lines=0;
    char str[100];
    do {
        fgets(str, sizeof(str), in);
    } while(!feof(in) && ++file_lines);
    return file_lines;
}


tree* get_temp_structure(int* file_lines_){
    int file_lines = 0;
    if(!(file_lines=filenlines(temp_file))) return 0;

    FILE *in = fopen(temp_file, "r");
    tree* tree_array = (tree*)malloc(sizeof(tree) * file_lines);

    char str[100];
    for(int i=0; i<file_lines; i++){
        fgets(str, sizeof(str), in);
        tree_array[i].id = atoi(strtok(str, ";"));
        tree_array[i].type = atoi(strtok(NULL, ";"));
        tree_array[i].sort = atoi(strtok(NULL, ";"));
        strcpy(tree_array[i].season, strtok(NULL, ";"));
        tree_array[i].price = atof(strtok(NULL, ";"));
    }
    fclose(in);
    *file_lines_ = file_lines;
    return tree_array;
}

dictionary* read_dictionary_(const char *filename, int *lines){
    int file_lines = 0;
    if(!(file_lines = filenlines(filename))) return 0;
    FILE *in = fopen(filename, "r");

    char str[100];
    dictionary* dictionary_array = (dictionary*)malloc(sizeof(dictionary) * file_lines);
    for(int i=0; i<file_lines; i++){
        fgets(str, sizeof(str), in);
        dictionary_array[i].id = atoi(strtok(str, ";"));
        strcpy(dictionary_array[i].value, strtok(NULL, ";"));
    }
    *lines = file_lines;
    return dictionary_array;
}

int _get_dictionary_index(dictionary* dictionary_, int lines, int id, int mode){
    for(int i=0; i<lines; i++){
        if(dictionary_[i].id == id) return i;
    }
    if(mode){
        clearscreen();
        printf("Error... dictionary note id %d does not exist!\nPress ENTER to go back...", id);
        getcharLock(2);
    }
    return -1;
}

void file_print(tree* tree_array, int length){
    int sort_lines=-1, type_lines=-1;
    dictionary* type_array = read_dictionary_(form_file, &type_lines);
    dictionary* sort_array = read_dictionary_(sort_file, &sort_lines);

    printf(" id\t  type\t\t\t  sort\t\t\tseason\t\t\tprice\n\n");
    for(int i=0; i<length; i++){
        char tmp_type[100] = "*!?no_value\0";
        char tmp_sort[100] = "*!?no_value\0";
        int type_ind = _get_dictionary_index(type_array, type_lines, tree_array[i].type, 0);
        int sort_ind = _get_dictionary_index(sort_array, sort_lines, tree_array[i].sort, 0);
        if(type_ind != -1) strcpy(tmp_type, type_array[type_ind].value);
        if(sort_ind != -1) strcpy(tmp_sort, sort_array[sort_ind].value);
        printf("%3d\t%-15s\t\t%-20s\t%-12s\t\t%.2f\n",
               tree_array[i].id,
               tmp_type, tmp_sort,
               tree_array[i].season,
               tree_array[i].price);
    }
}

void print_dict(const char* filename){
    int dict_lines=-1;
    dictionary* dict_array = read_dictionary_(filename, &dict_lines);
    printf("Dictionary %s\n\n", filename);
    printf(" id  value\n\n");
    for(int i=0; i<dict_lines; i++){
        printf(" %-4d%s\n",
               dict_array[i].id,
               dict_array[i].value
               );
    }
}

int _get_note_index(tree* tree_array, int file_length, int id){
    for(int i=0; i<file_length; i++)
        if(tree_array[i].id == id) return i;
    clearscreen();
    printf("Error... Note id %d does not exist!\nPress ENTER to go back...", id);
    getcharLock(2);
    return -1;
}
