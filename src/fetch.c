#include <errno.h>
#include <libfetch/fetch.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

static void rswc_fetch_print_error(void)
{
    struct fetch_error err;

    err = fetchLastErrCode;

    switch (err.category) {
    case FETCH_ERRCAT_ERRNO:
        fprintf(stderr, "rswc: %s\n", strerror(err.code));
        return;
    case FETCH_ERRCAT_NETDB:
        fprintf(stderr, "rswc: %s\n", gai_strerror(err.code));
        return;
    case FETCH_ERRCAT_HTTP:
        fprintf(stderr, "rswc: http error: %d\n", err.code);
        return;
    case FETCH_ERRCAT_TLS:
        fprintf(stderr, "rswc: tls error\n");
        return;
    default:
        fprintf(stderr, "rswc: unknown error\n");
        return;
    }
}

int rswc_fetch_data(const char *url, FILE *fp, int timeout)
{
    fetchIO *fetch;
    char buf[8192];
    ssize_t n;
    int ret;

    ret = 0;
    fetchTimeout = timeout;
    fetch = fetchGetURL(url, "");

    if (fetch == NULL) {
        rswc_fetch_print_error();
        return 1;
    }

    while ((n = fetchIO_read(fetch, buf, sizeof buf)) > 0) {
        if (fwrite(buf, 1, (size_t)n, fp) != (size_t)n) {
            fprintf(stderr, "rswc: %s\n", strerror(errno));
            ret = 1;
            break;
        }
    }

    if (n < 0) {
        rswc_fetch_print_error();
        ret = 1;
    }

    fetchIO_close(fetch);
    return ret;
}
