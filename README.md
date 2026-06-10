# 🐾 Sistema Pet Shop — 3º Ciclo

> Trabalho desenvolvido para a disciplina de Lógica de Programação | Linguagem C  

---

## 📋 Sobre o Projeto

Sistema de gerenciamento para pet shop desenvolvido em **C**, com armazenamento de dados em arquivos `.txt`. O sistema cobre desde o cadastro de pets e donos até agendamento de consultas veterinárias e venda de medicamentos.

### Funcionalidades

| Módulo | Descrição |
|--------|-----------|
| 🐶 **Cadastro** | Registra pet, nome do dono e telefone |
| ✂️ **Serviços** | Pedidos de banho, tosa ou banho+tosa |
| 🩺 **Consulta Veterinária** | Agendamento com data/hora, veterinário e motivo |
| 💊 **Medicamentos** | Catálogo de produtos, registro de compra e cálculo de total |
| 💾 **Arquivos** | Todos os dados salvos e lidos em `.txt` |

### Arquivos de Dados

```
pets.txt          → cadastros de pets e donos
pedidos.txt       → pedidos de serviço
consultas.txt     → agendamentos veterinários
medicamentos.txt  → catálogo de medicamentos
compras.txt       → compras de medicamentos realizadas
```

---

## 🚀 Como Compilar e Executar

### Pré-requisitos

- GCC instalado (`gcc --version` para verificar)
- Terminal (Linux/macOS) ou MinGW/WSL (Windows)

### Compilar

```bash
gcc -o petshop main.c -Wall
```

### Executar

```bash
./petshop
```

> No Windows: `petshop.exe`

---

## 🌿 Git & GitHub — Guia para a Equipe

### Configuração inicial (apenas uma vez)

```bash
git config --global user.name "Seu Nome"
git config --global user.email "seu@email.com"
```

### Clonar o repositório

```bash
git clone https://github.com/usuario/petshop.git
cd petshop
```

---

### 🔀 Subindo sua própria branch

Cada integrante deve trabalhar na sua própria branch para não conflitar com o trabalho dos colegas.

**1. Certifique-se de estar na main atualizada**
```bash
git checkout main
git pull origin main
```

**2. Crie sua branch com seu nome ou funcionalidade**
```bash
git checkout -b feature/nome-da-funcionalidade
# Exemplos:
# git checkout -b feature/modulo-medicamentos
# git checkout -b feature/joao-cadastro
```

**3. Faça suas alterações no código e salve os arquivos**

**4. Veja o que foi alterado**
```bash
git status
```

**5. Adicione os arquivos modificados**
```bash
git add .               # adiciona tudo
git add main.c          # ou adicione arquivo por arquivo
```

**6. Faça o commit com uma mensagem clara**
```bash
git commit -m "feat: adiciona módulo de agendamento veterinário"
```

**7. Suba sua branch para o GitHub**
```bash
git push origin feature/nome-da-funcionalidade
```

**8. Abra um Pull Request no GitHub**
- Acesse o repositório no GitHub
- Clique em **"Compare & pull request"**
- Descreva o que foi feito e clique em **"Create pull request"**
- Aguarde revisão de um colega antes de dar merge

---

### 🔄 Mantendo sua branch atualizada

Se a `main` foi atualizada enquanto você trabalhava, sincronize sua branch:

```bash
git checkout main
git pull origin main
git checkout feature/sua-branch
git merge main
```

Se houver conflito, o Git indicará os arquivos. Abra-os, resolva as diferenças marcadas com `<<<<<<` e `>>>>>>`, salve e então:

```bash
git add .
git commit -m "fix: resolve conflito com main"
```

---

### 📌 Comandos úteis do dia a dia

| Comando | O que faz |
|---------|-----------|
| `git status` | Mostra arquivos modificados |
| `git log --oneline` | Histórico de commits resumido |
| `git diff` | Mostra as mudanças ainda não commitadas |
| `git stash` | Guarda alterações temporariamente sem commitar |
| `git stash pop` | Recupera o que foi guardado com stash |
| `git branch` | Lista todas as branches locais |
| `git branch -d nome` | Deleta uma branch local |
| `git pull origin main` | Atualiza sua cópia local da main |

---

### 📝 Boas Práticas de Commit

Use mensagens de commit no formato: `tipo: descrição curta`

| Tipo | Quando usar |
|------|-------------|
| `feat:` | Nova funcionalidade |
| `fix:` | Correção de bug |
| `docs:` | Alteração em documentação |
| `refactor:` | Refatoração sem mudar comportamento |
| `test:` | Adição ou ajuste de testes |

**Exemplos:**
```
feat: adiciona função de cadastro de pet
fix: corrige leitura do arquivo consultas.txt
docs: atualiza README com instruções de compilação
```

---

### 🛡️ Proteção da branch main

Recomendamos configurar no GitHub (**Settings → Branches → Branch protection rules**):

- ✅ Require a pull request before merging
- ✅ Require at least 1 approval
- ✅ Do not allow direct pushes to main

Isso garante que ninguém sobrescreva o trabalho dos colegas acidentalmente.

---

### 🐛 Issues — Organizando as tarefas

Use a aba **Issues** do GitHub para distribuir e acompanhar as tarefas:

1. Acesse **Issues → New Issue**
2. Dê um título claro: `Implementar módulo de medicamentos`
3. Descreva o que precisa ser feito
4. Atribua a um integrante em **Assignees**
5. Feche a issue com `Closes #numero` na mensagem do commit ou PR

---

## 👥 Integrantes

| Nome | Módulo Responsável |
|------|--------------------|
| Arthur | |
| Henrique | |
| João | |
| Luis | |
| Sthefanny | |
| Túlio | |

---

*Desenvolvido para a disciplina Lógica Matemática e Algoritmo — 3º Ciclo*
