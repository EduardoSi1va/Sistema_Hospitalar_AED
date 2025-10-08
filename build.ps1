# build.ps1 - Compila o projeto usando gcc no PowerShell
# Uso: .\build.ps1

$gcc = Get-Command gcc -ErrorAction SilentlyContinue
if (-not $gcc) {
    Write-Host "gcc não encontrado no PATH. Instale MinGW-w64 ou use WSL/MSYS2." -ForegroundColor Red
    exit 1
}

$srcs = @(
    'main.c',
    'Lista_Simples_Encadeada\lista.c',
    'Fila_Encadeada\fila.c',
    'Pilha_Encadeada\pilha.c',
    'TAD_Paciente\paciente.c',
    'TAD_functions\functions.c',
    'TAD_IO\IO.c'
)

$flags = '-Wall -Wextra -std=c99 -pedantic -g'
$output = 'sistema_hospitalar.exe'

$cmd = "gcc $flags " + ($srcs -join ' ') + " -o $output"
Write-Host "Executando: $cmd"

$args = @()
$args += $flags -split ' '
$args += $srcs
$args += '-o'
$args += $output
$proc = Start-Process -FilePath gcc -ArgumentList $args -NoNewWindow -Wait -PassThru
if ($proc.ExitCode -ne 0) {
    Write-Host "Compilação falhou com código de saída $($proc.ExitCode)" -ForegroundColor Red
    exit $proc.ExitCode
}

Write-Host "Compilação concluída: $output" -ForegroundColor Green
