#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "helper.h"


int write_smallest(FILE *fp, Record *tmp_array, int size) {
    int smallest_idx = -1;
    int smallest_freq = 999999;
    int found_valid = 0;
    for (int i = 0; i < size; i++) {
        if (tmp_array[i].freq == -1) {
            continue;
        } else {
            found_valid = 1;
            if (tmp_array[i].freq < smallest_freq) {
                smallest_idx = i;
                smallest_freq = tmp_array[i].freq;
            }
        }
    }
    if (found_valid == 0) {
        return -1;
    }
    fprintf(stderr, "[%s] %d\n", tmp_array[smallest_idx].word, tmp_array[smallest_idx].freq);
    int ret = fwrite(tmp_array+smallest_idx, sizeof(Record), 1, fp);
    if (ret < 1) {
        perror("fwrite");
        exit(1);
    }
    return smallest_idx;
}

Record *read_num_records(char *filename, int num, long idx) {
    FILE *input_fp;
    if ((input_fp = fopen(filename, "rb")) == NULL) {
         perror("input_fp");
         exit(1);
    }
    Record *res = malloc(num*sizeof(Record));
    if (fseek(input_fp, idx*sizeof(Record), SEEK_SET) == -1) {
        perror("fseek");
        exit(1);
    }
    int ret = fread(res, sizeof(Record), num, input_fp);
    // fprintf(stderr, "ret=%d\n", ret);
    if (ret < num) {
        fprintf(stderr, "read_records error\n");
        exit(1);
    }
    fclose(input_fp);
    return res;
}

int get_file_size(char *filename) {
    struct stat sbuf;

    if ((stat(filename, &sbuf)) == -1) {
       perror("stat");
       exit(1);
    }

    return sbuf.st_size;
}

/* A comparison function to use for qsort */
int compare_freq(const void *rec1, const void *rec2) {

    struct rec *r1 = (struct rec *) rec1;
    struct rec *r2 = (struct rec *) rec2;

    if (r1->freq == r2->freq) {
        return 0;
    } else if (r1->freq > r2->freq) {
        return 1;
    } else {
        return -1;
    }
}
