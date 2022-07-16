#include "records.h"
#include <stdio.h>

void test_basic() {
	FILE *f = fopen("sample.dat","rb");
	if (f == NULL) {
		perror("sample-main fopen");
		return;
	}
	// Get Dennis Ritchie suncents
	unsigned y;
	if (get_suncents(f, "Dennis Ritchie", &y)) {
		printf("Ritchie has %u suncents\n", y);
	} else {
		printf("Ritchie not found\n");
	}

	// Add a new record.
	set_suncents(f, "William Henry Gates XXXVIII", 6);
	if (get_suncents(f, "William Henry Gates XXXVIII", &y)) {
		printf("gates has %u suncents\n", y);
	} else {
		printf("Gatez not found\n");
	}

	// Change Archimedes's YOB to the best estimate 288 BCE, hex fee0
	set_suncents(f, "Archimedes", 2200);
	if (get_suncents(f, "Archimedes", &y)) {
		printf("archi has %u suncents\n", y);
	} else {
		printf("archi not found\n");
	}
	if (get_suncents(f, "Alan Turing", &y)) {
		printf("alan has %u suncents\n", y);
	} else {
		printf("alan not found\n");
	}
	fclose(f);
}

int main() {
	test_basic();
}
