"use strict";
var InMemoryDataService = (function () {
    function InMemoryDataService() {
    }
    InMemoryDataService.prototype.createDb = function () {
        var alunos = [
            { id: 1, nome: 'Jorge Barroso Fonseca', sexo: 'M', profissao: '1', endereco: 'Rua Voluntários da Pátria 320 apto 201', bairro: 'Botafogo', cidade: 'Rio de Janeiro', estado: 'RJ', telefone: '996529783', foto: 'boy.png', cpf: '', cartao: '', email: '' },
            { id: 2, nome: 'Ricardo de Abreu Nogueira', sexo: 'M', profissao: '2', endereco: 'Rua das Laranjeiras 100 apto 112', bairro: 'Laranjeiras', cidade: 'Rio de Janeiro', estado: 'RJ', telefone: '984732495', foto: 'boy-1.png', cpf: '', cartao: '', email: '' },
            { id: 3, nome: 'Elizete Barbosa Noronha', sexo: 'F', profissao: '2', endereco: 'Rua Nascimento Silva 107 apto 103', bairro: 'Ipanema', cidade: 'Rio de Janeiro', estado: 'RJ', telefone: '974596231', foto: 'girl-1.png', cpf: '', cartao: '', email: '' },
            { id: 4, nome: 'Roberto de Araujo Silas', sexo: 'M', profissao: '4', endereco: 'Rua N.S. de Copacabana 1327 apto 604', bairro: 'Copacabana', cidade: 'Rio de Janeiro', estado: 'RJ', telefone: '99563188', foto: 'boy-2.png', cpf: '', cartao: '', email: '' },
            { id: 5, nome: 'Pedro Arnaldo Soares', sexo: 'M', profissao: '3', endereco: 'Rua das Palmeiras 34 apto 303', bairro: 'Botafogo', cidade: 'Rio de Janeiro', estado: 'RJ', telefone: '978765658', foto: 'boy-3.png', cpf: '', cartao: '', email: '' },
            { id: 6, nome: 'Maria Clara Pertence', sexo: 'F', profissao: '1', endereco: 'Rua Barão de Lucena 23 apto 703', bairro: 'Botafogo', cidade: 'Rio de Janeiro', estado: 'RJ', telefone: '984286655', foto: 'girl-2.png', cpf: '', cartao: '', email: '' },
            { id: 7, nome: 'Joana Soares Peçanha', sexo: 'F', profissao: '3', endereco: 'Rua Bambina 120 casa 3', bairro: 'Botafogo', cidade: 'Rio de Janeiro', estado: 'RJ', telefone: '976433425', foto: 'girl-3.png', cpf: '', cartao: '', email: '' },
            { id: 8, nome: 'Sonia Rodrigues Silva', sexo: 'F', profissao: '5', endereco: 'Rua Conde de Irajá 65 apto 203', bairro: 'Botafogo', cidade: 'Rio de Janeiro', estado: 'RJ', telefone: '997762234', foto: 'girl-4.png', cpf: '', cartao: '', email: '' },
            { id: 9, nome: 'Vinicius Aguiar Santana', sexo: 'M', profissao: '5', endereco: 'Rua Vinicius de Moraes 12 apto 1001', bairro: 'Ipanema', cidade: 'Rio de Janeiro', estado: 'RJ', telefone: '9961964467', foto: 'boy-4.png', cpf: '', cartao: '', email: '' },
            { id: 10, nome: 'Luis Carlos Noronha', sexo: 'M', profissao: '6', endereco: 'Rua Cosme Velho 67 apto 302', bairro: 'Cosme Velho', cidade: 'Rio de Janeiro', estado: 'RJ', telefone: '995772290', foto: 'boy-5.png', cpf: '', cartao: '', email: '' }
        ];
        return { alunos: alunos };
    };
    return InMemoryDataService;
}());
exports.InMemoryDataService = InMemoryDataService;
//# sourceMappingURL=in-memory-data.service.js.map