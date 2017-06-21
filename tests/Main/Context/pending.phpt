--TEST--
Glib\Main\Context->pending()
--SKIPIF--
<?php include __DIR__ . '/../../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

use Glib\Main\Context;

class foo extends Context {}

// our context is empty so pending should always be false
$context = new Context();
var_dump($context->pending());

// our context is empty so pending should always be false
$context = new foo();
var_dump($context->pending());

// error with wrong count
try {
    $object = new Context();
    $object->pending(false);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
bool(false)
bool(false)
Glib\Main\Context::pending() expects exactly 0 parameters, 1 given
