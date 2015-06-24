--TEST--
Glib::checkVersion
--SKIPIF--
<?php if (!extension_loaded("glib")) print "skip"; ?>
--FILE--
<?php
var_dump(Glib::checkVersion(0));
var_dump(Glib::checkVersion(10));
var_dump(Glib::checkVersion(2));
?>
--EXPECT--
bool(true)
bool(false)
bool(true)