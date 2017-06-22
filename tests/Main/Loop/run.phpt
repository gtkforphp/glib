--TEST--
Glib\Main\Loop->run() - TODO: finish when timeout is available
--SKIPIF--
<?php include __DIR__ . '/../../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

use Glib\Main\Context;
use Glib\Main\Loop;

class foo extends Loop {}

$context = new Context();
$object = new Loop($context, true);
//var_dump($object->run());

$object = new foo($context, true);
//var_dump($object->run());

// error with wrong count
try {
    $object = new Loop($context, false);
    $object->run(false);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
Glib\Main\Loop::run() expects exactly 0 parameters, 1 given