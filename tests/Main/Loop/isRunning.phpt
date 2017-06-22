--TEST--
Glib\Main\Loop->isRunning()
--SKIPIF--
<?php include __DIR__ . '/../../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

use Glib\Main\Context;
use Glib\Main\Loop;

class foo extends Loop {}

// doesn't do much,make sure no segfaulting
$context = new Context();
$object = new Loop($context, false);
var_dump($object->isRunning());

$object = new foo($context, true);
var_dump($object->isRunning());

// error with wrong count
try {
    $object = new Loop($context, false);
    $object->isRunning(false);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
bool(false)
bool(true)
Glib\Main\Loop::isRunning() expects exactly 0 parameters, 1 given
