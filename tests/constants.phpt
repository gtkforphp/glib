--TEST--
Glib Namespace Constants
--SKIPIF--
<?php include __DIR__ . '/skipif.inc'; ?>
--FILE--
<?php
echo Glib\COMPILED_MAJOR_VERSION, PHP_EOL;
echo Glib\COMPILED_MINOR_VERSION, PHP_EOL;
echo Glib\COMPILED_MICRO_VERSION, PHP_EOL;

echo Glib\MAJOR_VERSION, PHP_EOL;
echo Glib\MINOR_VERSION, PHP_EOL;
echo Glib\MICRO_VERSION, PHP_EOL;
echo Glib\BINARY_AGE, PHP_EOL;
echo Glib\INTERFACE_AGE, PHP_EOL;
?>
--EXPECTF--
2
%d
%d
2
%d
%d
%d02
2