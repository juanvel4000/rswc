libfetch_sources = files('common.c', 'fetch.c', 'http.c')

openssl = dependency('openssl')

libfetch = static_library(
  'fetch',
  libfetch_sources,
  c_args: ['-D_DEFAULT_SOURCE', '-D_XOPEN_SOURCE=700'],
  dependencies: [openssl],
  install: false,
)

libfetch_dep = declare_dependency(
  link_with: libfetch,
)
