--TEST--
Glib\Source\Timeout->dispatch()
--SKIPIF--
<?php include __DIR__ . '/../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);
use Glib\Source\Timeout;

$object = new Timeout(6);

// TODO: this doesn't quite work yet ...
$object->dispatch(null, null);

?>
--EXPECT--
build a GSourceFunc from args sent
