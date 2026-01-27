# PowerShell script to compile and run main.cpp

Write-Host "Compiling main.cpp..." -ForegroundColor Cyan

# Compile the C++ file
g++ main.cpp -o main.exe

# Check if compilation was successful
if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilation successful!" -ForegroundColor Green
    Write-Host "Running main.exe..." -ForegroundColor Cyan
    Write-Host "------------------------" -ForegroundColor Yellow
    
    # Run the executable
    .\main.exe
} else {
    Write-Host "Compilation failed!" -ForegroundColor Red
    exit 1
}
