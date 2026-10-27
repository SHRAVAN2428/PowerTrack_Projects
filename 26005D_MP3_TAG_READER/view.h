#ifndef VIEW_H
#define VIEW_H

typedef enum STATUS
{
    success,
    failure
}status;

void print_usage();
void print_help();
status validate_arguement(int argc, char *argv[]);
status view_details(char *file);
int read_size(FILE *file);
void read_tag(FILE *file, int size);

#endif
