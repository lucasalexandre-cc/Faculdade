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
var http_1 = require('@angular/http');
var Rx_1 = require('rxjs/Rx'); // Importa todos os operadores de Observable
var AlunoService = (function () {
    function AlunoService(http) {
        this.http = http;
        this.totalAlunos = 10; // <<===
        this.alunosUrl = 'app/alunos'; // URL to web api
        // Aqui!!!
        this.headers = new http_1.Headers({ 'Content-Type': 'application/json' });
    }
    AlunoService.prototype.getAluno = function (id) {
        return this.http.get(this.alunosUrl + ("/?id=" + id))
            .map(function (response) {
            console.log(response.json());
            console.log(response.json().data);
            var alunos = response.json().data;
            return alunos[0];
        })
            .catch(function (erro) {
            return Rx_1.Observable.throw('status - ' + (erro.status) + ' '
                + (erro.statusText) + ' - '
                + (erro._body));
        });
    };
    AlunoService.prototype.getAlunos = function () {
        return this.http.get(this.alunosUrl)
            .map(function (response) {
            console.log(response.json());
            console.log(response.json().data);
            return response.json().data;
        })
            .catch(function (erro) {
            return Rx_1.Observable.throw('status - ' + (erro.status) + ' '
                + (erro.statusText) + ' - '
                + (erro._body));
        });
    };
    // We identify which aluno the server should update by encoding the aluno id in the URL. The put body is the
    // JSON string encoding of the aluno, obtained by calling JSON.stringify. We identify the body content  type
    // (application/json) in the request header.
    AlunoService.prototype.atualizar = function (aluno) {
        var url = this.alunosUrl + "/" + aluno.id;
        return this.http.put(url, JSON.stringify(aluno), { headers: this.headers })
            .map(function () {
            console.log(url);
            return aluno;
        })
            .catch(function (erro) {
            return Rx_1.Observable.throw('status - ' + (erro.status) + ' '
                + (erro.statusText) + ' - '
                + (erro._body));
        });
    };
    AlunoService.prototype.cadastrar = function (aluno) {
        aluno.id = ++this.totalAlunos;
        var url = this.alunosUrl + "/" + aluno.id;
        return this.http.post(url, JSON.stringify(aluno), { headers: this.headers })
            .map(function () {
            console.log(url);
            return aluno;
        })
            .catch(function (erro) {
            return Rx_1.Observable.throw('status - ' + (erro.status) + ' '
                + (erro.statusText) + ' - '
                + (erro._body));
        });
    };
    AlunoService.prototype.remover = function (id) {
        var url = this.alunosUrl + "/" + id;
        return this.http.delete(url, { headers: this.headers })
            .map(function () {
            console.log(url);
        })
            .catch(function (erro) {
            return Rx_1.Observable.throw('status - ' + (erro.status) + ' '
                + (erro.statusText) + ' - '
                + (erro._body));
        });
    };
    AlunoService = __decorate([
        // Importa todos os operadores de Observable
        core_1.Injectable(), 
        __metadata('design:paramtypes', [http_1.Http])
    ], AlunoService);
    return AlunoService;
}());
exports.AlunoService = AlunoService;
//# sourceMappingURL=aluno.service.js.map