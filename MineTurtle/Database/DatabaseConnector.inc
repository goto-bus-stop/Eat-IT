<?php

namespace MineTurtle\Database;

interface Connector {

  public function findRecord($Model, $id);
  public function findRecords($Model, $ids = null);
  public function findRecordBy($Model, $property, $value);
  public function insertRecord($Model, $data);
  public function updateRecord($Model, $id, $data);
  public function deleteRecord($Model, $id);

  public function createTable($Model);

}