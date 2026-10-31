libfetch_sources = files('common.c', 'fetch.c', 'http.c')

openssl = dependency('openssl', required: true)

libfetch = static_library(
  'fetch',
  libfetch_sources,
  c_args: ['-D_DEFAULT_SOURCE', '-D_XOPEN_SOURCE=700'],
  dependencies: openssl,
  include_directories: inc,
  install: false,
)

libfetch_dep = declare_dependency(
  link_with: libfetch,
)
