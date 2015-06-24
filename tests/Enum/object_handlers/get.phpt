--TEST--
G\Enum object get handler;
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
}

$fruit1 = new Fruit(Fruit::Apple);
$fruit2 = new Fruit(Fruit::Pear);

var_dump($fruit1 + $fruit2);
?>
= DONE =
--EXPECTF--
int(3)
= DONE =