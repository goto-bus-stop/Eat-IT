<?php

class IndexController extends EatITController {

  public function get() {
    $layout = new IndexView();
    $this->render(
        $layout->render(array(
      'maaltijden' => Maaltijd::all(),
    ))
    );
  }

}