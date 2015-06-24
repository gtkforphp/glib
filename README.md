Glib for PHP 7
=============

Glib is a general-purpose utility library originally written for the gnome desktop system. It
provides data types, conversions, string utilities, file utilities, mainloop
abstractions and other useful tools for building applications. The library works
on most UNIX-like platforms, Windows, and OSX.

This extension provides access to Glib functionality in PHP7 in the Glib namespace

Status
=============
This is currently very experimental
There are plans to add appveyor and travis builds for testing

Requirements
=============
 * PHP 7.0.0-alpha1+
 * Glib 2.28+

Additional features are supported up to Glib version 2.44

Features are enabled at compile time based on the library version they are compiled against.

Documentation and information about the underlying library can be found at [gnome.org](http://developer.gnome.org/glib/stable/)

Installation
=============
There are plans to make this available via [pecl](http://pecl.php.net) and [pickle](https://github.com/FriendsOfPHP/pickle)


Until then, please compile and install the extension and enable it in your php.ini file

```
extension=glib.so
```

Compile
=============

This extension can be compiled and tested using phpize

This extension also requires glib development files.  You can build the package
manually or use your system's package manager.  For example on ubuntu use

```
apt-get install libglib-2.0-dev
```

Then you can use phpize to install the extension against your current PHP install

```
phpize
./configure
make && make test && make install
```

If you want to use a non-standard location for your PHP use

```
/path/to/phpize
./configure --with-php-config=/path/to/php-config
make && make test && make install
```

`make install` copies `glib.so` to the right location, but you still need to enable the module
in your php.ini file.  Although the extension can be used with a webserver, that is not recommended.

Examples
====
The examples directory holds samples of all currently working utilities for the extension

Community
=====
You can find us on [freenode](http://freenode.org) on #gtkforphp

The main website is [Gtk For PHP](http://gtkforphp.net)

You can view commits and released on [twitter](http://twitter.com/gtkforphp)

You can send comments, patches, questions [here on github](https://github.com/gtkforphp/glib/issues)

See Contributing.md for information on how to get involved

Authors
====
Elizabeth M Smith

License
=====
PHP extension binding code released under the [MIT license](http://opensource.org/licenses/MIT)
See [LICENSE](LICENSE)

The Glib library is is released under the [LGPL](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)

Documentation
=====
What little documentation we currently have is in code comments and the docs directory

We'd like to use some kind of markdown or rst format for docs, a decision isn't final yet
