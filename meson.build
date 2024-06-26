project('render', ['c', 'cpp'],
  default_options: [
    'prefix=' + meson.global_source_root() / 'packaged',
    'buildtype=debugoptimized',
    'warning_level=3',
    'werror=false',
    'cpp_std=c++20',
  ]
)

add_project_arguments(
  '-Wno-unused-parameter',
  '-Wno-documentation',
  language: ['c', 'cpp'],
)

executable(
  'testy',
  'test.cc',
  dependencies: [
    dependency('gl'),
    dependency('glfw3'),
    dependency('glew'),
  ],
  include_directories: [
    'src',
  ],
  install: true,
)
