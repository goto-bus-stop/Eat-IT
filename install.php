<?php

require 'include.inc';

$db = new MineTurtle\Database\PDOConnector('mysql:host=localhost;dbname=eatit', 'root', '');
MineTurtle\Model::useDB($db);

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

// artikelen
$a = array();
$a[] = array (
  'artikelnr' => '1',
  'naam' => 'Test',
  'leverancier' => NULL,
  'voorraad' => '10',
  'gereserveerd' => NULL,
  'besteld' => NULL,
  'prijs' => '100',
  'verkoop' => '1',
);
$a[] = array (
  'artikelnr' => '2',
  'naam' => 'niet verkoop',
  'leverancier' => NULL,
  'voorraad' => NULL,
  'gereserveerd' => NULL,
  'besteld' => NULL,
  'prijs' => '43',
  'verkoop' => '0',
);
$a[] = array (
  'artikelnr' => '3',
  'naam' => 'Tilapiafilet',
  'leverancier' => NULL,
  'voorraad' => '27',
  'gereserveerd' => '0',
  'besteld' => '0',
  'prijs' => '4.15',
  'verkoop' => '0',
);
$a[] = array (
  'artikelnr' => '4',
  'naam' => 'Tortilla',
  'leverancier' => NULL,
  'voorraad' => '166',
  'gereserveerd' => '0',
  'besteld' => '0',
  'prijs' => '0.1',
  'verkoop' => '0',
);
$a[] = array (
  'artikelnr' => '5',
  'naam' => 'Chipotle-adobosaus',
  'leverancier' => NULL,
  'voorraad' => '78',
  'gereserveerd' => '0',
  'besteld' => '0',
  'prijs' => '0.3',
  'verkoop' => '0',
);
$a[] = array (
  'artikelnr' => '6',
  'naam' => 'IJsbergsla 100g',
  'leverancier' => NULL,
  'voorraad' => '254',
  'gereserveerd' => '0',
  'besteld' => '0',
  'prijs' => '0.7',
  'verkoop' => '0',
);
$a[] = array (
  'artikelnr' => '7',
  'naam' => 'Komkommer',
  'leverancier' => NULL,
  'voorraad' => '70',
  'gereserveerd' => '0',
  'besteld' => '0',
  'prijs' => '1.3',
  'verkoop' => '0',
);
$a[] = array (
  'artikelnr' => '8',
  'naam' => 'Tomaat',
  'leverancier' => NULL,
  'voorraad' => '120',
  'gereserveerd' => '0',
  'besteld' => '0',
  'prijs' => '0.2',
  'verkoop' => '0',
);

foreach ($a as $x) {
  $b = new Artikel($x);
  $b->save();
}

// Ingredienten
$i = array();
$i[] = array (
  'ingedientnr' => '1',
  'maaltijd' => '2',
  'artikel' => '3',
  'hoeveelheid' => '1',
);
$i[] = array (
  'ingedientnr' => '2',
  'maaltijd' => '2',
  'artikel' => '4',
  'hoeveelheid' => '1',
);
$i[] = array (
  'ingedientnr' => '3',
  'maaltijd' => '2',
  'artikel' => '5',
  'hoeveelheid' => '2',
);
$i[] = array (
  'ingedientnr' => '4',
  'maaltijd' => '3',
  'artikel' => '6',
  'hoeveelheid' => '3',
);
$i[] = array (
  'ingedientnr' => '5',
  'maaltijd' => '3',
  'artikel' => '7',
  'hoeveelheid' => '1',
);
$i[] = array (
  'ingedientnr' => '6',
  'maaltijd' => '3',
  'artikel' => '8',
  'hoeveelheid' => '2',
);

foreach ($i as $x) {
  $b = new Ingredient($x);
  $b->save();
}

// Maaltijden
$m = array();
$m[] = array (
  'maaltijdnr' => '1',
  'naam' => 'maaltijd',
  'prijs' => '20.34',
  'beschikbaar' => '7',
  'daghap' => '0',
  'img' => '',
);
$m[] = array (
  'maaltijdnr' => '2',
  'naam' => 'Gegrilde Vistaco met Chipotle/limoen-dressing',
  'prijs' => '12.99',
  'beschikbaar' => '20',
  'daghap' => '0',
  'img' => '',
);
$m[] = array (
  'maaltijdnr' => '3',
  'naam' => '"Tao Lin"-salade',
  'prijs' => '5',
  'beschikbaar' => '20',
  'daghap' => '0',
  'img' => '',
);
$m[] = array (
  'maaltijdnr' => '4',
  'naam' => '	Spinazie met zalm',
  'prijs' => '8.45',
  'beschikbaar' => '1',
  'daghap' => '0',
  'img' => 'spinazie.jpg',
);
$m[] = array (
  'maaltijdnr' => '5',
  'naam' => 'Broccoli met amandelen',
  'prijs' => '6.7',
  'beschikbaar' => '1',
  'daghap' => '0',
  'img' => 'broccoli.jpg',
);

foreach ($m as $x) {
  $b = new Maaltijd($x);
  $b->save();
}