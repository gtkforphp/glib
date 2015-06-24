--TEST--
G\Enum object set handler;
--SKIPIF--
<?php
include __DIR__ . '/../../skipif.inc';
?>
--FILE--
<?php
use G\Enum as Enum;

class Fruit extends Enum {
    const Apple = 1;
    const Pear = 2;
    const Banana = 3;
}

$fruit = new Fruit(Fruit::Apple);
echo $fruit, PHP_EOL;
var_dump($fruit);

$fruit = Fruit::Pear;
echo $fruit, PHP_EOL;

$fruit = new Fruit(Fruit::Apple);
echo $fruit, PHP_EOL;

$fruit = 'Banana';
echo $fruit, PHP_EOL;

// bad value, bad
try {
     $fruit = 8;
} catch (UnexpectedValueException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECTF--
1
object(Fruit)#%d (2) {
  ["__elements"]=>
  array(3) {
    ["Apple"]=>
    int(1)
    ["Pear"]=>
    int(2)
    ["Banana"]=>
    int(3)
  }
  ["__value"]=>
  int(1)
}
2
1
3
Value provided is not a const in enum Fruit
= DONE =