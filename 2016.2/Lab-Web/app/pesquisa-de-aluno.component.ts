import { Observable }        from 'rxjs/Rx';
import { Component, OnInit } from '@angular/core';
import { Router }            from '@angular/router';
import { Subject }           from 'rxjs/Subject';
import { PesquisaDeAlunoService } from './pesquisa-de-aluno.service';
import { Aluno }             from './aluno';

@Component({
    selector: 'aluno-search',
    templateUrl: 'app/partials/pesquisa-de-aluno.component.html',
    styleUrls:  ['app/css/pesquisa-de-aluno.component.css'],
    providers: [PesquisaDeAlunoService]
})

export class PesquisaDeAlunoComponent implements OnInit {
    alunos: Observable<Aluno[]>;
    private searchTerms = new Subject<string>();

    // assunto = new Subject();

    constructor(
        private pesquisaDeAlunoService: PesquisaDeAlunoService,
        private router: Router) {}

    // Push a search termo into the observable stream.
    search(termo: string): void {
        console.log('executou search de PesquisaDeAlunoComponent(' + termo + ')');
        this.searchTerms.next(termo);
        // this.assunto.next(2);
    }

    ngOnInit(): void {

        // this.assunto.subscribe(valor => console.log('valor = ', valor));

        this.alunos = this.searchTerms
            .debounceTime(2000)        // wait for 300ms pause in events
            .distinctUntilChanged()   // ignore if next search term is same as previous
            .switchMap(termo => termo ? this.pesquisaDeAlunoService.pesquisa(termo) : Observable.of<Aluno[]>([]))
            .catch(error => {
                // TODO: real error handling
                console.log(error);
                return Observable.of<Aluno[]>([]);
            });
    }

    gotoAluno(aluno: Aluno): void {
        let link = ['/alunos', aluno.id];
        this.router.navigate(link);
    }
}
