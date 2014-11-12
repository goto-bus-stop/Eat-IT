<?php
/**
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * Represents an "Artikel", i.e. a physical item in storage. Some can be sold straight
 * away and others are ingredients for full meals.
 *
 * @property int         $id          Primary key ID of this Artikel.
 * @property string      $naam        Item name.
 * @property Leverancier $leverancier Item vendor.
 * @property int         $voorraad    Amount of items currently in stock.
 * @property int         $besteld     Amount of items that have been ordered.
 * @property double      $prijs       Cost of one unit of this item.
 * @property bool        $verkoop     Whether this item is for sale as is.
 *
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