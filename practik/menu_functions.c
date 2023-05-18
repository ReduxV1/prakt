#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "other_headers.h"
#include "structures.h"

void read_file(){
    int file_lines = 0;
    if(!(file_lines=filenlines("garden.db"))) return;

    FILE *in = fopen(main_file, "r");
    FILE *in_tmp = fopen(temp_file, "w");

    char str[100];
    for(int i=0; i<file_lines; i++){
        fgets(str, sizeof(str), in);
        fprintf(in_tmp, "%s", str);
    }

    fclose(in); fclose(in_tmp);
    printf("File '%s' opened!\nPress ENTER to go back...\n", main_file);
    getcharLock(2);
}

void close_file(){
    if (remove(temp_file) == 0) printf("The file is closed successfully.");
    else printf("The file is not closed.");
    getcharLock(2);
}

void save_file(){
    int file_lines = 0;
    if(!(file_lines=filenlines(temp_file))) {
        printf("Open File first!");
        return;
    }

    FILE *in = fopen(main_file, "w");
    FILE *in_tmp = fopen(temp_file, "r");

    char str[100];
    for(int i=0; i<file_lines; i++){
        fgets(str, sizeof(str), in_tmp);
        fprintf(in, "%s", str);
    }

    fclose(in); fclose(in_tmp);
    printf("File '%s' saved!\nPress ENTER to go back...\n", main_file);
    getcharLock(2);
}

void add_note(){
    int file_lines = 0;
    tree* tree_array = get_temp_structure(&file_lines);
    int newID = tree_array[file_lines - 1].id + 1;
    free(tree_array);

    printf("New ID: %d\n", newID);
    int typeID = 0;
    printf("Type ID: ");
    scanf("%d", &typeID);
    int sortID = 0;
    printf("Sort ID: ");
    scanf("%d", &sortID);
    char season[50];
    printf("Sowing season: ");
    scanf("%s", season);
    float price = 0;
    printf("Price: ");
    scanf("%f", &price);

    FILE *tmp = fopen(temp_file, "a");
    fprintf(tmp, "%d;%d;%d;%s;%.2f;\n", newID, typeID, sortID, season, price);
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);

}

void delete_note(){
    int file_lines = 0;
    tree* tree_array = get_temp_structure(&file_lines);
    file_print(tree_array, file_lines);
    printf("\nChoose index to remove: ");
    int id_to_remove = 0;
    scanf("%d", &id_to_remove);
    int index = 0;
    if((index = _get_note_index(tree_array, file_lines, id_to_remove))==-1) return;
    FILE *tmp = fopen(temp_file, "w");
    int i;
    for(i = 0; tree_array[i].id != id_to_remove; i++)
        fprintf(tmp, "%d;%d;%d;%s;%.2f;\n",
                tree_array[i].id,
                tree_array[i].type,
                tree_array[i].sort,
                tree_array[i].season,
                tree_array[i].price
                );
    for(i++;  i < file_lines; i++)
        fprintf(tmp, "%d;%d;%d;%s;%.2f;\n",
                tree_array[i].id,
                tree_array[i].type,
                tree_array[i].sort,
                tree_array[i].season,
                tree_array[i].price
                );
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}


void edit_note(){
    int file_lines = 0;
    tree* tree_array = get_temp_structure(&file_lines);
    file_print(tree_array, file_lines);
    printf("\nChoose index to edit: ");
    int id_to_edit = 0;
    scanf("%d", &id_to_edit);
    int index = 0;
    if((index = _get_note_index(tree_array, file_lines, id_to_edit))==-1) return;
    printf("\n\nEditing ID: %d\n", index);

    printf("New Type ID: ");
    scanf("%d", &tree_array[index].type);

    printf("New Sort ID: ");
    scanf("%d", &tree_array[index].sort);

    printf("New Sowing season: ");
    scanf("%s", tree_array[index].season);

    printf("New Price: ");
    scanf("%f", &tree_array[index].price);


    FILE *tmp = fopen(temp_file, "w");
    for(int i=0; i<file_lines; i++){
    fprintf(tmp, "%d;%d;%d;%s;%.2f;\n",
            tree_array[i].id,
            tree_array[i].type,
            tree_array[i].sort,
            tree_array[i].season,
            tree_array[i].price
            );
    }
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);

}

