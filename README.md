WindowGroomer
=============

WindowGroomer arranges windows in Microsoft Windows on a grid. It is an
open-source (GPL) clone of the now-defunct [dfgbt Window Manager][dfgbt].

[dfgbt]: http://www.youtube.com/watch?v=NM8OMcvTk9U "dfgbt Window Manager"

Building from source
--------------------

WindowGroomer uses [Qt 4.8.4][qt] for [Microsoft Visual C++ 2010][msvc] and
[libqxt 0.6.2][libqxt].

[qt]: http://qt-project.org/downloads
[libqxt]: https://bitbucket.org/libqxt/libqxt
[msvc]: http://www.microsoft.com/visualstudio/eng/downloads#d-2010-express

### Setup
1. Install Microsoft Visual C++ 2010. Any edition, including Express, will
work.
2. Install Qt 4.8.x for VS 2010.
3. Compile and install Qxt:
    1. Download and extract libqxt 0.6.x to a directory.
    2. Open a Qt 4.8 Command Prompt and do the following:

            cd [extracted-libqxt]

            # Compile and install for release
            configure
            qmake
            nmake
            nmake install

            # Compile and install for debug
            configure -debug
            qmake
            nmake
            nmake install

### Compiling
1. Clone WindowGroomer into a directory.
2. Open a Qt 4.8 Command Prompt and do the following:

        cd [cloned-source]
        qmake
        nmake

For release mode, replace `qmake` with `qmake release`. You may need to copy
Qt and Qxt *.dll files from their install directories to the WindowGroomer
directory for it to run.
