<form class="form-horizontal" style="max-width:500px" method="post" action="">
  <div class="form-group">
    <label class="control-label col-sm-4">Artikel</label>
    <div class="col-sm-7">
      <select name="regel[]" class="form-control">
        <optgroup label="Maaltijden">
          {{#each maaltijd in maaltijden}}
            <option value="m{{maaltijd.id}}">{{maaltijd.naam}} (&euro;{{maaltijd.prijs}})</option>
          {{/each}}
        </optgroup>
        <optgroup label="Bijzaken">
          {{#each artikel in artikelen}}
            <option value="a{{artikel.id}}">{{artikel.naam}} (&euro;{{artikel.prijs}})</option>
          {{/each}}
        </optgroup>
      </select>
    </div>
    <div class="col-sm-1">
      <button type="button" class="btn btn-default" data-js="add-row"><i class="glyphicon glyphicon-plus"></i></button>
    </div>
  </div>
  <div class="form-group aflever">
    <label class="control-label col-sm-4">Bezorgtijdstip</label>
    <div class="col-sm-8">
      <input name="tijd" type="text" class="form-control" placeholder="{{bezorgtijdstip}}">
    </div>
  </div>
  <div class="form-group">
    <div class="col-sm-8 col-sm-offset-4">
      <button type="submit" class="btn btn-primary order-submit">Plaats bestelling</button>
    </div>
  </div>
</form>

<script>
  window.addEventListener('click', function (e) {
    var button = e.target
      , submit = document.querySelector('.aflever')
    if (button.getAttribute('data-js') === 'add-row') {
      var group = button
      do { group = group.parentNode } while (button.parentNode !== window &&
                                              group.className !== 'form-group')
      // lol cloning </3
      var div = group.cloneNode()
      div.innerHTML = group.innerHTML
      group.parentNode.insertBefore(div, submit)
    }
  })
</script>