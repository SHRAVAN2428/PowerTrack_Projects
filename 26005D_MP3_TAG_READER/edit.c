#include <stdio.h>
#include <string.h>
#include "edit.h"
#include "view.h"

status edit_details(char **argv)
{
    if(open_edit_files(argv) == failure)
    {
        printf("File opening failed\n");
        return failure;
    }
    return success;
}

status open_edit_files(char **argv)
{
    FILE *fptr = fopen(argv[4], "rb");
    FILE *eptr = fopen("duplicate.mp3", "wb");

    if(!fptr)
    {
        perror("Error in opening file\n");
        return failure;
    }
    if(!eptr)
    {
        perror("Error in opening file\n");
        return failure;
    }

    char *str_op;
    if(strcmp(argv[2], "-a") == 0)
    {
        str_op =  "TPE1";
    }
    else if(strcmp(argv[2], "-A") == 0)
    {
        str_op = "TALB";
    }
    else if(strcmp(argv[2], "-t")== 0)
    {
        str_op = "TIT2";
    }
    else if(strcmp(argv[2], "-y") == 0)
    {
        str_op = "TYER";
    }
    else if(strcmp(argv[2], "-c") == 0)
    {
        str_op = "TCON";
    }
    else if(strcmp(argv[2], "-C") == 0)
    {
        str_op = "TCOM";
    }
    else
    {
        return failure;
    }

    //printf("%s\n", str_op);

    if(strcmp(str_op, "failure") == 0)
    {
        printf("Invalid edit option\n");
        print_usage();
        return failure;
    }
    //reading first 10bytes
    char header[10];
    fread(header, 1, 10, fptr);
    fwrite(header, 1, 10, eptr);

    for(int i=0;i<6; i++)
    {
        unsigned char tag[5];
    
        fread(tag, 4, 1,fptr);
        tag[4] = '\0';
        //printf("%s\n",tag);
        if(data_to_duplicate(argv, str_op, tag, fptr, eptr) == success)
        {
            break;
        }
    }
    fclose(fptr);
    fclose(eptr);
    return success;
}


status data_to_duplicate(char **argv, char *str_op, char *tag,
                         FILE *fptr, FILE *eptr)
{
    if(strcmp(tag, str_op) == 0)
    {
        /* Write frame ID */
        fwrite(tag, 1, 4, eptr);

        /* Read old frame size */
        unsigned int size;
        fread(&size, 4, 1, fptr);

        /* Convert big endian -> little endian */
        unsigned char *p = (unsigned char *)&size;

        unsigned int old_size =
            ((unsigned int)p[0] << 24) |
            ((unsigned int)p[1] << 16) |
            ((unsigned int)p[2] << 8)  |
            ((unsigned int)p[3]);

        /* Read flags */
        unsigned char flags[2];
        fread(flags, 1, 2, fptr);

        /* Read encoding byte */
        unsigned char encoding;
        fread(&encoding, 1, 1, fptr);

        /*
         * New frame size:
         *
         * 1 byte  -> encoding
         * N bytes -> new data
         */
        unsigned int new_size = strlen(argv[3]) + 1;

        /* Convert new size to big endian */
        unsigned char size_bytes[4];

        size_bytes[0] = (new_size >> 24) & 0xFF;
        size_bytes[1] = (new_size >> 16) & 0xFF;
        size_bytes[2] = (new_size >> 8) & 0xFF;
        size_bytes[3] = new_size & 0xFF;

        /* Write new frame size */
        fwrite(size_bytes, 1, 4, eptr);

        /* Write flags */
        fwrite(flags, 1, 2, eptr);

        /* Write encoding */
        fwrite(&encoding, 1, 1, eptr);

        /* Write new value */
        fwrite(argv[3], 1, strlen(argv[3]), eptr);

        /*
         * old_size includes the encoding byte.
         * We already consumed encoding.
         * So skip only old_size - 1 bytes.
         */
        fseek(fptr, old_size - 1, SEEK_CUR);

        /* Copy remaining MP3 data */
        unsigned char ch;

        while(fread(&ch, 1, 1, fptr) == 1)
        {
            fwrite(&ch, 1, 1, eptr);
        }

        return success;
    }

    else
    {
        /* Copy frame ID */
        fwrite(tag, 1, 4, eptr);

        /* Read frame size */
        unsigned char size_bytes[4];

        fread(size_bytes, 1, 4, fptr);
        fwrite(size_bytes, 1, 4, eptr);

        /* Convert size to integer */
        unsigned int size =
            ((unsigned int)size_bytes[0] << 24) |
            ((unsigned int)size_bytes[1] << 16) |
            ((unsigned int)size_bytes[2] << 8)  |
            ((unsigned int)size_bytes[3]);

        /* Copy flags */
        unsigned char flags[2];

        fread(flags, 1, 2, fptr);
        fwrite(flags, 1, 2, eptr);

        /* Copy frame data */
        for(unsigned int i = 0; i < size; i++)
        {
            unsigned char ch;

            fread(&ch, 1, 1, fptr);
            fwrite(&ch, 1, 1, eptr);
        }

        return failure;
    }
}