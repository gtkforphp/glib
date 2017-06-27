--TEST--
Glib\Source->setPriority()
--SKIPIF--
<?php include __DIR__ . '/../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);
use Glib\Source;
use Glib\Main\Context;

include __DIR__ . '/source_test.inc';

$object = new test();

var_dump($object->getPriority());
$object->setPriority(3);
var_dump($object->getPriority());

// error with wrong args
try {
    $object->setPriority(1, false);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}

// error with wrong args
try {
    $object->setPriority('sucker');
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
int(0)
int(3)
Glib\Source::setPriority() expects exactly 1 parameter, 2 given
Argument 1 passed to Glib\Source::setPriority() must be of the type integer, string given