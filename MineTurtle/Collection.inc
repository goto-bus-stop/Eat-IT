<?php
/**
 * @package MineTurtle
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * A Collection represents a bunch of "things" in the database.
 *
 * The Collection's items all have to be instances of the same Model class.
 * If you try to add a different Model from the previous ones, you will receive
 * an Exception in return.
 *
 * @package MineTurtle
 * @author  René Kooi <rene@kooi.me>
 */
class Collection implements \ArrayAccess, \IteratorAggregate, \Countable {

  /** @var array Items in this Collection. */
  private $items;

  /**
   * Collection Constructor.
   *
   * @param array|void $items Default items for the collection.
   */
  public function __construct(array $items = null) {
    if (!is_null($items)) {
      $this->items = $items;
    }
    else {
      $this->items = array();
    }
  }

  /**
   * Returns the first item in the Collection.
   *
   * @return mixed The first item.
   */
  public function first() {
    return $this->items[0];
  }

  /**
   * Returns the last item in the Collection.
   *
   * @return mixed The last item.
   */
  public function last() {
    return $this->items[count($this->items) - 1];
  }

  /**
   * Side-loads all models that are referenced by the models in this collection.
   *
   * @param ...string|void $links Linked properties to load. Defaults to all linked properties if omitted.
   *
   * @see Schema
   * @return void
   */
  public function load(/* ...$links */) {
    if (count($this->items) <= 0) {
      return /* nothing to do */;
    }
    $links = func_get_args();
    $first = $this->first();
    $schema = $first::getSchema();
    $Model = get_class($first);
    if (empty($links)) {
      $links = $schema->getLinks();
    }

    foreach ($links as $link) {
      // $findIds will contain an associative array of
      // RelatedId → Models
      // where RelatedId is the ID of a linked model and
      // Models is an array of models that reference said ID.
      $findIds = array();
      foreach ($this->items as $item) {
        $idx = $item->getLinkId($link);
        if (is_null($idx)) {
          // the current link does not reference anything
          $item->resolveLink($link, null);
          continue;
        }
        if (empty($findIds[$idx])) {
          $findIds[$idx] = array();
        }
        $findIds[$idx][] = $item;
      }

      if (count($findIds) > 0) {
        $RelatedModel = $schema->getRelatedModel($link);
        $relateds = $RelatedModel::findMany(array_keys($findIds));
        foreach ($relateds as $related) {
          foreach ($findIds[$related->id] as $item) {
            $item->resolveLink($link, $related);
          }
        }
      }
    }
  }

  /**
   * Saves all dirty Models in this Collection.
   *
   * @return void
   */
  public function save() {
    foreach ($this->items as $model) {
      $model->save();
    }
  }

  /**
   * Creates a new collection by filtering this one through a callback function.
   *
   * @param callable $cb Callback function. Gets the `($item, $index, $collection)` and
   *      returns `true` to keep the item, `false` to leave it out.
   *
   * @return Collection A filtered collection.
   */
  public function filter($cb) {
    $coll = array();
    foreach ($this->items as $index => $item) {
      if ($cb($item, $index, $this)) {
        $coll[] = $item;
      }
    }
    return new Collection($coll);
  }

  /**
   * Counts the number of items in this Collection.
   *
   * The preferred way of counting items in Collections is to use:
   * <code>
   *     $n = count($collection);
   * </code>
   *
   * @return int Number of items in this Collection.
   */
  public function count() {
    return count($this->items);
  }

  // ArrayAccess Interface
  /**
   * ArrayAccess::offsetExists
   * @ignore
   */
  public function offsetExists($i) {
    return $i >= 0 && $i < count($this->items);
  }
  /**
   * ArrayAccess::offsetGet
   * @ignore
   */
  public function offsetGet($i) {
    return $this->items[$i];
  }
  /**
   * ArrayAccess::offsetUnset
   * @ignore
   */
  public function offsetUnset($i) {
    array_splice($this->items, $i, 1);
  }
  /**
   * ArrayAccess::offsetSet
   * @ignore
   */
  public function offsetSet($i, $v) {
    // ensure that a Model is being added
    if (!($v instanceof Model)) {
      throw new \Exception('Collections can only contain Models');
    }
    // ensure that the Model is of the same type as the other Models
    // in the Collection
    if (count($this->items) > 0) {
      $class = get_class($this->first());
      if (!($v instanceof $class)) {
        throw new \Exception('inconsistent types in Collection');
      }
    }
    // the key $i is `null` when using:
    // $collection[] = $model
    // Here we should append to the $items array.
    if (is_null($i)) {
      $i = count($this->items);
    }
    return $this->items[$i] = $v;
  }

  // IteratorAggregate Interface
  /**
   * IteratorAggregate::getIterator
   * @ignore
   */
  public function getIterator() {
    return new \ArrayIterator($this->items);
  }

}