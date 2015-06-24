--TEST--
Glib Class Constants
--SKIPIF--
<?php if (!extension_loaded("glib")) print "skip"; ?>
--FILE--
<?php
echo Glib::MAJOR_VERSION, PHP_EOL;
echo Glib::MINOR_VERSION, PHP_EOL;
echo Glib::MICRO_VERSION, PHP_EOL;

echo Glib::major_version, PHP_EOL;
echo Glib::minor_version, PHP_EOL;
echo Glib::micro_version, PHP_EOL;
?>
--EXPECTF--
%d
%d
%d
%d
%d
%d