#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

#define MAX_FILENAME 80

int main(int argc, char **argv) {
	// Ensures correct number of arguments
	if (argc != 7) {
		fprintf(stderr, "Usage: psort -n <number of processes> -f <inputfile> -o <outputfile>\n");
		exit(1);
	}

	// Parse command-line arguments
	int ch, num_processes, input_file_size;
	char input_filename[MAX_FILENAME];
	char output_filename[MAX_FILENAME];

	while ((ch = getopt(argc, argv, ":n:f:o:")) != -1) {
		switch (ch) {
			case 'n':
				num_processes = strtol(optarg, NULL, 10);
				break;
			case 'f':
				strcpy(input_filename, optarg);
				input_file_size = get_file_size(optarg);
				break;
			case 'o':
				strcpy(output_filename, optarg);
				break;
			case '?':
			case ':':
			default:
			    fprintf(stderr, "Usage: psort -n <number of processes> -f <inputfile> -o <outputfile>\n");
			    exit(1);
		}
	}
	argc -= optind;
	argv += optind;

	// Read records into memory
	int num_of_records = input_file_size / sizeof(Record);

	int lower_records_per_process = num_of_records / num_processes;
	int actual_records_per_process = lower_records_per_process;
	int remainder = num_of_records % num_processes;
	int fd[num_processes][2];
	int base_idx = 0;
	for (int i = 0; i < num_processes; i++) {
		if (i < remainder) {
			actual_records_per_process = lower_records_per_process + 1;
		}
	    if (pipe(fd[i]) == -1) {
	        perror("pipe");
	        exit(1);
	    }
		pid_t ret = fork();
		if (ret < 0) {
			perror("fork");
			exit(1);
		} else if (ret == 0) { // child
			// close read end
			if (close(fd[i][0]) == -1) {
	            perror("close");
	            exit(1);
	        }
	        // close remaining pipes from before
	        for (int j = 0; j < i; j++) {
	        	// write end has already been closed in parent
	        	close(fd[j][0]);
	        }
	        // read num records
	        Record *data_array = read_num_records(input_filename, actual_records_per_process, base_idx);
			// qsort
			qsort(data_array, actual_records_per_process, sizeof(Record), compare_freq);
			// write in a loop !! important
			for (int j = 0; j < actual_records_per_process; j++) {
				if (write(fd[i][1], data_array+j, sizeof(Record)) == -1) {
	                perror("write_main");
	                exit(1);
	            }
			}
			// free mem
			free(data_array);
			// close pipe
            if (close(fd[i][1]) == -1) {
	            perror("close");
	            exit(1);
	        }
			// exit
			exit(0);
		} else { // parent
			// close write
			if (close(fd[i][1]) == -1) {
	            perror("close");
	            exit(1);
	        }
			base_idx += actual_records_per_process;
		}
	}

	Record tmp_array[num_processes];
	for (int i = 0; i < num_processes; i++) {
		if (read(fd[i][0], tmp_array+i, sizeof(Record)) == -1) {
            perror("read");
            exit(1);
        }
	}

	FILE *output_fp;
	if ((output_fp = fopen(output_filename, "wb")) == NULL) {
	     perror("output_fp");
	     exit(1);
	}

	int ret = write_smallest(output_fp, tmp_array, num_processes);
	while (ret != -1) {
		int bytes = read(fd[ret][0], tmp_array+ret, sizeof(Record));
		if (bytes == -1) {
            perror("read");
            exit(1);
        } else if (bytes == 0) {
        	tmp_array[ret].freq = -1;
        }
        ret = write_smallest(output_fp, tmp_array, num_processes);
	}

	for (int i = 0; i < num_processes; i++) {
		pid_t pid;
        int status;
        if( (pid = wait(&status)) == -1) {
            perror("wait");
        } else {
            if (WIFEXITED(status)) {
                // exits normally
            } else {
                fprintf(stderr, "Child terminated abnormally\n");
            }
        }
	}

	fclose(output_fp);
	
	return 0;
}