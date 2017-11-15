#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <Windows.h>

struct checkPerson {
	char nome[50];
	char sexo[2][10] = { "Masculino", "Feminino" };
	char corCabelo[6][10] = { "Preto", "Castanho", "Loiro", "Vermelho", "Azul", "Branco" };
	char hobby[5][25] = { "Caminhar", "Jogar", "Tocar instrumento(s)", "Ler", "Discutir" };
	char feature[7][10] = { "Chapéu", "Boné", "Tatuagem", "Óculos", "Pulseira", "Anel", "Colar" };
};

struct tipoPersonagem {
	char nome[50];
	int sexo;
	int corCabelo;
	int hobby;
	int feature;
};

struct tipoCaso {
	tipoPersonagem personagens[30];
	char historiaGeral[999];
	char historiaCidade[30][999];
	char cidades[30][50];
	char pistas[90][999];
	char POI[90][20];
	int numeroCidades;
};

struct adminType {
	char nome[30];
	char login[30];
	char senha[30];
	char keycripto[13];
};

struct tipoJogador {
	char nome[30];
	char login[30];
	char senha[30];
	int pontos;
};

enum loginType {
	administrador = 1, jogado, sair
};
enum admOptions {
	cadastroadm = 1, loginadm, returnmenu
};
enum admLoginOptions {
	chgn = 1, chgl, chgs, cadastrocasos, cadastropersonagem, removecasos, deladm, chgsair
};
enum playerOptions {
	cadastroJogador = 1, loginjogador, saair
};

enum alterarCadastro {
	alterarNome = 1, alterarLogin, alterarSenha, excluirConta, sairAlterarCadastro
};

enum playerLogadoOptions {
	alterarCadastro = 1, jogar = 2, logOut
};

enum personas {
	cadastrarPersonagem = 1, usarCadastrado
};


enum QualCaracteristica {
	sexo, corDeCabelo, Hobby, Feature
};

void cripto(char* key, char* orig, char* cript);
void newPersona();
int oldPersona(tipoPersonagem* personagem);
int checkCarac(QualCaracteristica caracteristica);
void ranking();

