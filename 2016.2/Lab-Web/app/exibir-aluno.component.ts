import { Component, OnInit }      from '@angular/core';
import { ActivatedRoute, Params } from '@angular/router';
import { AlunoService }           from './aluno.service';
import { Aluno }                  from './aluno';
import { Router }                 from '@angular/router';
import { ValidationService }      from './validation.service';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';


@Component({
    selector: 'exibir-aluno',
    templateUrl: 'app/partials/exibir-aluno.component.html',
    styleUrls: ['app/css/exibir-aluno.css']
})

export class ExibirAlunoComponent implements OnInit{

    alunos: Aluno[];
    aluno: Aluno = null;
    isDesabilitado: boolean = true;

    // Adicionar campos aqui!
    exibirEditar: boolean = true;
    exibirAlterar: boolean = false;
    mensagem: string = "Esta mensagem será alterada ao exibir!";
    visibilidade: string = "hidden";
    cor: string = "blue";

    exibirCadastrar: boolean = false;



    constructor(private alunoService:AlunoService,
                private fb: FormBuilder,
                private route:ActivatedRoute,
                private router: Router) { }

    // Adicionar métodos

    ngOnInit():void {
        console.log('executando ngOninit de ExibirAlunoComponent');

        let id = +this.route.snapshot.params['id'];
        console.log('id = ', id);
        // id =  NaN

        if (isNaN(id)) {
            this.novo();
            this.buildForm(this.aluno);
        }
        else {
            this.alunoService.getAluno(id)
                .subscribe(
                    data => {
                        this.aluno = data;
                        this.buildForm(this.aluno);
                    },
                    err => {
                        this.mensagem = "Aluno NÃO encontrado! Status:" + err.status;
                        this.cor = "red";
                        this.visibilidade = "visible";
                    }
                );
        }
    }

    //Mudança
    usuarioGroup: FormGroup;

    buildForm(umAluno: Aluno): void {
        this.usuarioGroup = this.fb.group({

            'id': [umAluno.id],
            'foto':[umAluno.foto],
            'nome': [umAluno.nome, [Validators.required, ValidationService.nomeValido]],
            'endereco': [umAluno.endereco,[Validators.required,ValidationService.enderecoValidator]],
            'telefone': [umAluno.telefone,[Validators.required,ValidationService.telefoneValidator]],
            'sexo': [umAluno.sexo,[Validators.required]],
            'cidade':[umAluno.cidade,[Validators.required]],
            'cpf':[umAluno.cpf,[Validators.required,ValidationService.cpfValido]],
            'estado':[umAluno.estado,[Validators.required]],
            'cartao':[umAluno.cartao,[Validators.required,ValidationService.creditCardValidator]],
            'bairro':[umAluno.bairro,[Validators.required]],
            'email':[umAluno.email,[Validators.required,ValidationService.emailValidator]]
        });
        this.usuarioGroup.valueChanges.subscribe(data => this.onValueChanged(data));
        //      this.usuarioGroup.valueChanges.subscribe(function(data) { this.onValueChanged(data)} );
        this.onValueChanged(); // (re)setando as mensagens de validação agora.
    }

    // Em javascript se uma função é chamada faltando argumentos (menos do que declarado), os valores que estiverem
    // faltando são designados para undefined. Já em typescript podemos definir o parâmetro como opcional com ?.

    // Resseta para cada campo a mensagem
    formErrors = {
        'nome': '',
        'cpf': '',
        'endereco':'',
        'telefone':'',
        'cartao':'',
        'email':''
    };




    onValueChanged(data?: any) {

        console.log('data = ', data);
        // data =  Object {nome: "1", cpf: "", dataNasc: "", doacao: ""}

        var form = this.usuarioGroup;
        for (var field in this.formErrors) {    // field irá valer: nome, cpf, dataNasc e doacao
            this.formErrors[field] = '';  // limpando mensagens de erro anteriores - o mesmo que this.formErrors.nome ...

            // control representa cada um dos 4 campos de usuarioGroup acima.
            var control = form.get(field);
            if (control && !control.valid) {
                var messages = ValidationService.validationMessages[field];  // O mesmo que ValidationService.validationMessages.nome, etc
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
                    // this.formErrors[nome] =  Nome inválido
                    // this.formErrors[cpf] =  Campo CPF de preenchimento obrigatório
                    // this.formErrors[dataNasc] =  Campo Data de Nasc de preenchimento obrigatório
                    // this.formErrors[doacao] =  Campo Salário de preenchimento obrigatório
                }
            }
        }
    }
    //Fim





    novo() {
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
            cpf:'',
            cartao:'',
            email:''
        }
    }

    editavel() {
        this.isDesabilitado = false;
        this.exibirEditar = false;
        this.exibirAlterar = true;
        this.visibilidade = "hidden";
        this.exibirCadastrar = false;
    }

    salvo() {
        this.isDesabilitado = true;
        this.exibirEditar = true;
        this.exibirAlterar = false;
        this.exibirCadastrar = false;
    }

    cadastrar(aluno: Aluno) {
        this.salvo();
        this.alunoService.cadastrar(aluno)
            .subscribe(
                resposta => {
                    console.log (resposta);
                    this.mensagem = "Sócio cadastrado com sucesso!";
                    this.cor = "blue";
                    this.visibilidade = "visible";
                },
                err => {
                    this.mensagem = "Sócio NÃO cadastrado! Status:" + err.status;
                    this.cor = "red";
                    this.visibilidade = "visible";
                }
            );
    }

    alterar(aluno: Aluno) {
        this.salvo();
        this.alunoService.atualizar(aluno)
            .subscribe(
                resposta => {
                    console.log (resposta);
                    this.mensagem = "Sócio alterado com sucesso!";
                    this.cor = "blue";
                    this.visibilidade = "visible";
                },
                err => {
                    this.mensagem = "Sócio NÃO alterado! Status:" + err.status;
                    this.cor = "red";
                    this.visibilidade = "visible";
                }
            );
    }

    voltar(): void {
        let link = ['/alunos/exibirtodos'];
        this.router.navigate(link);
        // window.history.back();
    }

    // Adicionar métodos getVisibilidade() e getCor()

    getVisibilidade() {
        return this.visibilidade;
    }

    getCor() {
        return this.cor;
    }

}
