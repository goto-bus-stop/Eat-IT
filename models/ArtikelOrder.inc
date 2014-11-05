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
class ArtikelOrder extends Model {

  protected static $schema = array(
    'artikelordernr' => 'id',
    'artikelnr' => 'link:Artikel',
    'ordernr' => 'link:InkoopOrder',
    'hoeveelheid' => 'int',
    'leverstatus' => 'int',
  );

}