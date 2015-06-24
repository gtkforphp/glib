--TEST--
glib class listing
--SKIPIF--
<?php
include __DIR__ . '/skipif.inc';
?>
--FILE--
<?php
$ext = new ReflectionExtension('glib');
var_dump($ext->getClassNames());
?>
= DONE =
--EXPECT--
array(5) {
  [0]=>
  string(6) "G\Enum"
  [1]=>
  string(8) "G\Struct"
  [2]=>
  string(11) "G\Exception"
  [3]=>
  string(8) "G\String"
  [4]=>
  string(9) "G\Unicode"
}
= DONE =