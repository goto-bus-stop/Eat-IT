<?php

interface DatabaseConnector {

  public function findRecord($Model, $id);
  public function findRecords($Model, $ids = null);
  public function insertRecord($Model, $data);
  public function updateRecord($Model, $id, $data);
  public function deleteRecord($Model, $id);

}