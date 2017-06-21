--TEST--
Glib\Main\Context->iteration()
--SKIPIF--
<?php include __DIR__ . '/../../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

use Glib\Main\Context;

class foo extends Context {}

$context = new Context();
var_dump($context->iteration(true));

$context = new foo();
var_dump($context->iteration(true));

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
    $object->iteration([]);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
bool(false)
bool(false)
Glib\Main\Context::iteration() expects exactly 1 parameter, 2 given
Argument 1 passed to Glib\Main\Context::iteration() must be of the type boolean, array given
