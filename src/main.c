#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc != 4) {
        fprintf(stderr, "Args must be: input file, charset, output file\n");
        exit(1);
    }

    const char* cp = argv[2];
    if (strcmp(cp, "cp1251") && strcmp(cp, "iso8859")) {
        fprintf(stderr, "Coding page must be cp1251 or iso8859\n");
        exit(1);
    }

    FILE* in = fopen(argv[1], "r");
    FILE* out = fopen(argv[3], "w");

    if (in == NULL || out == NULL) {
        fprintf(stderr, "Open file error\n");
        exit(1);
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
