--TEST--
Glib\Timer->stop
--SKIPIF--
<?php include __DIR__ . '/../skipif.inc'; ?>
--FILE--
<?php
use Glib\Timer;

class foo extends Timer{}

// Basic use case tops timing
$object = new Timer();
$object->stop();
$first = $object->elapsed();
usleep(1);
$second = $object->elapsed();
var_dump($first == $second); // only showing start -> stop time
$object->stop(); // new mark
$third = $object->elapsed();
var_dump($second < $third);

// extedned use case tops timing
$object = new foo();
$object->stop();
$first = $object->elapsed();
usleep(1);
$second = $object->elapsed();
var_dump($first == $second); // only showing start -> stop time
$object->stop(); // new mark
$third = $object->elapsed();
var_dump($second < $third);


// error with wrong args
try {
    $object = new Timer();
    $object->stop('hello');
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}

?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
Glib\Timer::stop() expects exactly 0 parameters, 1 given
