<?php

/**
 * @link helper
 */
MineTurtle\Template::addHelper('link', function ($args, $data) {
  $args = explode(' ', $args);
  $route = array_shift($args);
  return MineTurtle\Router\Router::getInstance()->link('GET', $route, $args);
});