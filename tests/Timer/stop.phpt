--TEST--
Glib\Timer->stop
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
$object->stop();
echo $object->elapsed(), PHP_EOL;

$object = new foo();
$object->stop();
echo $object->elapsed(), PHP_EOL;

$object = new bad();
$object->stop();
echo $object->elapsed(), PHP_EOL;

?>
--EXPECTF--
%f
%f

Fatal error: Glib\Timer::stop(): Internal object missing in bad class, you must call parent::__construct in extended classes in %s on line %d