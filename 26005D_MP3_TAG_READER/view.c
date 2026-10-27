#include <stdio.h>
#include <string.h>
#include "view.h"


void print_usage()
{
    printf("ERROR : ./a.out : INVALID ARGUEMENTS\n");
    printf("USAGE:\n");
    printf("To view please pass like : ./a.out -v filename.mp3\n");
    printf("To edit please pass like : ./a.out -e -t/-a/-A/-y/-c/-C 'text_to_edit' filename.mp3\n");
    printf("To help please pass like : ./a.out --help\n");
}

void print_help()
{
    printf("Usage : ./a.out -v filename.mp3     [To list all details]\n");
    printf("        ./a.out -e [-t/-a/-A/-m/-y/-c] text_to_edit filename.mp3    [to edit particular data]\n");
    printf("                    -t  modifies a title tag\n");
    printf("                    -a  modifies an Artist tag\n");
    printf("                    -A  modifies an Album tag\n");
    printf("                    -y  modifies a year tag\n");
    printf("                    -c  modifies a Comment tag\n");
    printf("                    -g  modifies an Genre tag\n");
}
status validate_arguement(int argc, char *argv[])
{
    if(argc < 2)
    {
        return failure;
    }
    
}

status view_details(char *file)
{
    FILE *fptr = fopen(file, "rb");
    if(!fptr)
    {
        return failure;
    }

    char signature[4];
    fread(signature, 3, 1, fptr);
    signature[3] = '\0';
    //printf("%s\n",signature);

    if(strcmp(signature, "ID3") != 0)
    {
        printf("The file must be '.mp3' file\n");
        return failure;
    }

    fseek(fptr, 10, SEEK_SET);

    for(int i=0; i<6; i++)
    {
        read_tag(fptr, 4);
        int size = read_size(fptr);
        fseek(fptr, 3, SEEK_CUR);
        printf("--->");
        char ch;
        for(int i=0; i<size-1; i++)
        {
            fread(&ch, 1, 1, fptr);
            printf("%c",ch);
        }
        printf("\n");
    }

    int size = read_size(fptr);
}

void read_tag(FILE *file, int size)
{
    char tag[size];
    fread(tag, size, 1, file);
    tag[size] = '\0';
    printf("%s",tag);
}

int read_size(FILE *file)
{
    int size ;
    fread(&size, 4, 1, file);
    //printf("%d\n",size);
    char *num = (char*) &size;
    char temp;

    temp = num[0]; num[0] = num[3]; num[3] = temp;
    temp = num[1]; num[1] = num[2]; num[2] = temp;
    //printf("%d\n",size);
    return size;
}
