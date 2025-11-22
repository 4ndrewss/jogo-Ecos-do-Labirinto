Código em Markdown:
# 🎮 Ecos do Labirinto  

Este repositório contém o projeto desenvolvido para as disciplinas **Programação Imperativa e Funcional (2025.2)** e **Lógica para Computação (2025.2)** da **CESAR School**.  

O jogo combina **lógica proposicional** e **programação em C** para criar uma experiência interativa, prática e desafiadora, envolvendo raciocínio lógico, estruturas de controle e modularização.  
O jogador percorre **três fases de labirinto**, enfrentando guardiões que testam seus conhecimentos de lógica, enquanto uma história misteriosa se desenrola nos bastidores.  

---

## 👥 Integrantes do Grupo  

| Nome | Usuário no GitHub |  
|------|-----------------|  
| [Andrews Queiroz](https://github.com/4ndrewss) | @4ndrewss |  
| [Arthur Ferreira](https://github.com/ArchangelLoer) | @ArchangelLoer |  
| [Enzo Amorim](https://github.com/ENZOBRS) | @ENZOBRS |  
| [Gustavo Veloso](https://github.com/velosogustavo) | @velosogustavo |  
| [Pedro Henrique](https://github.com/Pedrohcs13) | @Pedrohcs13 |  
| [Hilton Resende](https://github.com/HResende23) *(Lógica para Computação)* | @HResende23 |  

---

## 🧠 Disciplinas  

- **Programação Imperativa e Funcional - 2025.2**  
- **Lógica para Computação - 2025.2**  

---

## 🏫 Instituição  

**CESAR School**  

---

## 📜 Sobre o Jogo  

**Nome:** Ecos do Labirinto  
**Objetivo:** Avançar pelas três fases do labirinto, responder corretamente às perguntas dos guardiões e descobrir a história secreta por trás do jogo.  

**Fases:**  
1. **Fase 1 – Labirinto Inicial:** Introdução à lógica proposicional e estruturas básicas do labirinto.  
2. **Fase 2 – Desafios Intermediários:** Labirinto mais complexo, perguntas de lógica mais elaboradas.  
3. **Fase 3 – Guardião Final:** Conecta tudo que foi aprendido, respostas certas revelam partes da história secreta.  

**Interação:**  
- Movimentação pelo labirinto usando WASD
- Ao encontrar um guardião, o jogador deve **responder perguntas de lógica**, usando as teclas 1, 2, 3 ou 4, que conectam conceitos das duas disciplinas.  
- Acertos avançam o jogador, isso pode gerar mais pontos; erros podem levá-lo a recomeçar a fase, isso pode gerar menos pontos no final.

---

## 🖼️ Screenshots  

 <img width="940" height="537" alt="Screenshot_1" src="https://github.com/user-attachments/assets/e1e9e933-7bd9-4d55-94d1-7a81cee5913e" />
*Mapa de uma das fases do labirinto.*  

<img width="951" height="543" alt="Screenshot_5" src="https://github.com/user-attachments/assets/4831fde4-0f55-4a24-a9ef-4c2133d10cdb" />
*Exemplo de tela de resposta correta.*  

<img width="944" height="538" alt="Screenshot_2" src="https://github.com/user-attachments/assets/dc07abcc-9987-45fa-965a-1c035be0cd05" /> 
*Exemplo de tela de resposta incorreta.*  

*(Substitua os caminhos pelas imagens reais do projeto.)*  

---
## 🚀 Como Executar o Projeto

O jogo foi desenvolvido e otimizado para ambientes Linux, sendo o **WSL** (Windows Subsystem for Linux) a forma **recomendada** de rodá-lo no Windows.

---

### 🖥️ 1. Linux (Natível)

Siga os passos abaixo em seu terminal Linux:

1.  **Atualize o sistema e instale as ferramentas essenciais** (GCC, G++, Make, etc.):

    ```bash
    sudo apt update && sudo apt upgrade -y
    sudo apt install build-essential -y
    ```

2.  **Clone o repositório e entre na pasta do projeto**:

    ```bash
    git clone <link-do-repositorio>
    cd <pasta-do-repositorio>
    ```

3.  **Use os comandos `make` para gerenciar a execução**:

    | Comando        | Descrição                                 |
    | :------------- | :---------------------------------------- |
    | `make`         | **Compila** o projeto.                    |
    | `make run`     | **Executa** o jogo.                       |
    | `make clean`   | **Remove** os arquivos compilados (`.o`, executável, etc.). |

---

### 🪟 2. Windows (via WSL) – Recomendado ✨

**Observação Importante:** Algumas dependências, como a `cli-lib`, funcionam corretamente apenas em ambiente Linux. Por isso, o WSL oferece a melhor experiência no Windows.

1.  **Instale o WSL (se ainda não estiver habilitado)**:
    * Abra o **PowerShell como Administrador**.
    * Execute o comando para instalar o WSL (e o Ubuntu, por padrão):

    ```powershell
    wsl --install
    ```
    * Siga as instruções para configurar seu usuário Linux.

2.  **Prepare o ambiente Linux dentro do WSL**:
    * Após abrir a distro Linux (ex: Ubuntu), execute no terminal da distro:

    ```bash
    sudo apt update && sudo apt upgrade -y
    sudo apt install build-essential -y
    ```

3.  **Clone e gerencie o projeto (igual ao Linux)**:
    * **Clone o repositório e entre na pasta**:

    ```bash
    git clone <link-do-repositorio>
    cd <pasta-do-repositorio>
    ```

    * **Compile e execute** (comandos `make`):

    ```bash
    make
    make run
    make clean
    ```

> 📌 **Lembrete:** Todos os comandos de `apt`, `git`, e `make` devem ser executados **dentro do terminal da sua distro Linux (Ubuntu, Debian, etc.)**, e **NÃO** no PowerShell do Windows.
