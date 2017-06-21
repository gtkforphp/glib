--TEST--
Glib\Timer->start()
--SKIPIF--
<?php include __DIR__ . '/../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

use Glib\Timer;

class foo extends Timer{}

// Basic use case
$object = new Timer();
usleep(1);
$first = $object->elapsed();
$object->start(); // resets time to now
$second = $object->elapsed();
// second should be greater than first
var_dump($second < $first);

// extended use case
$object = new foo();
usleep(1);
$first = $object->elapsed();
$object->start(); // resets time to now
$second = $object->elapsed();
// second should be greater than first
var_dump($second < $first);

// error with wrong args
try {
	$object = new Timer();
    $object->start('hello');
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
bool(true)
bool(true)
Glib\Timer::start() expects exactly 0 parameters, 1 given
