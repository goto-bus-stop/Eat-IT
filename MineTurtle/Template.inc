<?php
/**
 * @package MineTurtle
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * The Template class translates our custom MineTemplate syntax to PHP.
 * To display values in MineTemplates, you use `{{key}}`. If you need to go down a path
 * into arrays or objects, separate your key names with dots, like so:
 * `{{key.subkey.i.need.to.go.deeper}}`. To pass something to a block helper, use
 *
 *    {{#helpername arguments}}
 *      content
 *    {{/helpername}}
 *
 * By default, two block helpers are defined: #each and #if.
 *
 *    {{#each user in users}}
 *      <li> {{user.name}} </li>
 *    {{/each}}
 *    {{#if sale}}
 *      Today: 10% OFF on every single thing!
 *    {{/if}}
 *
 * To pass something to an inline helper, use
 *
 *    {{@helpername arguments}}
 *
 * By default, one inline helper is defined, namely @raw:
 *
 *    {{@raw keyWithHtml}}
 *
 * This will output a value without first escaping HTML. Use with caution ;)
 *
 * To define your own helpers, use `Template::addHelper`. See relevant documentation.
 *
 * @package MineTurtle
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */
class Template {

  private static $helpers = array();
  private $src;
  private $eval;

  /**
   * Template Constructor.
   *
   * @param strinc $src Template source code.
   */
  public function __construct($src) {
    $this->src = $src;
  }

  /**
   * Translates template source into PHP.
   * This is public primarily for debugging purposes, normally you shouldn't need to call this yourself.
   *
   * @return string The translated source.
   */
  public function parse() {
    // simple value expressions
    $this->eval = preg_replace_callback('/\{\{([a-z0-9_\.]+)\}\}/i', function ($match) {
      $path = explode('.', $match[1]);
      return '<?php ' . $this->propertySource($path) . 'echo htmlentities($__val) ?>';
    }, $this->src);

    // inline helpers
    $this->eval = preg_replace_callback('/\{\{@([a-z0-9_\.]+)( .*?)?\}\}/i', function ($match) {
      $helper = $match[1];
      $args = $match[2];
      return '<?php echo Template::callHelper("' . addslashes($helper) . '", "' . addslashes(trim($args)) . '", $data); ?>';
    }, $this->eval);

    // block helpers
    $this->eval = preg_replace_callback('/\{\{#([a-z0-9_\.]+)( .*?)?\}\}/i', function ($match) {
      $helper = $match[1];
      $args = $match[2];
      return '<?php Template::callHelper("' . addslashes($helper) . '", "' . addslashes(trim($args)) . '", $data, function ($data) { ?>';
    }, $this->eval);
    $this->eval = preg_replace_callback('/\{\{\/([a-z0-9_\.]+)\}\}/i', function ($match) {
      return '<?php }) ?>';
    }, $this->eval);
    return $this->eval;
  }

  /**
   * Renders a template with the given data.
   *
   * @param array|object $data Data to pass to the template.
   *
   * @return string Resulting source.
   */
  public function render($data) {
    if (is_null($this->eval)) {
      $this->parse();
    }
    ob_start();
    eval('?>' . $this->eval);
    return ob_get_clean();
  }

  /**
   * Shorthand alias to render. Allows you to use `$template($data)` in modern PHP versions.
   *
   * @param array|object $data Data to pass to the template.
   *
   * @return string Resulting source.
   */
  public function __invoke($data) {
    return $this->render($data);
  }

  /**
   * Calls a helper.
   *
   * @param string        $name Name of the helper.
   * @param string        $arg  Arguments string to pass to the helper.
   * @param array|object  $data Data outside the helper context.
   * @param callable|null $cb   Callback rendering block contents, if this is a block helper.
   *
   * @return string|null Result of the helper call, if this is an inline helper.
   */
  private static function callHelper($name, $arg, $data, $cb = null) {
    $helper = self::$helpers[$name];
    return $helper($arg, $data, $cb);
  }

  /**
   * Defines a new helper function.
   *
   * @param string   $name Helper name.
   * @param callable $fn   Helper function. This gets 3 arguments: $arg, $data, $cb.
   *    $arg is the argument string passed to the helper in the template, eg. if your template
   *    contains `{{@helper argument string}}`, $arg will contain "argument string".
   *    $data is the data passed to the template.
   *    $cb is a callback rendering block contents, if this helper was called as a block helper.
   *    It takes one argument `$data` which will be the new template context used for rendering the block.
   *
   * @return void
   */
  public static function addHelper($name, $fn) {
    self::$helpers[$name] = $fn;
  }

  /**
   * Gets the value at a path. Intended for use in template helpers only.
   *
   * @param array|object $data Base data object/array to descend into.
   * @param string       $path Dot-separated string of subkeys, eg. "post.author.name".
   *
   * @return * The value at the given path.
   */
  public static function getProperty($data, $path) {
    $path = explode('.', $path);
    foreach ($path as $sub) {
      if (is_array($data)) {
        $data = $data[$sub];
      }
      else {
        $data = $data->$sub;
      }
    }
    return $data;
  }

  /**
   * Builds a PHP source string that descends along the given path.
   *
   * @param array $path The path's parts.
   *
   * @return string PHP source code.
   */
  private function propertySource($path) {
    $src = '';
    $prev = '$data';
    foreach ($path as $i => $sub) {
      $src .= '$__' . $i . ' = ' . $this->descendSource($prev, $sub) . '; ';
      $prev = '$__' . $i;
    }
    $src .= '$__val = ' . $prev . '; ';
    return $src;
  }
  /**
   * Builds a PHP source string that descends one step into an object or array.
   *
   * @param string $base PHP source for the object or array to descend into.
   * @param string $key  Next subkey name.
   *
   * @return string PHP source.
   */
  private function descendSource($base, $key) {
    return 'is_array(' . $base . ') ? ' . $base . '["' . addslashes($key) . '"] : ' . $base . '->{"' . addslashes($key) . '"}';
  }

}

/**
 * The #each helper.
 */
Template::addHelper('each', function ($args, $data, $cb) {
  list ($keyName, $arrayName) = explode(' in ', $args, 2);
  $arr = Template::getProperty($data, $arrayName);
  foreach ($arr as $item) {
    $cb(array_merge($data, array( $keyName => $item )));
  }
});

/**
 * The #if helper.
 */
Template::addHelper('if', function ($args, $data, $cb) {
  $val = Template::getProperty($data, $args);
  if ($val) {
    $cb($data);
  }
});

/**
 * The @raw helper.
 */
Template::addHelper('raw', function ($args, $data) {
  return Template::getProperty($data, $args);
});