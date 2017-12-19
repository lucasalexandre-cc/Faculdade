"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};
var Rx_1 = require('rxjs/Rx');
var core_1 = require('@angular/core');
var router_1 = require('@angular/router');
var Subject_1 = require('rxjs/Subject');
var pesquisa_de_aluno_service_1 = require('./pesquisa-de-aluno.service');
var PesquisaDeAlunoComponent = (function () {
    // assunto = new Subject();
    function PesquisaDeAlunoComponent(pesquisaDeAlunoService, router) {
        this.pesquisaDeAlunoService = pesquisaDeAlunoService;
        this.router = router;
        this.searchTerms = new Subject_1.Subject();
    }
    // Push a search termo into the observable stream.
    PesquisaDeAlunoComponent.prototype.search = function (termo) {
        console.log('executou search de PesquisaDeAlunoComponent(' + termo + ')');
        this.searchTerms.next(termo);
        // this.assunto.next(2);
    };
    PesquisaDeAlunoComponent.prototype.ngOnInit = function () {
        // this.assunto.subscribe(valor => console.log('valor = ', valor));
        var _this = this;
        this.alunos = this.searchTerms
            .debounceTime(2000) // wait for 300ms pause in events
            .distinctUntilChanged() // ignore if next search term is same as previous
            .switchMap(function (termo) { return termo ? _this.pesquisaDeAlunoService.pesquisa(termo) : Rx_1.Observable.of([]); })
            .catch(function (error) {
            // TODO: real error handling
            console.log(error);
            return Rx_1.Observable.of([]);
        });
    };
    PesquisaDeAlunoComponent.prototype.gotoAluno = function (aluno) {
        var link = ['/alunos', aluno.id];
        this.router.navigate(link);
    };
    PesquisaDeAlunoComponent = __decorate([
        core_1.Component({
            selector: 'aluno-search',
            templateUrl: 'app/partials/pesquisa-de-aluno.component.html',
            styleUrls: ['app/css/pesquisa-de-aluno.component.css'],
            providers: [pesquisa_de_aluno_service_1.PesquisaDeAlunoService]
        }), 
        __metadata('design:paramtypes', [pesquisa_de_aluno_service_1.PesquisaDeAlunoService, router_1.Router])
    ], PesquisaDeAlunoComponent);
    return PesquisaDeAlunoComponent;
}());
exports.PesquisaDeAlunoComponent = PesquisaDeAlunoComponent;
//# sourceMappingURL=pesquisa-de-aluno.component.js.map