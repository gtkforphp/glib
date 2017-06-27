--TEST--
Glib\Source->prepare()
--SKIPIF--
<?php include __DIR__ . '/../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);
use Glib\Source;
use Glib\Main\Context;

// class that will ONLY call prepare
class preparesource extends Source{
public function prepare() : array { echo 'calling prepare' . PHP_EOL; return [false, 0];}
public function check() : bool { return false;}
public function dispatch(callable $callback, array $args) : bool { return false; }
public function finalize() : void { }
}
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
