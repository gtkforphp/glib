--TEST--
Glib\Timer->continue
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
$object->continue();
$object->stop();
$object->continue();
echo $object->elapsed(), PHP_EOL;

$object = new foo();
$object->continue();
$object->stop();
$object->continue();
echo $object->elapsed(), PHP_EOL;

$object = new bad();
$object->continue();

?>
--EXPECTF--

Warning: Glib\Timer::continue(): Cannot continue a Timer that has not been stopped in %s on line %d
%f

Warning: Glib\Timer::continue(): Cannot continue a Timer that has not been stopped in %s on line %d
%f

Fatal error: Glib\Timer::continue(): Internal object missing in bad class, you must call parent::__construct in extended classes in %s on line %d