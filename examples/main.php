<?php
use \Glib\Main;
use \Glib\Main\Context;
use \Glib\Source;

// Source is an abstract class, you must extend it and implement the four abstract functions
class Mysource extends Source {
    
}

$source = new Mysource();
var_dump($source);

$context = new Context();
var_dump($context);

$context = Context::getDefault();
var_dump($context);

var_dump($context->iteration());
// this is the same as doing iteration on Context::getDefault();
var_dump(Main::iteration());

var_dump($context->pending());
// this is the same as doing pending on Context::getDefault();
var_dump(Main::pending());

//wakeup only works on a context object
var_dump($context->wakeup());

//prepare only works on a context object
var_dump($context->prepare());