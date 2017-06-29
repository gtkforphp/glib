--TEST--
Glib\Main\Context->findSourceById()
--SKIPIF--
<?php include __DIR__ . '/../../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

use Glib\Main\Context;
use Glib\Source\Timeout;

// super easy case, does not exist
// "unknown" sources will also show up here
// that would be REALLY hard to do though
$context = new Context();
var_dump($context->findSourceById(5));

// easy case = a PHP custom source
include __DIR__ . '/../../Source/source_test.inc';

$object = new test();
$id = $object->attach($context);
$source = $context->findSourceById($id);
var_dump($object == $source);

// our custom subclasses
$object = new Timeout(4);
$id = $object->attach($context);
$source = $context->findSourceById($id);
var_dump($object == $source);
?>
--EXPECT--
NULL
bool(true)
bool(true)
