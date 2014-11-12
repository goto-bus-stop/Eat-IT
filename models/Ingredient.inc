<?php
/**
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * Represents an ingredient.
 *
 * @property int      $id          Primary key ID of this ingredient.
 * @property Maaltijd $maaltijd    The meal that this ingredient goes into.
 * @property Artikel  $artikel     Item type.
 * @property int      $hoeveelheid Amount of item units that go into the meal.
 *
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