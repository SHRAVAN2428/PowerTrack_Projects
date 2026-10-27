MP3 Tag Reader and Editor

Author: Shravan Gopal
Batch: 26005D_188
Course: Embedded Systems
Organization: Emertxe Information Technologies
Language: C | Compiler: GCC | Platform: Linux

Overview

A command-line C application intended to read selected ID3 metadata frames from MP3 files and edit selected fields using binary file operations.

Files

main.c — command-line entry point.

view.c, view.h — help, validation, and metadata viewing functions.

edit.c, edit.h — frame selection and edit/copy logic.

Makefile — builds the program.

original.mp3, duplicate.mp3 — sample files from the supplied archive.

Build

Requirements: GCC and GNU Make.

make

Clean generated executable:

make clean

Usage

./mp3_tag_reader --help
./mp3_tag_reader -v original.mp3
./mp3_tag_reader -e -t "New Song Title" original.mp3
./mp3_tag_reader -e -a "Artist Name" original.mp3
./mp3_tag_reader -e -A "Album Name" original.mp3
./mp3_tag_reader -e -y "2026" original.mp3
./mp3_tag_reader -e -c "Genre" original.mp3
./mp3_tag_reader -e -C "Composer Name" original.mp3

The edit path writes the output to duplicate.mp3 in the current working directory. Back up audio files before testing.

Edit options implemented in edit.c

-t: title (TIT2)

-a: artist (TPE1)

-A: album (TALB)

-y: year (TYER)

-c: genre (TCON)

-C: composer (TCOM)

Implementation notes and limitations

The viewer checks for an ID3 signature and attempts to read six frames. This is a simplified implementation, not a complete parser for every ID3 version or metadata layout. The editor uses a fixed output filename. The supplied source compiles with GCC, but warnings were observed for missing return statements and an unused variable; compilation alone does not confirm that every operation is correct. The help text is not fully consistent with the edit-option mapping. Please test only on copies of MP3 files and verify edited metadata independently.