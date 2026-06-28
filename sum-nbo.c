#include <stdio.h>
#include <stdint.h>

uint32_t myntohl(uint32_t n) {
        uint32_t n1 = (n & 0xFF000000) >> 24;
        uint32_t n2 = (n & 0x00FF0000) >> 8;
        uint32_t n3 = (n & 0x0000FF00) << 8;
        uint32_t n4 = (n & 0x000000FF) << 24;
        return n1 | n2 | n3 | n4;
}

int main(int argc, char *argv[]) {
        if (argc < 2) {
                fprintf(stderr, "syntax : %s <file1> [<file2>...]\n", argv[0]);
                fprintf(stderr, "sample : %s a.bin b.bin c.bin\n", argv[0]);
                return 1;
        }

        uint32_t sum = 0;

        for (int i=1;i<argc;i++) {
                FILE *fp = fopen(argv[i], "rb");
                if (fp == NULL) {
                        fprintf(stderr, "Error: cannot open file '%s'\n", argv[i]);
                        return 1;
                }

                uint32_t raw;
                size_t n = fread(&raw, sizeof(raw), 1, fp);
                fclose(fp);

		if (n != 1) {
			fprintf(stderr, "Error: cannot read 4 bytes from '%s'\n", argv[i]);
			fclose(fp);
			return 1;
		}

                uint32_t value = myntohl(raw);
                sum = sum + value;

                if (i > 1)
                        printf(" + ");
                printf("%u(0x%08x)", value, value);
        }

        printf(" = %u(0x%08x)\n", sum, sum);

        return 0;
}
