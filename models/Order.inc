<?php
/**
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * Represents an order from a customer to Eat-IT.
 *
 * @property int    $id         Primary key ID of this order.
 * @property Klant  $klant      Customer that is sending this order.
 * @property string $datum      Date when this order was received.
 * @property string $bezorgtijd Time when this order should be at the customer's doorstep.
 * @property string $status     Current status of this order: received, cookin', completed, etc.
 *
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