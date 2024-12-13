#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(){
    // Configurações para exibir acentuação no CMD
    setlocale(LC_ALL, "");
    system("chcp 65001 > nul");

    system("color a");
    printf("=======================================\n");
    printf("    INICIANDO SCRIPT DE COMPLIANCE     \n");
    printf("=======================================\n\n");

    int status;

    // Parar o serviço MBAMAgent
    printf("[1/7] Parando o serviço MBAMAgent...\n");
    status = system("net stop MBAMAgent");
    if (status != 0){
        printf("ERRO: Não foi possível parar o serviço MBAMAgent.\n");
        return 1;
    }
    printf("Serviço MBAMAgent parado com sucesso.\n\n");

    // Importar configurações de registro
    printf("[2/7] Aplicando configurações de registro para o BitLocker...\n");
    status = system("reg import \"\\\\brsaoapp121\\Installer_Bitlocker\\MBAM 2.5 SP1Installers\\Installers\\x64\\Bitlocker_frequency.reg\"");
    if (status != 0){
        printf("ERRO: Falha ao aplicar o arquivo de registro. Verifique o caminho ou as permissões.\n");
        return 1;
    }
    printf("Configurações de registro aplicadas com sucesso.\n\n");

    // Abrir o MMC e aguardar fechamento
    printf("[3/7] Abrindo o MMC para verificação manual...\n");
    status = system("mmc");
    if (status != 0){
        printf("ERRO: Não foi possível abrir o MMC.\n");
        return 1;
    }
    printf("MMC fechado. Continuando...\n\n");

    // Reiniciar o serviço MBAMAgent
    printf("[4/7] Reiniciando o serviço MBAMAgent...\n");
    status = system("net start MBAMAgent");
    if (status != 0){
        printf("ERRO: Falha ao reiniciar o serviço MBAMAgent.\n");
        return 1;
    }
    printf("Serviço MBAMAgent iniciado com sucesso.\n\n");

    // Atualizar políticas de grupo
    printf("[5/7] Atualizando as políticas de grupo...\n");
    status = system("gpupdate /force");
    if (status != 0){
        printf("ERRO: Não foi possível atualizar as políticas de grupo.\n");
        return 1;
    }
    printf("Políticas de grupo atualizadas com sucesso.\n\n");

    // Exibir o nome do host e abrir configurações "Sobre"
    printf("[6/7] Abrindo configurações do sistema para captura de tela...\n");
    status = system("start ms-settings:about");
    if (status != 0){
        printf("ERRO: Não foi possível abrir as configurações do sistema.\n");
        return 1;
    }
    printf("Configurações do sistema abertas com sucesso.\n\n");

    // Exibir protetores do BitLocker e Hostname
    printf("[7/7] Obtendo protetores do BitLocker e Hostname...\n");
    status = system("manage-bde -protectors -get c:");
    status = system("hostname");
    if (status != 0){
        printf("ERRO: Não foi possível obter as informações solicitadas.\n");
        return 1;
    }
    printf("Informações exibidas com sucesso.\n\n");

    // Finalizar
    printf("=======================================\n");
    printf("    SCRIPT CONCLUÍDO COM SUCESSO!      \n");
    printf("=======================================\n");
    printf("Pressione ENTER para sair.\n");
    getchar();

    return 0;
}
