--TEST--
Glib\Main\Context->iteration
--SKIPIF--
<?php include __DIR__ . '/../../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

use Glib\Main\Context;

class foo extends Context {}

$object = new Context();
var_dump($object->iteration('banana'));

// error with wrong count
try {
    $object = new Context();
    $object->iteration(false, false);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}

// error with wrong type
try {
    $object = new Context();
    $object->iteration('banana');
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
Glib\Main\Context::iteration() expects exactly 1 parameter, 2 given
