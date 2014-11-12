<?php
/**
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * Base Model class for Eat-IT related models.
 *
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */
class EatITModel extends MineTurtle\Model {

  /**
   * @return string The table name for this model.
   */
  public static function getTableName() {
    return strtolower(array_pop(explode('\\', get_called_class())));
  }

}