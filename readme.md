                            Gerenciador de Playlist de Músicas


                Funcionalidades

- Exibir playlist pela ordem de cadastro
- Exibir playlist ordenada pelo nome das músicas
- Inserir nova música
- Remover uma música
- Buscar por uma música
- Avançar para próxima música
- Retornar à música anterior

Como Compilar e Executar

Pré-requisitos

- GCC (GNU Compiler Collection)
          Compilação

```sh
gcc main.c -o gerenciador_playlist

## para correçao de acentos
utilizar no CMD
chcp 65001

utilizar no powershell
$OutputEncoding = [console]::InputEncoding = [console]::OutputEncoding = New-Object System.Text.UTF8Encoding
