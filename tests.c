#include "records.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *cpy(char *in) {
	char srcs[40] = "data-in/";
	strcat(srcs,in);
	char *dests = (char *)calloc(sizeof(char),40);
	strcat(dests,"data-out/");
	strcat(dests,in);
	FILE *src = fopen(srcs,"rb");
	if (src == NULL) {
		perror(srcs);
		assert(false);
	}
	FILE *dest = fopen(dests,"wb");
	if (dest == NULL) {
		perror(dests);
		assert(false);
	}
	char ch;
	while ((ch = fgetc(src)) != EOF) {
		fputc(ch,dest);
	}
	fclose(src);
	fclose(dest);
	return dests;
}
void a_nonull(record *r) {
	char *name = r->name;
	int name_len = r->name_len;
	assert(name[name_len-1] != 0);
}



void test_basic() {
	char *dest =cpy("sample.dat");
	FILE *f = fopen(dest,"rb+");
	free(dest);
	if (f == NULL) {
		perror("tests_basic fopen");
		return;
	}
	// Get Dennis Ritchie suncents
	unsigned y;
	if (get_suncents(f, "Dennis Ritchie", &y)) {
		assert(1926 == y);
	} else {
		assert(false);
	}

	// Add a new record.
	set_suncents(f, "William Henry Gates XXXVIII", 6);
	if (get_suncents(f, "William Henry Gates XXXVIII", &y)) {
		assert(y == 6);
	} else {
		puts("Gates not found");
		assert(false);
	}

	// Change Archimedes's YOB to the best estimate 288 BCE, hex fee0
	set_suncents(f, "Archimedes", 290);
	if (get_suncents(f, "Archimedes", &y)) {
		assert(y == 290);
	} else {
		printf("archi not found\n");
		assert(false);
	}

	if (get_suncents(f, "Alan Turing", &y)) {
		assert(y == 4000000000);
	} else {
		printf("alan not found\n");
		assert(false);
	}
	fclose(f);
}

void test_basic2() {
	char *dest =cpy("sample.dat");
	FILE *f = fopen(dest,"rb+");
	free(dest);
	if (f == NULL) {
		perror("tests_basic2 fopen");
		return;
	}
	// Get Dennis Ritchie suncents
	record r;
	if (get_record(f, "Dennis Ritchie", &r)) {
		assert(r.suncents == 1926);
		assert(r.name_len == 14);
		a_nonull(&r);
	} else {
		assert(false);
	}

	// Add a new record.
	set_suncents(f, "William Henry Gates XXXVIII", 6);
	if (get_record(f, "William Henry Gates XXXVIII", &r)) {
		assert(r.suncents == 6);
		assert(r.name_len == 27);
		a_nonull(&r);
	} else {
		puts("Gates not found");
		assert(false);
	}

	if (get_record(f, "William Henry Gates XXXVIIV", &r)) {
		puts("Gates should not found");
		assert(false);
	} else {
		assert(true);
	}

	// Change Archimedes's YOB to the best estimate 288 BCE, hex fee0
	set_suncents(f, "Archimedes", 290);
	if (get_record(f, "Archimedes", &r)) {
		assert(r.suncents == 290);
		assert(r.name_len == 10);
		a_nonull(&r);
	} else {
		printf("archi not found\n");
		assert(false);
	}

	if (get_record(f, "Alan Turing", &r)) {
		assert(r.suncents == 4000000000);
		assert(r.name_len == 11);
		a_nonull(&r);
	} else {
		printf("alan not found\n");
		assert(false);
	}
	fclose(f);
}

void test_liam() {
	char *dest =cpy("liam.dat");
	FILE *f = fopen(dest,"rb+");
	free(dest);
	if (f == NULL) {
		perror("tests_liam fopen");
		return;
	}
	record r;
	if (get_record(f,"Liam Naddell",&r)) {
		assert(r.name_len == 0xc);
		a_nonull(&r);
		assert(r.suncents == 42069);
	} else {
		puts("liam not found");
		assert(false);
	}
	fclose(f);
}

void test_liam2() {
	char *dest =cpy("liam.dat");
	FILE *f = fopen(dest,"rb+");
	free(dest);
	if (f == NULL) {
		perror("tests_liam2 fopen");
		return;
	}
	record r;
	if (get_record(f,"Liam Naddell",&r)) {
		assert(r.name_len == 0xc);
		a_nonull(&r);
		assert(r.suncents == 42069);
	} else {
		puts("liam not found");
		assert(false);
	}
	set_suncents(f,"Liam Naddel",42068);
	if (get_record(f,"Liam Naddell",&r)) {
		assert(r.name_len == 0xc);
		a_nonull(&r);
		assert(r.suncents == 42069);
	} else {
		puts("liam not found");
		assert(false);
	}
	set_suncents(f,"Liam Naddelll",42070);
	if (get_record(f,"Liam Naddell",&r)) {
		assert(r.name_len == 0xc);
		a_nonull(&r);
		assert(r.suncents == 42069);
	} else {
		puts("liam not found");
		assert(false);
	}
	unsigned y;
	if (get_suncents(f,"Liam Naddel",&y)) {
		assert(y == 42068);
	} else {
		assert(false);
	}
	if (get_suncents(f,"Liam Naddell",&y)) {
		assert(y == 42069);
	} else {
		assert(false);
	}
	if (get_suncents(f,"Liam Naddelll",&y)) {
		assert(y == 42070);
	} else {
		assert(false);
	}

	if (get_suncents(f,"Liam Naddel",&y)) {
		assert(y == 42068);
	} else {
		assert(false);
	}
	if (get_suncents(f,"Liam Naddelll",&y)) {
		assert(y == 42070);
	} else {
		assert(false);
	}
	if (get_suncents(f,"Liam Naddell",&y)) {
		assert(y == 42069);
	} else {
		assert(false);
	}

	if (get_suncents(f,"Liam Naddell",&y)) {
		assert(y == 42069);
	} else {
		assert(false);
	}
	if (get_suncents(f,"Liam Naddel",&y)) {
		assert(y == 42068);
	} else {
		assert(false);
	}
	if (get_suncents(f,"Liam Naddelll",&y)) {
		assert(y == 42070);
	} else {
		assert(false);
	}

	if (get_suncents(f,"Liam Naddell",&y)) {
		assert(y == 42069);
	} else {
		assert(false);
	}
	if (get_suncents(f,"Liam Naddelll",&y)) {
		assert(y == 42070);
	} else {
		assert(false);
	}
	if (get_suncents(f,"Liam Naddel",&y)) {
		assert(y == 42068);
	} else {
		assert(false);
	}

	if (get_suncents(f,"Liam Naddelll",&y)) {
		assert(y == 42070);
	} else {
		assert(false);
	}
	if (get_suncents(f,"Liam Naddell",&y)) {
		assert(y == 42069);
	} else {
		assert(false);
	}
	if (get_suncents(f,"Liam Naddel",&y)) {
		assert(y == 42068);
	} else {
		assert(false);
	}

	if (get_suncents(f,"Liam Naddelll",&y)) {
		assert(y == 42070);
	} else {
		assert(false);
	}
	if (get_suncents(f,"Liam Naddel",&y)) {
		assert(y == 42068);
	} else {
		assert(false);
	}
	if (get_suncents(f,"Liam Naddell",&y)) {
		assert(y == 42069);
	} else {
		assert(false);
	}

	fclose(f);
}

int main() {
	test_basic();
	test_basic2();
	test_liam();
	test_liam2();
}
