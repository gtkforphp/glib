<?php
var_dump(PHP_VERSION_ID);
var_dump(PHP_VERSION_ID > 701000);
if(PHP_VERSION_ID > 701000) {
    include __DIR__ . '/source_class.inc';
} else {
    include __DIR__ . '/source_class_old.inc';
}