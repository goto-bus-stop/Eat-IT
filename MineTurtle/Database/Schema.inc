<?php
/**
 * @package MineTurtle
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * Describes what kind of information a Model contains.
 *
 * @see Model
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */
class Schema implements \IteratorAggregate {

  private $schema = array();
  private $links = array();

  /**
   * Defines a column type on this Schema.
   *
   * A type looks like "type:parameter", where "parameter" is optional.
   * eg. "string:16" for a string with max length 16, or "int" for an integer. There is a special type
   * "link" that takes a Model name as a parameter, eg. "link:Employee", which refers to a Model that
   * is stored elsewhere.
   *
   * Available data types:
   * "id"     A unique ID. Picked by the Database implementation.
   * "string" A text string. The parameter is the max length of the string.
   * "int"    An integer.
   * "double" A double.
   * "bool"   A boolean. True or false.
   * "date"   A date. YYYY-MM-DD style.
   * "time"   A time. hh:mm:ss style.
   * "link"   A link to a table. Parameter is the Model class name of the link endpoint.
   *
   * @param string $column Column or property name.
   * @param string $type   Its Type
   *
   * @return void
   */
  public function defineColumn($column, $type) {
    $typeParts = explode(':', $type);
    if ($typeParts[0] === 'link') {
      $this->links[$column] = array( 'fromColumn' => $column, 'toModel' => $typeParts[1] );
    }
    $this->schema[$column] = array( 'type' => $typeParts[0], 'param' => count($typeParts) > 1 ? $typeParts[1] : null );
  }

  /**
   * Check if the Schema has a certain column.
   *
   * @param string $column Column to check.
   *
   * @return bool True if the column exists, false otherwise.
   */
  public function hasColumn($column) {
    return isset($this->schema[$column]);
  }

  /**
   * Returns the primary key name of this schema.
   *
   * @return string|null The primary key name of this schema.
   */
  public function getPrimaryKey() {
    foreach ($this->schema as $column => $type) {
      if ($type['type'] === 'id') {
        return $column;
      }
    }
  }

  /**
   * Get the type of a certain column.
   *
   * @param string $column The column.
   *
   * @return array The specified type as an array of the form: `[ $type, $parameter ]`.
   */
  public function getType($column) {
    return $this->schema[$column];
  }

  /**
   * Returns the column names that are links to other Models.
   *
   * @return string[] Array of column names.
   */
  public function getLinks() {
    return array_keys($this->links);
  }

  /**
   * Finds the Model class that's linked to by a given column.
   *
   * @param string $link Linking column name.
   *
   * @return string|null Model class name or null if there is no link on the given column.
   */
  public function getRelatedModel($link) {
    if (isset($this->links[$link])) {
      return $this->links[$link]['toModel'];
    }
  }

  /**
   * IteratorAggregate::getIterator
   * @ignore
   */
  public function getIterator() {
    return new \ArrayIterator($this->schema);
  }

  /**
   * Parses an array descriptor into a Schema.
   *
   * @param array Schema descriptor as an array. Column names as keys, Types as values.
   *
   * @see Schema::defineColumn
   * @return Schema The resulting Schema definition.
   */
  public static function parse($descr) {
    $schema = new Schema();
    foreach ($descr as $column => $type) {
      $schema->defineColumn($column, $type);
    }
    return $schema;
  }

}