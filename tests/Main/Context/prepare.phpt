--TEST--
Glib\Main\Context->prepare()
--SKIPIF--
<?php include __DIR__ . '/../../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

use Glib\Main\Context;

class foo extends Context {}

// this does an acquire, prepare, release cycle
$context = new Context();
var_dump($context->prepare());

$context = new foo();
var_dump($context->prepare());

// error with wrong count
try {
    $object = new Context();
    $object->prepare(false);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
array(2) {
  [0]=>
  bool(false)
  [1]=>
  int(%d)
}
array(2) {
  [0]=>
  bool(false)
  [1]=>
  int(%d)
}
Glib\Main\Context::prepare() expects exactly 0 parameters, 1 given
