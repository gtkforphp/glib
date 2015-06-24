--TEST--
Glib::filenameFromUri
--SKIPIF--
<?php if (!extension_loaded("glib")) print "skip"; ?>
--FILE--
<?php
var_dump(Glib::filenameFromUri('file:///tmp/%C3%B8.cnf'));
?>
--EXPECT--
string(11) "/tmp/ø.cnf"
