<?php
/**
 * @package MineTurtle
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

namespace MineTurtle;
use MineTurtle\Database\Schema;
use MineTurtle\Database\Connector;

/**
 * A Model represents a "thing" in the database, and provides
 * methods to read and write "things".
 *
 * @property-read int $id The primary key ID of this Model.
 * @package MineTurtle
 * @author  René Kooi <rene@kooi.me>
 */
class Model {

  protected static $dbConn = null;

  protected $data = array();
  protected $linkCache = array();
  protected $dirty = false;

  /**
   * Model constructor. You usually won't need this.
   *
   * @param array $data Default data for this Model.
   */
  public function __construct($data = array()) {
    // \PDO::FETCH_CLASS sets the properties before calling the class constructor,
    // so they may already have been set on $this->data.
    $this->data = array_merge($this->data, $data);
    $this->dirty = false;
  }

  /**
   * Sets a property on the model and marks as dirty.
   *
   * @param string $prop  The property name.
   * @param mixed  $value The new value for the property.
   *
   * @return void
   */
  public function __set($prop, $value) {
    $schema = static::getSchema();

    if (!$schema->hasColumn($prop)) {
      throw new \Exception('tried to set nonexistent property on ' . get_called_class());
    }

    $type = $schema->getType($prop);
    if ($type['type'] === 'link') {
      if ($value instanceof Model) {
        $this->resolveLink($prop, $value);
        $value = $value->id;
      }
      //$prop .= 'ID';
    }

    $this->data[$prop] = $value;
    $this->dirty = true;
  }

  /**
   * Gets a property from the model.
   *
   * Throws if the property does not exist
   * according to the Model's schema. Resolves linked records if necessary.
   *
   * @param string $prop The property name.
   *
   * @throws Exception
   * @return void
   */
  public function __get($prop) {
    $schema = static::getSchema();

    if ($prop === 'id') {
      $prop = $schema->getPrimaryKey();
      return isset($this->data[$prop]) ? $this->data[$prop] : null;
    }

    if (!$schema->hasColumn($prop)) {
      throw new \Exception('nonexistent property on ' . get_called_class());
    }

    $type = $schema->getType($prop);
    if ($type['type'] === 'link') {
      if (!array_key_exists($prop, $this->linkCache)) {
        $RelatedModel = $schema->getRelatedModel($prop);
        // Cache the newly fetched model, so next time someone needs it,
        // it'll just instantly resolve to the same thing.
        $this->resolveLink($prop, $RelatedModel::find($this->data[$prop]));
      }
      return $this->linkCache[$prop];
    }

    return $this->data[$prop];
  }

  /**
   * Checks if a property exists according to the schema.
   *
   * @param string $prop The property name.
   *
   * @return bool True if the property exists, false otherwise.
   */
  public function __isset($prop) {
    $schema = static::getSchema();
    return $schema->hasColumn($prop) || $prop === 'id';
  }

  /**
   * Finds the ID of the Model that is referenced by the given property.
   *
   * @param string $link The name of the linking property.
   *
   * @return int|null The ID of the related Model, or null if there is no related Model.
   */
  public function getLinkId($link) {
    return $this->data[$link];
  }

  /**
   * Resolves a linking property with a Model.
   *
   * @param string     $link         The name of the linking property.
   * @param Model|null $relatedModel The Model to resolve to.
   *
   * @internal
   * @return void
   */
  public function resolveLink($link, $relatedModel) {
    $this->linkCache[$link] = $relatedModel;
  }

  /**
   * Saves this Model to the database, if it is marked dirty.
   *
   * @return void
   */
  public function save() {
    $isNew = is_null($this->id);
    if (!$this->isDirty() && !$isNew) {
      return;
    }
    $class = get_called_class();
    $data = $this->data;
    if ($isNew) {
      $id = self::$dbConn->insertRecord($class, $data);
      if ($id !== false) {
        $primaryKey = static::getSchema()->getPrimaryKey();
        $this->data[$primaryKey] = $id;
      }
      else {
        throw new \Exception('Could not save ' . $class);
      }
    }
    else {
      return self::$dbConn->updateRecord($class, $this->id, $data);
    }
    $this->dirty = false;
  }

