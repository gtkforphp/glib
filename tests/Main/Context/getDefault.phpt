--TEST--
Glib\Main\Context::getDefault()
--SKIPIF--
<?php include __DIR__ . '/../../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

use Glib\Main\Context;

$object = Context::getDefault();
var_dump($object);
var_dump($object->isOwner());

// error with wrong args
try {
	$object = Context::getDefault('hello');
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Glib\Main\Context)#%d (0) {
}
bool(false)
Glib\Main\Context::getDefault() expects exactly 0 parameters, 1 given
