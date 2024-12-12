#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    // Configura��es para exibir acentua��o no CMD
    setlocale(LC_ALL, "");
    system("chcp 65001 > nul");
    system("color a");

    // Verifica se o programa est� sendo executado como administrador
    system("cls");
    printf("=======================================\n");
    printf("    INICIANDO SCRIPT DE COMPLIANCE     \n");
    printf("=======================================\n\n");
    printf("Verificando permiss�es de administrador...\n");
    int status = system("net session >nul 2>&1");
    if (status != 0) {
        printf("\nERRO: Este programa deve ser executado como administrador.\n\n");
        printf("Por favor, execute novamente clicando com o bot�o direito no arquivo e escolhendo 'Executar como administrador'.\n\n");
        printf("Pressione ENTER para sair.\n");
        getchar();
        return 1;
    }
    printf("Permiss�es de administrador verificadas com sucesso.");

    // Parar o servi�o MBAMAgent
    system("cls");
    printf("[1/7] Parando o servi�o MBAMAgent...\n");
    status = system("net stop MBAMAgent");
    if (status != 0) {
        printf("ERRO: N�o foi poss�vel parar o servi�o MBAMAgent.\n");
        return 1;
    }
    printf("Servi�o MBAMAgent parado com sucesso.\n\n");

    // Importar configura��es de registro
    system("cls");
    printf("[2/7] Aplicando configura��es de registro para o BitLocker...\n");
    status = system("reg import \"\\\\brsaoapp121\\Installer_Bitlocker\\MBAM 2.5 SP1Installers\\Installers\\x64\\Bitlocker_frequency.reg\"");
    if (status != 0) {
        printf("ERRO: Falha ao aplicar o arquivo de registro. Verifique o caminho ou as permiss�es.\n");
        return 1;
    }
    printf("Configura��es de registro aplicadas com sucesso.\n\n");

    // Abrir o MMC e aguardar fechamento
    system("cls");
    printf("[3/7] Abrindo o MMC para verifica��o manual...\n");
    status = system("mmc");
    if (status != 0) {
        printf("ERRO: N�o foi poss�vel abrir o MMC.\n");
        return 1;
    }
    printf("MMC fechado. Continuando...\n\n");

    // Reiniciar o servi�o MBAMAgent
    system("cls");
    printf("[4/7] Reiniciando o servi�o MBAMAgent...\n");
    status = system("net start MBAMAgent");
    if (status != 0) {
        printf("ERRO: Falha ao reiniciar o servi�o MBAMAgent.\n");
        return 1;
    }
    printf("Servi�o MBAMAgent iniciado com sucesso.\n\n");

    // Atualizar pol�ticas de grupo
    system("cls");
    printf("[5/7] Atualizando as pol�ticas de grupo...\n");
    status = system("gpupdate /force");
    if (status != 0) {
        printf("ERRO: N�o foi poss�vel atualizar as pol�ticas de grupo.\n");
        return 1;
    }
    printf("Pol�ticas de grupo atualizadas com sucesso.\n\n");

    // Abrir configura��es "Sobre" para captura de tela
    system("cls");
    printf("[6/7] Abrindo configura��es do sistema...\n");
    status = system("start ms-settings:about");
    if (status != 0) {
        printf("ERRO: N�o foi poss�vel abrir as configura��es do sistema.\n");
        return 1;
    }
    printf("Configura��es do sistema abertas com sucesso.\n\n");

    // Exibir protetores do BitLocker e Hostname para captura de tela
    system("cls");
    printf("[7/7] Exibindo protetores do BitLocker e Hostname...\n");
    status = system("manage-bde -protectors -get c:");
    status = system("hostname");
    if (status != 0) {
        printf("ERRO: N�o foi poss�vel obter as informa��es solicitadas.\n");
        return 1;
    }
    printf("Protetores do BitLocker e Hostname exibidos com sucesso.\n\n");

    // Finalizar
    printf("=======================================\n");
    printf("    SCRIPT CONCLU�DO COM SUCESSO!      \n");
    printf("=======================================\n");
    printf("Pressione ENTER para sair.\n");
    getchar();

    return 0;
}