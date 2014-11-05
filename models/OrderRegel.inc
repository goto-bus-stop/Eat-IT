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
class OrderRegel extends Model {

  protected static $schema = array(
    'OrderregelID' => 'id',
    'ordernr' => 'link:Order',
    'type' => 'string:10',
    'artikelmaaltijdID' => 'ID',//TODO: HOE?
  );

}