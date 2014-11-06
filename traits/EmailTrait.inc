<?php

trait EmailTrait {

  protected function sendEmail($to, $subject, $content) {
    mail($to, $subject, $content, 'From: orders@eatit.nl');
  }

}