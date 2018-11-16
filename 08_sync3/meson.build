project('08_sync3', 'cpp',
        license : ['Boost'],
        version : '0.1',
        default_options : ['cpp_std=c++14', 'warning_level=3', 'werror=true'])

thread_dep = dependency('threads')

add_global_arguments('-I ~/workspace/builds/asio/asio/include/', language : 'cpp')
add_global_arguments('-DASIO_STANDALONE', language : 'cpp')
add_global_arguments('-DASIO_NO_DEPRECATED', language : 'cpp')

inc_dir = include_directories('include')
src = ['src/main.cpp', 'src/Philosopher.cpp']

executable('08_sync3',
           sources : src,
           include_directories : inc_dir,
           dependencies : thread_dep
          )