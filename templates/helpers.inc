<?php

/**
 * @link helper
 */
Template::addHelper('link', function ($args, $data) {
  $args = explode(' ', $args);
  $route = array_shift($args);
  return Router::getInstance()->link('GET', $route, $args);
});