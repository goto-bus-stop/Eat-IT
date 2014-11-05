<?php

require 'include.inc';

$router = Router::getInstance();

$router->add('GET', '/', 'IndexController#get');

// testing
$router->dispatch('GET', '/');