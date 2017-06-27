<?php
use Glib\Source;

class test extends Source {
    public function prepare() : array { return [true, 0];}
    public function check() : bool { return true;}
    public function dispatch(callable $callback, array $args) : bool { return true;}
    public function finalize() : void { }
}