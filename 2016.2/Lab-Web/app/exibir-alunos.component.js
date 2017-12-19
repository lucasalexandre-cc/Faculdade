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
var core_1 = require('@angular/core');
var aluno_service_1 = require('./aluno.service');
var router_1 = require('@angular/router');
var ExibirAlunosComponent = (function () {
    function ExibirAlunosComponent(alunoService, router) {
        this.alunoService = alunoService;
        this.router = router;
        this.alunos = [];
        this.erroAlunos = '';
    }
    ExibirAlunosComponent.prototype.ngOnInit = function () {
        console.log('executou ngOnInit() de ExibirAlunosComponent');
        this.getAlunos();
    };
    ExibirAlunosComponent.prototype.gotoAluno = function (aluno) {
        var link = ['/alunos', aluno.id];
        console.log('link = ' + link);
        this.router.navigate(link);
    };
    ExibirAlunosComponent.prototype.getAlunos = function () {
        var _this = this;
        this.alunoService.getAlunos()
            .subscribe(function (resposta) {
            _this.alunos = resposta;
        }, function (erro) {
            _this.erroAlunos = erro;
        });
    };
    // Of course, we delegate aluno deletion to the aluno service, but the component is still responsible for
    // updating the display: it removes the deleted aluno from the array and resets the selected aluno if
    // necessary.
    ExibirAlunosComponent.prototype.remover = function (aluno) {
        var _this = this;
        this.alunoService.remover(aluno.id)
            .subscribe(function (resposta) {
            _this.getAlunos();
            // this.alunos = this.alunos.filter(a => a !== aluno);
        });
    };
    ExibirAlunosComponent = __decorate([
        core_1.Component({
            selector: 'exibir-alunos',
            templateUrl: 'app/partials/exibir-alunos.component.html',
            styleUrls: ['app/css/exibir-alunos.css']
        }), 
        __metadata('design:paramtypes', [aluno_service_1.AlunoService, router_1.Router])
    ], ExibirAlunosComponent);
    return ExibirAlunosComponent;
}());
exports.ExibirAlunosComponent = ExibirAlunosComponent;
//# sourceMappingURL=exibir-alunos.component.js.map