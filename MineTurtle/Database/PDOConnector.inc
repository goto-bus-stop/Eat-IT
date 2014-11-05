<?php
/**
 * @package MineTurtle
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * A PDO Database connection. (MySQL, MariaDB, Postgres…)
 *
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */
class PDOConnector implements DatabaseConnector {

  private $pdo;
  private $queries;

  /**
   * PDOConnector Constructor.
   *
   * @param string $dsn      Data Source Name, see {@link http://php.net/pdo.construct}
   * @param string $username Database user name.
   * @param string $password Database password.
   */
  public function __construct($dsn, $username, $password) {
    $this->pdo = new \PDO($dsn, $username, $password, [
      \PDO::ATTR_ERRMODE => \PDO::ERRMODE_EXCEPTION
    ]);
  }

  /**
   * Escape a value as a string that's safe to insert into a SQL statement.
   *
   * @param string $string The value to escape.
   *
   * @see PDO::quote
   * @return string Escaped string.
   */
  public function escape($string) {
    return $this->pdo->quote($string);
  }

  /**
   * Executes a SQL statement with placeholders.
   *
   * <code>
   *    $db->execute('SELECT :placeholder', array( 'placeholder' => 1 ));
   * </code>
   *
   * @param string $sql    SQL statement, optionally with `?` or `:name` placeholders.
   * @param array  $values Array of values to insert for the placeholders. ({@link http://php.net/pdo.execute})
   *
   * @return bool True if execution succeeded, false otherwise.
   */
  private function execute($sql, $values) {
    $this->queries[] = $sql;
    $st = $this->pdo->prepare($sql);
    $res = $st->execute($values);
    $st->closeCursor();
    return $res;
  }

  /**
   * Gets all records matching a SQL statement.
   *
   * @param string $sql    SQL statement, optionally with `?` or `:name` placeholders.
   * @param array  $values Array of values to insert for the placeholders. ({@link http://php.net/pdo.execute})
   * @param string $class  Class name to use for result objects.
   *
   * @return Collection Collection of result instances.
   */
  private function getAll($class, $sql, $values) {
    $this->queries[] = $sql;
    $st = $this->pdo->prepare($sql);
    $st->setFetchMode(\PDO::FETCH_CLASS, $class);
    $st->execute($values);
    $res = $st->fetchAll();
    $st->closeCursor();
    return new Collection($res);
  }

  /**
   * Gets a single record matching a SQL statement.
   *
   * @param string $sql    SQL statement, optionally with `?` or `:name` placeholders.
   * @param array  $values Array of values to insert for the placeholders. ({@link http://php.net/pdo.execute})
   * @param string $class  Class name to use for the result object.
   *
   * @return object Resulting class instance.
   */
  private function getOne($class, $sql, $values) {
    $this->queries[] = $sql;
    $st = $this->pdo->prepare($sql);
    $st->setFetchMode(\PDO::FETCH_CLASS, $class);
    $st->execute($values);
    $res = $st->fetch();
    $st->closeCursor();
    return $res;
  }

  /**
   * Finds a single record by primary key ID.
   *
   * @param string $Model Record type, aka. a Model subclass name.
   * @param int    $id    Primary key ID.
   *
   * @return object|null Record Model instance.
   */
  public function findRecord($Model, $id) {
    $schema = $Model::getSchema();
    $select = array();
    foreach ($schema as $column => $type) {
      if ($type['type'] === 'link') {
        $column .= 'ID AS ' . $column;
      }
      $select[] = $column;
    }
    $sql = 'SELECT ' . implode(', ', $select);
    $sql .= ' FROM ' . $Model::getTableName();
    $sql .= ' WHERE ' . $schema->getPrimaryKey() . ' = :id';

    return $this->getOne($Model, $sql, array( 'id' => $id ));
  }

  /**
   * Finds records by primary key ID, or all records if no IDs are given.
   *
   * @param string $Model Record type, aka. a Model subclass name.
   * @param int[]  $ids   Primary key IDs. Optional.
   *
   * @return Collection Collection of Model instances.
   */
  public function findRecords($Model, $ids = null) {
    $schema = $Model::getSchema();
    $select = array();
    foreach ($schema as $column => $type) {
      if ($type['type'] === 'link') {
        $column .= 'ID AS ' . $column;
      }
      $select[] = $column;
    }
    $sql = 'SELECT ' . implode(', ', $select);
    $sql .= ' FROM ' . $Model::getTableName();
    if (is_array($ids)) {
      $inIds = array_map(array( &$this, 'escape' ), $ids);
      $sql .= ' WHERE ' . $schema->getPrimaryKey() . ' IN(' . implode(', ', $inIds) . ')';
    }

    return $this->getAll($Model, $sql, array());
  }

  /**
   * Inserts a record into the database.
   *
   * @param string $Model Record type, aka. a Model subclass name.
   * @param array  $data  Array containing data for this new record.
   *
   * @return int|bool The primary key ID assigned to the new record, or false on failure.
   */
  public function insertRecord($Model, $data) {
    $schema = $Model::getSchema();
    $sql = 'INSERT INTO `' . $Model::getTableName() . '`';

    $columns = array();
    foreach ($schema as $column => $type) {
      if ($type['type'] === 'link') {
        $column .= 'ID';
      }
      if (array_key_exists($column, $data)) {
        $columns[] = '`' . $column . '`';
      }
    }
    $sql .= ' (' . implode(', ', $columns) . ')';

    $values = array();
    foreach ($schema as $column => $type) {
      if (array_key_exists($column, $data)) {
        $values[] = ':' . $column;
      }
    }
    $sql .= ' VALUES (' . implode(', ', $values) . ')';

    if ($this->execute($sql, $data)) {
      return $this->pdo->lastInsertId();
    }
    return false;
  }

  /**
   * Updates a single record in the database.
   *
   * @param string $Model Record type, aka. a Model subclass name.
   * @param int    $id    Primary key ID of the record to update.
   * @param array  $data  Array containing data for this record.
   *
   * @return bool True if the update was carried out successfully, false otherwise.
   */
  public function updateRecord($Model, $id, $data) {
    $schema = $Model::getSchema();
    $sql = 'UPDATE ' . $Model::getTableName();

    $update = array();
    foreach ($schema as $column => $type) {
      if ($type['type'] === 'id') {
        continue;
      }
      else if ($type['type'] === 'link') {
        $update[] = $column . 'ID = :' . $column;
      }
      else {
        $update[] = $column . ' = :' . $column;
      }
    }
    $sql .= ' SET ' . implode(', ', $update);

    $sql .= ' WHERE `' . $schema->getPrimaryKey() . '` = :' . $schema->getPrimaryKey();

    return $this->execute($sql, $data);
  }

  /**
   * Deletes a record from the database.
   *
   * @param string $Model Record type, aka. a Model subclass name.
   * @param int    $id    Primary key ID of the record to delete.
   *
   * @return bool True if the delete succeeded, false otherwise.
   */
  public function deleteRecord($Model, $id) {
    $schema = $Model::getSchema();
    $sql = 'DELETE FROM ' . $Model::getTableName();

    $sql .= ' WHERE `' . $schema->getPrimaryKey() . '` = :id';

    return $this->execute($sql, array( 'id' => $id ));
  }

  /**
   * Dumps all queries that were executed so far to the user.
   *
   * @return void
   */
  public function debugDumpQueries() {
    var_dump($this->queries);
  }

}
