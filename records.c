#include <stdio.h>
#include <string.h>
#include "records.h"

void set_suncents(FILE *f, const char *name, unsigned suncents) {
	fseek(f,0,SEEK_SET);
	record r;
	while (fread(&r,sizeof(record),1,f) == 1) {
		if (strncmp(r.name,name,r.name_len) == 0) {
			//check size here
			r.suncents=suncents;
			fseek(f,-sizeof(record),SEEK_CUR);
			fwrite(&r,sizeof(record),1,f);
			return;
		}
	}
	size_t l = strlen(name);
	strncpy(r.name,name,l);
	r.suncents=suncents;
	fwrite(&r,sizeof(record),1,f);
	return;
}

int get_suncents(FILE *f, const char *name, unsigned *psuncents) {
	fseek(f,0,SEEK_SET);
	record r;
	while (fread(&r,sizeof(record),1,f) == 1) {
		if (strncmp(r.name,name,r.name_len) == 0) {
			*psuncents=r.suncents;
			return 1;
		}
	}
	return 0;
}
