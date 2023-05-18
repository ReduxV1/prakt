#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu_headers.h"
#include "structures.h"
#include "other_headers.h"

int file_opened(){
    FILE *in = fopen(main_file, "r");
    if(!in) {
        printf("File is not opened!");
        getcharLock(2);
        return 0;
    }
    fclose(in);
    return 1;
}

void main_menu()
{
    remove(temp_file);
    while(1){
        clearscreen();

        printf("1. File\n");
        printf("2. Edit document\n");
        printf("3. Display document\n");
        printf("4. Export to .txt file\n");
        printf("5. Dictionary\n");
        printf("6. About programm\n");
        printf("7. Exit\n\n");
        printf("Enter the number of menu: ");

        int ch = getchar();
        clearscreen();

        switch(ch){
        case '1':
            file_menu();
            break;
        case '2':
            if(file_opened()) edit_menu();
            break;
        case '3':
            if(file_opened()) file_display();
            break;
        case '4':
            if(file_opened()) export_txt();
            break;
        case '5':
            dictionary_menu();
            break;
        case '6':
            about();
            break;
        case '7':
            remove(temp_file);
            return;
        }
    }
}

void file_menu(){
    while(1){
        clearscreen();

        printf("1. Open\n");
        printf("2. Save\n");
        printf("3. Close\n");
        printf("4. Back\n\n");

        printf("Enter the number of menu: ");
        int ch = getchar();
        clearscreen();

        switch(ch){
        case '1':
            read_file();
            break;
        case '2':
            if(file_opened()) save_file();
            break;
        case '3':
            if(file_opened()) close_file();
            break;
        case '4':
            return;
        }
    }
}

void edit_menu(){
    while(1){
        clearscreen();

        printf("1. Add note \n");
        printf("2. Remove note \n");
        printf("3. Edit note\n");
        printf("4. Back\n\n");

        printf("Enter the number of menu: ");
        int ch = getchar();
        clearscreen();

        switch(ch){
        case '1':
            add_note();
            break;
        case '2':
            delete_note();
            break;
        case '3':
            edit_note();
            break;
        case '4':
            return;
        }
    }
}

void dictionary_menu(){
    char *dictionary = form_file;
    int dictionary_state = 1;
    while(1){
        clearscreen();

        printf("Current: %s\n\n", dictionary);

        printf("1. Swich to other dictionary\n");
        printf("2. Display dictionary\n");
        printf("3. Edit note \n");
        printf("4. Add note \n");
        printf("5. Remove note\n");
        printf("6. Back\n\n");

        printf("Enter the number of menu: ");
        int ch = getchar();
        clearscreen();

        switch(ch){
        case '1':
            if(dictionary_state == 1) {
                dictionary = sort_file;
                dictionary_state--;
            }
            else {
                dictionary_state++;
                dictionary = form_file;
            }
            break;
        case '2':
            display_dictionary(dictionary);
            break;
        case '3':
            edit_dictionary(dictionary);
            break;
        case '4':
            add_note_dictionary(dictionary);
            break;
        case '5':
            delete_element_dictionary(dictionary);
            break;
        case '6':
            return ;
        }


    }
}