int main()
{
	setlocale(LC_ALL, "Portuguese");
	tipoCaso caso;
	adminType adm, aux, cmp;
	enum personas matsf;
	enum alterarCadastro change;
	enum playerLogadoOptions jorge;
	strcpy(adm.keycripto, "sleepycabin");
	loginType log;
	admOptions casesadm;
	admLoginOptions casesloginadm;
	playerOptions opcaojogador;
	tipoPersonagem personagem[100];
	FILE *admin;
	FILE *reserva;
	FILE *casos;
	tipoJogador jogador, auxlogin, player;
	char resposta;
	int quantidade = 0, i, qtdPersonas, contaCidade;
	bool valido = true, login = true, jaescreveu, condicao = false;
	bool sairalteracaoadm = false, logou = false, logFora, returntomenu = false;
	char ajuda = 'N';

	//VARS DO JOGO
	tipoCaso casoatual;
	FILE *casoatualDesc;
	int casoparaloadar = 1;
	bool gameover = false;
	int temporestante = 1500;
	int cidadeatual = 0;
	int opcaoemopcao;
	int opcaoemjogo;
	bool stayinoption = true;
	bool temMandato = false;
	tipoPersonagem retratofalado;

	do {
		system("cls");
		system("color F2");
		printf("\n\tBem vindo ao jogo Where in the world!");
		printf("\n\tDeseja logar como administrador ou jogador?\n\n\t1. Administrador\n\t2. Jogador\n\t3. Sair\n\n\tOpcao desejada: ");
		scanf("%i", &log);

		if (log != sair)
		{
			switch (log)
			{
			case administrador:
				do {
					system("cls");
					system("color 04");
					printf("\n\tOpção escolhida: 1. Administrador\n\tEscolha uma das opções abaixo:\n\n\t1. Cadastro de Administrador\n\t2. Login do Administrador\n\t3. Retornar ao menu anterior\n\n\tOpcao desejada: ");
					scanf("%i", &casesadm);
					if (casesadm > 0 && casesadm < 4)
					{
						switch (casesadm)
						{
						case cadastroadm:
							system("cls");
							admin = fopen("logincripto.dat", "rb");

							if (admin != NULL)
							{
								fclose(admin);
								printf("\n\tAdministrador já cadastrado! Desculpe\n\tRetornando ao menu...");
								Sleep(3000);
							}
							else
							{
								fclose(admin);

								printf("\n\tOpção 1. Cadastro de Administrador:\n\n\tNome: ");
								getchar();
								fgets(adm.nome, 30, stdin);
								printf("\n\tLogin: ");
								fgets(adm.login, 30, stdin);
								printf("\n\tSenha: ");
								fgets(adm.senha, 30, stdin);
								strcpy(aux.nome, adm.nome);
								cripto(adm.keycripto, adm.login, aux.login);
								cripto(adm.keycripto, adm.senha, aux.senha);
								admin = fopen("logincripto.dat", "wb");

								if (admin == NULL)
									printf("Erro na abertura do arquivo de login do administrador. Contacte o desenvolvedor!");
								else
									fwrite(&aux, sizeof(adminType), 1, admin);

								fclose(admin);
							}

							system("cls");

							break;

						case loginadm:
							system("cls");
							admin = fopen("logincripto.dat", "rb");
							if (admin == NULL)
							{
								printf("\n\t É necessário o cadastro de administrador primeiro!");
								//Sleep(3000);
							}
							else
							{
								fclose(admin);
								printf("\n\tOpção 2. Login Administrativo:\n\n\tDigite o login atual: ");
								getchar();
								fgets(adm.login, 30, stdin);
								printf("\n\tSenha atual: ");
								fgets(adm.senha, 30, stdin);
								cripto(adm.keycripto, adm.login, cmp.login);
								cripto(adm.keycripto, adm.senha, cmp.senha);
								admin = fopen("logincripto.dat", "r+b");

								if (admin == NULL)
									printf("\n\tErro na abertura do arquivo de login do administrador. Contacte o desenvolvedor!");
								else
									fread(&aux, sizeof(adminType), 1, admin);

								fclose(admin);
								system("cls");

								if (strcmp(cmp.login, aux.login) == 0 && strcmp(cmp.senha, aux.senha) == 0)
								{
									do {
										printf("\n\tLogin bem sucedido!\n\tSr(a) %s\tQuais das opções deseja executar?\n\n\t1. Alterar nome\n\t2. Alterar login\n\t3. Alterar senha", aux.nome);
										printf("\n\t4. Cadastrar caso\n\t5. Cadastrar personagem \n\t6. Remover caso\n\t7. Excluir credencial de administrador\n\t8. Sair\n\n\tOpcao desejada: ");
										scanf("%i", &casesloginadm);
										system("cls");
										admin = fopen("logincripto.dat", "w+b");

										if (admin == NULL)
											printf("\n\tErro na abertura do arquivo de login do administrador. Contacte o desenvolvedor!");
										else
											fread(&aux, sizeof(adminType), 1, admin);

										switch (casesloginadm)
										{
										case chgn:

											printf("\n\tOpção 1.2.1. Alterar nome:\n\n\tDigite o novo nome: ");
											getchar();
											fgets(adm.nome, 30, stdin);
											strcpy(aux.nome, adm.nome);
											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);
											break;

										case chgl:

											printf("\n\tOpção 1.2.2. Alterar login:\n\n\tDigite o novo login: ");
											getchar();
											fgets(adm.login, 30, stdin);
											cripto(adm.keycripto, adm.login, aux.login);
											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);
											break;

										case chgs:

											printf("\n\tOpção 1.2.3. Alterar senha:\n\n\tDigite a nova senha: ");
											getchar();
											fgets(adm.senha, 30, stdin);
											cripto(adm.keycripto, adm.senha, aux.senha);
											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);
											break;

										case cadastrocasos: //-------------------------------------------------------------------CADASTRO CASOS

											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);

											casos = fopen("casos.dat", "a + b");

											//HISTORIA

											system("cls");
											printf("\n\tOpção 1.2.4. Cadastrar casos:");
											printf("\n\n\tPrimeiro digite a história do caso (MAX 999 caracteres): ");
											getchar();
											fgets(caso.historiaGeral, 999, stdin);

											printf("\n\tHistória cadastrada com sucesso! Aguarde um momento....");
											Sleep(2000);

											quantidade = 1;
											contaCidade = 0;
											do //CIDADES
											{
												system("cls");
												printf("\n\tAgora digite as cidades que farão parte do caso (MAX 30 cidades e 50 caracteres):");
												printf("\n\tPara encerrar o cadastro digite 'Sair' (Sem as aspas)");
												printf("\n\n\tDigite o nome da cidade %i: ", quantidade);
												fgets(caso.cidades[contaCidade], 50, stdin); //30 cidades 50 caracteres

												if (strcmp(caso.cidades[contaCidade], "Sair") == 0 || strcmp(caso.cidades[contaCidade], "sair") == 0 || strcmp(caso.cidades[contaCidade], "sair\n") == 0 || strcmp(caso.cidades[contaCidade], "Sair\n") == 0 && quantidade < 32)
												{
													if (quantidade == 31)
													{
														system("cls");
														printf("\n\tLimite máximo de cidades atingido! Aguarde enquanto vamos ao proximo passo...");
													}
													else
													{
														printf("\n\tAguarde enquanto lhe redirecionamos ao proximo passo...");
													}

													caso.numeroCidades = quantidade - 1;
													Sleep(2000);

													break;
												}
												else
												{
													for (i = 0; i < strlen(caso.cidades[contaCidade]); i++)
													{
														if (caso.cidades[contaCidade][i] == '\n')
															caso.cidades[contaCidade][i] = '\0';
													}
													for (int j = 0; j < 3; j++)
													{
														printf("\n\n\tPonto de interesse %i da cidade %s: ", j + 1, caso.cidades[contaCidade]);
														fgets(caso.POI[(3 * contaCidade) + j], 20, stdin);
														printf("\n\n\tPista %i da cidade %s: ", j + 1, caso.cidades[contaCidade]);
														fgets(caso.pistas[(3 * contaCidade) + j], 999, stdin);
														system("cls");
													}
													contaCidade++;
												}

												quantidade++;

											} while (true);

											for (i = 0; i < quantidade - 1; i++)
											{
												system("cls");
												printf("\n\tCadastre agora a descrição / história de cada cidade (MAX 999 Caracteres):");
												printf("\n\n\tHistoria da cidade %s: ", caso.cidades[i]);
												fflush(stdin);
												//getchar();
												fgets(caso.historiaCidade[i], 999, stdin);
											}

											system("cls");

											printf("\n\tCidades concluídas com sucesso!");
											printf("\n\n\tDigite a opção desejada: \n");
											printf("\n\t1.Cadastrar novos personagens");
											printf("\n\t2.Usar personagens já cadastrados");
											printf("\n\n\tOpção: ");
											scanf("%i", &matsf);

											switch (matsf)
											{
											case cadastrarPersonagem:

												newPersona();
												qtdPersonas = oldPersona(personagem);

												break;
											case usarCadastrado:

												qtdPersonas = oldPersona(personagem);

												break;
											default:
												break;
											}

											system("cls");

											for (i = 0; i < qtdPersonas; i++)
											{
												strcpy(caso.personagens[i].nome, personagem[i].nome);
												caso.personagens[i].sexo = personagem[i].sexo;
												caso.personagens[i].corCabelo = personagem[i].corCabelo;
												caso.personagens[i].hobby = personagem[i].hobby;
												caso.personagens[i].feature = personagem[i].feature;
											}

											Sleep(1000);

											fwrite(&caso, sizeof(tipoCaso), 1, casos);

											fclose(casos);

											break;

										case cadastropersonagem:

											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);

											newPersona(); //=================AQUIIII BURROOOOO

											break;

										case removecasos:

											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);

											fclose(admin);
											system("cls");
											printf("\tOpção 1.2.5. Remover casos:\n\n");
											system("cls");
											break;

										case deladm:

											printf("\n\tOpção 1.2.6. Excluir credencial de administrador:\n\tTem certeza desta opção?(S/N): ");
											getchar();
											scanf("%c", &resposta);

											if (resposta == 'S' || resposta == 's')
											{
												fclose(admin);
												printf("\n\tVocê será redirecionado para o menu administrativo em instantes...");
												//Sleep(2000);
												sairalteracaoadm = true;
												remove("logincripto.dat");
											}
											else
												fclose(admin);
											break;

										case chgsair:
											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);
											sairalteracaoadm = true;
											break;
										}

										system("cls");

									} while (sairalteracaoadm == false);

									sairalteracaoadm = false;
								}
								else
								{
									printf("\n\tLogin ou senha incorretos! Voltando ao menu inicial...");
									//Sleep(2000);
								}
							}

							system("cls");
							break;

						case returnmenu:returntomenu = true;
							break;
						}
					}
					else
					{
						printf("\n\n\tOpção inválida! Tente novamente em instantes...");
						//Sleep(3000);
					}
				} while (returntomenu == false);
				returntomenu = false;
				break;

			case jogado:
				system("cls");

				printf("\n\tOpção escolhida: 2. Jogador\n\tEscolha uma das opções abaixo:\n\n\t1. Cadastrar novo jogador\n\t2. Login Jogador\n\t3. Retornar ao menu anterior\n\n\tOpcao desejada: ");
				scanf("%i", &opcaojogador);

				FILE*players = fopen("players.dat", "a+b");
				system("cls");

				switch (opcaojogador)
				{
				case cadastroJogador: //-------------------------------------------------CADASTRO JOGADOR INICIO

					printf("\n\tOpção 1. Cadastro novo Jogador:\n\n\tDigite seu primeiro nome: ");
					scanf("%s", jogador.nome);

					do  //INICIO VERIFICAÇÃO NOME EXISTENTE
					{
						rewind(players);

						do
						{

							fread(&auxlogin, sizeof(auxlogin), 1, players);

							if (strcmp(auxlogin.nome, jogador.nome) == 0)
							{
								login = false;
								break;
							}
							else
							{
								login = true;
							}

						} while (!feof(players));

						if (login == false)
						{
							system("cls");

							printf("\n\tNome ja cadastrado!\n");
							printf("\n\tTente digitar diferente: ");
							scanf("%s", jogador.nome);
						}

					} while (login == false);  //FIM VERIFICAÇÃO NOME EXISTENTE

					printf("\n\tDigite seu login: ");
					scanf("%s", jogador.login);

					do  //INICIO VERIFICAÇÃO LOGIN EXISTENTE
					{
						rewind(players);

						do
						{

							fread(&auxlogin, sizeof(auxlogin), 1, players);

							if (strcmp(auxlogin.login, jogador.login) == 0)
							{
								login = false;
								break;
							}
							else
							{
								login = true;
							}

						} while (!feof(players));

						if (login == false)
						{
							system("cls");

							printf("\n\tLogin ja cadastrado!\n");
							printf("\n\tDigite outro login: ");
							scanf("%s", jogador.login);
						}

					} while (login == false);  //FIM VERIFICAÇÃO LOGIN EXISTENTE

					printf("\n\tDigite sua senha: ");
					scanf("%s", jogador.senha);
					jogador.pontos = 0;

					fwrite(&jogador, sizeof(tipoJogador), 1, players);
					//Sleep(1000);

					fclose(players);

					printf("\n\tCadastro realizado com sucesso! Aguarde um momento...");
					logou = true;
					//Sleep(2000);

					break; //-------------------------------------------------------------------FIM LOGIN CADASTRO JOGADOR

				case loginjogador: //-------------------------------------------------------LOGIN JOGADOR

					rewind(players);

					system("cls");

					valido = true;


					do {

						system("cls");

						printf("\n\tOpção 2. Login Jogador:\n\n\tDigite seu login: ");
						scanf("%s", &auxlogin.login);

						do {
							fread(&jogador, sizeof(jogador), 1, players); //Verifica se o login esta cadastrada

							if (strcmp(jogador.login, auxlogin.login) == 0)
							{
								valido = true;
								break;
							}
							else
							{
								valido = false;
							}

						} while (!feof(players));

						if (valido == false)
						{
							rewind(players);
							system("cls");
							printf("\n\tLogin Invalido...\n\n\tDeseja tentar novamente? (S / N)\n\n\tResposta: ");
							getchar();
							scanf("%c", &resposta);

							ajuda = resposta;
						}
						else
						{
							break;
						}

					} while (valido == false && ajuda == 'S' || ajuda == 's');

					//rewind(players);

					if (valido == true)
					{

						do
						{
							system("cls");

							printf("\n\tOlá %s\n", jogador.nome);
							printf("\n\tDigite sua senha: ");
							scanf("%s", &auxlogin.senha);

							if (strcmp(jogador.senha, auxlogin.senha) == 0)
							{
								system("cls");
								printf("\n\tLogin efetuado com sucesso!");
								printf("\n\n\tSeja bem vindo %s, Atualmente você têm %i pontos", jogador.nome, jogador.pontos);
								printf("\n\n\tCarregando página jogador...");
								Sleep(2000);
								logou = true;
								break;
							}
							else
							{
								rewind(players);

								system("cls");
								printf("\n\tSenha Invalida...\n\n\tDeseja tentar novamente? (S / N)\n\n\tResposta: ");
								getchar();
								scanf("%c", &resposta);
							}

						} while (resposta != 'n' || resposta != 'N');
					}

					fclose(players);

					break;

				case saair:
					break;
				}

				if (logou == true)
				{
					logFora = false;

					players = fopen("players.dat", "a+b");
					do {
						system("cls");
						printf("\n\tBem vindo %s!", jogador.nome);
						printf("\n\n\tEscolha uma das opções abaixo:");
						printf("\n\n\t1.Alterar Cadastro");
						printf("\n\t2.Jogar");
						printf("\n\t3.Log out");
						printf("\n\n\tOpção desejada: ");
						scanf("%i", &jorge);

						switch (jorge)
						{
						case alterarCadastro:
							rewind(players);

							system("cls");

							valido = true;

							if (valido == true)
							{
								do {

									system("cls");

									printf("\n\tSeja bem vindo %s", jogador.nome);
									printf("\n\n\tPor gentileza insira a opcao desejada:");
									printf("\n\n\t1. Alterar nome");
									printf("\n\t2. Alterar login");
									printf("\n\t3. Alterar senha");
									printf("\n\t4. Excluir conta");
									printf("\n\t5. Voltar");
									printf("\n\n\tDigite a opcao desejada: ");
									scanf("%i", &change);

									switch (change)
									{
									case alterarNome: //-------------------------------------------------------ALTERAR NOME

										reserva = fopen("reserva.dat", "a+b");

										system("cls");

										printf("\n\tOpcao escolhida 1.Alterar nome");
										printf("\n\n\tDigite o novo nome: ");
										scanf("%s", &player.nome);

										do  //INICIO VERIFICAÇÃO NOME EXISTENTE
										{
											rewind(players);

											do
											{
												fread(&auxlogin, sizeof(auxlogin), 1, players);

												if (strcmp(player.nome, auxlogin.nome) == 0)
												{
													login = false;
													break;
												}
												else
												{
													login = true;
												}

											} while (!feof(players));

											if (login == false)
											{
												system("cls");

												printf("\n\tNome ja cadastrado!\n");
												printf("\n\tTente digitar um nome diferente: ");
												scanf("%s", player.nome);
											}

										} while (login == false);

										//JOGADOR NOME ANTERIOR
										//PLAYER NOME ATUAL

										rewind(players);
										rewind(reserva);

										jaescreveu = false;

										do
										{

											fread(&auxlogin, sizeof(auxlogin), 1, players);

											if (strcmp(jogador.nome, auxlogin.nome) == 0)
											{
												if (jaescreveu == false)
												{
													strcpy(auxlogin.nome, player.nome);
													fwrite(&auxlogin, sizeof(tipoJogador), 1, reserva);
												}

												jaescreveu = true;
											}
											else if (!feof(players))
											{
												fwrite(&auxlogin, sizeof(tipoJogador), 1, reserva);
											}

										} while (!feof(players));

										fclose(players);
										fclose(reserva);

										players = fopen("players.dat", "wb");
										reserva = fopen("reserva.dat", "rb");

										do
										{
											fread(&jogador, sizeof(jogador), 1, reserva);

											if (!feof(reserva))
												fwrite(&jogador, sizeof(tipoJogador), 1, players);

										} while (!feof(reserva));

										fclose(reserva);
										fclose(players);

										//remove("reserva.dat");

										break;

									case alterarLogin: //----------------------------------------------------ALTERAR LOGIN

													   //reserva = fopen("reserva.dat", "a+b");

										system("cls");

										printf("\n\tOpcao escolhida 2.Alterar alterar login");
										printf("\n\n\tDigite o novo login: ");
										scanf("%s", &player.login);

										fclose(players);
										players = fopen("players.dat", "a+b");

										do  //INICIO VERIFICAÇÃO NOME EXISTENTE
										{
											rewind(players);

											do
											{
												fread(&auxlogin, sizeof(auxlogin), 1, players);

												if (strcmp(player.login, auxlogin.login) == 0)
												{
													login = false;
													break;
												}
												else
												{
													login = true;
												}

											} while (!feof(players));

											if (login == false)
											{
												system("cls");

												printf("\n\n\tLogin ja cadastrado!\n");
												printf("\n\tTente digitar um login diferente: ");
												scanf("%s", player.login);
											}

										} while (login == false);

										//JOGADOR NOME ANTERIOR
										//PLAYER NOME ATUAL

										reserva = fopen("reserva.dat", "wb");

										rewind(players);

										jaescreveu = false;

										do
										{

											fread(&auxlogin, sizeof(auxlogin), 1, players);

											if (strcmp(jogador.login, auxlogin.login) == 0)
											{
												if (jaescreveu == false)
												{
													strcpy(auxlogin.login, player.login);
													fwrite(&auxlogin, sizeof(tipoJogador), 1, reserva);
													jaescreveu = true;
												}

												jaescreveu = true;
											}
											else if (!feof(players))
											{
												fwrite(&auxlogin, sizeof(tipoJogador), 1, reserva);
											}

										} while (!feof(players) && !feof(reserva));

										fclose(players);
										fclose(reserva);

										players = fopen("players.dat", "wb");
										reserva = fopen("reserva.dat", "rb");

										do
										{
											fread(&jogador, sizeof(jogador), 1, reserva);

											if (!feof(reserva))
												fwrite(&jogador, sizeof(tipoJogador), 1, players);

										} while (!feof(reserva));

										fclose(reserva);
										fclose(players);

										remove("reserva.dat");

										break;

									case alterarSenha://------------------------------------------------------ALTERAR SENHA

										system("cls");

										printf("\n\tOpcao escolhida 3.Alterar senha");
										printf("\n\n\tDigite a nova senha: ");
										scanf("%s", &player.senha);

										//JOGADOR NOME ANTERIOR
										//PLAYER NOME ATUAL

										fclose(players);

										reserva = fopen("reserva.dat", "wb");
										players = fopen("players.dat", "rb");

										jaescreveu = false;

										do
										{
											fread(&auxlogin, sizeof(auxlogin), 1, players);

											if (strcmp(jogador.senha, auxlogin.senha) == 0)
											{
												if (jaescreveu == false)
												{
													strcpy(auxlogin.senha, player.senha);
													fwrite(&auxlogin, sizeof(tipoJogador), 1, reserva);
												}

												jaescreveu = true;
											}
											else if (!feof(players))
											{
												fwrite(&auxlogin, sizeof(tipoJogador), 1, reserva);
											}

										} while (!feof(players));

										fclose(players);
										fclose(reserva);

										players = fopen("players.dat", "wb");
										reserva = fopen("reserva.dat", "rb");

										do
										{
											fread(&jogador, sizeof(jogador), 1, reserva);

											if (!feof(reserva))
												fwrite(&jogador, sizeof(tipoJogador), 1, players);

										} while (!feof(reserva));

										fclose(reserva);
										fclose(players);

										remove("reserva.dat");

										break;

									case excluirConta://----------------------------------------------------EXLUIR CONTA

										system("cls");

										printf("\n\tTem certeza que deseja excluir a conta?");
										printf("\n\n\t1. Sim");
										printf("\n\t2. Não\n\n\tOpção: ");
										scanf("%i", &change);

										if (change == 2)
											break;
										else
										{

											do {
												system("cls");

												printf("\n\tPara exluirmos a conta %s por favor reinsira sua senha", jogador.nome);
												printf("\n\n\tSenha: ");
												scanf("%s", auxlogin.senha);

												//jogador  - antigo
												//auxlogin - novo

												if (strcmp(auxlogin.senha, jogador.senha) == 0)
												{
													fclose(players);

													reserva = fopen("reserva.dat", "wb");
													players = fopen("players.dat", "rb");

													do
													{
														fread(&player, sizeof(player), 1, players);

														if (!feof(players) && strcmp(player.nome, jogador.nome) != 0)
														{
															fwrite(&player, sizeof(tipoJogador), 1, reserva);
														}

													} while (!feof(players) && !feof(reserva));

													fclose(reserva);
													fclose(players);

													reserva = fopen("reserva.dat", "rb");
													players = fopen("players.dat", "wb");


													do
													{
														fread(&player, sizeof(player), 1, reserva);

														if (!feof(players) && !feof(reserva))
															fwrite(&player, sizeof(tipoJogador), 1, players);

													} while (!feof(players) && !feof(reserva));

													fclose(reserva);
													fclose(players);

													remove("reserva.dat");
													condicao = true;
													break;
												}

												else
												{
													system("cls");

													printf("\n\tSenha inválida, deseja digitar novamente?");
													printf("\n\n\t1. Sim");
													printf("\n\t2. Não\n\n\tOpção: ");
													scanf("%i", &change);

													if (change == 2)
													{
														break;
													}
												}

											} while (true);
										}



										break;

									case sairAlterarCadastro:
										condicao = true;
										break;
										break;

									default:
										break;
									}

								} while (condicao == false);
							}

							break;
						case jogar:
							retratofalado.sexo = 1;
							retratofalado.corCabelo = 1;
							retratofalado.hobby = 1;
							retratofalado.feature = 1;
							//loadar o caso

							//casoparaloadar = 1;
							casoatualDesc = fopen("casos.dat", "r + b");
							//fseek(casoatualDesc, casoparaloadar * sizeof(tipoCaso), 0);//Achar o caso específico para carregar
							fread(&casoatual, sizeof(tipoCaso), 1, casoatualDesc);
							system("cls");
							while (!gameover && temporestante > 0) {
								printf("\t\tCaso número %i\n", casoparaloadar);
								printf("\t\t%s\n", casoatual.historiaGeral);
								printf("\t\tVocê está em %s\n\n", casoatual.cidades[0]);
								printf("\t\tO que deseja fazer?\n\n");
								printf("\t\t1 - Procurar pistas pela cidade\n");
								printf("\t\t2 - Viajar para outra cidade\n");
								printf("\t\t3 - Atualizar o retrato falado\n\n");
								printf("\tSua opção: ");
								scanf("%i", &opcaoemjogo);
								switch (opcaoemjogo) { //mudar para enum depois
								case 1://Procurar pistas pela cidade
									stayinoption = true;
									while (stayinoption) {
										system("cls");
										//printf("\t\tQual pista você deseja obter? (Pista 1, 2 ou 3, ou digite 4 para VOLTAR)\n");
										//printf("\tSua opção: ");
										printf("\t\tVocê está na cidade %s, e pode procurar por pistas nos seguintes lugares:\n\n");
										printf("\t1 - %s\n", casoatual.POI[cidadeatual * 3 + 0]);
										printf("\t2 - %s\n", casoatual.POI[cidadeatual * 3 + 1]);
										printf("\t3 - %s\n", casoatual.POI[cidadeatual * 3 + 2]);
										printf("\n\tOu digite 4 para VOLTAR");
										scanf("%i", &opcaoemopcao);
										if (opcaoemopcao > 0 && opcaoemopcao < 4) {
											printf("\tVocê vai para o(a) %s, e recebe uma pista: \n", casoatual.POI[cidadeatual * 3 + opcaoemopcao - 1]);
											printf("\t\t%s\n", casoatual.pistas[cidadeatual * 3 + opcaoemopcao - 1]);
											temporestante -= 50;
										}
										else if (opcaoemopcao == 4)
										{
											stayinoption = false;
											system("cls");
										}
										else printf("\n\t\tPista inválida\n");
									}
									break;
								case 2://Viajar para outra cidade (PRECISA CHECAR SE O VILAO ESTÁ AQUI)
									stayinoption = true;
									while (stayinoption) {
										system("cls");
										printf("\tPara qual cidade você quer ir? (ou digite 31 para VOLTAR)\n\n");
										for (int i = 0; i < casoatual.numeroCidades; i++)
											printf("\t\t%i - %s\n", i + 1, casoatual.cidades[i]);
										break;
										printf("\n\tSua opção: ");
										scanf("%i", &opcaoemopcao);
										if (opcaoemopcao > 0 && opcaoemopcao < casoatual.numeroCidades + 1) {
											printf("\n\n\t\tIndo para %s...", casoatual.cidades[opcaoemopcao - 1]);
											cidadeatual = opcaoemopcao - 1;
											temporestante -= 100;
											Sleep(1500);
											stayinoption = false;
										}
										else if (opcaoemopcao == 31) stayinoption = false;
										else printf("\n\tCidade inválida\n");
									}
									break;
								case 3://Retrato falado
									stayinoption = true;

									while (stayinoption) {
										system("cls");
										printf("\n\tO seu retrato falado atualmente é: ");
										checkPerson tempcheck;

										printf("\t\tSexo:             %s\n", tempcheck.sexo[retratofalado.sexo - 1]);
										printf("\t\tCor do cabelo:    %s\n", tempcheck.corCabelo[retratofalado.corCabelo - 1]);
										printf("\t\tHobby:            %s\n", tempcheck.hobby[retratofalado.hobby - 1]);
										printf("\t\tSímbolo marcante: %s\n", tempcheck.feature[retratofalado.feature - 1]);

										printf("\n\n\t\tQual característica você deseja atualizar?\n");
										printf("\t\t1 - Gênero\n");
										printf("\t\t2 - Cor do cabelo\n");
										printf("\t\t3 - Hobby\n");
										printf("\t\t4 - Símbolo marcante\n");
										printf("\t\t5 - VOLTAR\n");

										QualCaracteristica car;
										scanf("%i", &car);
										int newval = checkCarac(car);
										switch (car) {
										case sexo: retratofalado.sexo = newval; break;
										case corDeCabelo: retratofalado.corCabelo = newval; break;
										case Hobby: retratofalado.hobby = newval; break;
										case Feature: retratofalado.feature = newval; break;
										case 5: stayinoption = false; break;
										default: printf("\n\tCaracterística inválida\n"); break;
										}

										if (stayinoption) {//Checar se o retrato falado está correto

										}
									}
									break;
								default: printf("Opção não reconhecida, tente novamente...");
									Sleep(2000);
									break;
								}
							}

							break;
						case logOut:
							logFora = true;
							break;
						default:
							break;
						}
					} while (logFora == false);
				}
				break;
			}
		}

	} while (log != sair);

	return 0;
}

