--TEST--
Glib::checkRuntimeVersion
--SKIPIF--
<?php if (!extension_loaded("glib")) print "skip"; ?>
--FILE--
<?php
var_dump(Glib::checkRuntimeVersion(0));
var_dump(Glib::checkRuntimeVersion(10));
var_dump(Glib::checkRuntimeVersion(2));
?>
--EXPECT--
string(37) "GLib version too new (major mismatch)"
string(37) "GLib version too old (major mismatch)"
NULL