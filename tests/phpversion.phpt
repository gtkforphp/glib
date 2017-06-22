--TEST--
phpversion('glib') value
--SKIPIF--
<?php include __DIR__ . '/skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

var_dump(phpversion('glib'));
?>
= DONE =
--EXPECTF--
string(%d) "%d.%d.%d%s"
= DONE =
