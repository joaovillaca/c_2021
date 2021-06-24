# makefile para compilar C em
# Windows + MingW + Powershell
# arquivo source = argumento 1
# nome do executavel = argumento 2 (SEM extensao .exe)
# by zerodois

$file = $args[0]
$target = $args[1]
$headers = $args[2]

if($file -eq '-help') {
    Write-Output "Como usar esse makefile:"
    Write-Output "tente:"
    Write-Output "> ./make.ps1 <arquivo.c> <executavel_a_ser_gerado> <opcoes>"
    Write-Output "Opções    |   Descrição"
    Write-Output "-help     |   ajuda"
    Write-Output "-h        |   atualizar cabeçalhos"
    exit
}

if($null -eq $file) {
    Write-Output "Make falhou: nenhum arquivo especificado."
    Write-Output "tente:"
    Write-Output "> ./make.ps1 <arquivo.c> <executavel_a_ser_gerado>"
    exit
}

if($null -eq $target) {
    $target = 'teste'
}

$simple = '-o', $target, '-Wall', '-std=c11'
$scripted = '-o', "$target *.c *.h", '-Wall', '-std=c11'

if($null -eq $headers) {
    gcc $file $simple
}
elseif($headers -eq '-h') {
    python3.exe make_headers.py

    if($LASTEXITCODE -eq 0) {
        Write-Output "make_headers.py: Cabeçalhos (headers) gerados com sucesso."
        gcc $file $scripted

        if($LASTEXITCODE -eq 0) {
            Write-Output "Arquivo $file compilado para $target.exe."
            Write-Output "==================== Executando ===================="
            &"./$target"
            exit
        }
        else {
            Write-Output "Make falhou: erro de compilação."
            exit
        }
    }
    else {
        Write-Output "Make falhou: erro ao gerar cabeçalhos (headers)."
        exit
    }
}
elseif($headers -eq '-help') {
    Write-Output "Como usar esse makefile:"
    Write-Output "tente:"
    Write-Output "> ./make.ps1 <arquivo.c> <executavel_a_ser_gerado> <opcoes>"
    Write-Output "Opções    |   Descrição"
    Write-Output "-help     |   ajuda"
    Write-Output "-h        |   ativar geração de cabeçalhos"
    exit
}
else {
    Write-Output "Make falhou: argumento de cabeçalhos (headers) inválido."
    exit
}

if($LASTEXITCODE -eq 0) {
    Write-Output "Arquivo $file compilado para $target.exe."
    Write-Output "==================== Executando ===================="
    &"./$target"
}
else {
    Write-Output "Make falhou: erro de compilação."
    exit
}
