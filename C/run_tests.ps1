# Array com número de threads para testar
$threads = @(1, 2, 4, 8)
$datasets = @("dataset_4096_byte", "dataset_65536_byte")

# Função para executar o teste e retornar o tempo
function Run-Test {
    param (
        [string]$program,
        [string]$dataset,
        [int]$threads = 0
    )
    
    if ($threads -gt 0) {
        $result = Get-Content $dataset | & ".\$program" $threads 2>&1
    } else {
        $result = Get-Content $dataset | & ".\$program" 2>&1
    }
    
    # Extrair o tempo de execução da saída
    $time = ($result | Select-String "Execution time:").ToString()
    return $time
}

Write-Host "Iniciando testes de performance..."
Write-Host "=================================="

foreach ($dataset in $datasets) {
    Write-Host "`nDataset: $dataset"
    Write-Host "----------------"
    
    # Versão sequencial
    Write-Host "`nVersão Sequencial:"
    $result = Run-Test "nbody.exe" $dataset
    Write-Host $result
    
    # Versão paralela com diferentes números de threads
    Write-Host "`nVersão Paralela:"
    foreach ($thread in $threads) {
        Write-Host "`nThreads: $thread"
        $result = Run-Test "nbody_parallel.exe" $dataset $thread
        Write-Host $result
    }
} 