#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

//Define os ponteiros.
FILE *base_de_dados;
FILE *base_de_dados1;
int opcao = 0, i;
char username[20], password[20], validadorsenha[30]; addusuario[20], newsenha[30], newsenha1[30], c, nmtxt[100], nmtxtl[100];
char rack_shaft[100], sala[100], ponto[50], swit[200], sc[3], porta_switch[100], porta_patchpanel[100], ler[1000], lersenha[21], senhapadrao[12], senha[21];
int main(void)
{
    setlocale(LC_ALL, "Portuguese_Brazil");
    //Caso o diret�rio especificado n�o exista, esta fun��o cria o diret�rio; caso j� exista, a fun��o apenas cria o arquivo e insere os dados conforme necess�rio.
    system("mkdir C:\\Documents\\Cable_Map\\Base_de_dados\\");
    system("attrib +H ""C:\\Documents\\Cable_Map");
    system("mkdir C:\\Documents\\Cable_Map\\Users");
    system("attrib +H ""C:\\Documents\\Cable_Map");
    system("mkdir C:\\Documents\\Cable_Map\\Base_de_dados");
    login();
}
void login(void)
{
    setlocale(LC_ALL, "Portuguese_Brazil");
    system("cls");
    system("color 02");
    setlocale(LC_ALL, "Portuguese_Brazil");
    system("cls");
    //Define a cor verde para todo o Console.
    system("color 02");
    printf("\n\t--==|Mapeamento de cabos|==--\n\n\n\n");
    printf("| Data: ");
    //Define a cor cinza para uma linha espec�fica.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    //Exibe a data.
    system("date/t");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("| Hora: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    //Exibe o hor�rio.
    system("time/t");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("\n|Usu�rio:\n| ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    fflush(stdin);
    scanf("%s", &username);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("\n|Senha:\n| ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    fflush(stdin);
    //M�scara de senha que oculta a entrada do usu�rio.
    while (1){
        c = getch();
            if (c == 13)
            {
                break;
            }
            else if(c == 8)
            {
                if(i > 0)
                {
                    i--;
                    printf("\b \b");
                    printf("");
                    password[i] = NULL;
                }
            }
            else
            {
            password[i] = c;
            printf("*");
            i++;
            }
    }   //Pausa a execu��o do c�digo por alguns segundos.
        Sleep(750);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        //Abre o diret�rio especificado, verifica o usu�rio e a senha; se tudo estiver correto, realiza o login.
        nmtxtl[0] = '\0';
        validadorsenha[0] = '\0';
        strcat(nmtxtl, "C:\\Documents\\Cable_Map\\Users\\");
        strcat(nmtxtl, username);
        strcat(nmtxtl, ".txt");
        base_de_dados = fopen(nmtxtl, "r");
            if(base_de_dados == NULL){
                fclose(base_de_dados);
                validadoradm();
            }
            else{
                while (fgets(lersenha, 21, base_de_dados) != NULL){
                     strcat(validadorsenha, lersenha);
                }
                if (strcmp(validadorsenha, password)==0 && strcmp(validadorsenha, "$3nh4P4drao")==1){
                    fclose(base_de_dados);
                    printf("\n\nLogin realizado com sucesso!\n");
                    printf("Carregando...");
                    Sleep(2000);
                    menu();
                }
                else{
                    while (fgets(lersenha, 21, base_de_dados) != NULL){
                        strcat(validadorsenha, lersenha);
                    }
                    if (strcmp(validadorsenha, "$3nh4P4drao")==0){
                        fclose(base_de_dados);
                        primeiroacesso();
                    }
                    else{
                         MessageBox(NULL, "Credenciais incorretas ou usu�rio n�o cadastrado\n      Entre em contato com a sua administra��o\n                                FECHANDO!", "ERRO", MB_ICONERROR | MB_APPLMODAL);
                        exit(0);
                    }
                }
        }
        fclose(base_de_dados);
}
//Esta fun��o desempenha o papel de permitir que o usu�rio substitua a senha padr�o por uma senha personalizada durante o seu primeiro acesso ao sistema.
void primeiroacesso(void){
    setlocale(LC_ALL, "Portuguese_Brazil");
    system("cls");
    system("color 02");
    printf("\n\t--==|Mapeamento de cabos|==--\n\n\n\n");
    printf("|Primeiro acesso|\n\n");
    printf("\n\nDigite e senha padr�o que lhe foi passada:\n| ");
    fflush(stdin);
    fflush(stdin);
    scanf("%s", &senhapadrao);
    printf("\n\n|Digite a nova senha:\n| ");
    fflush(stdin);
    scanf("%s", &newsenha1);
    printf("\n\n|Confirme a nova senha:\n| ");
    fflush(stdin);
    scanf("%s", &newsenha);
    //Verifica se o usu�rio informou a senha padr�o corretamente
    if (strcmp(senhapadrao, "$3nh4P4drao")==1 || strcmp(newsenha1, newsenha)==1)
    {
        MessageBox(NULL, "\tAs senhas n�o coincidem\n  Tente novamente!.", "ERRO", MB_ICONINFORMATION | MB_APPLMODAL);
        primeiroacesso();
    }
    //Registra a nova senha definida pelo usu�rio na base de dados.
    else{
        base_de_dados = fopen(nmtxtl, "w");
        fprintf(base_de_dados, "%s", newsenha);
        fclose(base_de_dados);
        MessageBox(NULL, "\tSenha alterada com sucesso!\n  Reinicie o sistema para concluir a configura��o.", "Aten��o", MB_ICONINFORMATION | MB_APPLMODAL);
        MessageBox(NULL, "Fechando!", "ATEN��O", MB_ICONINFORMATION | MB_APPLMODAL);
        Sleep(500);
        exit(0);
    }
}
//Verifica as credenciais para o login do administrador.
void validadoradm(void){
    setlocale(LC_ALL, "Portuguese_Brazil");
        if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0)
        {
            printf("\n\nLogin realizado com sucesso!\n");
            printf("Carregando...");
            Sleep(2000);
            menuadm();
        }
        else{
            //Exibe uma caixa de erro fora da IDE, informando que o usu�rio esgotou suas tentativas de login.
            MessageBox(NULL, "Credenciais incorretas ou usu�rio n�o cadastrado\n      Entre em contato com a sua administra��o\n                                FECHANDO!", "ERRO", MB_ICONERROR | MB_APPLMODAL);
            exit(0);
        }
}
//Exibe o menu do administrador.
void menuadm(void){
    setlocale(LC_ALL, "Portuguese_Brazil");
    fclose(base_de_dados);
    system("cls");
    system("color 02");
    printf("\n\t--==|Mapeamento de cabos|==--\n\n\n\n");
    printf(" Ol�, Administrador.\n\n");
    printf("| Data: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    system("date/t");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("| Hora: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    system("time/t");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("               ______\n");
    printf("  ____________| Menu |____________\n");
    printf(" |                                |\n");
    printf(" | * Digite apenas o n�mero       |\n");
    printf(" |   referente a op��o!           |\n");
    printf(" |                                |\n");
    printf(" | [1] Adicionar usu�rio          |\n");
    printf(" | [2] Ver/excluir usu�rios atuais|\n");
    printf(" | [3] Editar ou apagar caminho   |\n");
    printf(" | [4] Sair                       |\n");
    printf(" |________________________________|\n");
    printf("\n | OP��O: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    fflush(stdin);
    scanf("%d", &opcao);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4)){
        system("cls");
        //Exibe uma caixa de erro fora do Visual Studio Code, informando que o Administrador escolheu um op��o inv�lida
        MessageBox(NULL, "OP��O INV�LIDA!", "ERRO", MB_ICONERROR | MB_APPLMODAL);
        system("color 02");
        printf("\n\t--==|Mapeamento de cabos|==--\n\n\n\n");
        printf(" Ol�, Administrador.\n\n");
        printf("| Data: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        system("date/t");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        printf("| Hora: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        system("time/t");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        printf("               ______\n");
        printf("  ____________| Menu |____________\n");
        printf(" |                                |\n");
        printf(" | ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        printf("* Digite apenas o n�mero");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        printf("       |\n");
        printf(" |   ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        printf("referente a op��o!");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        printf("           |\n");
        printf(" |                                |\n");
        printf(" | [1] Adicionar usu�rio          |\n");
        printf(" | [2] Ver/excluir usu�rios atuais|\n");
        printf(" | [3] Editar ou apagar caminho   |\n");
        printf(" | [4] Sair                       |\n");
        printf(" |________________________________|\n");
        printf("\n | OP��O: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        fflush(stdin);
        scanf("%d", &opcao);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    }
    switch (opcao){
        case 1: 
        //Chama a fun��o 'AddUser', que permite ao administrador cadastrar um novo usu�rio.
            adduser();
            break;
        case 2:
        //Abre a base de dados e exibe os usu�rios cadastrados pelo administrador.
            MessageBox(NULL, "Qualquer erro pode comprometer a documenta��o\nPortanto, aten��o ao acessar a base de dados!", "ATEN��O", MB_ICONINFORMATION | MB_APPLMODAL);
            system("start C:\\Documents\\Cable_Map\\Users");
            menuadm();
            break;
        case 3:
        //Abre a base de dados de texto e permite que o administrador remova o registro de um caminho de cabo.
            base_de_dados = fopen("C:\\Documents\\Cable_Map\\Base_de_dados\\Caminhos_de_Cabos.txt", "r");
            if (base_de_dados = NULL){
                MessageBox(NULL, "N�o h� caminhos registrados", "ERRO", MB_ICONERROR | MB_APPLMODAL);
                fclose(base_de_dados);
                menuadm();
            }
            else{
                fclose(base_de_dados);
                MessageBox(NULL, "Qualquer erro pode comprometer a documenta��o\nPortanto, aten��o ao acessar a base de dados!", "ATEN��O", MB_ICONINFORMATION | MB_APPLMODAL);
                system("start C:\\Documents\\Cable_Map\\Base_de_dados\\Caminhos_de_Cabos.txt");
                menuadm();
            }
            fclose(base_de_dados);
            break;
        case 4:
        //Encerra o programa.
            exit(0);
    }
}
void adduser(void){
    setlocale(LC_ALL, "Portuguese_Brazil");
    system("cls");
    system("color 02");
    printf("\n\t--==|Mapeamento de cabos|==--\n\n\n\n");
    printf("|Adicionar usu�rio|\n\n");
    printf("| Usu�rio:\n| ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    fflush(stdin);
    scanf("%s", &addusuario);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("\n\n| [S] Salvar\n| [C] Corrigir\n| [V] Voltar ao menu\n\n| OP��O: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    fflush(stdin);
    scanf("%s", &sc);
    if((strcmp(sc, "c") == 0) || (strcmp(sc, "C") == 0))
    {
        menuadm();
        addusuario[0] = '\0';
    }
    else if((strcmp(sc, "s") == 0) || (strcmp(sc, "S") == 0))
    {   
        //Se o usu�rio confirmar o cadastro do novo usu�rio, as informa��es s�o salvas na base de dados.
        salvaruser();
    }
    else if((strcmp(sc, "v") == 0) || (strcmp(sc, "V") == 0))
    {   
        menuadm();
    }
    while((sc != "s") && (sc != "S") && (sc != "c") && (sc != "C") && (sc != "v") && (sc != "V"))
    {
        MessageBox(NULL, "OP��O INV�LIDA!", "ERRO", MB_ICONERROR | MB_APPLMODAL);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        printf("\n\n| [S] Salvar\n| [C] Corrigir\n| [V] Voltar ao menu\n\n| OP��O: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        fflush(stdin);
        scanf("%s", &sc);
        if((strcmp(sc, "c") == 0) || (strcmp(sc, "C") == 0))
        {
         menuadm();
         addusuario[0] = '\0';
         break;
        }
        else if((strcmp(sc, "s") == 0) || (strcmp(sc, "S") == 0))
        {   
            //Se o usu�rio confirmar o cadastro do novo usu�rio, as informa��es s�o salvas na base de dados.
            salvaruser();
            break;
        }
        else if((strcmp(sc, "v") == 0) || (strcmp(sc, "V") == 0))
        {   
            menuadm();
            break;
        }
    }
}
//Fun��o para cadastrar novos usu�rios e salvar na base de dados.
void salvaruser(void){
    setlocale(LC_ALL, "Portuguese_Brazil");
    nmtxt[100] = "";
    strcat(nmtxt, "C:\\Documents\\Cable_Map\\Users\\");
    strcat(nmtxt, addusuario);
    strcat(nmtxt, ".txt");
    base_de_dados = fopen(nmtxt, "r");
    if(base_de_dados == NULL && strcmp(addusuario, "admin") == 1)
    {
        base_de_dados = fopen(nmtxt, "a");
        fprintf(base_de_dados,"$3nh4P4drao");
        fclose(base_de_dados);
        printf("\nSalvando...");
        Sleep(600);
        printf("\nDados gravados com sucesso!");
        fclose(base_de_dados);
        MessageBox(NULL, "Usu�rio adicionado com sucesso!\n  Reinicie o sistema para concluir.", "Aten��o", MB_ICONINFORMATION | MB_APPLMODAL);
        exit(0);
    }
    else{
        MessageBox(NULL, "Nome de usuario indipon�vel, entre em conato com o usu�rio!", "ATEN��O", MB_ICONERROR | MB_APPLMODAL);
        fclose(base_de_dados);
        MessageBox(NULL, "Reinicie o sistema para uma nova tentativa", "ATEN��O", MB_ICONINFORMATION | MB_APPLMODAL);
        exit(0);
    }
}
//Menu principal que possibilita a cria��o e exclus�o de caminhos de cabos.
void menu(void){
    setlocale(LC_ALL, "Portuguese_Brazil");
    system("cls");
    system("color 02");
    printf("\n\t--==|Mapeamento de cabos|==--\n\n\n\n");
    printf(" Ol�, %s.\n\n", username);
    printf("| Data: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    system("date/t");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("| Hora: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    system("time/t");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("               ______\n");
    printf("  ____________| Menu |____________\n");
    printf(" |                                |\n");
    printf(" | * Digite apenas o n�mero       |\n");
    printf(" |   referente a op��o!           |\n");
    printf(" |                                |\n");
    printf(" | [1] Adicionar caminho          |\n");
    printf(" | [2] Ver caminhos atuais        |\n");
    printf(" | [3] Sair                       |\n");
    printf(" |________________________________|\n");
    printf("\n | OP��O: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    fflush(stdin);
    scanf("%d", &opcao);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    while ((opcao != 1) && (opcao != 2) && (opcao != 3)){
        system("cls");
        MessageBox(NULL, "OP��O INV�LIDA!", "ERRO", MB_ICONERROR | MB_APPLMODAL);
        printf("\t_____________________\n");
        printf("\t|Mapeamento de cabos|\n\n\n\n");
        printf(" Ol�, %s.\n\n", username);
        printf("| Data: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        system("date/t");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        printf("| Hora: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        system("time/t");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        printf("               ______\n");
        printf("  ____________| Menu |____________\n");
        printf(" |                                |\n");
        printf(" | ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        printf("* Digite apenas o n�mero");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        printf("       |\n");
        printf(" |   ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        printf("referente a op��o!");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        printf("           |\n");
        printf(" |                                |\n");
        printf(" |                                |\n");
        printf(" | [1] Adicionar caminho          |\n");
        printf(" | [2] Ver caminhos atuais        |\n");
        printf(" | [3] Sair                       |\n");
        printf(" |________________________________|\n");
        printf("\n | OP��O: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        fflush(stdin);
        scanf("%d", &opcao);
    }
    switch (opcao){
        case 1:
        //Chama a fun��o respons�vel por adicionar um novo caminho.
        adicionarcaminho();
        break;
        case 2:
        base_de_dados = fopen("C:\\Documents\\Cable_Map\\Base_de_dados\\Caminhos_de_Cabos.txt", "r");
        fgets(ler, 2, base_de_dados);
        if(fgets(ler, 2, base_de_dados) == NULL){
            fclose(base_de_dados);
            MessageBox(NULL, "NENHUMA BASE DE DADOS ENCONTRADA!", "ERRO", MB_ICONERROR | MB_APPLMODAL);
            menu();
        }
        else{
            fclose(base_de_dados);
            //Chama a fun��o respons�vel por ler a base de dados.
            lerArquivo();
        }
        break;
        case 3:
        exit(0);
        break;
    }
}
//Fun��o respons�vel por adicionar um novo caminho.
void adicionarcaminho(void)
{
    setlocale(LC_ALL, "Portuguese_Brazil");
    system("cls");
    system("color 02");
    printf("\n\t--==|Mapeamento de cabos|==--\n\n\n\n");
    printf("|Adicionar caminho|\n\n");
    printf("-Local\n\n");
    printf("| Rack/Shaft:\n| ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    fflush(stdin);
    scanf("%[^\n]", rack_shaft);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("\n| Sala:\n| ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    fflush(stdin);
    scanf("%[^\n]", sala);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("\n| Ponto:\n| ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    fflush(stdin);
    scanf("%[^\n]", ponto);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("\n-Identifica��es\n\n");
    printf("\n| Switch:\n| ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    fflush(stdin);
    scanf("%[^\n]", swit);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("\n| Autor do caminho:\n| ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    printf("%s", username);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("\n\n-Portas\n");
    printf("\n| Porta do Switch:\n| ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    fflush(stdin);
    scanf("%[^\n]", porta_switch);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("\n| Porta do Patch Panel:\n| ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    fflush(stdin);
    scanf("%[^\n]", porta_patchpanel);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("\n\n| [S] Salvar\n| [C] Corrigir\n| [V] Voltar ao menu\n\n| OP��O: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    fflush(stdin);
    scanf("%s", &sc);
    if((strcmp(sc, "c") == 0) || (strcmp(sc, "C") == 0))
    {
        adicionarcaminho();
    }
    else if((strcmp(sc, "s") == 0) || (strcmp(sc, "S") == 0))
    {   //Se o usu�rio confirmar as altera��es, a fun��o salva o novo caminho na base de dados.
        GerarOuSalvarArquivo();
    }
    else if((strcmp(sc, "v") == 0) || (strcmp(sc, "V") == 0))
    {
        menu();
    }
    while((sc != "s") && (sc != "S") && (sc != "c") && (sc != "C") && (sc != "v") && (sc != "V"))
    {
        MessageBox(NULL, "OP��O INV�LIDA!", "ERRO", MB_ICONERROR | MB_APPLMODAL);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        printf("\n\n| [S] Salvar\n| [C] Corrigir\n| [V] Voltar ao menu\n\n| OP��O: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        fflush(stdin);
        scanf("%s", &sc);
        if((strcmp(sc, "c") == 0) || (strcmp(sc, "C") == 0))
        {
            adicionarcaminho();
            break;
        }
        else if((strcmp(sc, "s") == 0) || (strcmp(sc, "S") == 0))
        {   //Se o usu�rio confirmar as altera��es, a fun��o salva o novo caminho na base de dados.
            GerarOuSalvarArquivo();
            break;
        }
        else if((strcmp(sc, "v") == 0) || (strcmp(sc, "V") == 0))
        {
            menu();
            break;
        }
    }
}
//Fun��o respons�vel por salvar o novo caminho na base de dados.
void GerarOuSalvarArquivo(void)
{
    setlocale(LC_ALL, "Portuguese_Brazil");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    base_de_dados = fopen("C:\\Documents\\Cable_Map\\Base_de_dados\\Caminhos_de_Cabos.txt", "r");
    if(base_de_dados == NULL)
    {
        base_de_dados = fopen("C:\\Documents\\Cable_Map\\Base_de_dados\\Caminhos_de_Cabos.txt", "a");
        fprintf(base_de_dados, "\n %s | %s | %s | %s | %s | %s | %s", ponto, rack_shaft, sala, swit, username, porta_switch, porta_patchpanel);
        fclose(base_de_dados);
        printf("\nSalvando...");
        Sleep(600);
        printf("\nDados gravados com sucesso!");
    }
    else
    {
        base_de_dados = fopen("C:\\Documents\\Cable_Map\\Base_de_dados\\Caminhos_de_Cabos.txt", "a");
        fprintf(base_de_dados, "\n %s | %s | %s | %s | %s | %s | %s |", ponto, rack_shaft, sala, swit, username, porta_switch, porta_patchpanel);
        fclose(base_de_dados);
        printf("\nSalvando...");
        Sleep(600);
        printf("\nDados gravados com sucesso!");
    }
    fclose(base_de_dados);
    Sleep(1000);
    menu();
}
//Fun��o respons�vel por ler um caminho previamente salvo.
void lerArquivo(void)
{
    setlocale(LC_ALL, "Portuguese_Brazil");
    system("cls");
    system("color 02");
    printf("\n\t--==|Mapeamento de cabos|==--\n\n\n\n");
    printf("|Caminhos de cabos|\n\n");
    printf("PONTO | RACK/SHAFT | SALA | SWITCH | AUTOR DO REGISTRO | PORTA DO SWITCH | PORTA DO PATCH PANEL\n\n");
    base_de_dados = fopen("C:\\Documents\\Cable_Map\\Base_de_dados\\Caminhos_de_Cabos.txt", "r");
            if(base_de_dados == NULL)
            {
                MessageBox(NULL, "NENHUMA BASE DE DADOS ENCONTRADA!", "ERRO", MB_ICONERROR | MB_APPLMODAL);
                Sleep(500);
                menu();
            }
            else
            {
                while (fgets(ler, 1000, base_de_dados) != NULL)
                {
                    printf("%s", ler);
                }
                fclose(base_de_dados);
            }
    printf("\n\n| (1) Voltar");
    printf("\n| OP��O: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    fflush(stdin);
    scanf("%d", &opcao);
    if (opcao = 1)
    {
        menu();
    }
    else{
        MessageBox(NULL, "OP��O INV�LIDA!", "ERRO", MB_ICONERROR | MB_APPLMODAL);
    }
}