--TEST--
Glib\Source->finalize()
--SKIPIF--
<?php include __DIR__ . '/../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);
use Glib\Source;
use Glib\Main\Context;

// class only care about finalize
class finalsource extends Source{
public function prepare() : array { return [false, -1];}
public function check() : bool { return false;}
public function dispatch(callable $callback, array $args) : bool { return false; }
public function finalize() { echo 'Calling finalize', PHP_EOL; }
}
$object = new finalsource();
$object->finalize();


// run prepare once in our loop
$context = new Context();
$object->attach($context);
$context->iteration(true);

$object->finalize(); // this will never run because source is dead by here

// because prepare is implemented in PHPish, it won't error on too many args
?>
--EXPECT--
Calling finalize
Calling finalize
