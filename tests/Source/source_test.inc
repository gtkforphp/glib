<?php
if(PHP_VERSION_ID > 70100) {
    include __DIR__ . '/source_class.inc';
} else {
    include __DIR__ . '/source_class_old.inc';
}