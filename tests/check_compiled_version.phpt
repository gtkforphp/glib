--TEST--
Glib\check_compiled_version()
--SKIPIF--
<?php include __DIR__ . '/skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);
use Glib as G;

var_dump(G\check_compiled_version(0));
var_dump(G\check_compiled_version(10));
var_dump(G\check_compiled_version(2));
?>
--EXPECT--
bool(true)
bool(false)
bool(true)