void display_dictionary(const char* filename){
    print_dict(filename);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}

void edit_dictionary(const char* filename){
    int dict_lines=-1;
    print_dict(filename);
    dictionary* dict_array = read_dictionary_(filename, &dict_lines);
    printf("\nChoose index to edit: ");
    int id_to_edit = 0;
    scanf("%d", &id_to_edit);
    int index = 0;
    if((index = _get_dictionary_index(dict_array, dict_lines, id_to_edit, 1))==-1) return;
    printf("\nEditing ID: %d\n", id_to_edit);
    printf("New value: ");
    char str[1001]; char temp;
    scanf("%c",&temp); scanf("%[^\n]",str);
    strcpy(dict_array[index].value, str);
    FILE *in = fopen(filename, "w");
    for(int i=0; i<dict_lines; i++){
    fprintf(in, "%d;%s;\n",
            dict_array[i].id,
            dict_array[i].value
            );
    }
    fclose(in);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}



void add_note_dictionary(const char* filename){
    int file_lines = 0;
    dictionary* dictionary_ = read_dictionary_(filename, &file_lines);
    int newID = dictionary_[file_lines - 1].id + 1;
    free(dictionary_);

    printf("New ID: %d\n", newID);
    char value[50];
    printf("New value: ");
    scanf("%s", value);

    FILE *tmp = fopen(filename, "a");
    fprintf(tmp, "%d;%s;\n", newID, value);
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}


void delete_element_dictionary(const char* filename){
    int dict_lines=-1;
    print_dict(filename);
    dictionary* dict_array = read_dictionary_(filename, &dict_lines);
    printf("\nChoose index to remove: ");
    int id_to_remove = 0;
    scanf("%d", &id_to_remove);
    int index = 0;
    if((index = _get_dictionary_index(dict_array, dict_lines, id_to_remove, 1))==-1) return;
    FILE *tmp = fopen(filename, "w");
    int i;
    for(i = 0; dict_array[i].id != id_to_remove; i++)
        fprintf(tmp, "%d;%s;\n",
                dict_array[i].id,
                dict_array[i].value
                );
    for(i++;  i < dict_lines; i++)
        fprintf(tmp, "%d;%s;\n",
                dict_array[i].id,
                dict_array[i].value
                );
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);

}

void file_display(){
    int file_lines = 0;
    tree* tree_array = get_temp_structure(&file_lines);
    file_print(tree_array, file_lines);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}

void export_txt(){
    int file_lines = 0;
    tree* tree_array = get_temp_structure(&file_lines);
    FILE *out = fopen("out.txt", "w");
    int sort_lines=-1, type_lines=-1;
    dictionary* type_array = read_dictionary_(form_file, &type_lines);
    dictionary* sort_array = read_dictionary_(sort_file, &sort_lines);

    for(int i=0; i<file_lines; i++){
        char tmp_type[100] = "*!?no_value\0";
        char tmp_sort[100] = "*!?no_value\0";
        int type_ind = _get_dictionary_index(type_array, type_lines, tree_array[i].type, 0);
        int sort_ind = _get_dictionary_index(sort_array, sort_lines, tree_array[i].sort, 0);
        if(type_ind != -1) strcpy(tmp_type, type_array[type_ind].value);
        if(sort_ind != -1) strcpy(tmp_sort, sort_array[sort_ind].value);
        fprintf(out, "%3d\t%-15s\t\t%-20s\t%-12s\t\t%.2f\n",
               tree_array[i].id,
               tmp_type, tmp_sort,
               tree_array[i].season,
               tree_array[i].price);
    }
    fclose(out);
    printf("\nData exported to 'out.txt'\n");
    printf("Press ENTER to go back...\n");
    getcharLock(2);
}


void about(){
    printf("Programm is made for processing data from files and writing the results back");
    printf("\nPress ENTER to go back...\n");
    getcharLock(2);
}


