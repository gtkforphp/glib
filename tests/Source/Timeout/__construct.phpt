--TEST--
Glib\Source\Timeout->__construct()
--SKIPIF--
<?php include __DIR__ . '/../skipif.inc'; ?>
--FILE--
<?php
declare(strict_types=1);
use Glib\Main\Context;
use Glib\Source\Timeout;

$object = new Timeout(5);

var_dump($object);

// error with wrong args
try {
    $object = new Timeout('banana');
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
// error with wrong args
try {
    $object = new Timeout(5, 'banana');
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
class foo extends Timeout {
    public function __construct(int $interval) {}
}

// purposely fail a bad extended class
try {
    $bad = new foo(5);
    $bad->getPriority();
} catch (TypeError $e) {
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Glib\Source\Timeout)#%d (0) {
}
Argument 1 passed to Glib\Source\Timeout::__construct() must be of the type integer, string given
Glib\Source\Timeout::__construct() expects exactly 1 parameter, 2 given
The Glib\Source object has not been correctly initialized by its constructor
