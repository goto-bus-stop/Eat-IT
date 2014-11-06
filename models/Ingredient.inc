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
class Ingredient extends EatITModel {

  protected static $schema = array(
    'ingedientnr' => 'id',
    'maaltijd' => 'link:Maaltijd',
    'artikel' => 'link:Artikel',
    'hoeveelheid' => 'int',
  );

}