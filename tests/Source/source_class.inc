<?php
use Glib\Source;

class test extends Source {
    public function prepare() : array { return [true, 0];}
    public function check() : bool { return true;}
    public function dispatch(?callable $callback, ?array $args) : bool { return true;}
    public function finalize() : void { }
}

// class that will call prepare and check
class checksource extends Source{
    public function prepare() : array {return [false, -1];}
    public function check() : bool { echo 'calling check', PHP_EOL; return false;}
    public function dispatch(?callable $callback, ?array $args) : bool { return false; }
    public function finalize() : void { }
}

// class that will ONLY call prepare
class preparesource extends Source{
    public function prepare() : array { echo 'calling prepare' . PHP_EOL; return [false, 0];}
    public function check() : bool { return false;}
    public function dispatch(?callable $callback, ?array $args) : bool { return false; }
    public function finalize() : void { }
}

// class only care about finalize
class finalsource extends Source{
    public function prepare() : array { return [false, -1];}
    public function check() : bool { return false;}
    public function dispatch(?callable $callback, ?array $args) : bool { return false; }
    public function finalize() : void { echo 'Calling finalize', PHP_EOL; }
}

class dispatchsource extends Source{
    public function prepare() : array {return [false, -1];}
    public function check() : bool { return true;}
    public function dispatch(?callable $callback, ?array $args) : bool { echo 'doing dispatching', PHP_EOL; return false; }
    public function finalize() : void { }
}