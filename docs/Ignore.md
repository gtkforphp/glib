# Ignored Functionality

## From [Glib](https://developer.gnome.org/glib/stable/index.html) Documentation

This is documentation and reasoning for what is and isn't wrapped in the Glib PHP extension.

### Glib Fundamentals

Other than some version information and the glib_version_check call, none of these items are wrapped, nor do they need to be.  Macros, bounds checking, even the definition of PI exist in PHP in useable forms.

### Glib Core Application Support

The main event loop section is almost completely wrapped.  For individual symbol information see the symbols file.

The IO channels are also important for the functionality of the event loop.  These may also need some integration with PHP's streams via a stream wrapper.

The threading sections are problematic since PHP doesn't do threading well or correctly.  At least some of the wait condition and mutex code would be useful for later gtk functionality.  The async queues will probably be wrapped.  The threading and thread pools might not be, although some of their functionality might be added (similar to the pthreads extension) for threaded builds of php only.

The remaining sections - dynamic loading of modules, memory allocation, memory slices, warning and assertions, message output and debugging are all unnecessary and will be ignored.

### Glib Utilities

Most of the items here will be wrapped.  Some will be simple functions in the Glib namespace, others will be full objects (such as timers)

The string utility functions (std), character set conversions (iconv),  internationalization (gettext), Date, time, timezone and datetime (date), file utilities (std), pipes,  and signals, and processes spawning all have support in PHP already.  Some of these may be mapped later or on demand, but will probably be ignored in favor of PHP versions

The Hook Functions are also low on the list of importance, although they could be implemented by "wrapping" php callables.

### Glib Data Types

At least to start with, only datatypes that are not currently support in PHP will be wrapped.  The really interesting items (sequences, binary and ntrees) will be first on the list.  Later others may be added if someone gets bored.

Datatypes that make no sense in PHP (trash stacks, strings and string chunks, quarks, datasets and gvariants) will not be wrapped.

### Deprecated

No symbol marked as deprecated will be wrapped.  No API marked as deprecated will be wrapped, no tools will be wrapped.