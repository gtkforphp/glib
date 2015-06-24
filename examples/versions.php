<?php

// print out a string for the current runtime library version
printf('Our current Glib version runtime is %d.%d.%d', Glib::major_version, Glib::minor_version, Glib::micro_version);

echo PHP_EOL;

// print out a string for the current compiled against library version
printf('Our extension was compiled against %d.%d.%d', Glib::MAJOR_VERSION, Glib::MINOR_VERSION, Glib::MICRO_VERSION);

echo PHP_EOL;

// Check that our runtime library is compatible with our compiled library
if (Glib::checkVersion(Glib::major_version, Glib::minor_version, Glib::micro_version)) {
    echo 'The runtime version is compatible with the compiled version';
} else {
    echo 'The runtime version is not compatible with the compiled version';
}

echo PHP_EOL;

// Check that our runtime library has 2.20 features
if($error = Glib::checkRuntimeVersion(2, 20)) {
    echo 'The runtime version does not have 2.20 features ' . $error;
} else {
    echo 'The runtime version has 2.20 features';
}