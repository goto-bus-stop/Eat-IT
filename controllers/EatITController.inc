<?php

class EatITController {
  use AuthTrait;

  protected function render($content) {
    $data = array(
      'title' => !empty($this->title) ? $this->title . ' « Eat-IT' : 'Eat-IT',
      'content' => $content,
      'user' => $this->getCurrentUser()
    );
    $layout = new LayoutView();
    echo $layout->render($data);
  }

}