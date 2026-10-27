// ******************************************************************************
// --------------------------DOCUMENTATION---------------------------------------
//  * Project Name   : MP3 Tag Reader and Editor
//  * File Name      : Shravan_Gopal_MP3_TAG_READER_PROJECT_zip
//  * Author         : Shravan Gopal
//  * Batch no       : 26005D_188
//  * Course         : Embedded Systems
//  * Organization   : Emertxe Information Technologies
//  * Language       : C programming 
//  * Compiler       : GCC
//  * Operating System : Linux
//  *
//  * Description:
//  * ---------------
//  * This project implements an MP3 Tag Reader and Editor using the C programming
//  * language. It reads and modifies ID3 metadata stored in MP3 audio files.
//  * The project uses file handling operations and binary file processing to
//  * extract, display, and edit information such as song title, artist name,
//  * album name, year, genre, and comments.
//  *
//  * The project supports reading ID3 tag information from an MP3 file and
//  * displaying the metadata in a user-friendly format. It also provides editing
//  * functionality to modify selected tag fields and create an updated MP3 file
//  * while preserving the remaining audio data.
//  *
//  * Features:
//  * ---------
//  * - View MP3 ID3 tag information
//  * - Edit song title
//  * - Edit artist name
//  * - Edit album name
//  * - Edit year
//  * - Edit genre
//  * - Edit comments
//  * - Handle MP3 files using binary file operations
//  * - Copy and update MP3 file contents
//  * - Validate command-line arguments
//  * - Display appropriate error messages
//  *
//  * ID3 Tags Supported:
//  * ------------------
//  * - TIT2 : Title
//  * - TPE1 : Artist
//  * - TALB : Album
//  * - TYER : Year
//  * - TCON : Genre
//  * - COMM : Comment
//  *
//  * Date Created   : 18/09/2026
//  * Last Modified  : 23/09/2026
//  * Version        : 1.0
//  ****************************************************************************** 
#include <stdio.h>
#include <string.h>
#include "view.h"
#include "edit.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(validate_arguement(argc, argv) == failure)
    {
        print_usage();
        return 0;
    }
    if(strcmp(argv[1], "--help") == 0)
    {
        if(argc == 2)
        {
            print_help();
            return success;
        }
        else
        {
            return failure;
        }
    }
    else if(strcmp(argv[1], "-v") == 0)
    {
        if(argc != 3)
        {
            print_usage();
            return 0;
        }
        else
        {
            printf("==========Details of the Song==========\n");
            
            if(view_details(argv[2]) == failure)
            {
                printf("Failed to fetch details.\n");
                return 0;
            }
        }
    }
    else if(strcmp(argv[1], "-e") == 0)
    {
        if(argc != 5)
        {
            print_usage();
            return 0;
        }
        else 
        {
            printf("==========Edited Details of the Song==========\n");
            if(edit_details(argv) == failure)
            {
                printf("Failed to edit details\n");
                return 0;
            }
            printf("Edited successfully....\n");
            printf("To view Use command : ./a.out -v duplicate.mp3\n");
        }
    }

    else
    {
        print_usage();
    }

    return 0;
}