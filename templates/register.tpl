
<div class="row">
  <div class="col-md-4">
    {{#if errors}}
      <ul class="errors">
        {{#each error in errors}}
          <li>{{error}}</li>
        {{/each}}
      </ul>
    {{/if}}


    <form method="post" action="{{@link register}}" role="form">
      <div class="form-group">
        <label for="naam">Naam</label>
        <input type="text" class="form-control" id="naam" placeholder="Mine Turtle">
      </div>
      <div class="form-group">
        <label for="email">Email</label>
        <input type="email" class="form-control" id="email" placeholder="mineturtle@explosion.boom">
      </div>
      <div class="form-group">
        <label for="telefoon">Telefoon</label>
        <input class="form-control" type="text" id="telefoon">
      </div>
      <div class="form-group">
        <label for="adres">Adres</label>
        <input class="form-control" type="text" name="adres" placeholder="Adres">
        <input class="form-control" type="text" name="postcode" placeholder="Postcode">
        <input class="form-control" type="text" name="plaats" placeholder="Plaats">
      </div>
      <button type="submit" class="btn btn-default">Registreer</button>
    </form>
  </div>
   <div class="col-md-8">
    
   </div>
</div>