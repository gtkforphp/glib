<?php
use Glib\Source;

class test extends Source {
    public function prepare() : array { return [true, 0];}
    public function check() : bool { return true;}
    public function dispatch($callback, $args) : bool { return true;}
    public function finalize() { }
}

// class that will call prepare and check
class checksource extends Source{
    public function prepare() : array {return [false, -1];}
    public function check() : bool { echo 'calling check', PHP_EOL; return false;}
    public function dispatch($callback, $args) : bool { return false; }
    public function finalize() { }
}

class dispatchsource extends Source{
    public function prepare() : array {return [false, -1];}
    public function check() : bool { return true;}
    public function dispatch($callback, $args) : bool { echo 'doing dispatching', PHP_EOL; return false; }
    public function finalize() { }
}

// class that will ONLY call prepare
class preparesource extends Source{
    public function prepare() : array { echo 'calling prepare' . PHP_EOL; return [false, 0];}
    public function check() : bool { return false;}
    public function dispatch($callback, $args) : bool { return false; }
    public function finalize() { }
}

// class only care about finalize
class finalsource extends Source{
    public function prepare() : array { return [false, -1];}
    public function check() : bool { return false;}
    public function dispatch($callback, $args) : bool { return false; }
    public function finalize() { echo 'Calling finalize', PHP_EOL; }
}