<?php
/**
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * Represents a meal.
 *
 * @property int    $id           Primary key ID of this meal.
 * @property string $naam         Meal name.
 * @property string $omschrijving Short description of what makes this meal awesome.
 * @property double $prijs        Cost of one of these meals.
 * @property int    $beschikbaar  Amount of meals that are ready to go.
 * @property bool   $daghap       Whether this meal is the "daghap", i.e. daily special.
 * @property string $img          File name of a food porn-esque photograph of this meal.
 * @property string $type         Type of meal: meaty/fishy/vegany.
 *
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */
class Maaltijd extends EatITModel {

  protected static $schema = array(
    'maaltijdnr' => 'id',
    'naam' => 'string:64',
    'omschrijving' => 'string:255',
    'prijs' => 'double',
    'beschikbaar' => 'int',
    'daghap' => 'bool',
    'img' => 'string:128',
    'type' => 'string:5' // vlees/vis/vega
  );

}