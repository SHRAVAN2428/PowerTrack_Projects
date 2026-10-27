#ifndef EDIT_H
#define EDIT_H
#include "view.h"

status edit_details(char **argv);
status open_edit_files(char **argv);
status data_to_duplicate(char **argv, char *str_op, char *tag, FILE *fptr, FILE *eptr);

#endif

