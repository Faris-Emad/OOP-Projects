param(
    [Parameter(Mandatory=$false)]
    [string]$SourceFile
)

# If no source file provided, ask for it
if ([string]::IsNullOrWhiteSpace($SourceFile)) {
    $SourceFile = Read-Host "Enter the source file name (e.g., main.cpp)"
    
    # If still empty, use default
    if ([string]::IsNullOrWhiteSpace($SourceFile)) {
        $SourceFile = "main.cpp"
        Write-Host "No file specified, using default: $SourceFile" -ForegroundColor Yellow
    }
}

# Check if source file exists
if (-not (Test-Path $SourceFile)) {
    Write-Host "Error: Source file '$SourceFile' not found!" -ForegroundColor Red
    exit 1
}

# Extract filename without extension for executable name
$baseName = [System.IO.Path]::GetFileNameWithoutExtension($SourceFile)
$exeName = "$baseName.exe"

Write-Host "Compiling $SourceFile..." -ForegroundColor Yellow

# Compile the C++ file
$compileResult = & g++ -o $exeName $SourceFile 2>&1

if ($LASTEXITCODE -ne 0) {
    Write-Host "Compilation failed:" -ForegroundColor Red
    Write-Host $compileResult -ForegroundColor Red
    exit 1
}

Write-Host "Compilation successful!" -ForegroundColor Green
Write-Host "Running $exeName..." -ForegroundColor Cyan
Write-Host ("=" * 50) -ForegroundColor Blue

# Run the executable
& .\$exeName

Write-Host ("=" * 50) -ForegroundColor Blue
Write-Host "Program finished." -ForegroundColor Green