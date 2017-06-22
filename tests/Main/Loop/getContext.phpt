--TEST--
Glib\Main\Loop->getContext()
--SKIPIF--
<?php include __DIR__ . '/../../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

use Glib\Main\Context;
use Glib\Main\Loop;

class foo extends Loop {}
class ricky extends Context {}

$context = new Context();

$object = new Loop($context, true);
var_dump($object->getContext() == $context);

unset($context);

var_dump($object->getContext() instanceof Context);

$context = new ricky();
$object = new Loop($context, true);
var_dump($object->getContext() == $context);

// error with wrong count
try {
    $object = new Loop();
    $object->getContext(false);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
Glib\Main\Loop::__construct() expects exactly 2 parameters, 0 given
