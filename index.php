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

$router->add('installmaaltijd', 'GET', '/installmaaltijd', function () {
  global $db;
  $db->createTable('Maaltijd');
});

$router->add('install', 'GET', '/install', function () {
  global $db;
  $db->createTable('Artikel');
  $db->createTable('ArtikelOrder');
  $db->createTable('Ingredient');
  $db->createTable('InkoopFactuur');
  $db->createTable('InkoopOrder');
  $db->createTable('Klant');
  $db->createTable('Leverancier');
  $db->createTable('Maaltijd');
  $db->createTable('Order');
  $db->createTable('OrderRegel');
});

// testing
$router->dispatch(null, !empty($_SERVER['PATH_INFO']) ? $_SERVER['PATH_INFO'] : '/');
