<?php

require 'MineTurtle/include.inc';

require 'traits/AuthTrait.inc';

require 'templates/helpers.inc';


require 'models/EatITModel.inc';
require 'models/Artikel.inc';
require 'models/ArtikelOrder.inc';
require 'models/Ingredient.inc';
require 'models/InkoopFactuur.inc';
require 'models/InkoopOrder.inc';
require 'models/Klant.inc';
require 'models/Leverancier.inc';
require 'models/Maaltijd.inc';
require 'models/Order.inc';
require 'models/OrderRegel.inc';

require 'controllers/EatITController.inc';
require 'controllers/IndexController.inc';
require 'controllers/LoginController.inc';

require 'views/RegisterView.inc';
require 'views/LayoutView.inc';
require 'views/IndexView.inc';