<?php

class IndexController {

  public function get() {
    $layout = new LayoutView();
    echo $layout->render(array(
      'content' => 'Please use the menu above.',
      'title' => 'Index « Eat-IT'
    ));
  }

}