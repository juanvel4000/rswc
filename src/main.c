#include <errno.h>
#include <limits.h>
#include <rswc/fetch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void usage(void)
{
    fprintf(stderr, "usage: rswc [-o output] [-T timeout] url\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    int opt;
    int timeout;
    const char *output;
    char *end;
    long tmint;
    FILE *fp;
    int res;
    char *inferred;

    timeout = 30;
    output = NULL;
    inferred = NULL;

    while ((opt = getopt(argc, argv, "o:T:")) != -1) {
        switch (opt) {
        case 'T':
            errno = 0;
            tmint = strtol(optarg, &end, 10);

            if (end == optarg || *end != '\0' || errno == ERANGE || tmint < 0 ||
                tmint > INT_MAX) {
                fprintf(stderr, "rswc: invalid timeout: %s\n", optarg);
                return EXIT_FAILURE;
            }

            timeout = (int)tmint;
            break;
        case 'o':
            output = optarg;
            break;
        case '?':
            usage();
        }
    }

    if (argc == optind)
        usage();

    argv += optind;
    argc -= optind;

    if (output != NULL && strcmp(output, "-") == 0)
        return rswc_fetch_data(argv[0], stdout, timeout);

    if (output == NULL) {
        inferred = rswc_fetch_filename(argv[0]);
        if (inferred == NULL)
            return EXIT_FAILURE;
        output = inferred;
    }

    fp = fopen(output, "wb");
    if (fp == NULL) {
        fprintf(stderr, "rswc: %s\n", strerror(errno));
        free(inferred);
        return EXIT_FAILURE;
    }

    res = rswc_fetch_data(argv[0], fp, timeout);

    if (fclose(fp) != 0) {
        fprintf(stderr, "rswc: %s\n", strerror(errno));
        res = 1;
    }

    free(inferred);
    return res;
}
