project(
  'C-xdg_base_dir',
  'c',
  version: '0.0.1',
  default_options: [
    'c_std=c89',
  ],
)

add_project_arguments('-D_POSIX_C_SOURCE=200809L', language: ['c'],)

incdir = include_directories('include',)
sources = files()
subdir('src')

libC_xdg_base_dir = library(
  'libC-xdg_base_dir',
  sources,
  include_directories: incdir,
)

libC_xdg_base_dir_dep = declare_dependency(
  include_directories: incdir,
  link_with: libC_xdg_base_dir,
)

subdir('test')
