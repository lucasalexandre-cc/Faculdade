import { NgModule }              from '@angular/core';
import { BrowserModule }         from '@angular/platform-browser';
import { FormsModule,ReactiveFormsModule }           from '@angular/forms';
import { HttpModule }            from '@angular/http';
import { routing }               from './app.routing';

// Imports for loading & configuring the in-memory web api
import { InMemoryWebApiModule }  from 'angular2-in-memory-web-api';
import { InMemoryDataService }   from './in-memory-data.service';

import { AppComponent }          from './app.component';
import { HomeComponent }         from './home.component';
import { QuemsomosComponent }    from './quemsomos.component';
import { ExibirAlunosComponent } from './exibir-alunos.component';
import { AlunoService }          from './aluno.service';
import { ExibirAlunoComponent }  from './exibir-aluno.component';
import { PesquisaDeAlunoComponent } from './pesquisa-de-aluno.component';

@NgModule({
    imports:      [ BrowserModule, FormsModule, HttpModule, InMemoryWebApiModule.forRoot(InMemoryDataService), routing,ReactiveFormsModule ],
    declarations: [ AppComponent, HomeComponent, QuemsomosComponent, ExibirAlunosComponent, ExibirAlunoComponent, PesquisaDeAlunoComponent ],
    providers:    [ AlunoService ],
    bootstrap:    [ AppComponent ]
})

export class AppModule { }
