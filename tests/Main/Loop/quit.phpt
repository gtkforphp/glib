--TEST--
Glib\Main\Loop->quit()
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
var_dump($object->quit());

$object = new foo($context, true);
var_dump($object->quit());

// error with wrong countf
try {
    $object = new Loop($context, false);
    $object->quit(false);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
NULL
NULL
Glib\Main\Loop::quit() expects exactly 0 parameters, 1 given
