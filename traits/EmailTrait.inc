<?php
/**
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * Adds email functionality.
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */
trait EmailTrait {

  protected function sendEmail($to, $subject, $content) {
    // only send if we have sendmail (should be the case on prod server…)
    if (in_array('sendmail', get_loaded_extensions())) {
      mail($to, $subject, $content, 'From: orders@eatit.nl');
    }
    else {
      echo '<h2>Could not send email:</h2>';
      echo '<dl> <dt> To </dt> <dd> ' . $to . ' </dd> ';
      echo '<dt> Subject </dt> <dd> ' . $subject . '</dd>';
      echo '<dt> Content </dt> <dd> ' . $content . '</dd>';
    }
  }

}