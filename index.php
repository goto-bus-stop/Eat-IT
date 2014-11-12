<?php

require 'include.inc';

session_start();

$router = MineTurtle\Router\Router::getInstance();

$db = new MineTurtle\Database\PDOConnector('mysql:host=localhost;dbname=eatit', 'root', '');
MineTurtle\Model::useDB($db);

$router->add('index',    'GET', '/', 'IndexController#get');

$router->add('register', 'GET',  '/register', 'LoginController#register');
$router->add(            'POST', '/register', 'LoginController#doRegister');

$router->add('order', 'GET',  '/order/[klant_id]', 'OrderController#form');
$router->add(         'POST', '/order/[klant_id]', 'OrderController#placeOrder');

$router->add(                      'GET', '/maaltijden',                         'MaaltijdController#get');
$router->add('maaltijd',           'GET', '/maaltijden/[maaltijd_id]',           'MaaltijdController#show');
$router->add('maaltijd_bestellen', 'GET', '/maaltijden/[maaltijd_id]/bestellen', 'MaaltijdController#bestelling');

// testing
$router->dispatch(null, !empty($_SERVER['PATH_INFO']) ? $_SERVER['PATH_INFO'] : '/');
