<?php
/**
 * @package MineTurtle
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * Represents a Route, matching a URL regex to a callback function / Controller method.
 *
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */
class Router_Route {
  /**
   * @param string          $name     Name for this route. Used for Reverse Routing.
   * @param string          $regex    Regular expression to match the URL. Group matches will
   *      be passed to the callback as separate parameters, in order, the 1st parameter being
   *      the 1st subgroup match etc.
   * @param callable|string $callback Function to call if this route matches, or a shorthand
   *      Controller string "Controller#method", eg. "InventoryController#itemList", which will
   *      call "itemList" on a new instance of "InventoryController".
   */
  public function __construct($name, $url, $callback) {
    $this->name = $name;
    $this->url = $url;
    // all these slashes </3
    $this->regex = '/^' . preg_replace('/\\\\\[([a-z]+)\\\\\]/', '(.*?)', preg_quote($url, '/')) . '\/?$/i';
    $this->callback = $callback;
  }

  /**
   * Checks if this route matches a given URL.
   *
   * @param string $url URL to match against.
   *
   * @return array|bool An array of regex matches, or false if there's no match.
   */
  public function matches($url) {
    $matches = array();
    if (preg_match($this->regex, $url, $matches)) {
      array_shift($matches);
      return $matches;
    }
    return false;
  }

  /**
   * Returns the route URL for this route with the given parameters.
   *
   * @param array $matches Parameters to enter into the URL.
   *
   * @return string URL to this route.
   */
  public function getUrl($matches = array()) {
    $i = 0;
    return preg_replace_callback('/\[([a-z]+)\]/', function () use ($matches, &$i) {
      return $matches[$i++];
    }, $this->url);
  }

  /**
   * Calls this route's callback function with the given parameters.
   *
   * @param array $params Array of parameters.
   *
   * @return void
   */
  public function call($params) {
    if (is_string($this->callback) && strpos($this->callback, '#') !== false) {
      list ($controller, $action) = explode('#', $this->callback, 2);
      $self = new $controller();
      call_user_func_array(array($self, $action), $params);
    }
    else {
      call_user_func_array($this->callback, $params);
    }
  }

}