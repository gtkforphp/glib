<?php
use G\Enum;

class Fruit extends Enum {
    const Apple = 1;
    const Pear = 2;
    const Banana = 3;
    const Orange = 4;
    const Peach = 5;
}

class Exotic extends Fruit {
    const Papaya = 1;
    const Starfruit = 6;
    const Mango = 7;
}

$lunch1 = new Fruit('Apple');
$lunch2 = new Fruit(Fruit::Orange);

$dinner1 = new Exotic('Mango');
$dinner2 = new Exotic(Exotic::Papaya);

echo $lunch1, PHP_EOL;
echo $lunch2->getName(), PHP_EOL;

echo $dinner1, PHP_EOL;
echo $dinner2->getName(), PHP_EOL;

var_dump($lunch1->getElements());

var_dump($lunch1);
var_dump($dinner2);