  /**
   * Removes the Model from the database. Be VERY careful with this please -.-
   *
   * @return void
   */
  public function delete() {
    $class = get_called_class();
    self::$dbConn->deleteRecord($class, $this->id);
    // clear model ID so it can be inserted again with save()
    $this->dirty = false;
    $primaryKey = static::getSchema()->getPrimaryKey();
    unset($this->data[$primaryKey]);
  }

  /**
   * Returns whether the Model is marked dirty, i.e., if it has unsynced changes with the database.
   *
   * @return bool True if the Model was changed since its last fetch or save, false otherwise.
   */
  public function isDirty() {
    return $this->dirty;
  }

  /**
   * Returns an associative array with this Model's information, including resolved linked Models.
   *
   * @return array
   */
  public function toArray() {
    $schema = $this->getSchema();
    $data = array();
    foreach ($schema as $column => $type) {
      $data[$column] = $this->$column;
    }
    return $data;
  }

  /**
   * Gets the database Schema for this Model class. Can only be called on subclasses of Model.
   *
   * @static
   * @return Schema
   */
  public static function getSchema() {
    // getSchema() calls come from different classes and need to return
    // different values accordingly, so we can't just cache one call
    // and return the same thing everywhere. Instead we use this
    // associative array to store ClassName → Schema pairs.
    static $parsedSchemas = array();
    $class = get_called_class();
    if (!isset($parsedSchemas[$class])) {
      $parsedSchemas[$class] = Schema::parse(static::$schema);
    }
    return $parsedSchemas[$class];
  }

  /**
   * Tells Model which database connection to use.
   *
   * Make sure to call this before you start your day, or it will be your last.
   *
   * @param DatabaseConnector $db Connection to a database.
   *
   * @static
   * @return void
   */
  public static function useDB(Connector $db) {
    self::$dbConn = $db;
  }

  /**
   * Returns the in-database table name for this Model.
   *
   * By default, Models are assumed to have singular BumpyCased names, and tables 
   * are assumed to have lowercase plural names, so this converts the former to the latter.
   * Override if your database uses a different naming convention!
   *
   * @static
   * @return string Table name.
   */
  public static function getTableName() {
    $table = get_called_class();
    $table = explode('\\', $table);
    return strtolower($table[count($table)-1]) . 's';
  }

  /**
   * Returns a Collection of all available Models of this type.
   *
   * @static
   * @return Collection All the available Models.
   */
  public static function all() {
    $class = get_called_class();
    return self::$dbConn->findRecords($class);
  }

  /**
   * Returns a Collection of all available Models of this type.
   *
   * @static
   * @return Collection All the available Models.
   */
  public static function allBy($prop, $value) {
    $class = get_called_class();
    return self::$dbConn->findRecordsBy($class, $prop, $value);
  }

  /**
   * Finds a specific Model by primary key.
   *
   * @param int $id Primary key ID.
   *
   * @return Model|null The specified Model, or null if it does not exist.
   */
  public static function find($id) {
    $class = get_called_class();
    return self::$dbConn->findRecord($class, $id);
  }

  /**
   * Finds a Collection of Models by primary key.
   *
   * @param int[] $ids Primary key IDs to look for.
   *
   * @return Collection The specified Models.
   */
  public static function findMany($ids) {
    $class = get_called_class();
    return self::$dbConn->findRecords($class, $ids);
  }

  /**
   * Finds a specific Model by a property. Returns only one, even if there would be many results.
   *
   * @param string $property Property to check.
   * @param *      $value    Value to restrict to.
   *
   * @return Model|null The specified Model, or null if it does not exist.
   */
  public static function findBy($property, $value) {
    $class = get_called_class();
    return self::$dbConn->findRecordBy($class, $property, $value);
  }
}
