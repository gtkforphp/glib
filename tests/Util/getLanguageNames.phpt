--TEST--
Glib::getLanguageNames
--SKIPIF--
<?php if (!extension_loaded("glib")) print "skip"; ?>
--FILE--
<?php
$array = Glib::getLanguageNames();
var_dump(is_array($array));
var_dump(array_pop($array));
?>
--EXPECT--
bool(true)
string(1) "C"