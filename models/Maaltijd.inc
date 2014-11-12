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
class Maaltijd extends EatITModel {

  protected static $schema = array(
    'maaltijdnr' => 'id',
    'naam' => 'string:64',
    'omschrijving' => 'string:255',
    'prijs' => 'double',
    'beschikbaar' => 'int',
    'daghap' => 'bool',
    'img' => 'string:128',
    'type' => 'string:5' // vlees/vis/vega
  );

}