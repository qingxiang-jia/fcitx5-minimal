# fcitx5-minimal
A simple noop input method for Fcitx5 served as a starting point for new input methods.
- Everything about the input method is in one `.hpp` file.
- The input method does nothing but returning the same string you entered. The purpose of this project is been used as a starting template for Fcitx5 input methods.
- The project is built using [Meson](https://mesonbuild.com/Tutorial.html) instead of CMake.

# How to Build
1. Generate build files and create a build directory In the root folder, run `meson setup build`.
2. In the build folder run `meson compile`

# Motivation
Recently I am trying to write an input method that's based on Fcitx5. I used [fcitx5-quwei](https://github.com/fcitx/fcitx5-quwei) as a starting point because the [tutorial](https://fcitx-im.org/wiki/Develop_an_simple_input_method) used it. However, (probably due to my lack of experience in C++), it has plenty of unnecessary things that make it a bit hard to follow:

1. The interfaces defined by Fcitx5 itself are quite straightforward but the actual implementation of fcitx5-quwei is a bit convoluted.
2. It's using CMake as the build system. It worked fine but as I want a simpler project structure, I will need to tweak it and I want something simpler and easier to work with.
