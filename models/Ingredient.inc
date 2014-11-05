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
class Ingredient extends Model {

  protected static $schema = array(
    'ingedientID' => 'id',
    'maaltijdID' => 'link:InkoopOrder',
    'artikelnr' => 'link:InkoopOrder',
    'hoeveelheid' => 'int',
  );

}