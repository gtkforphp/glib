--TEST--
Glib\Source->prepare()
--SKIPIF--
<?php include __DIR__ . '/../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);
use Glib\Source;
use Glib\Main\Context;

include __DIR__ . '/source_test.inc';
$object = new preparesource();

// run prepare once in our loop
$context = new Context();
$object->attach($context);
$context->iteration(true);

$object->prepare();

// because prepare is implemented in PHPish, it won't error on too many args
?>
--EXPECT--
calling prepare
calling prepare
