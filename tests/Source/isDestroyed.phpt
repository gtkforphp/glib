--TEST--
Glib\Source->isDestroyed()
--SKIPIF--
<?php include __DIR__ . '/../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);
use Glib\Source;
use Glib\Main\Context;

include __DIR__ . '/source_test.inc';

$object = new test();

$context = new Context();
$object->attach($context);
var_dump($object->isDestroyed());
$object->destroy();
var_dump($object->isDestroyed());

// error with wrong args
try {
    $object->isDestroyed(false);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
bool(false)
bool(true)
Glib\Source::isDestroyed() expects exactly 0 parameters, 1 given