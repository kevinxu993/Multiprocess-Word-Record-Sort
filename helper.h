#ifndef _HELPER_H
#define _HELPER_H

#define SIZE 44

typedef struct rec {
    int freq;
    char word[SIZE];
} Record;

int get_file_size(char *filename);
int compare_freq(const void *rec1, const void *rec2);
Record *read_num_records(char *filename, int num, long idx);
int write_smallest(FILE *fp, Record *tmp_array, int size);

#endif /* _HELPER_H */
