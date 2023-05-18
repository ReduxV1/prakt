#ifndef MENU_HEADERS_H
#define MENU_HEADERS_H

void main_menu();
void file_menu();
void edit_menu();
void dictionary_menu();

void read_file();
void close_file();
void save_file();

void add_note();
void delete_note();
void edit_note();

void display_dictionary(const char*);
void edit_dictionary(const char*);
void add_note_dictionary(const char*);
void delete_element_dictionary(const char*);

void file_display();
void export_txt();
void about();

#endif // MENU_HEADERS_H
