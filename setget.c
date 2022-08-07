#include "records.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	if (!(argc == 3 || argc == 4)) {
		fprintf(stderr,"usage: %s DATABASE (name | name value)\n", argv[0]);
	}
	char name[27];
	memset(name,'\0',27*sizeof(char));
	strncpy(name,argv[2],27);
	int namelen = strlen(argv[2]);
	if (namelen > 27) {
		fprintf(stderr, "name too long\n");
	}
	FILE *db = fopen(argv[1],"r+b");
	if (db == NULL) {
		perror("fopen :(");
		exit(482);
	}

	if (argc == 4) {
		int sc;
		if (sscanf(argv[3],"%d",&sc) < 0) {
			perror("scanf");
			exit(5);
		}
		set_suncents(db,name,sc);
	}
	unsigned ps;
	int ok = get_suncents(db, name, &ps);
	if (!ok) {
		printf("not found\n");
	} else {
		printf("%s has %u suncents\n", argv[2], ps);
	}
	return 0;
}


