--TEST--
Glib\Timer->__construct
--SKIPIF--
<?php include __DIR__ . '/skipif.inc'; ?>
--FILE--
<?php
use Glib\Timer;

class foo extends Timer{}

$object = new Timer();
var_dump($object);

$object = new foo();
var_dump($object);

// error with wrong args
try {
	$object = new Timer('hello');
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Glib\Timer)#%d (0) {
}
object(foo)#%d (0) {
}
Glib\Timer::__construct() expects exactly 0 parameters, 1 given
