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
class Maaltijd extends Model {

  protected static $schema = array(
    'maaltijdID' => 'id',
    'naam' => 'string:64',
    'prijs' => 'double',
    'beschikbaar' => 'int',
  );

}