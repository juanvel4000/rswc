#include <errno.h>
#include <limits.h>
#include <rswc/fetch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void usage(void)
{
    fprintf(stderr, "usage: rswc [-Av46] [-o output] [-T timeout] url\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    int opt;
    int timeout;
    int res;
    size_t nfetchflags;
    const char *output;
    char fetchflags[8];
    char *end;
    char *inferred;
    long tmint;
    FILE *fp;

    timeout = 30;
    output = NULL;
    inferred = NULL;

    fetchflags[0] = '\0';
    nfetchflags = 0;

    while ((opt = getopt(argc, argv, "Av46o:T:")) != -1) {
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
        case '4':
        case '6':
        case 'v':
        case 'A':
            if (nfetchflags < sizeof fetchflags - 1) {
                fetchflags[nfetchflags++] = (char)opt;
                fetchflags[nfetchflags] = '\0';
            }
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
        return rswc_fetch_data(argv[0], stdout, timeout, fetchflags);

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

    res = rswc_fetch_data(argv[0], fp, timeout, fetchflags);

    if (fclose(fp) != 0) {
        fprintf(stderr, "rswc: %s\n", strerror(errno));
        res = 1;
    }

    free(inferred);
    return res;
}
