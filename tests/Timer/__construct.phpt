--TEST--
Glib\Timer->__construct
--SKIPIF--
<?php if (!extension_loaded("glib")) print "skip"; ?>
--FILE--
<?php
use Glib\Timer;

class foo extends Timer{}

$object = new Timer();
var_dump($object);

$object = new foo();
var_dump($object);
?>
--EXPECTF--
object(Glib\Timer)#%d (0) {
}
object(foo)#%d (0) {
}