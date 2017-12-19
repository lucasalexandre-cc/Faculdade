import { ModuleWithProviders }   from '@angular/core';
import { Routes, RouterModule }  from '@angular/router';
import { HomeComponent }         from './home.component';
import { QuemsomosComponent }    from './quemsomos.component';
import { ExibirAlunosComponent } from './exibir-alunos.component';
import { ExibirAlunoComponent }  from './exibir-aluno.component';

const appRoutes: Routes = [
    { path: '', redirectTo: '/home', pathMatch: 'full' },
    { path: 'home', component: HomeComponent },
    { path: 'quemsomos', component: QuemsomosComponent },
    { path: 'alunos/cadastrar', component: ExibirAlunoComponent },
    { path: 'alunos/exibirtodos', component: ExibirAlunosComponent },
    { path: 'alunos/:id', component: ExibirAlunoComponent }
];

export const routing: ModuleWithProviders = RouterModule.forRoot(appRoutes);

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
