--TEST--
Glib\check_version()
--SKIPIF--
<?php include __DIR__ . '/skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);
use Glib as G;

var_dump(G\check_version(0));
var_dump(G\check_version(10));
var_dump(G\check_version(2));
?>
--EXPECT--
string(37) "GLib version too new (major mismatch)"
string(37) "GLib version too old (major mismatch)"
NULL