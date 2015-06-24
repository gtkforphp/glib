--TEST--
Glib\Bookmarkfile->__toString
--SKIPIF--
<?php if (!extension_loaded("glib")) print "skip"; ?>
--FILE--
<?php
use Glib\Bookmarkfile;

class foo extends Bookmarkfile{}
class bad extends Bookmarkfile {
    public function __construct() {}
}

$object = new Bookmarkfile();
echo $object->__toString(), PHP_EOL;
echo $object, PHP_EOL;

$object = new foo();
echo $object->__toString(), PHP_EOL;
echo $object, PHP_EOL;;

$object = new bad();
echo $object->__toString(), PHP_EOL;
echo $object, PHP_EOL;

?>
--EXPECTF--
<?xml version="1.0" encoding="UTF-8"?>
<xbel version="1.0"
      xmlns:bookmark="http://www.freedesktop.org/standards/desktop-bookmarks"
      xmlns:mime="http://www.freedesktop.org/standards/shared-mime-info"
></xbel>
<?xml version="1.0" encoding="UTF-8"?>
<xbel version="1.0"
      xmlns:bookmark="http://www.freedesktop.org/standards/desktop-bookmarks"
      xmlns:mime="http://www.freedesktop.org/standards/shared-mime-info"
></xbel>
<?xml version="1.0" encoding="UTF-8"?>
<xbel version="1.0"
      xmlns:bookmark="http://www.freedesktop.org/standards/desktop-bookmarks"
      xmlns:mime="http://www.freedesktop.org/standards/shared-mime-info"
></xbel>
<?xml version="1.0" encoding="UTF-8"?>
<xbel version="1.0"
      xmlns:bookmark="http://www.freedesktop.org/standards/desktop-bookmarks"
      xmlns:mime="http://www.freedesktop.org/standards/shared-mime-info"
></xbel>

Fatal error: Glib\Bookmarkfile::__toString(): Internal object missing in bad class, you must call parent::__construct in extended classes in %s on line %d