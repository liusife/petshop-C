# 🐾 Pet Shop — Sistema em C

Sistema de gerenciamento para pet shop desenvolvido em **C**, com armazenamento em arquivos `.txt` e compilação incremental via `Makefile`.

---

## Funcionalidades

| Módulo | Descrição |
|--------|-----------|
| ✂️ **Serviços** | Cadastro, listagem, edição e exclusão de pedidos de banho, tosa ou banho+tosa (com valor automático) |
| 🩺 **Consultas** | Agendamento de consultas veterinárias com data, hora, veterinário e motivo |
| 🐕 **Pet** | Em cada registro: nome do dono, nome do pet, **espécie** e **raça** |

## Estrutura do Projeto

```
petshop-C/
├── main.c                  ← Menu principal
├── include/
│   ├── util.h              ← limpar_tela(), aguardar_enter()
│   ├── servico.h           ← struct Pedido e protótipos
│   └── consulta.h          ← struct Consulta e protótipos
├── src/
│   ├── servico.c           ← Implementação do CRUD de pedidos
│   └── consulta.c          ← Implementação do CRUD de consultas
├── data/                   ← Arquivos .txt gerados em execução
│   ├── pedidos.txt
│   └── consultas.txt
├── Makefile                ← Compilação incremental
├── make.bat                ← Wrapper para Windows (MinGW)
└── .gitignore
```

## Como Compilar e Executar

### Pré-requisitos

- GCC (MinGW no Windows)
- Make (ou `mingw32-make` no Windows via MSYS2 / Git Bash)

### Compilar

```bash
# Linux / macOS
make

# Windows (MinGW)
mingw32-make
# ou
.\make.bat
```

### Executar

```bash
./petshop         # Linux / macOS
petshop.exe       # Windows
```

O `Makefile` compila apenas os arquivos modificados (incremental) e gera os `.o` na pasta `obj/`.

---

## 👥 Integrantes

| Nome | Módulo |
|------|--------|
| Arthur | |
| Henrique | |
| João | |
| Luis | |
| Sthefanny | |
| Túlio | |

---

*Disciplina de Lógica de Programação — 3º Ciclo*
