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
var router_1 = require('@angular/router');
var aluno_service_1 = require('./aluno.service');
var router_2 = require('@angular/router');
var validation_service_1 = require('./validation.service');
var forms_1 = require('@angular/forms');
var ExibirAlunoComponent = (function () {
    function ExibirAlunoComponent(alunoService, fb, route, router) {
        this.alunoService = alunoService;
        this.fb = fb;
        this.route = route;
        this.router = router;
        this.aluno = null;
        this.isDesabilitado = true;
        // Adicionar campos aqui!
        this.exibirEditar = true;
        this.exibirAlterar = false;
        this.mensagem = "Esta mensagem será alterada ao exibir!";
        this.visibilidade = "hidden";
        this.cor = "blue";
        this.exibirCadastrar = false;
        // Em javascript se uma função é chamada faltando argumentos (menos do que declarado), os valores que estiverem
        // faltando são designados para undefined. Já em typescript podemos definir o parâmetro como opcional com ?.
        // Resseta para cada campo a mensagem
        this.formErrors = {
            'nome': '',
            'cpf': '',
            'endereco': '',
            'telefone': '',
            'cartao': '',
            'email': ''
        };
    }
    // Adicionar métodos
    ExibirAlunoComponent.prototype.ngOnInit = function () {
        var _this = this;
        console.log('executando ngOninit de ExibirAlunoComponent');
        var id = +this.route.snapshot.params['id'];
        console.log('id = ', id);
        // id =  NaN
        if (isNaN(id)) {
            this.novo();
            this.buildForm(this.aluno);
        }
        else {
            this.alunoService.getAluno(id)
                .subscribe(function (data) {
                _this.aluno = data;
                _this.buildForm(_this.aluno);
            }, function (err) {
                _this.mensagem = "Aluno NÃO encontrado! Status:" + err.status;
                _this.cor = "red";
                _this.visibilidade = "visible";
            });
        }
    };
    ExibirAlunoComponent.prototype.buildForm = function (umAluno) {
        var _this = this;
        this.usuarioGroup = this.fb.group({
            'id': [umAluno.id],
            'foto': [umAluno.foto],
            'nome': [umAluno.nome, [forms_1.Validators.required, validation_service_1.ValidationService.nomeValido]],
            'endereco': [umAluno.endereco, [forms_1.Validators.required, validation_service_1.ValidationService.enderecoValidator]],
            'telefone': [umAluno.telefone, [forms_1.Validators.required, validation_service_1.ValidationService.telefoneValidator]],
            'sexo': [umAluno.sexo, [forms_1.Validators.required]],
            'cidade': [umAluno.cidade, [forms_1.Validators.required]],
            'cpf': [umAluno.cpf, [forms_1.Validators.required, validation_service_1.ValidationService.cpfValido]],
            'estado': [umAluno.estado, [forms_1.Validators.required]],
            'cartao': [umAluno.cartao, [forms_1.Validators.required, validation_service_1.ValidationService.creditCardValidator]],
            'bairro': [umAluno.bairro, [forms_1.Validators.required]],
            'email': [umAluno.email, [forms_1.Validators.required, validation_service_1.ValidationService.emailValidator]]
        });
        this.usuarioGroup.valueChanges.subscribe(function (data) { return _this.onValueChanged(data); });
        //      this.usuarioGroup.valueChanges.subscribe(function(data) { this.onValueChanged(data)} );
        this.onValueChanged(); // (re)setando as mensagens de validação agora.
    };
    ExibirAlunoComponent.prototype.onValueChanged = function (data) {
        console.log('data = ', data);
        // data =  Object {nome: "1", cpf: "", dataNasc: "", doacao: ""}
        var form = this.usuarioGroup;
        for (var field in this.formErrors) {
            this.formErrors[field] = ''; // limpando mensagens de erro anteriores - o mesmo que this.formErrors.nome ...
            // control representa cada um dos 4 campos de usuarioGroup acima.
            var control = form.get(field);
            if (control && !control.valid) {
                var messages = validation_service_1.ValidationService.validationMessages[field]; // O mesmo que ValidationService.validationMessages.nome, etc
                console.log('messages = ', messages);
                // messages =  Object {required: "Campo Nome de preenchimento obrigatório", invalidNome: "Nome inválido"}
                // messages =  Object {required: "Campo CPF de preenchimento obrigatório", invalidCPF: "CPF inválido"}
                // messages =  Object {required: "Campo Data de Nasc de preenchimento obrigatório"}
                // messages =  Object {required: "Campo Salário de preenchimento obrigatório", invalidValorMonetario: "Salário inválido"}
                for (var key in control.errors) {
                    console.log('key = ', key);
                    // key =  invalidNome
                    // key =  required
                    // key =  required
                    // key =  required
                    this.formErrors[field] += messages[key] + ' ';
                    console.log('this.formErrors[field] = ', this.formErrors[field]);
                }
            }
        }
    };
    //Fim
    ExibirAlunoComponent.prototype.novo = function () {
        this.isDesabilitado = false;
        this.exibirEditar = false;
        this.exibirCadastrar = true;
        this.exibirAlterar = false;
        this.visibilidade = "hidden";
        this.aluno = {
            id: null,
            nome: '',
            sexo: '',
            endereco: '',
            bairro: '',
            cidade: '',
            estado: '',
            telefone: '',
            foto: 'avatar.png',
            cpf: '',
            cartao: '',
            email: ''
        };
    };
    ExibirAlunoComponent.prototype.editavel = function () {
        this.isDesabilitado = false;
        this.exibirEditar = false;
        this.exibirAlterar = true;
        this.visibilidade = "hidden";
        this.exibirCadastrar = false;
    };
    ExibirAlunoComponent.prototype.salvo = function () {
        this.isDesabilitado = true;
        this.exibirEditar = true;
        this.exibirAlterar = false;
        this.exibirCadastrar = false;
    };
    ExibirAlunoComponent.prototype.cadastrar = function (aluno) {
        var _this = this;
        this.salvo();
        this.alunoService.cadastrar(aluno)
            .subscribe(function (resposta) {
            console.log(resposta);
            _this.mensagem = "Sócio cadastrado com sucesso!";
            _this.cor = "blue";
            _this.visibilidade = "visible";
        }, function (err) {
            _this.mensagem = "Sócio NÃO cadastrado! Status:" + err.status;
            _this.cor = "red";
            _this.visibilidade = "visible";
        });
    };
    ExibirAlunoComponent.prototype.alterar = function (aluno) {
        var _this = this;
        this.salvo();
        this.alunoService.atualizar(aluno)
            .subscribe(function (resposta) {
            console.log(resposta);
            _this.mensagem = "Sócio alterado com sucesso!";
            _this.cor = "blue";
            _this.visibilidade = "visible";
        }, function (err) {
            _this.mensagem = "Sócio NÃO alterado! Status:" + err.status;
            _this.cor = "red";
            _this.visibilidade = "visible";
        });
    };
    ExibirAlunoComponent.prototype.voltar = function () {
        var link = ['/alunos/exibirtodos'];
        this.router.navigate(link);
        // window.history.back();
    };
    // Adicionar métodos getVisibilidade() e getCor()
    ExibirAlunoComponent.prototype.getVisibilidade = function () {
        return this.visibilidade;
    };
    ExibirAlunoComponent.prototype.getCor = function () {
        return this.cor;
    };
    ExibirAlunoComponent = __decorate([
        core_1.Component({
            selector: 'exibir-aluno',
            templateUrl: 'app/partials/exibir-aluno.component.html',
            styleUrls: ['app/css/exibir-aluno.css']
        }), 
        __metadata('design:paramtypes', [aluno_service_1.AlunoService, forms_1.FormBuilder, router_1.ActivatedRoute, router_2.Router])
    ], ExibirAlunoComponent);
    return ExibirAlunoComponent;
}());
exports.ExibirAlunoComponent = ExibirAlunoComponent;
//# sourceMappingURL=exibir-aluno.component.js.map