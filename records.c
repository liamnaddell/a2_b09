#include <stdio.h>
#include <string.h>
#include "records.h"

//rname does not have to be null-terminated, bname must be
int is_same(const char *rname, const char *bname, int rname_len) {
	size_t len = strlen(bname);
	if (len != rname_len) {
		return 0;
	}
	int res = memcmp(rname,bname,rname_len);
	if (res == 0) {
		return 1;
	} else {
		return 0;
	}
}

void set_suncents(FILE *f, const char *name, unsigned suncents) {
	fseek(f,0,SEEK_SET);
	record r;
	while (fread(&r,sizeof(record),1,f) == 1) {
		if (is_same(r.name,name,r.name_len)) {
			r.suncents=suncents;
			fseek(f,-sizeof(record),SEEK_CUR);
			fwrite(&r,sizeof(record),1,f);
			return;
		}
	}
	size_t l = strlen(name);
	strncpy(r.name,name,l);
	r.name_len = l;
	r.suncents=suncents;
	fwrite(&r,sizeof(record),1,f);
	return;
}


//should we get name_len from here?
int get_record(FILE *f, const char *name, record *r) {
	fseek(f,0,SEEK_SET);
	while (fread(r,sizeof(record),1,f) == 1) {
		if (is_same(r->name,name,r->name_len)) {
			return 1;
		}
	}
	return 0;
}

int get_suncents(FILE *f, const char *name, unsigned *psuncents) {
	fseek(f,0,SEEK_SET);
	record r;
	int retval = get_record(f,name,&r);
	if (retval == 1) {
		*psuncents = r.suncents;
	}
	return retval;
}
