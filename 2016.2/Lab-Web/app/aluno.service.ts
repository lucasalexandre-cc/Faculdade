import { Injectable }    from '@angular/core';
import { Http, Headers } from '@angular/http';
import { Aluno }         from './aluno';
import { Observable }    from 'rxjs/Rx';   // Importa todos os operadores de Observable

@Injectable()
export class AlunoService {

    constructor(private http: Http) {}

    private totalAlunos = 10;          // <<===
    private alunosUrl = 'app/alunos';  // URL to web api


    getAluno(id: number): Observable<Aluno> {
        return this.http.get(this.alunosUrl + `/?id=${id}`)
            .map(response => {
                console.log(response.json());
                console.log(response.json().data);
                var alunos: Aluno[] = response.json().data as Aluno[];
                return alunos[0];
            })
            .catch(erro => {
                return Observable.throw('status - ' + (erro.status) + ' '
                    + (erro.statusText) + ' - '
                    + (erro._body));
            })
    }

    getAlunos(): Observable<Aluno[]> {
        return this.http.get(this.alunosUrl)
            .map(response => {
                console.log(response.json());
                console.log(response.json().data);
                return response.json().data as Aluno[];
            })
            .catch(erro => {
                return Observable.throw('status - ' + (erro.status) + ' '
                    + (erro.statusText) + ' - '
                    + (erro._body));
            })
    }

    // Aqui!!!
    private headers = new Headers({'Content-Type': 'application/json'});

    // We identify which aluno the server should update by encoding the aluno id in the URL. The put body is the
    // JSON string encoding of the aluno, obtained by calling JSON.stringify. We identify the body content  type
    // (application/json) in the request header.

    atualizar(aluno: Aluno): Observable<Aluno> {
        const url = `${this.alunosUrl}/${aluno.id}`;
        return this.http.put(url, JSON.stringify(aluno), {headers: this.headers})
            .map(() => {
                console.log(url);
                return aluno;
            })
            .catch(erro => {
                return Observable.throw('status - ' + (erro.status) + ' '
                    + (erro.statusText) + ' - '
                    + (erro._body));
            })
    }

    cadastrar(aluno: Aluno): Observable<Aluno> {
        aluno.id = ++this.totalAlunos;
        const url = `${this.alunosUrl}/${aluno.id}`;
        return this.http.post(url, JSON.stringify(aluno), {headers: this.headers})
            .map(() => {
                console.log(url);
                return aluno;
            })
            .catch(erro => {
                return Observable.throw('status - ' + (erro.status) + ' '
                    + (erro.statusText) + ' - '
                    + (erro._body));
            })
    }

    remover(id: number): Observable<void> {
        let url = `${this.alunosUrl}/${id}`;
        return this.http.delete(url, {headers: this.headers})
            .map(() => {
                console.log(url);
            })
            .catch(erro => {
                return Observable.throw('status - ' + (erro.status) + ' '
                    + (erro.statusText) + ' - '
                    + (erro._body));
            })
    }
}