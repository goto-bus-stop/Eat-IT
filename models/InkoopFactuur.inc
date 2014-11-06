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
class InkoopFactuur extends EatITModel {

  protected static $schema = array(
    'factuurnr' => 'id',
    'order' => 'link:InkoopOrder',
    'betaaldatum' => 'date',
    'status' => 'string:20',
  );

}