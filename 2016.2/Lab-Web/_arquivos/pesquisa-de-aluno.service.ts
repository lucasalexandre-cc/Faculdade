import { Injectable }              from '@angular/core';
import { Http, Response } from '@angular/http';   // <== Response
import { Observable }              from 'rxjs';            // <== Observable
import { Aluno }                   from "../app/aluno";

@Injectable()
export class PesquisaDeAlunoService {

    constructor(private http: Http) {}

    // The http.get() call is similar to the ones above, although the URL now has a query string. Another notable
    // difference: we no longer call toPromise, we simply return the observable instead.
    pesquisa(termo: string): Observable<Aluno[]> {
        return this.http
            .get(`app/alunos/?nome=${termo}`)
            .map((r: Response) => r.json().data as Aluno[]);
    }
}