--TEST--
Glib\Main\Context->isOwner()
--SKIPIF--
<?php include __DIR__ . '/../../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

use Glib\Main\Context;

class foo extends Context {}

// because we haven't aquired/set thread default we do not own it
$context = new Context();
var_dump($context->isOwner());

$context = new foo();
var_dump($context->isOwner());

// error with wrong count
try {
    $object = new Context();
    $object->isOwner(false);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
bool(false)
bool(false)
Glib\Main\Context::isOwner() expects exactly 0 parameters, 1 given
