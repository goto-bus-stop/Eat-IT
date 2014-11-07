<?php

class EatITModel extends MineTurtle\Model {

  public static function getTableName() {
    return strtolower(array_pop(explode('\\', get_called_class())));
  }

}