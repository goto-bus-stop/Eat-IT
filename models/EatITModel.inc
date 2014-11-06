<?php

class EatITModel extends Model {

  public static function getTableName() {
    return strtolower(array_pop(explode('\\', get_called_class())));
  }

}