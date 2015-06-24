--TEST--
Glib\Bookmarkfile->__construct
--SKIPIF--
<?php if (!extension_loaded("glib")) print "skip"; ?>
--FILE--
<?php
use Glib\Bookmarkfile;

class foo extends Bookmarkfile{}

$object = new Bookmarkfile();
var_dump($object);

$object = new foo();
var_dump($object);
?>
--EXPECTF--
object(Glib\Bookmarkfile)#%d (0) {
}
object(foo)#%d (0) {
}