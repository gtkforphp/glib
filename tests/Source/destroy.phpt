--TEST--
Glib\Source->destroy()
--SKIPIF--
<?php include __DIR__ . '/../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);
use Glib\Source;

include __DIR__ . '/source_test.inc';

$object = new test();

$object->destroy();

// error with wrong args
try {
    $object->destroy(false);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
Glib\Source::destroy() expects exactly 0 parameters, 1 given