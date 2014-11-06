<?php

trait AuthTrait {

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

  public function checkLogin() {
    if (!$this->isLoggedIn()) {
      Router::getInstance()->redirect('login');
    }
    return $this->getCurrentUser();
  }

}