int oldPersona(tipoPersonagem* personagens)
{
	FILE* fd = fopen("personagem.dat", "a + b");
	int i = 0, qtdPersonas = 0, minAjuda = 0, j = 0;
	char personaEscolhida[200];
	tipoPersonagem aux[300], intermediaria;
	checkPerson checarCaract;

	system("cls");

	printf("\n\tEscolha o personagem que deseja colocar em seu caso\n\n");

	rewind(fd);

	do
	{
		fread(&intermediaria, sizeof(intermediaria), 1, fd);

		if (!feof(fd))
		{
			printf("\t%i. %s do sexo %s, cabelo %s,", i + 1, intermediaria.nome, checarCaract.sexo[intermediaria.sexo - 1], checarCaract.corCabelo[intermediaria.corCabelo - 1]);
			printf(" gosta de %s e seu símbolo marcante é %s \n", checarCaract.hobby[intermediaria.hobby - 1], checarCaract.feature[intermediaria.feature - 1]);
			qtdPersonas++;

			{
				strcpy(aux[i].nome, intermediaria.nome);
				aux[i].sexo = intermediaria.sexo;
				aux[i].corCabelo = intermediaria.corCabelo;
				aux[i].hobby = intermediaria.hobby;
				aux[i].feature = intermediaria.feature;
			}
		}

		i++;
	} while (!feof(fd));

	printf("\n\tOpções (digite os números separados por vírgula, MAX 100 personagens): ");
	scanf("%s", personaEscolhida);

	for (i = 0; i < strlen(personaEscolhida); i++)
	{
		if (personaEscolhida[i] != ',')
		{
			minAjuda = personaEscolhida[i] - 49;
			if (personaEscolhida[i + 1] != ',' && personaEscolhida[i + 1] != '\0')
			{
				minAjuda = (minAjuda * 10) + (personaEscolhida[i + 1] - 49);
				if (personaEscolhida[i + 2] != ',')
					minAjuda = (minAjuda * 10) + (personaEscolhida[i + 2] - 49);
			}
			strcpy(personagens[j].nome, aux[minAjuda].nome);
			personagens[j].sexo = aux[minAjuda].sexo;
			personagens[j].corCabelo = aux[minAjuda].corCabelo;
			personagens[j].hobby = aux[minAjuda].hobby;
			personagens[j].feature = aux[minAjuda].feature;

			j++;
		}
	}

	fclose(fd);

	return j;
}

