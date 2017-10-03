# LibMdHtml++
##### A library for converting markdown to html
###### v0.0.1



#### Currently supported features

* Markdown for headings, simple text formatting and lists

###### Future features

* Support all Markdown formats
* Add CMake and pkgconfig files
* Add documentation
* Add PKGBUILD
* Syntax highlighting for Qt
* Test on windows

___

## Building

You can simply build this with:

```
 % cd /path/to/clone/in
 % git clone https://github.com/nullptrT/libmdhtml.git
 % mkdir libmdhtml/build
 % cd libmdhtml/build
 % cmake .. # You may add CMake options here (see below)
 % make
```

On windows you may use the `cmake-gui` or `qtcreator` to create build files for MSVC 2015 or later.


#### CMake options

Additionally to the default options CMake currently offers the following options (can be specified with `-DOPTION=ON`):

* `MDHTML_SHARED`: Enables building a
shared library `libMdHtml++.so`. Not using this option builds a static `libMdHtml++.a` by default.
* `MDHTML_BUILD_BIN`: Build the command line utility that converts a markdown document into a html document.
  * `MDHTML_QT_SUPPORT`: Build the libMdHtmlQt
  library providing some widgets and convenience functions for editing markdown with Qt.
  * `MDHTML_DESTDIR`: Where are the files installed to. Defaults to `CMAKE_INSTALL_PREFIX` (`/usr` on UNIX and `C:\Program Files` on WIN32)
* `MDHTML_HEADER_INSTALL_DIR`: Can be set to control, where headers are installed. Defaults to `MDHTML_DESTDIR/include/libMDHTML`.
* `MDHTML_LIB_INSTALL_DIR`: Can be set to control where the library is installed. Defaults to `MDHTML_DESTDIR/lib`.
* `MDHTML_INSTALL_LIBS`: Enables targets for installation of library files. Because it is useful not to install the library (e.g. when used as submodule of a project) this defaults to off. If enabled, it installs all headers to `MDHTML_HEADER_INSTALL_DIR` and the libraries to `MDHTML_LIB_INSTALL_DIR`

#### Compiler options / Config variables

You can define the following with your g++-compiler by `-DOPTION=ON` or cmake's `add_definitions( -DOPTION=ON )` function:

*


#### Usage


