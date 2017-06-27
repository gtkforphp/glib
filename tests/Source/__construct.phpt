--TEST--
Glib\Source->__construct()
--SKIPIF--
<?php include __DIR__ . '/../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);
use Glib\Main\Context;

include __DIR__ . '/source_test.inc';

$object = new test();

var_dump($object);

// error with wrong args
try {
    $object = new test('banana');
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(test)#%d (0) {
}
Glib\Source::__construct() expects exactly 0 parameters, 1 given
