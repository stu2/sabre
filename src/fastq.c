
#include "fastq.h"

int get_line(gzFile fq_fd, char *line, int buff) {

    char *new_line = gzgets(fq_fd, line, buff);

    if(new_line == NULL) {
        return -1;
    }

    int str_len = strlen(new_line);

    if(new_line[str_len-1] != '\n') {
        fprintf(stderr, "Line too long %d\n", buff);
	exit(1);
    }

    new_line[str_len-1] = '\0';

    return 0;
}
//user strchr
int get_fq_rec(fq_rec_t *fq_rec, gzFile fq_fd) {

    int done = get_line(fq_fd, fq_rec->name, LINE_SIZE);
    done = done || get_line(fq_fd, fq_rec->seq, LINE_SIZE);
    done = done || get_line(fq_fd, fq_rec->other, LINE_SIZE);
    done = done || get_line(fq_fd, fq_rec->qual, LINE_SIZE);
    char *ptr = strchr(fq_rec->name,' ');
    if (ptr) {
        *ptr='\0';
     read->comment = ptr+1;
    } else {
	read->comment = NULL;
    }
    // before writing it out check that comment isn't null

    return done;
}
