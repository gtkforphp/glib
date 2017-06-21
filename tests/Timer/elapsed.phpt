--TEST--
Glib\Timer->elapsed
--SKIPIF--
<?php include __DIR__ . '/../skipif.inc'; ?>
--FILE--
<?php
use Glib\Timer;

class foo extends Timer{}

// Basic use case
$object = new Timer();
$first = $object->elapsed();
usleep(1);
$second = $object->elapsed(); // time since start still
// reset with a start call
$object->start();
$third = $object->elapsed(); // time since start call

// second should be greater than first
var_dump($second > $first);
// but third should be less than second
var_dump($third < $second);

// extended use case
$object = new foo();
$first = $object->elapsed();
usleep(1);
$second = $object->elapsed(); // time since start still
// reset with a start call
$object->start();
$third = $object->elapsed(); // time since start call

// second should be greater than first
var_dump($second > $first);
// but third should be less than second
var_dump($third < $second);

// error with wrong args
try {
	$object = new Timer();
    $object->elapsed('hello');
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
Glib\Timer::elapsed() expects exactly 0 parameters, 1 given
