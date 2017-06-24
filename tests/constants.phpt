--TEST--
Glib Namespace Constants
--SKIPIF--
<?php include __DIR__ . '/skipif.inc'; ?>
--FILE--
<?php
echo Glib\MAJOR_VERSION, PHP_EOL;
echo Glib\MINOR_VERSION, PHP_EOL;
echo Glib\MICRO_VERSION, PHP_EOL;

echo Glib\major_version, PHP_EOL;
echo Glib\minor_version, PHP_EOL;
echo Glib\micro_version, PHP_EOL;
echo Glib\binary_age, PHP_EOL;
echo Glib\interface_age, PHP_EOL;

if(defined('Glib\OS_WIN')) {
  echo Glib\OS_WIN, PHP_EOL;  
} 

if(defined('Glib\OS_UNIX')) {
  echo Glib\OS_UNIX, PHP_EOL;  
} 
?>
--EXPECTF--
2
%d
%d
2
%d
%d
%d02
%d
1