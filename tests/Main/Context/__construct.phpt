--TEST--
Glib\Main\Context->__construct
--SKIPIF--
<?php include __DIR__ . '/../../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

use Glib\Main\Context;

class foo extends Context {}

$object = new Context();
var_dump($object);

$object = new foo();
var_dump($object);

// error with wrong args
try {
	$object = new Context('hello');
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Glib\Main\Context)#%d (0) {
}
object(foo)#%d (0) {
}
Glib\Main\Context::__construct() expects exactly 0 parameters, 1 given
