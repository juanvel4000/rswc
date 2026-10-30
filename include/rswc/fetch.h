#ifndef RSWC_FETCH_H
#define RSWC_FETCH_H

#include <stdio.h>

int rswc_fetch_data(const char *url, FILE *fp, int timeout,
                    const char *fetchflags);
char *rswc_fetch_filename(const char *url);

#endif /* RSWC_FETCH_H */
