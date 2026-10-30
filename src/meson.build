src = files('fetch.c', 'main.c')

executable(
  'rswc',
  src,
  dependencies: libfetch_dep,
  c_args: ['-D_DEFAULT_SOURCE', '-D_XOPEN_SOURCE=700'],
  include_directories: inc,
  install: true,
)
