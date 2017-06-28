--TEST--
Glib\Source\Timeout->finalize()
--SKIPIF--
<?php include __DIR__ . '/../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);
use Glib\Source\Timeout;

$object = new Timeout(5);

// this doesn't DO anything but you can call it :)
var_dump($object->finalize());
?>
--EXPECT--
NULL
