import { Observable }        from 'rxjs/Rx';
import { Component, OnInit } from '@angular/core';
import { Router }            from '@angular/router';
import { Subject }           from 'rxjs/Subject';
import { PesquisaDeAlunoService } from './pesquisa-de-aluno.service';
import { Aluno }             from '../app/aluno';

@Component({
    selector: 'aluno-search',
    templateUrl: 'app/partials/pesquisa-de-aluno.component.html',
    styleUrls:  ['app/css/pesquisa-de-aluno.component.css'],
    providers: [PesquisaDeAlunoService]
})

export class PesquisaDeAlunoComponent implements OnInit {
    alunos: Observable<Aluno[]>;
    private searchTerms = new Subject<string>();
    constructor(
        private pesquisaDeAlunoService: PesquisaDeAlunoService,
        private router: Router) {}

    // Push a search termo into the observable stream.
    search(termo: string): void {
        this.searchTerms.next(termo);
    }

    ngOnInit(): void {
        this.alunos = this.searchTerms
            .debounceTime(300)        // wait for 300ms pause in events
            .distinctUntilChanged()   // ignore if next search term is same as previous
            .switchMap(termo => termo   // switch to new observable each time
                // return the http search observable
                ? this.pesquisaDeAlunoService.pesquisa(termo)
                // or the observable of empty heroes if no search term
                : Observable.of<Aluno[]>([]))
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
