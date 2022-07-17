#include <stdio.h>
#include "records.h"

// Create file
int init() {
    FILE *file = fopen("amogus.txt", "w");
    if (file == NULL) {
        printf("Can't create file, exiting tests...");
        return 0;
    }

    fclose(file);

    return 1;
}

int checks = 0;

// Comparison function
int neq(unsigned int expected, unsigned int actual, char name[1024]) {
    if (expected != actual) {
        printf("Expected %d, got %d for: %s\n", expected, actual, name);
        return 1;
    }

    printf("[%d] Passed value check for: %s\n", ++checks, name);

    return 0;
}

unsigned int cents_paco = 14412;
unsigned int cents_paco_2 = 9182412;
unsigned int cents_benny = 69;
unsigned int cents_maaz = 42069;


int test_read_write(FILE* file) {

    set_suncents(file, "Paco Estrada", cents_paco);
    
    unsigned int read = 0;

    fseek(file, 3, SEEK_SET);

    get_suncents(file, "Paco Estrada", &read);

    return neq(cents_paco, read, "Paco Estrada") && neq(32, ftell(file), "Stream position [0]");
}


int test_random_position(FILE* file) {

    fseek(file, 23, SEEK_SET);
    set_suncents(file, "Benny", cents_benny);
    
    unsigned int read = 0;
    
    fseek(file, 41, SEEK_SET);

    get_suncents(file, "Benny", &read);

    return neq(cents_benny, read, "Benny");
}

int test_check_position(FILE* file) {

    set_suncents(file, "Starboi", cents_maaz);
    
    if (neq(32*3, ftell(file), "Stream position [1]")) {
        return 1;
    }

    unsigned int read = 0;

    get_suncents(file, "Starboi", &read);

    if (neq(cents_maaz, read, "Starboi")) {
        return 1;
    }

    // ================================

    set_suncents(file, "Paco Estrada", cents_paco_2);

    if (neq(32, ftell(file), "Stream position [2]")) {
        return 1;
    }

     fseek(file, 69, SEEK_SET);

    get_suncents(file, "Paco Estrada", &read);

    if (neq(32, ftell(file), "Stream position [3]")) {
        return 1;
    }

    return neq(cents_paco_2, read, "Paco Estrada");
}

int test_name_checks(FILE* file) {

    unsigned int read = 12;

    fseek(file, 6, SEEK_SET);

    if (neq(0, get_suncents(file, "Paco Estradaa", &read), "Name doesn't exists") && neq(12, read, "Read value")) {
        return 1;
    } 

    fseek(file, 65, SEEK_SET);

    if (neq(0, get_suncents(file, "Paco Estrad", &read), "Name doesn't exists") && neq(12, read, "Read value")) {
        return 1;
    } 

    fseek(file, 35, SEEK_SET);

    if (neq(1, get_suncents(file, "Paco Estrada", &read), "Name exists") && neq(cents_paco_2, read, "Read value")) {
        return 1;
    } 

    fseek(file, 5, SEEK_SET);

    if (neq(1, get_suncents(file, "Starboi", &read), "Name exists") && neq(cents_maaz, read, "Read value")) {
        return 1;
    } 

    fseek(file, 8, SEEK_SET);

    if (neq(1, get_suncents(file, "Benny", &read), "Name exists") && neq(cents_benny, read, "Read value")) {
        return 1;
    } 

    if (neq(0, get_suncents(file, "Maaz X Benny Fanfiction Uwu", &read), "Name doesn't exists") && neq(cents_benny, read, "Read value")) {
        return 1;
    } 

    return 0;
}

int main()
{
    if (!init()) {
        return 1;
    }

    FILE *file = fopen("amogus.txt", "r+b");

    if (file == NULL) {
        printf("Can't access file, exiting tests...");
        return 0;
    }

    if (test_read_write(file)) {
        return 1;
    }

    if (test_random_position(file)) {
        return 1;
    }

    if (test_check_position(file)) {
        return 1;
    }

    if (test_name_checks(file)) {
        return 1;
    }

    printf("All tests passed uwu!\n");

    fclose(file);

    return 0;
}
