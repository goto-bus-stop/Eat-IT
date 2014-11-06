{{#if errors}}
  <ul class="errors">
    {{#each error in errors}}
      <li>{{error}}</li>
    {{/each}}
  </ul>
{{/if}}

<form method="post" action="{{@link register}}">
  <div>
    <label>Emailadres</label>
    <div>
      <input type="email" name="email">
    </div>
  </div>
  <div>
    <label>Naam</label>
    <div>
      <input type="text" name="naam">
    </div>
  </div>
  <div>
    <label>Telefoonnummer</label>
    <div>
      <input type="text" name="telefoon">
    </div>
  </div>
  <div>
    <label>Adres</label>
    <div>
      <input type="text" name="adres" placeholder="Adres">
      <input type="text" name="postcode" placeholder="Postcode">
      <input type="text" name="plaats" placeholder="Plaats">
    </div>
  </div>

  <div>
    <button type="submit">Login</button>
  </div>
</form>