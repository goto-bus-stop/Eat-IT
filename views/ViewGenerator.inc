<?php
/**
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * TODO: write docs
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */
class ViewGenerator {

  public function autoload($class) {
    if (substr($class, -4) === 'View') {
      $tplName = 'templates/' . strtolower(substr($class, 0, -4)) . '.tpl';
      if (file_exists($tplName)) {
        eval('class ' . $class . ' extends MineTurtle\View {
                protected $template = ' . var_export($tplName, true) . ';
              }');
      }
    }
  }

  public static function register() {
    spl_autoload_register(array( new self, 'autoload' ));
  }

}

ViewGenerator::register();