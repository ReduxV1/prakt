#ifndef STRUCTURES_H
#define STRUCTURES_H

#define main_file "garden.db"
#define temp_file "garden_tmp.db"
#define form_file "form.db"
#define sort_file "sort.db"

typedef struct{
    int id;
    int type;
    int sort;
    char season[50];
    float price;
} tree;

typedef struct{
    int id;
    char value[50];
} dictionary;

#endif // STRUCTURES_H
