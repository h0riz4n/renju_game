# sfml-vscode-boilerplate

A cross-platform [SFML](https://www.sfml-dev.org) 2.5.1 & C++17 build environment for [Visual Studio Code](https://code.visualstudio.com/)

> Note: This project has been superseded by: [https://github.com/chalet-org/chalet-example-sfml](https://github.com/chalet-org/chalet-example-sfml), utilizing a new build system called [Chalet](https://www.chalet-work.space/). Please give that a try instead!

---

## Features

- Cross-platform build environments (Windows, Linux & MacOS)
- GCC & Clang Compiler Configuration
- Debugger support or standalone Debug build
- Unit testing (with Catch2)
- Static Profiler on Windows/Linux (gprof)
- Bash terminal integration
- Automated copying of dependencies
- Automated production build
- Automated app bundling on MacOS
- Basic app bundle on Linux
- Optionally auto-generate assembly from compiled objects (using objdump)
- Optional precompiled header (cross-platform as well)
- Optional Keybindings (F8, F9 & F10)
- Optionally build on Raspberry Pi! (see bottom of Readme)

---

## Prerequisites

### Windows

- [SFML 2.5.1 - GCC 7.3.0 MinGW (DW2) 32-bit (for Windows)](https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit.zip)
- [GCC 7.3.0 MinGW (DW2) 32-bit (for Windows)](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/i686-7.3.0-release-posix-dwarf-rt_v5-rev0.7z/download)
- [Git Bash (for Windows) ](https://git-scm.com/downloads)

### MacOS

- [SFML 2.5.1 - Clang 64-bit](https://www.sfml-dev.org/files/SFML-2.5.1-macOS-clang.tar.gz)
- Command Line Tools / XCode (type "xcode-select --install" in terminal to trigger the installer)

### Linux

- Get SFML 2.5.1 from your distro if it has it, or compile from source

### All

- [Visual Studio Code](https://code.visualstudio.com/download)
- Extensions (install from Extensions panel):
  - [Official C/C++ Extension (0.21.0+)](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
  - [Shader languages support for VS Code (Optional Syntax Highlighting)](https://marketplace.visualstudio.com/items?itemName=slevesque.shader)
  - [x86 and x86_64 Assembly (Optional Syntax Highlighting)](https://marketplace.visualstudio.com/items?itemName=13xforever.language-x86-64-assembly)
  - [Studio Icons (Optional Icon Theme)](https://marketplace.visualstudio.com/items?itemName=jtlowe.vscode-icon-theme)

---

## Installation

### Windows

1. Download & Extract SFML to **C:/SFML-2.5.1/** where the bin/lib/include folders are contained within
2. Download & Extract MinGW to **C:/mingw32/** where the bin/lib/include folders are contained within

### All

3. Download & Install Visual Studio Code if you don't already have it.
4. Install the official **C/C++** Extension, reload the window & wait for the dependencies to install.
5. If on Windows, install **Git Bash**, and ensure the **"terminal.integrated.shell.windows"** property in the project's **settings.json** is set to **bash.exe**'s correct location (default: C:/Program Files/Git/bin/bash.exe). We'll be using this for the terminal in our workspace so that the Makefile can run in both Windows, Mac & Linux
6. In **settings.json** Ensure **Path** in the **terminal.integrated.env.windows** object is set to the correct location of the compiler's executable (example: C:\\mingw32\\bin) and the SFML directory is correct as well. Keep in mind Paths should be separated by a semi-colon with no spaces between.

**Note:** You can manage the "Path" environment variable from Windows if you'd like, but I've found sandboxing it in VS Code is better for tracking things like .dll dependencies.

---

## Configuration

At this point, everything you need is installed

1. Open the **sfml-vscode-boilerplate** folder in VS Code.
2. With Main.cpp (or any source file) open, check the lower-right to ensure "Win32/Mac/Linux" is the configuration set (this should be auto-selected by the C++ plugin). If it is not correct, hit **Ctrl+Shift+B** and select **C/Cpp: Select a configuration...** and choose the platform you're working on.
3. At this point you should be able to run a build task (**Ctrl+Shift+B** > **Build & Run**), but it'll be nicer to add keybindings for these tasks so you can build with 1 keypress.
4. Open the .vscode folder and click on the **\_keybindings.json** file. This is not an officially recognized file, but just contains the keybindings you can copy into the actual keybindings.json file.
5. Go into **File** > **Preferences** > **Keyboard Shortcuts** & click on the keybindings.json link at the top.
6. Copy the keybindings into this file. Feel free to change them if you don't like them later.
7. Hit the **F9** key to run the **Build & Run: Release** task. It should run the Makefile, find the compiler, build the Main.cpp into Main.o, and launch the sample SFML app. **Shift+F9** will launch the basic Debug build, and F8 will launch the actual Debugger alongside the Debug build.

---

## Adding Source Files

Source files and folders are automatically detected by the Makefile. It looks for them in the "src" folder, and at the moment builds from .c, .cpp, .cc & .rc files.

---

## Makefile Environment

The environment variables used by the Makefile are managed from the **env** folder in separate .mk (Make) files, organized by build type & platform, so you can customize which SFML libraries to include if you want, or pretty much anything without having to edit the tasks.json. Each file is outlined below:

    ./build.sh: Contains the build scripts that tasks.json calls

    ./env/.all.mk: All platforms & builds
    ./env/.debug.mk: All platforms, Debug build
    ./env/.release.mk: All platforms, Release build

    ./env/linux.all.mk: Linux, All builds
    ./env/linux.debug.mk: Linux, Debug build
    ./env/linux.release.mk: Linux, Release build

    ./env/osx.all.mk: MacOS, All builds
    ./env/osx.debug.mk: MacOS, Debug build
    ./env/osx.release.mk: MacOS, Release build

    ./env/rpi.release.mk: Linux (Raspberry Pi), Release build

    ./env/windows.all.mk: Windows, All builds
    ./env/windows.debug.mk: Windows, Debug build
    ./env/windows.release.mk: Windows, Release build

Unit Tests use the same settings as the Release build.

The environment variables that can be added to each .mk file are outlined below. If you need a line-break anywhere simply add a **"\\"** character. You can set base variables in _.all.mk and then build specific variables using "VAR := $(VAR)" syntax in _.debug.mk or \*.release.mk. The hierarchy goes:

    ./env/.all.mk
    ./env/.(build).mk
    ./env/(platform).all.mk
    ./env/(platform).(build).mk

---
