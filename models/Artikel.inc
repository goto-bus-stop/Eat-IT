<?php
/**
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * TODO: write docs
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */
class Artikel extends EatITModel {

  protected static $schema = array(
    'artikelnr' => 'id',
    'naam' => 'string:64',
    'leverancier' => 'link:Leverancier',
    'voorraad' => 'int',
    'gereserveerd' => 'int',
    'besteld' => 'int',
    'prijs' => 'double',
    'verkoop' => 'bool'
  );

}