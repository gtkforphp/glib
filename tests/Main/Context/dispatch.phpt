--TEST--
Glib\Main\Context->dispatch()
--SKIPIF--
<?php include __DIR__ . '/../../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

use Glib\Main\Context;

class foo extends Context {}

// doesn't do much,make sure no segfaulting
$context = new Context();
var_dump($context->dispatch());

$context = new foo();
var_dump($context->dispatch());

// error with wrong count
try {
    $object = new Context();
    $object->dispatch(false);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
NULL
NULL
Glib\Main\Context::dispatch() expects exactly 0 parameters, 1 given
