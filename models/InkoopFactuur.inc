<?php
/**
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * Represents an invoice from an upstream vendor.
 *
 * @property int         $id          Primary key ID of this invoice.
 * @property InkoopOrder $inkooporder The order that this invoice belongs to.
 * @property string      $betaaldatum Date when the payment was sent. YYYY-MM-DD.
 * @property string      $status      Current status of this invoice: received, paid, confirmed, …
 *
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */
class InkoopFactuur extends EatITModel {

  protected static $schema = array(
    'factuurnr' => 'id',
    'order' => 'link:InkoopOrder',
    'betaaldatum' => 'date',
    'status' => 'string:20',
  );

}