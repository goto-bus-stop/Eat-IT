<?php

require 'include.inc';

session_start();

$router = Router::getInstance();

$db = new PDOConnector('mysql:host=localhost;dbname=eatit', 'root', '');
Model::useDB($db);

$router->add('index', 'GET', '/', 'IndexController#get');

$router->add('register', 'GET', '/register', 'LoginController#register');
$router->add('POST', '/register', 'LoginController#doRegister');

$router->add('order', 'GET', '/order/[klant_id]', 'OrderController#form');

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