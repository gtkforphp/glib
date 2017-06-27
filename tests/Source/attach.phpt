--TEST--
Glib\Source->attach()
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
$id = $object->attach($context);
var_dump($id);

// can't attach after destroy
$object->destroy();
// error with wrong args
try {
    $object->attach($context);
} catch (RuntimeException $e) {
	echo $e->getMessage(), PHP_EOL;
}

// error with wrong args
try {
    $object->attach(false);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
// error with arg count
try {
    $object->attach($context, false);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
int(1)
Source has been destroyed
Argument 1 passed to Glib\Source::attach() must be an instance of Glib\Main\Context, boolean given
Glib\Source::attach() expects exactly 1 parameter, 2 given