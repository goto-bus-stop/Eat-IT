<?php

require 'include.inc';

$db = new MineTurtle\Database\PDOConnector('mysql:host=localhost;dbname=eatit', 'root', '');
MineTurtle\Model::useDB($db);

// tables

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

// data

$a = new Artikel(array (
  'naam' => 'Test',
  'leverancier' => NULL,
  'voorraad' => '10',
  'gereserveerd' => NULL,
  'besteld' => NULL,
  'prijs' => '100',
  'verkoop' => '1',
));
$a->save();

$a = new Artikel(array (
  'naam' => 'niet verkoop',
  'leverancier' => NULL,
  'voorraad' => NULL,
  'gereserveerd' => NULL,
  'besteld' => NULL,
  'prijs' => '43',
  'verkoop' => '0',
));
$a->save();

$a = new Artikel(array (
  'naam' => 'Tilapiafilet',
  'leverancier' => NULL,
  'voorraad' => '27',
  'gereserveerd' => '0',
  'besteld' => '0',
  'prijs' => '4.15',
  'verkoop' => '0',
));
$a->save();

$a = new Artikel(array (
  'naam' => 'Tortilla',
  'leverancier' => NULL,
  'voorraad' => '166',
  'gereserveerd' => '0',
  'besteld' => '0',
  'prijs' => '0.1',
  'verkoop' => '0',
));
$a->save();

$a = new Artikel(array (
  'naam' => 'Chipotle-adobosaus',
  'leverancier' => NULL,
  'voorraad' => '78',
  'gereserveerd' => '0',
  'besteld' => '0',
  'prijs' => '0.3',
  'verkoop' => '0',
));
$a->save();

$a = new Artikel(array (
  'naam' => 'IJsbergsla 100g',
  'leverancier' => NULL,
  'voorraad' => '254',
  'gereserveerd' => '0',
  'besteld' => '0',
  'prijs' => '0.7',
  'verkoop' => '0',
));
$a->save();

$a = new Artikel(array (
  'naam' => 'Komkommer',
  'leverancier' => NULL,
  'voorraad' => '70',
  'gereserveerd' => '0',
  'besteld' => '0',
  'prijs' => '1.3',
  'verkoop' => '0',
));
$a->save();

$a = new Artikel(array (
  'naam' => 'Tomaat',
  'leverancier' => NULL,
  'voorraad' => '120',
  'gereserveerd' => '0',
  'besteld' => '0',
  'prijs' => '0.2',
  'verkoop' => '0',
));
$a->save();

$a = new Maaltijd(array (
  'naam' => 'Frisse Vistaco',
  'omschrijving' => 'Gegrilde Vistaco met Chipotle/limoen-dressing',
  'prijs' => '12.99',
  'beschikbaar' => '20',
  'daghap' => '1',
  'img' => '2.jpg',
  'type' => 'vis',
));
$a->save();

$a = new Maaltijd(array (
  'naam' => 'Spinazie met zalm',
  'omschrijving' => 'Het is spinazie, en het is zalm.',
  'prijs' => '8.45',
  'beschikbaar' => '1',
  'daghap' => '0',
  'img' => 'spinazie.jpg',
  'type' => 'vis',
));
$a->save();

$a = new Maaltijd(array (
  'naam' => 'Broccoli met amandelen',
  'omschrijving' => 'Niemand houdt van broccoli. Maar met amandelen is het niet eens zo heel erg.',
  'prijs' => '6.7',
  'beschikbaar' => '1',
  'daghap' => '0',
  'img' => 'broccoli.jpg',
  'type' => 'vega',
));
$a->save();

$a = new Ingredient(array (
  'ingedientnr' => '1',
  'maaltijd' => '2',
  'artikel' => '3',
  'hoeveelheid' => '1',
));
$a->save();

$a = new Ingredient(array (
  'ingedientnr' => '2',
  'maaltijd' => '2',
  'artikel' => '4',
  'hoeveelheid' => '1',
));
$a->save();

$a = new Ingredient(array (
  'ingedientnr' => '3',
  'maaltijd' => '2',
  'artikel' => '5',
  'hoeveelheid' => '2',
));
$a->save();

$a = new Ingredient(array (
  'ingedientnr' => '4',
  'maaltijd' => '3',
  'artikel' => '6',
  'hoeveelheid' => '3',
));
$a->save();

$a = new Ingredient(array (
  'ingedientnr' => '5',
  'maaltijd' => '3',
  'artikel' => '7',
  'hoeveelheid' => '1',
));
$a->save();

$a = new Ingredient(array (
  'ingedientnr' => '6',
  'maaltijd' => '3',
  'artikel' => '8',
  'hoeveelheid' => '2',
));
$a->save();

