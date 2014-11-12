<?php
/**
 * @package MineTurtle
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

namespace MineTurtle\Router;

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
   * @param string          $url      URL expression. Add wildcards like "/user/[id]".
   *     Matches are passed to the callback.
   * @param callable|string $callback Callback function, called if the route matches.
   *
   * @return this
   */
  public function add($name, $method, $url, $callback = null) {
    if (!$callback) {
      // $name is optional, so if there's no $callback, we default to a bogus name
      // and move the parameters around
      list ($name, $method, $url, $callback) = array(uniqid('name_'), $name, $method, $url);
    }
    $method = strtoupper($method);
    if (!isset($this->routes[$method])) {
      $this->routes[$method] = array();
    }
    $this->routes[$method][] = new Route($name, $url, $callback);
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
    $this->error = new Route('error', '', $callback);
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

  /**
   * Gets a URL to a route.
   *
   * @param string $method  Method name.
   * @param string $name    Route name.
   * @param array  $matches Route parameters.
   *
   * @return string|void Route URL.
   */
  public function link($method, $name, $matches = array()) {
    foreach ($this->routes[$method] as $route) {
      if ($route->name === $name) {
        return ltrim($route->getUrl($matches), '/');
      }
    }
    throw new \Exception('no matching route found');
  }

  /**
   * Redirects to a route.
   *
   * @param string $name Route name.
   * @param array  $args Route parameters.
   *
   * @return void
   */
  public function redirect($name, $args = array()) {
    header('Location: ' . $this->link($name, $args));
    exit;
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