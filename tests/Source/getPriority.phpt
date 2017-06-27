--TEST--
Glib\Source->getPriority()
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

// error with wrong args
try {
    $object->getPriority(false);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
int(0)
Glib\Source::getPriority() expects exactly 0 parameters, 1 given