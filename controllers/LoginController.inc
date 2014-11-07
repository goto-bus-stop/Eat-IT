<?php

class LoginController extends EatITController {
  use EmailTrait;

  protected $title = 'Login';

  public function get() {
    $view = new LoginView();
    $this->render(
      $view->render()
    );
  }

  public function login() {
    $email = $_POST['email'];
    $pass = $_POST['pass'];
    $user = Klant::findBy('email', $email);
    if ($user && password_verify($pass, $user->password)) {
      $_SESSION['uid'] = $user->id;
      $_SESSION['pass'] = $pass;
      MineTurtle\Router\Router::getInstance()->redirect('index');
    }
    else {
      $errors = array( 'Email/wachtwoord-combinatie niet bekend' );
      $view = new LoginView();
      $this->render(
        $view->render(array( 'errors' => $errors ))
      );
    }
  }

  public function register() {
    $view = new RegisterView();
    $this->render(
      $view->render("")
    );
  }

  public function doRegister() {
    $client = new Klant();
    foreach (array( 'email', 'naam', 'adres', 'postcode', 'plaats', 'telefoon' ) as $prop) {
      $client->$prop = $_POST[$prop];
    }
    $client->save();
    $link = MineTurtle\Router\Router::getInstance()->link('GET', 'order', array( $client->id ));
    $this->sendEmail($client->email,
                     'Bestelling Eat-IT',
                     'Gebruik de volgende link om je bestelling te plaatsen: <a href="' . $link . '">' . $link . '</a>');
  }

}