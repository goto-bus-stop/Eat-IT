<!-- Heading Row -->
<div class="row">
  <div class="col-md-8">
    <img class="img-responsive img-rounded" src="/templates/img/bedrijf.png" alt="">
  </div>
  <!-- /.col-md-8 -->
  <div class="col-md-4">
    <h1>eat IT maaltijden</h1>
    <p>Dit geweldige restaurant bied omnomnomnom maaltijden, nu voor een geweldige prijs!</p>
    <a class="btn btn-primary btn-lg" href="/index.php/{{@link register}}">Bestel NU!</a>
  </div>
</div>

<h2>Daghap</h2>
<!-- Daghap Row -->
<div class="row">
  <div class="col-md-12">
    <div class="media">
      <a class="media-left">
        <img src="/data/meal-images/{{daghap.img}}" alt="{{daghap.naam}}">
      </a>
      <div class="media-body">
        <h4>{{daghap.naam}}</h4>
        <p>
          &hellip;
        </p>
        <p>
          <a href="/index.php/{{@link maaltijd_bestellen daghap.id}}" class="btn btn-primary" role="button">Bestel Nu!</a>
        </p>
      </div>
    </div>
  </div>
</div>

<h2>Maaltijden</h2>
<div class="row">
  {{#each maaltijd in maaltijden}}
    <div class="col-sm-6 col-md-4">
      <div class="thumbnail">
        <img src="/data/meal-images/{{maaltijd.img}}" alt="{{maaltijd.naam}}">
        <div class="caption">
          <h3>{{#if maaltijd.daghap}}<i class="glyphicon glyphicon-star text-success"></i> {{/if}}{{maaltijd.naam}}</h3>
          <p>
            &hellip;
          </p>
          <p>
            <a href="/index.php/{{@link maaltijd_bestellen maaltijd.id}}" class="btn btn-primary" role="button">Bestel Nu!</a>
          </p>
        </div>
      </div>
    </div>
  {{/each}}
</div>