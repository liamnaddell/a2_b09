#ifndef _RECORDS_H
#define _RECORDS_H

#include <stdio.h>

typedef struct record {
  unsigned suncents;       // 4 bytes on x86-64
  unsigned char name_len;  // length of name
  char name[27];           // name; NOT nul-terminated! use name_len above
} record;
// record size conspires to be 32 bytes on x86-64 :)

int get_record(FILE *f, const char *name, record *r);
int get_suncents(FILE *f, const char *name, unsigned *psuncents);
// In the file, get the suncents field of the record that has given name.
//
// If found, store the answer at the psuncents address, and return 1 (C
// true). The new file position should be right after the found record.
//
// If not found, don't touch the space at psuncents. Return 0 (C false). The new
// file position should be end of file.
//
// File position before this may be anywhere. Do your own "seek to the
// beginning" before you search.
//
// If multiple records have the same name, just use the 1st one.

void set_suncents(FILE *f, const char *name, unsigned suncents);
// In the file, change (overwrite) the suncents field of the record that has the
// given name.
//
// File position before this may be anywhere. Do your own "seek to the
// beginning" before you search.
//
// If multiple records have the same name, just change the 1st one.
//
// If no record has the name, add a new record at the end.
//
// In all cases, the new file position after this should be right after
// the updated/new record.

#endif  // #ifndef _RECORDS_H
