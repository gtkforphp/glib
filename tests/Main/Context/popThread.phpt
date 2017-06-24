--TEST--
Glib\Main\Context->popThread()
--SKIPIF--
<?php include __DIR__ . '/../../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

use Glib\Main\Context;

class foo extends Context {}

$context = new Context();
$context->pushThread();

var_dump($context->popThread());

$context = new foo();
$context->pushThread();
var_dump($context->popThread());

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