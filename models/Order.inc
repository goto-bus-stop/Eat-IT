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
class Order extends EatITModel {

  protected static $schema = array(
    'ordernr'=> 'id',
    'klant' => 'link:Klant',
    'datum' => 'date',
    'bezorgtijd' => 'time',
    'status' => 'string:20',
  );

}