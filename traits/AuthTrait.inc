<?php
/**
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */

/**
 * Adds login related functionality.
 *
 * @author  Marijn Pool <info@marijnpool.nl>
 * @author  René Kooi <rene@kooi.me>
 */
trait AuthTrait {

  /**
   * Gets the currently logged in user.
   *
   * @return User|void Currently logged in user or null if nobody is logged in.
   */
  public function getCurrentUser() {
    if (!property_exists($this, 'currentUser')) {
      $this->currentUser = null;
      $uid = isset($_SESSION['uid']) ? $_SESSION['uid'] : false;
      if ($uid) {
        $this->currentUser = User::find($uid);
      }
    }
    return $this->currentUser;
  }

  /**
   * Checks if a user is currently logged in.
   *
   * @return bool True if a user is logged in, false otherwise.
   */
  public function isLoggedIn() {
    if (!property_exists($this, 'loggedIn')) {
      $this->loggedIn = false;
      $user = $this->getCurrentUser();
      if ($user) {
        $pass = $_SESSION['pass'];
        $this->loggedIn = password_verify($pass, $user->password);
      }
    }
    return $this->loggedIn;
  }

  /**
   * Checks if a user is logged in. Redirects to login page if nobody is logged in.
   *
   * @return User|void The logged in user.
   */
  public function checkLogin() {
    if (!$this->isLoggedIn()) {
      Router::getInstance()->redirect('login');
    }
    return $this->getCurrentUser();
  }

}