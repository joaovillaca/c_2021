$file = 'matrizes.c'
$target = 'teste'
$cargs = '-o', $target, '-Wall', '-std=c11'

gcc $file $cargs

if($LASTEXITCODE -eq 0){
    &"./$target.exe"
}