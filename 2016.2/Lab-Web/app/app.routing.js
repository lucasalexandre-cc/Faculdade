"use strict";
var router_1 = require('@angular/router');
var home_component_1 = require('./home.component');
var quemsomos_component_1 = require('./quemsomos.component');
var exibir_alunos_component_1 = require('./exibir-alunos.component');
var exibir_aluno_component_1 = require('./exibir-aluno.component');
var appRoutes = [
    { path: '', redirectTo: '/home', pathMatch: 'full' },
    { path: 'home', component: home_component_1.HomeComponent },
    { path: 'quemsomos', component: quemsomos_component_1.QuemsomosComponent },
    { path: 'alunos/cadastrar', component: exibir_aluno_component_1.ExibirAlunoComponent },
    { path: 'alunos/exibirtodos', component: exibir_alunos_component_1.ExibirAlunosComponent },
    { path: 'alunos/:id', component: exibir_aluno_component_1.ExibirAlunoComponent }
];
exports.routing = router_1.RouterModule.forRoot(appRoutes);
/*

 A redirect route requires a pathMatch property to tell the router how to match a URL to the path of a route. In this
 app, the router should select the route to the HomeComponent when the entire URL matches '', so we set the pathMatch
 value to 'full'.

 Technically, pathMatch = 'full' results in a route hit when the remaining, unmatched segments of the URL match ''. In
 our example, the redirect is at the top level of the route configuration tree so the remaining URL and the entire URL
 are the same thing.

 The other possible pathMatch value is 'prefix' which tells the router to match the redirect route when the remaining
 URL begins with the redirect route's prefix path.

 Exemplo:

 path: 'alunos', redirectTo: '/alunos/cadastrar', pathMatch: 'prefix' }

*/
//# sourceMappingURL=app.routing.js.map