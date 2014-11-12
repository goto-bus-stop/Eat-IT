<?php
/**
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * Represents a buying order for an item, from Eat-IT to an upstream vendor.
 *
 * @property int         $id          Primary key ID of this order.
 * @property Artikel     $artikel     Type of item that's being ordered.
 * @property InkoopOrder $inkooporder The full order that this item order is a part of.
 * @property int         $hoeveelheid Amount of items that are being ordered.
 * @property int         $leverstatus Current status of this order: sent, acknowledged, completed, etc.
 *
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */
class ArtikelOrder extends EatITModel {

  protected static $schema = array(
    'artikelordernr' => 'id',
    'artikel' => 'link:Artikel',
    'inkooporder' => 'link:InkoopOrder',
    'hoeveelheid' => 'int',
    'leverstatus' => 'int',
  );

}