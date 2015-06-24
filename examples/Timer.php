<?php
// use the glib timer class
use Glib\Timer;

// create a timer object
$timer = new Timer();

// let's time some loops
for ($i = 1; $i <= 10000; $i++) {
    $foo = "I am $i";
}
echo 'Time elapsed was ' , $timer->elapsed(), PHP_EOL;

// same thing with foreach
$array = range(0, 10000);

// reset the timer to 0
$timer->reset();
foreach($array as $i) {
    $foo = "I am $i";
}
echo 'Time elapsed was ' , $timer->elapsed(), PHP_EOL;

// do both and get total time
$timer->start(); // this is equivalent to reset
for ($i = 1; $i <= 10000; $i++) {
    $foo = "I am $i";
}
// stop the timer and build the array
$timer->stop();
$array = range(0, 10000);
// continue the timer
$timer->continue();
foreach($array as $i) {
    $foo = "I am $i";
}

echo 'Time elapsed was ' , $timer->elapsed(), PHP_EOL;