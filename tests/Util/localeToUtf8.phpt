--TEST--
Glib::localeToUtf8
--SKIPIF--
<?php if (!extension_loaded("glib")) print "skip"; ?>
--FILE--
<?php
var_dump(Glib::localeToUtf8('my pretty string'));
?>
--EXPECT--
string(16) "my pretty string"