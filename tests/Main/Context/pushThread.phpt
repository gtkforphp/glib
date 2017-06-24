--TEST--
Glib\Main\Context->pushThread()
--SKIPIF--
<?php include __DIR__ . '/../../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

use Glib\Main\Context;

class foo extends Context {}

$context = new Context();
var_dump($context->pushThread());

$context = new foo();
var_dump($context->pushThread());

// error with wrong type
try {
    $object = new Context();
    $object->PushThread('foo');
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
NULL
NULL
Glib\Main\Context::pushThread() expects exactly 0 parameters, 1 given