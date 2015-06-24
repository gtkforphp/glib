--TEST--
Glib::filenameToUri
--SKIPIF--
<?php if (!extension_loaded("glib")) print "skip"; ?>
--FILE--
<?php
var_dump(Glib::filenameToUri('/tmp/ø.cnf'));
?>
--EXPECT--
string(22) "file:///tmp/%C3%B8.cnf"