void newPersona()
{
	FILE* fd = fopen("personagem.dat", "a + b");
	bool flag = false;
	char resposta;
	tipoPersonagem aux, ajudadora;

	do {
		system("cls");
		printf("\n\tCadastro de personagens\n");
		printf("\n\tDigite o nome do seu novo personagem: ");
		getchar();
		fgets(aux.nome, 50, stdin);
		for (int t = 0; t < strlen(aux.nome); t++)
		{
			if (aux.nome[t] == '\n')
				aux.nome[t] = '\0';
		}

		rewind(fd);

		do
		{
			fread(&ajudadora, sizeof(tipoPersonagem), 1, fd);

			if (strcmp(ajudadora.nome, aux.nome) == 0 && fd != NULL)
			{
				do
				{
					system("cls");
					printf("\n\tNome ja cadastrado!");
					printf("\n\n\tTente um nome diferente: ");
					fflush(stdin);
					fgets(aux.nome, 50, stdin);

				} while (strcmp(ajudadora.nome, aux.nome) == 0);
			}

		} while (!feof(fd));

		system("cls");
		printf("\tDigite o sexo de %s, de acordo com a tabela:\n", aux.nome);
		aux.sexo = checkCarac(sexo);
		system("cls");

		printf("\tDigite a cor do cabelo do(a) %s, de acordo com a tabela: ", aux.nome);
		aux.corCabelo = checkCarac(corDeCabelo);
		system("cls");

		printf("\tDigite um hobby do(a) %s, de acordo com a tabela: ", aux.nome);
		aux.hobby = checkCarac(Hobby);
		system("cls");

		printf("\tDigite um símbolo marcante do(a) %s, de acordo com a tabela: ", aux.nome);
		aux.feature = checkCarac(Feature);
		system("cls");

		getchar();
		printf("\n\tDeseja cadastrar mais personagens (S/N): ");
		scanf("%c", &resposta);

		fwrite(&aux, sizeof(tipoPersonagem), 1, fd);

		if (resposta == 'n' || resposta == 'N')
		{
			flag = true;
			fclose(fd);
		}

	} while (flag == false);


}

