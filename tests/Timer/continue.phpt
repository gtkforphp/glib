--TEST--
Glib\Timer->continue
--SKIPIF--
<?php include __DIR__ . '/../skipif.inc'; ?>
--FILE--
<?php
use Glib\Timer;

class foo extends Timer{}

// Basic use case - stop timer then continue it
$object = new Timer();
$first = $object->elapsed();
$object->stop();
$object->continue();
$second = $object->elapsed();
// second should be greater than first
var_dump($second > $first);

// repeat use case with extended class
$object = new foo();
$first = $object->elapsed();
$object->stop();
$object->continue();
$second = $object->elapsed();
// second should be greater than first
var_dump($second > $first);

// error with wrong args
try {
	$object = new Timer();
	$object->continue('hello');
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}

// error continuing a non-stopped timer
try {
	$object = new Timer();
	$object->continue();
} catch (BadMethodCallException $e) {
	echo $e->getMessage(), PHP_EOL;
}

?>
--EXPECT--
bool(true)
bool(true)
Glib\Timer::continue() expects exactly 0 parameters, 1 given
Cannot call continue on a timer that has not been stopped

