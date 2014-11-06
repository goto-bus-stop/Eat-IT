<?php

class OrderController extends EatITController {

  public function form() {
    $of = new OrderFormView();
    $this->render($of->render());
  }

}