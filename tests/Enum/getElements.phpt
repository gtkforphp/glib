--TEST--
G\Enum->getElements();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Enum as Enum;

class Fruit extends Enum {
    const Apple = 1;
    const Pear = 2;
}

$fruit = new Fruit(Fruit::Apple);
var_dump($fruit->getElements());

class Stupid extends Enum {
    const Apple = 'banana';
    const Pear = 'tootyfruity';
}

$rotten = new Stupid('Apple');
var_dump($rotten->getElements());

// too many args
try {
     $fruit->getElements(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECTF--
array(2) {
  ["Apple"]=>
  int(1)
  ["Pear"]=>
  int(2)
}

Warning: main(): Constant Apple is being cast to an integer in Enum subclass Stupid in %s on line %d

Warning: main(): Constant Pear is being cast to an integer in Enum subclass Stupid in %s on line %d
array(2) {
  ["Apple"]=>
  int(0)
  ["Pear"]=>
  int(0)
}
G\Enum::getElements() expects exactly 0 parameters, 1 given
= DONE =