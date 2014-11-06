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
class InkoopOrder extends EatITModel {

  protected static $schema = array(
    'ordernr' => 'id',
    'leveranciernr' => 'link:Leverancier',
    'datum' => 'date',
    'status' => 'string:20',
  );

}