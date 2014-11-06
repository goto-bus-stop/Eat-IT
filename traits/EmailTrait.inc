<?php

trait EmailTrait {

  protected function sendEmail($to, $subject, $content) {
    // totally sending mail here
    // mail($to, $subject, $content, 'From: orders@eatit.nl');
    echo '<dl> <dt> To </dt> <dd> ' . $to . ' </dd> ';
    echo '<dt> Subject </dt> <dd> ' . $subject . '</dd>';
    echo '<dt> Content </dt> <dd> ' . $content . '</dd>';
  }

}