--TEST--
Glib\Source\Timeout->check()
--SKIPIF--
<?php include __DIR__ . '/../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);
use Glib\Source\Timeout;

$object = new Timeout(5);

var_dump($object->check());

?>
--EXPECT--
bool(false)