<?php

class IndexController extends EatITController {

  public function get() {
    $layout = new LayoutView();
    $this->render('*yawn*');
  }

}