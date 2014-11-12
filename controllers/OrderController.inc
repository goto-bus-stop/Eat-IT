<?php
/**
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * Handles order placements.
 *
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */
class OrderController extends EatITController {

  /**
   * Shows an order form.
   *
   * @return void
   */
  public function form() {
    $artikel = Artikel::all()->filter(function ($a) { return $a->verkoop != 0; });
    $of = new OrderFormView();
    $suggestion = date('H:i',
                       // find the closest half hour at least 25 minutes from now
                       ceil(strtotime('+25 minutes') / 60 / 30) * 60 * 30);
    $this->render($of->render(array(
      'maaltijden' => Maaltijd::all(),
      'artikelen' => $artikel,
      'bezorgtijdstip' => $suggestion
    )));
  }

  /**
   * Handles order placements.
   *
   * @param int $klant Customer ID.
   *
   * @return void
   */
  public function placeOrder($klant) {
    $lines = isset($_POST['regel']) ? $_POST['regel'] : false;
    if ($lines) {
      $order = new Order(array(
        'klant' => $klant,
        'datum' => date('Y-m-d'),
        'bezorgtijd' => $_POST['tijd']
      ));
      $order->save();

      $orderLines = new MineTurtle\Collection();
      foreach ($lines as $line) {
        if ($line[0] === 'a') {
          $type = 'artikel';
        }
        else {
          $type = 'maaltijd';
        }
        $orderLines[] = new OrderRegel(array(
          'type' => $type,
          'order' => $order->id,
          $type => (int)substr($line, 1)
        ));
      }
      $orderLines->save();
    }
    $opv = new OrderPlacedView();
    $this ->render($opv->render());
  }

}