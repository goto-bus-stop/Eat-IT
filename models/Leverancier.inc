<?php
/**
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * Represents a vendor.
 *
 * @property int    $id       Primary key ID of this vendor.
 * @property string $naam     Vendor name.
 * @property string $adres    Vendor office address.
 * @property string $postcode Vendor's zip/postal code.
 * @property string $plaats   Vendor's city of residence.
 * @property string $telefoon Vendor's sales number.
 *
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */
class Leverancier extends EatITModel {

  protected static $schema = array(
    'leveranciernr' => 'id',
    'naam' => 'string:64',
    'adres' => 'string:128',
    'postcode' => 'string:8',
    'plaats' => 'string:64',
    'telefoon' => 'string:20',
  );

}