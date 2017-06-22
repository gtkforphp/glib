--TEST--
Glib\Main\Loop->__construct
--SKIPIF--
<?php include __DIR__ . '/../../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);

use Glib\Main\Loop;
use Glib\Main\Context;

class foo extends Loop {}
class bad extends Loop { public function __construct() {} }

$context = new Context();

$object = new Loop($context, true);
var_dump($object);

$object = new foo($context, true);
var_dump($object);

// bad constructor
try {
	$object = new bad($context, true);
	$object->run();
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}

// error with wrong args
try {
	$object = new Loop();
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
// error with wrong args
try {
	$object = new Loop($context);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
// error with wrong args
try {
	$object = new Loop($context, true, false);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
// error with wrong type
try {
	$object = new Loop([], true);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
// error with wrong type
try {
	$object = new Loop($context, []);
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Glib\Main\Loop)#%d (0) {
}
object(foo)#%d (0) {
}
The Glib\Main\Loop object has not been correctly initialized by its constructor
Glib\Main\Loop::__construct() expects exactly 2 parameters, 0 given
Glib\Main\Loop::__construct() expects exactly 2 parameters, 1 given
Glib\Main\Loop::__construct() expects exactly 2 parameters, 3 given
Argument 1 passed to Glib\Main\Loop::__construct() must be an instance of Glib\Main\Context, array given
Argument 2 passed to Glib\Main\Loop::__construct() must be of the type boolean, array given