int checkCarac(QualCaracteristica caracteristica) {
	int escolha;
	fflush(stdin);
	switch (caracteristica)
	{
	case sexo:
		do {
			printf("\n\n\tSexos disponíveis:\n\n\t1.Masculino;\n\t2.Feminino\n\n\tOpção: ");
			scanf("%i", &escolha);
			if (escolha < 1 || escolha > 2)
			{
				printf("\n\tDigite uma opção válida!");
				Sleep(1500);
				system("cls");
			}
		} while (escolha < 1 || escolha > 2);
		return escolha;
	case corDeCabelo:
		do {
			printf("\n\n\tCores de cabelo disponíveis:\n\n\t1.Preto;\n\t2.Castanho;\n\t3.Loiro;\n\t4.Vermelho;\n\t5.Azul;\n\t6.Branco\n\n\tOpção: ");
			scanf("%i", &escolha);
			if (escolha < 1 || escolha > 6)
			{
				printf("\n\tDigite uma opção válida!");
				Sleep(1500);
				system("cls");
			}
		} while (escolha < 1 || escolha > 6);
		return escolha;
	case Hobby:
		do {
			printf("\n\n\tHobbies disponíveis:\n\n\t1.Caminhar;\n\t2.Jogar;\n\t3.Tocar instrumento(s);\n\t4.Ler;\n\t5.Discutir\n\n\tOpção: ");
			//{ "Caminhar", "Jogar", "Tocar instrumento", "Ler", "Discutir" };
			scanf("%i", &escolha);
			if (escolha < 1 || escolha > 5)
			{
				printf("\n\tDigite uma opção válida!");
				Sleep(1500);
				system("cls");
			}
		} while (escolha < 1 || escolha > 5);
		return escolha;
	case Feature:
		do {
			printf("\n\n\tSímbolos marcantes disponíveis:\n\n\t1.Chapéu;\n\t2.Boné;\n\t3.Tatuagem;\n\t4.Óculos;\n\t5.Pulseira;\n\t6.Anel;\n\t7.Colar\n\n\tOpção: ");
			//{"Chapéu", "Boné", "Tatuagem", "Óculos", "Pulseira", "Anel", "Colar"};
			scanf("%i", &escolha);
			if (escolha < 1 || escolha > 7)
			{
				printf("\n\tDigite uma opção válida!");
				Sleep(1500);
				system("cls");
			}
		} while (escolha < 1 || escolha > 7);
		return escolha;
	}
	return caracteristica;
}

