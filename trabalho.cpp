#include <stdio.h>//Header para entrada e sa�da de arquivos;
#include <conio.h>//Header para entrada e sa�da de console
#include <stdlib.h>//
#include <locale.h>//Header para regionaliza��o de programa;
#include <windows.h>//Header para fun��es b�sicas windows;


//voc� pode definir ou abrir um arquivo
//Lembre-se que voc� precisa em C, duas contra barras para representar uma no caminho de um arquivo.
#define IMAGEM "C:\\Users\\V�tor Becker\\Desktop\\selegacer.bmp"
// 1032x581
//WORD == unsigned short %hu
//DWORD == unsigned long %lu
//LONG == long %li
void game_over(void);

struct cabecalho_da_imagem
{
  unsigned char tipo[2];//para os caracteres BM
  unsigned long tamanho;//tamanho total do arquivo em Bytes
  unsigned char reservado[4];//reservado, sempre 0
  unsigned long offset;//quantos bytes at� o in�cio da imagem propriamente dita.
  unsigned long TamCab;//tamanho do cabe�alho sempre 40d ou 0x28h
  unsigned long Larg;//Largura da imagem em pixels
  unsigned long Alt;//Altura da imagem em pixels
};

int main()
{//INICIO MAIN;
    //Menu inicial:
    setlocale(LC_ALL,"portuguese");//torna para portugues;
    system("COLOR 0a");//Color background/letras
    bool a=1;//Variavel para entrar e sair do programa/loop;
    struct cabecalho_da_imagem img;//refer�ncia para struct cabe�alho;
    char bro[3][3]={-1,-1,-1,-1,8,-1,-1,-1,-1};
    unsigned char bordou[3][3]={1,1,1,1,1,1,1,1,1};
    do
    {//Fa�a
        system("cls");//limpa o que havia antes do loop;
        printf("\t================================================\n");
        printf("\t====Bem vindo ao Manipulador de Imagens=========\n");
        printf("\t================================================\n\n\t\t");
        printf("<1> Cria copia da imagem\n\t\t");
        printf("<2> Torna imagem para escala de cinza\n\t\t");
        printf("<3> P�e filtro passa-baixa na imagem\n\t\t");
        printf("<4> Para mostrar informa��es do cabe�alho da imagem\n\t\t");
        printf("<5> Para sair do programa\n\t\t");
        printf("<6> Para mostrar informa��o do desenvolvedor\n\t\t");
        printf("<7> Passa filtro de media\n\t\t");


        //Declara��es de variaveis para controle:
        char op; FILE *image; FILE *copia; FILE *cinza; FILE *filtro;FILE *bord;
        op=getch();



        //==============PRIMEIRA CONDI��O============================
        if(op=='1')
        {//Inicio da primeira condi��o;
            unsigned char matriz[3096][582];
            image=fopen(IMAGEM,"r+b");//aponta ponteiro image para abertura de arquivo "IMAGEM";
            if(!image)//Caso ocorra erro na abertura do arquivo.;
            {
                system("cls");
                printf("\tParece que houve um erro na abertura do arquivo, tente novamente...\n");
                game_over();
                system("PAUSE");
            }
            else //Caso tenha sucesso na abertura do arquivo:
            {
                fread(img.tipo,sizeof(unsigned char),2,image);//fread(onde_armazenar,tamanho_da_var_lida,quantas_vezes,*ponteiro);
                fread(&img.tamanho,sizeof(unsigned long),1,image);//Tamanho em bits do arquivo;
                fread(img.reservado,sizeof(unsigned char),4,image);//Bits BReser1 e BReser2... Reservados (normalmente com zero);
                fread(&img.offset,sizeof(unsigned long),1,image);//Quantos byts at� o inicio da imagem;
                fread(&img.TamCab,sizeof(unsigned long),1,image);//Tamanho do cabe�alho em byts;
                fread(&img.Larg,sizeof(unsigned long),1,image);//Largura da imagem em pixels;
                fread(&img.Alt,sizeof(unsigned long),1,image);//Altura em pixels;
                for(int a=0;a<582;a++)
                {
                    for(int b=0;b<3096;b++)
                        fread(&matriz[b][a],sizeof(unsigned char),1,image);
                }
                fclose(image);

                //Declara��o da abertura de arquivo para escrita:
                copia=fopen("copia.bmp","w+b");
                if(!copia)//Caso ocorra erro na abertura de copia:
                {
                    system("cls");//Limpa tela;
                    printf("\tOps! Houve um erro...");
                    system("PAUSE");//Espera comando do usu�rio;
                }

                else //Caso ocorra sucesso:
                {
                    fwrite(img.tipo,sizeof(unsigned char),2,copia);//fwrite(onde_armazenar,tamanho_da_var_escrita,quantas_vezes,*ponteiro);
                    fwrite(&img.tamanho,sizeof(unsigned long),1,copia);//Tamanho em bits do arquivo;
                    fwrite(img.reservado,sizeof(unsigned char),4,copia);//Bits BReser1 e BReser2... Reservados (normalmente com zero);
                    fwrite(&img.offset,sizeof(unsigned long),1,copia);//Quantos byts at� o inicio da imagem;
                    fwrite(&img.TamCab,sizeof(unsigned long),1,copia);//Tamanho do cabe�alho em byts;
                    fwrite(&img.Larg,sizeof(unsigned long),1,copia);//Largura da imagem em pixels;
                    fwrite(&img.Alt,sizeof(unsigned long),1,copia);//Altura em pixels;
                    for(int a=0;a<582;a++)
                        for(int b=0;b<3096;b++)
                            fwrite(&matriz[b][a],sizeof(unsigned char),1,copia);
                    fclose(copia);//fecha ponteiro copia;
                    //Flag para usu�rio:
                    system("cls");
                    printf("\n\tParab�ns, verifique a imagem final no diretorio do seu programa...\n");
                    system("pause");
                }
            }
        }//Final da primeira condi��o;
        //===========================================================

        else if(op == '2')//Inicio segunda condi��o
        {
            unsigned char matriz[3096][582];
            unsigned char cab[54];
            image=fopen(IMAGEM,"r+b");//aponta ponteiro image para abertura de arquivo "IMAGEM";
            if(!image)//Caso ocorra erro na abertura do arquivo.;
            {
                system("cls");
                printf("\tParece que houve um erro na abertura do arquivo, tente novamente...\n");
                system("PAUSE");
            }
            else //Caso tenha sucesso na abertura do arquivo:
            {
                fread(&cab,sizeof(unsigned char),54,image);//fread(onde_armazenar,tamanho_da_var_lida,quantas_vezes,*ponteiro);
                for(int a=0;a<581;a++)
                {
                    for(int b=0;b<3096;b++)
                        fread(&matriz[b][a],sizeof(unsigned char),1,image);
                }
                fclose(image);

                cinza=fopen("cilnza.bmp","w+b");
                if(!cinza)//Erro na abertura:
                {
                    system("cls");//Limpa tela;
                    printf("\tOps! Houve um erro...");
                    system("PAUSE");//Espera comando do usu�rio;
                }

                else//Caso sucesso:
                {
                      //M�dia aritim�tica de RGB:
                        for(int a=0;a<581;a++)
                            for(int b=0;b<3096;b+=3)
                            {
                                matriz[b][a]=((matriz[b][a]+matriz[b+1][a]+matriz[b+2][a])/3);
                                matriz[b+1][a]=matriz[b][a];
                                matriz[b+2][a]=matriz[b+1][a];
                            }


                        //Fim M�dia aritim�tica:
                     fwrite(&cab,sizeof(unsigned char),54,cinza);//fwrite(onde_armazenar,tamanho_da_var_escrita,quantas_vezes,*ponteiro);
                     for(int a=0;a<581;a++)
                        for(int b=0;b<3096;b++)
                            fwrite(&matriz[b][a],sizeof(unsigned char),1,cinza);
                     fclose(cinza);//fecha ponteiro copia;
                     //Flag para usu�rio:
                     system("cls");
                     printf("\n\tParab�ns, verifique a imagem final no diretorio do seu programa...\n");
                     system("pause");
                }

            }
        }//Final da segunda condi��o;
        //===========================================================

        //===============TERCEIRA CONDI��O===========================
      else if(op=='3')
      {
            unsigned char matriz[3096][582];
            unsigned char cab[54];
            image=fopen(IMAGEM,"r+b");//aponta ponteiro image para abertura de arquivo "IMAGEM";
            if(!image)//Caso ocorra erro na abertura do arquivo.;
            {
                system("cls");
                printf("\tParece que houve um erro na abertura do arquivo, tente novamente...\n");
                system("PAUSE");
            }
            else //Caso tenha sucesso na abertura do arquivo:
            {
                unsigned char thicc[3096][582];
                fread(&cab,sizeof(unsigned char),54,image);//fread(onde_armazenar,tamanho_da_var_lida,quantas_vezes,*ponteiro);
                for(int a=0;a<581;a++)
                {
                    for(int b=0;b<3096;b++)
                        fread(&thicc[b][a],sizeof(unsigned char),1,image);
                }
                fclose(image);

                filtro=fopen("jooj.bmp","w+b");
                if(!filtro)//Erro na abertura:
                {
                    system("cls");//Limpa tela;
                    printf("\tOps! Houve um erro...");
                    system("PAUSE");//Espera comando do usu�rio;
                }

                else//Caso sucesso:
                {
                      //M�dia aritim�tica de RGB:
                        for(int a=0;a<581;a++)
                        {
                            for(int b=0;b<3096;b+=3)
                            {
                                thicc[b][a]=((thicc[b][a]+thicc[b+1][a]+thicc[b+2][a])/3);
                                thicc[b+1][a]=thicc[b][a];
                                thicc[b+2][a]=thicc[b+1][a];

                            }
                        }


                        int acc=0;//Variavel para acumula��o;

                        for(int a=0;a<582;a++)
                        {

                            for(int b=0;b<3096;b+=3)
                            {
                                acc=0;
                                for(int c=0;c<3;c++)
                                {//Inicio la�o acumulador
                                    for(int d=0;d<3;d++)
                                    {
                                        acc+=thicc[b+d][a+c]*bordou[d][c];
                                    }
                                }//Fim la�o




                                unsigned char media=acc/9;

                                for(int c=0;c<3;c++)
                                    for(int d=0;d<3;d++)
                                    {
                                        thicc[b+d][a+c] = media;
                                    }


                            }

                        }


                        //Fim M�dia aritim�tica:
                     fwrite(&cab,sizeof(unsigned char),54,filtro);//fwrite(onde_armazenar,tamanho_da_var_escrita,quantas_vezes,*ponteiro);
                     for(int a=0;a<581;a++)
                     {
                         for(int b=0;b<3096;b++)
                            fwrite(&thicc[b][a],sizeof(unsigned char),1,filtro);
                     }

                     fclose(filtro);//fecha ponteiro copia;
                     //Flag para usu�rio:
                     system("cls");
                     printf("\n\tParab�ns, verifique a imagem final no diretorio do seu programa...\n");
                     system("pause");
                }

            }
        }
        //===========================================================

        //===================QUARTA CONDI��O=========================
        else if(op == '4')
        {
            image=fopen(IMAGEM,"r+b");
            if(!image)
            {
                system("cls");
                printf("\tParece que houve um erro na abertura do arquivo, tente novamente...\n");
                game_over();
                system("PAUSE");
            }
            else
            {
                fread(img.tipo,sizeof(unsigned char),2,image);//fread(onde_armazenar,tamanho_da_var_lida,quantas_vezes,*ponteiro);
                fread(&img.tamanho,sizeof(unsigned long),1,image);//Tamanho em bits do arquivo;
                fread(img.reservado,sizeof(unsigned char),4,image);//Bits BReser1 e BReser2... Reservados (normalmente com zero);
                fread(&img.offset,sizeof(unsigned long),1,image);//Quantos byts at� o inicio da imagem;
                fread(&img.TamCab,sizeof(unsigned long),1,image);//Tamanho do cabe�alho em byts;
                fread(&img.Larg,sizeof(unsigned long),1,image);//Largura da imagem em pixels;
                fread(&img.Alt,sizeof(unsigned long),1,image);//Altura em pixels;
                fclose(image);
            }
            char tuba;
            do
            {
                char frase[]="Que parametros gostaria de conhecer?";
                system("cls");
                printf("\t");
                for(int i=0;i<sizeof(frase);i++)
                    printf("%c",frase[i]),Sleep(50);
                printf("\n\t\t<1>Tamanho da imagem");
                printf("\n\t\t<2>Offset-Quantos bytes at� come�ar a imagem");
                printf("\n\t\t<3>Tamanho do cabe�alho da imagem");
                printf("\n\t\t<4>Largura da imagem");
                printf("\n\t\t<5>Altura da imagem");

                char uto;
                uto=getch();

                switch(uto)
                {
                case '1':
                    printf("\n\tO tamanho da imagem � de %li bytes....",img.tamanho);
                    break;
                case '2':
                    printf("\n\tO offset da imagem � de %li bytes...",img.offset);
                    break;
                case '3':
                    printf("\n\tO tamanho do cabe�alho da imagem � de %li bytes...",img.TamCab);
                    break;
                case '4':
                    printf("\n\tA largura da imagem � de %li bytes...",img.Larg);
                    break;
                case '5':
                    printf("\n\tA altura da imagem � de %li bytes...",img.Alt);
                    break;
                default:
                    printf("\n\tEsta op��o � invalida...");

                }
                printf("\n\t\tDeseja realizar mais alguma a��o? Y/N");
                uto=getch();
                if(uto == 'n')
                    tuba='n';
                else
                    printf("\n\t\t"),system("PAUSE");
            }while(tuba != 'n');

        }
        else if(op == '5')
        {
           a=0;//Sai do "fa�a";
           system("cls");
           printf("\t");
           char frase[]="At� a pr�xima, usuario...";
           for(int a=0;a<sizeof(frase);a++)
                printf("%c",frase[a]),Sleep(50);
           system("pause");
        }//Final da quinta condi��o;
        //===========================================================

        //==================SEXTA CONDI��O===========================
        else if(op == '6')
        {
            system("cls");
            printf("\t");
            char info[]="Este programa foi desenvolvido pelo membro dos tem�veis Engenheiros Dissidentes!,V�tor Becker.";
            char infov[]="Trabalho realizado para disciplina de Elementos de Programa��o I, do curso t�cnico de eletr�nica da Funda��o Liberato";
            char info2[]="Gostaria de saber um segredo?";
            for(int a=0;a<sizeof(info);a++)
            {
                printf("%c",info[a]);
                Sleep(50);
            }
            printf("\n");
            for(int a=0;a<sizeof(infov);a++)
            {
                printf("%c",infov[a]);
                Sleep(50);
            }
            printf("\n\n\n");
            for(int a=0;a<sizeof(info2);a++)
            {
                printf("%c",info2[a]);
                Sleep(50);
            }
            printf(" Y/N?");
            char uto;
            uto=getch();
            if(uto == 'y')
            {
                printf("\t");
                char segredo[]="Dennis Ritchie was here, boy...";
                for(int a=0;a<sizeof(segredo);a++)
                {
                    printf("%c",segredo[a]);
                    Sleep(50);
                }
            }
            else if(uto == 'n')
            {
                char ok[]="okay then...";
                printf("\t");
                for(int a=0;a<sizeof(ok);a++)
                {
                    printf("%c",ok[a]);
                    Sleep(50);
                }
            }
            else
                printf("\n\tOp��o inv�lida...");

        }
        //================================================
        else if(op == '7')
        {
         unsigned char matriz[3096][582];
            unsigned char cab[54];
            image=fopen(IMAGEM,"r+b");//aponta ponteiro image para abertura de arquivo "IMAGEM";
            if(!image)//Caso ocorra erro na abertura do arquivo.;
            {
                system("cls");
                printf("\tParece que houve um erro na abertura do arquivo, tente novamente...\n");
                system("PAUSE");
            }
            else //Caso tenha sucesso na abertura do arquivo:
            {
                unsigned char thicc[3096][582];
                unsigned char thicc2[3096][582];
                unsigned char *t1;
                unsigned char *t2;
                unsigned char antes=0;
                fread(&cab,sizeof(unsigned char),54,image);//fread(onde_armazenar,tamanho_da_var_lida,quantas_vezes,*ponteiro);
                for(int a=0;a<581;a++)
                {
                    for(int b=0;b<3096;b++)
                        fread(&thicc[b][a],sizeof(unsigned char),1,image);
                }
                fclose(image);

                bord=fopen("borda.bmp","w+b");
                if(!bord)//Erro na abertura:
                {
                    system("cls");//Limpa tela;
                    printf("\tOps! Houve um erro...");
                    system("PAUSE");//Espera comando do usu�rio;
                }

                else//Caso sucesso:
                {
                        fwrite(&cab,sizeof(unsigned char),54,bord);//fwrite(onde_armazenar,tamanho_da_var_escrita,quantas_vezes,*ponteiro);
                        //M�dia aritim�tica de RGB:
                        for(int a=0;a<581;a++)
                        {
                            for(int b=0;b<3096;b+=3)
                            {
                                thicc[b][a]=((thicc[b][a]+thicc[b+1][a]+thicc[b+2][a])/3);
                                thicc[b+1][a]=thicc[b][a];
                                thicc[b+2][a]=thicc[b+1][a];

                            }
                        }

                        int acc=0;//Variavel para acumula��o;
                        for(int a=0;a<582;a++)
                        {

                            for(int b=0;b<3096;b++)
                            {
                                acc=0;
                                antes=thicc[b+1][a+1];
                                for(int c=0;c<3;c++)
                                {//Inicio la�o acumulador
                                    for(int d=0;d<3;d++)
                                    {

                                        acc+=thicc[b+d][a+c]*bro[d][c];

                                    }
                                }//Fim la�o


                                if(acc > 255)      // xx yy zz
                                    acc=255;

                                else if(acc<0)
                                    acc=0;

                                unsigned char media=acc;


                                fwrite(&media,sizeof(unsigned char),1,bord);



                            }

                        }
                        //Fim M�dia aritim�tica:

                     fclose(bord);//fecha ponteiro copia;
                     //Flag para usu�rio:
                     system("cls");
                     printf("\n\tParab�ns, verifique a imagem final no diretorio do seu programa...\n");
                     system("pause");
                }

            }
        }
 }while(a != 0);//Enquanto a n�o for zero;

}


//FIM MAIN;
void game_over(void)
{
    Beep(440,200);
    Beep(415.30,200);
    Beep(392,200);
    Beep(369.99,400);
    Beep(349.23,700);
    Beep(300,1000);
}
