<?php
/**
 * @package MineTurtle
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * The Router maps URLs to Controllers.
 *
 * Singleton.
 *
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */
class Router {

  private $routes = array();
  private $error = null;

  /**
   * Router is a singleton, don't use `new`.
   * @ignore
   */
  private function __construct() {
  }

  /**
   * Add a route.
   *
   * @see Router_Route
   * @param string          $name     Route name. Optional.
   * @param string          $method   Method to match against. Eg. GET, POST.
   * @param string          $regex    URL Regular expression. Group matches are passed to the callback.
   * @param callable|string $callback Callback function, called if the route matches.
   *
   * @return this
   */
  public function add($name, $method, $regex, $callback = null) {
    if (!$callback) {
      // $name is optional, so if there's no $callback, we default to a bogus name
      // and move the parameters around
      list ($name, $method, $regex, $callback) = array(uniqid('name_'), $name, $method, $regex);
    }
    $method = strtoupper($method);
    if (!isset($this->routes[$method])) {
      $this->routes[$method] = array();
    }
    $this->routes[$method][] = new Router_Route($name, $regex, $callback);
    return $this;
  }

  /**
   * Sets callback to use if an Exception is thrown at any point during the Router's business.
   *
   * @param callable|string $callback Callback function.
   *
   * @return this
   */
  public function error($callback) {
    $this->error = new Router_Route('error', '', $callback);
    return $this;
  }

  /**
   * Dispatch a request to the router. Calls matching route callback.
   *
   * @param string $method Request method. Optional. Defaults to _SERVER[REQUEST_METHOD].
   * @param string $url    Request URI. Optional. Defaults to _SERVER[REQUEST_URI].
   *
   * @throws Exception
   * @return bool
   */
  public function dispatch($method = null, $url = null) {
    if (is_null($method)) {
      $method = $_SERVER['REQUEST_METHOD'];
    }
    $method = strtoupper($method);
    if (is_null($url)) {
      $url = $_SERVER['REQUEST_URI'];
    }
    try {
      if (!empty($this->routes[$method])) {
        foreach ($this->routes[$method] as $route) {
          $matches = $route->matches($url);
          if ($matches !== false) {
            $route->call($matches);
            return true;
          }
        }
      }
      throw new \Exception('no matching route found');
    }
    catch (\Exception $e) {
      $cb = $this->error;
      if ($cb) {
        $cb->call(array( $e ));
      }
      else {
        throw $e;
      }
    }
  }

  public function redirect($name, $args = array()) {
    foreach ($this->routes['GET'] as $route) {
      if ($route->name === $name) {
        header('Location: index.php/todo');
        exit;
      }
    }
    throw new \Exception('no matching route found');
  }

  /**
   * Returns the singleton Router instance.
   *
   * @static
   * @return Router
   */
  public static function getInstance() {
    static $instance;
    if (!$instance) {
      $instance = new self;
    }
    return $instance;
  }

}