--TEST--
Glib\Source\Timeout->prepare()
--SKIPIF--
<?php include __DIR__ . '/../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);
use Glib\Source\Timeout;

$object = new Timeout(5);

var_dump($object->prepare());
?>
--EXPECT--
array(2) {
  [0]=>
  bool(false)
  [1]=>
  int(-1)
}
