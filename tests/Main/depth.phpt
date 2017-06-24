--TEST--
Glib\Main\depth()
--SKIPIF--
<?php include __DIR__ . '/skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);
use Glib\Main as G;

var_dump(G\depth());
// error with wrong args
try {
	G\depth('foo');
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
int(0)
Glib\Main\depth() expects exactly 0 parameters, 1 given