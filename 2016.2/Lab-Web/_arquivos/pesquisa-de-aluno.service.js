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
var http_1 = require('@angular/http'); // <== Response
var PesquisaDeAlunoService = (function () {
    function PesquisaDeAlunoService(http) {
        this.http = http;
    }
    // The http.get() call is similar to the ones above, although the URL now has a query string. Another notable
    // difference: we no longer call toPromise, we simply return the observable instead.
    PesquisaDeAlunoService.prototype.pesquisa = function (termo) {
        return this.http
            .get("app/alunos/?nome=" + termo)
            .map(function (r) { return r.json().data; });
    };
    PesquisaDeAlunoService = __decorate([
        core_1.Injectable(), 
        __metadata('design:paramtypes', [http_1.Http])
    ], PesquisaDeAlunoService);
    return PesquisaDeAlunoService;
}());
exports.PesquisaDeAlunoService = PesquisaDeAlunoService;
//# sourceMappingURL=pesquisa-de-aluno.service.js.map