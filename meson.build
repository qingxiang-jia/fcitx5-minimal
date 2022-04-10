project('fcitx-minimal', 'cpp', default_options : ['cpp_std=c++17'])
add_global_arguments('-DSOME_TOKEN=value', language : 'cpp')

fcitx_dep = [
    dependency('Fcitx5Core'),
    dependency('Fcitx5Utils'),
    dependency('Fcitx5Config')
]

minimal_sources = ['minimal.hpp']
minimal_lib = shared_library('libminimal', minimal_sources)

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : minimal_lib,
                 version : '1.0',
                 name : 'libminimal',
                 filebase : '',
                 description : '')