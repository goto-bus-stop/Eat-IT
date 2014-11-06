<?php

class OrderController extends EatITController {

  public function form() {
    $artikel = Artikel::all()->filter(function ($a) { return $a->verkoop != 0; });
    $of = new OrderFormView();
    $this->render($of->render(array(
      'maaltijden' => Maaltijd::all(),
      'artikelen' => $artikel
    )));
  }

  public function placeOrder() {
    
  }

}