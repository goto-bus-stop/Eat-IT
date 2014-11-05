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
class Order extends Model {

  protected static $schema = array(
    'OrderID' => 'id',
    'Klantnr' => 'link:Klant',
    'datum' => 'date',
    'bezorgtijd' => 'time',
    'status' => 'string:20',
  );

}