--TEST--
glib phpinfo information
--SKIPIF--
<?php
include __DIR__ . '/skipif.inc';
?>
--FILE--
<?php
$ext = new ReflectionExtension('glib');
$ext->info();
?>
= DONE =
--EXPECTF--
glib

GLib extension => enabled
Glib Library Version => 2.%d.%d
Extension Version => %s
= DONE =