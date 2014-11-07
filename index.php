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