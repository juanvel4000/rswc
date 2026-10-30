# rswc

a tiny utility to download files from the network.

rswc uses a vendored port of the BSD `fetch(3)` library to provide a simple interface for retrieving the contents of a URL.

## quick start

```sh
meson setup build # setup the project
meson compile -C build # compile the project
meson install -C build # install the project
```

## requirements

- meson
- a C89-compatible C compiler
- openssl

## usage

```sh
# download a url
rswc https://example.com/file.tar.gz
# download a url to a specific output
rswc -o file.tgz https://example.com/file.tar.gz
# download a url with a fixed timeout
rswc -T 30 https://example.com/file.tar.gz
# download a file using IPv6
rswc -6 https://example.com/file.tar.gz
# download a file using IPv4
rswc -4 https://example.com/file.tar.gz
# download a file with verbose output
rswc -v https://example.com/file.tar.gz
```

## project status

rswc is **not yet production-ready** for real-world usage.

- [CHANGELOG.md](CHANGELOG.md) -- release history
- [CONTRIBUTING.md](CONTRIBUTING.md) -- how to report bugs and send patches

## license

BSD-3-Clause, see [LICENSE](LICENSE)

> third-party source is specified in [THIRD-PARTY-LICENSES](THIRD-PARTY-LICENSES).