void cripto(char* key, char* orig, char* cript) {
	int MA = 65, MI = 97;
	int i, j = 0, origlen = strlen(orig), keylen = strlen(key);
	_strlwr(key);
	char cl, ck;
	for (i = 0; i < origlen; i++) {
		ck = key[j];
		cl = orig[i];
		if (cl > 64 && cl < 91) { //maiuscula
			cript[i] = MA + (cl + ck - MA - MI) % 26;
			j = (j + 1) % keylen;
		}
		else if (cl > 96 && cl < 123) { //minuscula
			cript[i] = MI + (cl + ck - MI - MI) % 26;
			j = (j + 1) % keylen;
		}
		else { //simbolo
			if (cl == '\n')
				cript[i] = '\0';
			else
				cript[i] = (char)((int)orig[i] + 1);
		}
	}
}

//for (int t = 0; t < strlen(caso.cidades[contaCidade]); t++)
//{
//	if (caso.cidades[contaCidade][t] == '\n')
//		caso.cidades[contaCidade][t] = '\0';
//}

void ranking()
{
	FILE* fd = fopen("players.dat", "rb");
	tipoJogador jogador, aux;
	int maior = 0;
	int opcao, quantMaior = 0, i, j, min;
	int quantidadeJogadores;
	int count;
	int tamAsc;
	int point[500], xx;
	char m[500][30], x[30], tecla;
	bool primeiro = true, sgundo = true;

	system("cls");

	printf("\n\tRanking dos jogadores!");
	printf("\n\n\tDigite o modo de ordenacao: \n");
	printf("\n\t1. Por nome"); //Alfabeto	
	printf("\n\t2. Por nivel"); //Pontos ordem cadastro
	printf("\n\t3. Por ranking"); //Nivel = logo pontos desempatam
	printf("\n\t4. Voltar");
	printf("\n\n\tOpcao: ");
	scanf("%i", &opcao);

	system("cls");

	switch (opcao)
	{
	case 1:

		printf("\n\tNivel      Nome\n\n");
		quantidadeJogadores = 0;
		tamAsc = 0;
		primeiro = true;
		i = 0;

		do
		{
			fread(&jogador, sizeof(tipoJogador), 1, fd);

			if (!feof(fd))
			{
				strcpy(m[i], jogador.nome);
				point[i] = jogador.pontos;
				quantidadeJogadores++;
			}
			i++;

		} while (!feof(fd));

		for (i = 0; i < quantidadeJogadores; i++)
		{
			for (j = 0; j < quantidadeJogadores - 1; j++)
			{
				if (strcmp(m[j], m[j + 1]) > 0)
				{
					strcpy(x, m[j]);
					xx = point[j];
					strcpy(m[j], m[j + 1]);
					point[j] = point[j + 1];
					strcpy(m[j + 1], x);
					point[j + 1] = xx;
				}
			}
		}

		for (i = 0; i < quantidadeJogadores; i++)
		{
			printf("\t%i         %s\n", point[i] / 100, m[i]);
		}

		break;


	case 2:

		printf("\n\tPosicao      Nivel      Nome\n\n");
		quantidadeJogadores = 0;

		do
		{
			fread(&jogador, sizeof(tipoJogador), 1, fd);

			if ((jogador.pontos / 100) >= maior)
				maior = jogador.pontos / 100;

			quantidadeJogadores++;

		} while (!feof(fd));

		rewind(fd);

		quantMaior = 0;
		i = 1;
		count = 0;

		do
		{
			fread(&aux, sizeof(tipoJogador), 1, fd);

			if ((aux.pontos / 100) == maior && !feof(fd))
			{
				printf("\t   %i           %i        %s\n", i, aux.pontos / 100, aux.nome);
				count++;
				i++;
			}
			if (feof(fd))
			{
				if (count == quantidadeJogadores - 1)
					break;

				rewind(fd);
				maior--;
			}

		} while (count != quantidadeJogadores - 1);

		rewind(fd);

		break;

	case 3:

		printf("\n\tRanking      Nivel      Nome\n\n");
		quantidadeJogadores = 0;

		do
		{
			fread(&jogador, sizeof(tipoJogador), 1, fd);

			if ((jogador.pontos) >= maior)
				maior = jogador.pontos;

			quantidadeJogadores++;

		} while (!feof(fd));

		rewind(fd);

		quantMaior = 0;
		i = 1;
		count = 0;

		do
		{
			fread(&aux, sizeof(tipoJogador), 1, fd);

			if (aux.pontos == maior && !feof(fd))
			{
				printf("\t   %i           %i        %s\n", i, aux.pontos / 100, aux.nome);
				count++;
				i++;
			}
			if (feof(fd))
			{
				if (count == quantidadeJogadores - 1)
					break;

				rewind(fd);
				maior--;
			}

		} while (count != quantidadeJogadores - 1);

		rewind(fd);

		break;
	case 4:
		fclose(fd);
		break;
	default:
		break;
	}

	printf("\n\n\tDigite qualquer tecla pra continuar...");
	getchar();
	scanf("%c", &tecla);
}
