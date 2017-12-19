import { Component, OnInit } from '@angular/core';
import { AlunoService }      from './aluno.service';
import { Aluno }             from './aluno';
import { Router }            from '@angular/router';

@Component({
    selector: 'exibir-alunos',
    templateUrl: 'app/partials/exibir-alunos.component.html',
    styleUrls: ['app/css/exibir-alunos.css']
})

export class ExibirAlunosComponent implements OnInit {

    alunos : Aluno[] = [];
    erroAlunos: string = '';

    constructor(private alunoService: AlunoService, private router: Router) {}

    ngOnInit(): void {
        console.log('executou ngOnInit() de ExibirAlunosComponent');
        this.getAlunos();
    }

    gotoAluno(aluno: Aluno): void {
        let link = ['/alunos', aluno.id];
        console.log('link = ' + link);
        this.router.navigate(link);
    }

    getAlunos(): void {
        this.alunoService.getAlunos()
            .subscribe(
                resposta => {
                    this.alunos = resposta;
                },
                erro => {
                    this.erroAlunos = erro;
                }
            );
    }

    // Of course, we delegate aluno deletion to the aluno service, but the component is still responsible for
    // updating the display: it removes the deleted aluno from the array and resets the selected aluno if
    // necessary.
    remover(aluno: Aluno): void {
        this.alunoService.remover(aluno.id)
            .subscribe(
                resposta => {
                    this.getAlunos();
                    // this.alunos = this.alunos.filter(a => a !== aluno);
                }
            );
    }
}
