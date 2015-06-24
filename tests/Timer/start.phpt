--TEST--
Glib\Timer->start
--SKIPIF--
<?php if (!extension_loaded("glib")) print "skip"; ?>
--FILE--
<?php
use Glib\Timer;

class foo extends Timer{}
class bad extends Timer {
    public function __construct() {}
}

$object = new Timer();
$object->start();
echo $object->elapsed(), PHP_EOL;

$object = new foo();
$object->start();
echo $object->elapsed(), PHP_EOL;

$object = new bad();
$object->start();
echo $object->elapsed(), PHP_EOL;

?>
--EXPECTF--
%f
%f

Fatal error: Glib\Timer::start(): Internal object missing in bad class, you must call parent::__construct in extended classes in %s on line %d