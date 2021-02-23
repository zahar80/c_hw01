#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void exit_program(const char* error) {
    fprintf(stderr, "%s\n", error);
    exit(1);
}

int main(int argc, char** argv) {
    if (argc != 4) {
        exit_program("Args must be: input file, charset, output file");
    }

    const char* cp = argv[2];
    if (strcmp(cp, "cp1251") && strcmp(cp, "iso8859")) {
        exit_program("Coding page must be cp1251 or iso8859");
    }

    FILE* in = fopen(argv[1], "r");
    FILE* out = fopen(argv[3], "w");

    if (in == NULL || out == NULL) {
        exit_program("Open file error");
    }

    int ch;
    int offset = !strcmp(cp, "cp1251") ? 0xC0 : 0xB0;
    while((ch=fgetc(in)) != EOF) {
        const int delta = ch - offset;
        if (delta > 0) {
            fputc(0x90 + delta > 0xbf ? 0xd1 : 0xd0, out);
            fputc(0x90 + delta > 0xbf ? 0x50 + delta : 0x90 + delta, out);
        } else {
            fputc(ch, out);
        }
    }

    fclose(in);
    fclose(out);

    return 0;
}
