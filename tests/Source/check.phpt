--TEST--
Glib\Source->check()
--SKIPIF--
<?php include __DIR__ . '/../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);
use Glib\Source;
use Glib\Main\Context;

// class that will call prepare and check
class checksource extends Source{
public function prepare() : array {return [false, -1];}
public function check() : bool { echo 'calling check', PHP_EOL; return false;}
public function dispatch(callable $callback, array $args) : bool { return false; }
public function finalize() : void { }
}
$object = new checksource();

// run prepare once in our loop
$context = new Context();
$object->attach($context);
$context->iteration(true);

$object->check();

// because prepare is implemented in PHPish, it won't error on too many args
?>
--EXPECT--
calling check
calling check
