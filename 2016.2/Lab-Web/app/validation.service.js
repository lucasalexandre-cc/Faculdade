"use strict";
var ValidationService = (function () {
    function ValidationService() {
    }
    ValidationService.nomeValido = function (control) {
        if (ValidationService.validaNome(control.value)) {
            return null;
        }
        else {
            return { 'invalidNome': true };
        }
    };
    ValidationService.cpfValido = function (control) {
        if (ValidationService.validaCPF(control.value)) {
            return null;
        }
        else {
            return { 'invalidCPF': true };
        }
    };
    ValidationService.dataValida = function (control) {
        if (ValidationService.validaData(control.value)) {
            return null;
        }
        else {
            return { 'invalidDate': true };
        }
    };
    ValidationService.valorMonetarioValido = function (control) {
        if (ValidationService.validaValorMonetario(control.value)) {
            return null;
        }
        else {
            return { 'invalidValorMonetario': true };
        }
    };
    ValidationService.creditCardValidator = function (control) {
        if (control.value.match(/^(?:4[0-9]{12}(?:[0-9]{3})?|5[1-5][0-9]{14}|6(?:011|5[0-9][0-9])[0-9]{12}|3[47][0-9]{13}|3(?:0[0-5]|[68][0-9])[0-9]{11}|(?:2131|1800|35\d{3})\d{11})$/)) {
            return null;
        }
        else {
            return { 'invalidCreditCard': true };
        }
    };
    ValidationService.emailValidator = function (control) {
        if (control.value.match(/[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?/)) {
            return null;
        }
        else {
            return { 'invalidEmail': true };
        }
    };
    ValidationService.enderecoValidator = function (control) {
        if (control.value.match(/[a-zA-Z][a-zA-Z\s]*/)) {
            return null;
        }
        else {
            return { 'invalidEndereco': true };
        }
    };
    ValidationService.telefoneValidator = function (control) {
        if (control.value.match(/[0-9]+$/)) {
            return null;
        }
        else {
            return { 'invalidTelefone': true };
        }
    };
    ValidationService.celularValidator = function (control) {
        if (control.value.match(/[0-9]+$/)) {
            return null;
        }
        else {
            return { 'invalidCelular': true };
        }
    };
    // static passwordValidator(control) {
    //     // {6,100}           - Assert password is between 6 and 100 characters
    //     // (?=.*[0-9])       - Assert a string has at least one number
    //     if (control.value.match(/^(?=.*[0-9])[a-zA-Z0-9!@#$%^&*]{6,100}$/)) {
    //         return null;
    //     } else {
    //         return { 'invalidPassword': true };
    //     }
    // }
    // Métodos de validação para cada campo
    // ------------------------------------
    ValidationService.validaNome = function (nome) {
        // Nome nunca será null pois será se a cx de texto estiver vazia, enviará submetido um string vazio e não null
        // mas um botão de rádio, se não selecionado, não submete um parâmetro de requisição.
        if (nome == null || nome == "" || nome == 'undefined') {
            return true;
        }
        if (nome.match(/^[a-zA-Z ]*$/)) {
            return true;
        }
        else {
            return false;
        }
    };
    ValidationService.validaCPF = function (strCPF) {
        var soma;
        var resto;
        soma = 0;
        if (strCPF == null || strCPF == "") {
            return true;
        }
        if (strCPF == "00000000000")
            return false;
        // if (strCPF == "11111111111") return false;
        // if (strCPF == "22222222222") return false;
        var i;
        for (i = 1; i <= 9; i++)
            soma = soma + parseInt(strCPF.substring(i - 1, i)) * (11 - i);
        resto = (soma * 10) % 11;
        if ((resto == 10) || (resto == 11))
            resto = 0;
        if (resto != parseInt(strCPF.substring(9, 10)))
            return false;
        soma = 0;
        for (i = 1; i <= 10; i++)
            soma = soma + parseInt(strCPF.substring(i - 1, i)) * (12 - i);
        resto = (soma * 10) % 11;
        if ((resto == 10) || (resto == 11))
            resto = 0;
        if (resto != parseInt(strCPF.substring(10, 11)))
            return false;
        return true;
    };
    ValidationService.validaData = function (umaData) {
        if (umaData == null || umaData == "" || umaData == 'undefined') {
            return true;
        }
        var dataString = umaData;
        if (!/^\d{4}[-]\d{2}[-]\d{2}$/.test(dataString))
            return false;
        var partes = dataString.split("-");
        var ano = parseInt(partes[0], 10);
        var mes = parseInt(partes[1], 10);
        var dia = parseInt(partes[2], 10);
        if (ano < 1000 || ano > 2200 || mes == 0 || mes > 12)
            return false;
        var tamMes = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
        if (ano % 400 == 0 || (ano % 100 != 0 && ano % 4 == 0))
            tamMes[1] = 29;
        return dia > 0 && dia <= tamMes[mes - 1];
    };
    ;
    ValidationService.validaValorMonetario = function (valorMonetario) {
        if (valorMonetario == null || valorMonetario == "" || valorMonetario == 'undefined') {
            return true;
        }
        if (valorMonetario.match(/^([]|[0-9]{1,7}(,[0-9]{2})?)$/)) {
            return true;
        }
        else {
            return false;
        }
    };
    ValidationService.validationMessages = {
        'nome': {
            'required': 'Campo Nome de preenchimento obrigatório',
            'invalidNome': 'Nome inválido'
        },
        'cpf': {
            'required': 'Campo CPF de preenchimento obrigatório',
            'invalidCPF': 'CPF inválido'
        },
        'email': {
            'required': 'Campo Email de preenchimento obrigatório',
            'invalidEmail': 'Email inválido'
        },
        'endereco': {
            'required': 'Campo Endereço de preenchimento obrigatório',
            'invalidEndereco': 'Endereço inválido'
        },
        'telefone': {
            'required': 'Campo Telefone de preenchimento obrigatório',
            'invalidTelefone': 'Telefone inválido'
        },
        'celular': {
            'required': 'Campo Celular de preenchimento obrigatório',
            'invalidCelular': 'Celular inválido'
        },
        'cartao': {
            'required': 'Campo Cartão de preenchimento obrigatório',
            'invalidCelular': 'Cartão inválido'
        }
    };
    return ValidationService;
}());
exports.ValidationService = ValidationService;
//# sourceMappingURL=validation.service.js.map