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
class Klant extends Model {

  protected static $schema = array(
    'Klantnr' => 'id',
    'naam' => 'link:Order',
    'adres' => 'string:128',
    'postcode' => 'string:8',
    'plaats' => 'string:64',
    'telefoon' => 'string:20',
    'email' => 'string:128',
  );

}