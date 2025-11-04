project(
  'C_xdg_base_directory',
  'c',
  version: '0.0.1',
  default_options: [
    'c_std=c89',
  ],
  meson_version: '>=1.4.0',
)

add_project_arguments('-D_POSIX_C_SOURCE=200809L', language: ['c'],)

incdir = include_directories('include',)
sources = files()
subdir('src')

C_xdg_base_directory = library(
  'C_xdg_base_directory',
  sources,
  include_directories: incdir,
)

C_xdg_base_directory_dep = declare_dependency(
  include_directories: incdir,
  link_with: C_xdg_base_directory,
)

subdir('test')
