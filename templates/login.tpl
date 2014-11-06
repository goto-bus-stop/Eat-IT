{{#if errors}}
  <ul class="errors">
    {{#each error in errors}}
      <li>{{error}}</li>
    {{/each}}
  </ul>
{{/if}}

<form method="post" action="">
  <div>
    Emailadres:
    <input type="text" name="email">
  </div>
  <div>
    Wachtwoord:
    <input type="password" name="pass">
  </div>

  <div>
    <button type="submit">Login</button>
  </div>
</form>