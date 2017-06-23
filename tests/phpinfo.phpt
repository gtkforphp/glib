--TEST--
glib phpinfo information
--SKIPIF--
<?php include __DIR__ . '/skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

$ext = new ReflectionExtension('glib');
$ext->info();
?>
= DONE =
--EXPECTF--
glib

GLib extension => enabled
Runtime Glib Library Version => 2.%d.%d
Compiled Glib Library Version => 2.%d.%d
Extension Version => %s
= DONE =