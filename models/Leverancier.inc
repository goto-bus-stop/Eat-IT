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
class Leverancier extends Model {

  protected static $schema = array(
    'leveranciernr' => 'id',
    'naam' => 'string:64',
    'adres' => 'string:128',
    'postcode' => 'string:8',
    'plaats' => 'string:64',
    'telefoon' => 'string:20',
  );

}