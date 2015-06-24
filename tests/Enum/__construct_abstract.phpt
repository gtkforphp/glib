--TEST--
G\Enum is abstract
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Enum as Enum;

$item = new Enum;

?>
--EXPECTF--
Fatal error: Cannot instantiate abstract class G\Enum in %s on line %d
