
        <!-- Heading Row -->
        <div class="row">
            <div class="col-md-8">
                <img class="img-responsive img-rounded" src="/templates/img/bedrijf.png" alt="">
            </div>
            <!-- /.col-md-8 -->
            <div class="col-md-4">
                <h1>eat IT maaltijden</h1>
                <p>Dit geweldige restaurant bied omnomnomnom maaltijden, nu voor een geweldige prijs!</p>
                <a class="btn btn-primary btn-lg" href="{{@link register}}">Bestel NU!</a>
            </div>
            <!-- /.col-md-4 -->
        </div>
        <!-- /.row -->

        <!-- Daghap Row -->
        <div class="row">
            <div class="col-md-12">
                <img class="img-responsive img-rounded" src="/templates/img/bedrijf.png" alt="">

            </div>
            <!-- /.col-md-12 -->
        </div>
        <!-- /.row -->
<div class="row">
    {{#each maaltijd in maaltijden}}
<div class="col-sm-6 col-md-4">
    <div class="thumbnail">
      <img src="/data/meal-images/{{maaltijd.img}}" alt="maaltijd">
      <div class="caption">
        <h3>{{maaltijd.naam}}</h3>
        <p>...</p>
        <p><a href="{{@link maaltijd_bestellen maaltijd.maaltijdnr}}" class="btn btn-primary" role="button">Bestel Nu!</a></p>
      </div>
    </div>
  </div>
    {{/each}}
</div>