<#
	update_enable_mocks_headers.ps1

	Replaces raw ENABLE_MOCKS toggles with the dedicated header includes.
	Usage examples:
	  powershell -ExecutionPolicy Bypass -File tools/update_enable_mocks_headers.ps1
	  powershell -File tools/update_enable_mocks_headers.ps1 -Paths tests/umock_c_int
	  powershell -File tools/update_enable_mocks_headers.ps1 -ExcludePaths deps,build
#>

[CmdletBinding(SupportsShouldProcess = $true)]
param(
	[Parameter(Position = 0)]
	[string[]]$Paths,

	[string[]]$ExcludePaths
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$scriptRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$repoRoot = [System.IO.Path]::GetFullPath((Join-Path -Path $scriptRoot -ChildPath '..'))

if (-not $Paths -or $Paths.Count -eq 0) {
	$Paths = @($repoRoot)
}

$targetExtensions = New-Object 'System.Collections.Generic.HashSet[string]' ([System.StringComparer]::OrdinalIgnoreCase)
[void]$targetExtensions.Add('.c')
[void]$targetExtensions.Add('.h')
[void]$targetExtensions.Add('.cpp')

$enableHeaderPath = [System.IO.Path]::GetFullPath((Join-Path -Path $repoRoot -ChildPath 'inc/umock_c/umock_c_ENABLE_MOCKS.h'))
$disableHeaderPath = [System.IO.Path]::GetFullPath((Join-Path -Path $repoRoot -ChildPath 'inc/umock_c/umock_c_DISABLE_MOCKS.h'))
$bypassFiles = New-Object 'System.Collections.Generic.HashSet[string]' ([System.StringComparer]::OrdinalIgnoreCase)
[void]$bypassFiles.Add($enableHeaderPath)
[void]$bypassFiles.Add($disableHeaderPath)

function Resolve-AbsolutePath {
	param(
		[Parameter(Mandatory = $true)]
		[string]$PathValue
	)

	if ([string]::IsNullOrWhiteSpace($PathValue)) {
		return $null
	}

	try {
		return (Resolve-Path -LiteralPath $PathValue -ErrorAction Stop).Path
	}
	catch {
		try {
			return [System.IO.Path]::GetFullPath((Join-Path -Path (Get-Location).Path -ChildPath $PathValue))
		}
		catch {
			return $null
		}
	}
}

function Normalize-DirectoryRoot {
	param(
		[Parameter(Mandatory = $true)]
		[string]$PathValue
	)

	$trimmed = $PathValue.TrimEnd([System.IO.Path]::DirectorySeparatorChar, [System.IO.Path]::AltDirectorySeparatorChar)
	if ($trimmed.Length -eq 0) {
		return [System.IO.Path]::DirectorySeparatorChar
	}

	return $trimmed + [System.IO.Path]::DirectorySeparatorChar
}

function Test-IsExcluded {
	param(
		[Parameter(Mandatory = $true)]
		[string]$FullName,

		[string[]]$Exclusions = @()
	)

	if ($null -eq $Exclusions -or $Exclusions.Count -eq 0) {
		return $false
	}

	foreach ($entry in $Exclusions) {
		if ($entry.Length -eq 0) {
			continue
		}

		if ($entry[$entry.Length - 1] -eq [System.IO.Path]::DirectorySeparatorChar) {
			if ($FullName.StartsWith($entry, [System.StringComparison]::OrdinalIgnoreCase)) {
				return $true
			}
		}
		else {
			if ($FullName.Equals($entry, [System.StringComparison]::OrdinalIgnoreCase)) {
				return $true
			}
		}
	}

	return $false
}

function Get-LineEnding {
	param(
		[Parameter(Mandatory = $true)]
		[string]$Text
	)

	if ($Text -match "`r`n") { return "`r`n" }
	if ($Text -match "`n") { return "`n" }
	if ($Text -match "`r") { return "`r" }
	return [Environment]::NewLine
}

function Update-EnableMocksLines {
	param(
		[Parameter(Mandatory = $true)]
		[AllowEmptyCollection()]
		[AllowEmptyString()]
		[string[]]$Lines
	)

	$output = New-Object 'System.Collections.Generic.List[string]'
	$changed = $false

	for ($i = 0; $i -lt $Lines.Count; $i++) {
		$line = $Lines[$i]

		if ($line -match '^(?<indent>\s*)#define\s+ENABLE_MOCKS\b') {
			$indent = $matches['indent']
			$output.Add(("{0}#include ""umock_c/umock_c_ENABLE_MOCKS.h"" // ============================== ENABLE_MOCKS" -f $indent))
			$changed = $true

			$pending = New-Object 'System.Collections.Generic.List[string]'
			$j = $i + 1
			while ($j -lt $Lines.Count -and $Lines[$j] -match '^\s*$') {
				$pending.Add($Lines[$j])
				$j++
			}

			if ($j -lt $Lines.Count -and $Lines[$j] -match '^\s*#include\s+[<\"]umock_c/umock_c_prod\.h[>\"]') {
				$changed = $true
				$i = $j
			}
			else {
				foreach ($blank in $pending) { $output.Add($blank) }
				$i = $j - 1
			}

			continue
		}

		if ($line -match '^(?<indent>\s*)#undef\s+ENABLE_MOCKS\b') {
			$indent = $matches['indent']
			$output.Add(("{0}#include ""umock_c/umock_c_DISABLE_MOCKS.h"" // ============================== DISABLE_MOCKS" -f $indent))
			$changed = $true

			$pending = New-Object 'System.Collections.Generic.List[string]'
			$j = $i + 1
			while ($j -lt $Lines.Count -and $Lines[$j] -match '^\s*$') {
				$pending.Add($Lines[$j])
				$j++
			}

			if ($j -lt $Lines.Count -and $Lines[$j] -match '^\s*#include\s+[<\"]umock_c/umock_c_prod\.h[>\"]') {
				$changed = $true
				$i = $j
			}
			else {
				foreach ($blank in $pending) { $output.Add($blank) }
				$i = $j - 1
			}

			continue
		}

		$output.Add($line)
	}

	return [pscustomobject]@{
		Changed = $changed
		Lines   = $output
	}
}

$normalizeExcludeInputs = @()
if ($ExcludePaths) {
	foreach ($exclude in $ExcludePaths) {
		if ($null -eq $exclude) { continue }

		foreach ($token in ($exclude -split ',')) {
			$trimmedToken = $token.Trim()
			if ($trimmedToken.Length -gt 0) {
				$normalizeExcludeInputs += $trimmedToken
			}
		}
	}
}

$exclusionRoots = @()
if ($normalizeExcludeInputs.Count -gt 0) {
	foreach ($exclude in $normalizeExcludeInputs) {
		$resolvedExclude = Resolve-AbsolutePath -PathValue $exclude
		if (-not $resolvedExclude) {
			Write-Warning "Exclude path '$exclude' could not be resolved."
			continue
		}

		if (-not (Test-Path -LiteralPath $resolvedExclude)) {
			Write-Warning "Exclude path '$resolvedExclude' does not exist."
			continue
		}

		$excludeItem = Get-Item -LiteralPath $resolvedExclude
		if ($excludeItem.PSIsContainer) {
			$exclusionRoots += Normalize-DirectoryRoot -PathValue $excludeItem.FullName
		}
		else {
			$exclusionRoots += $excludeItem.FullName
		}
	}
}

$filesToProcess = New-Object 'System.Collections.Generic.List[System.IO.FileInfo]'
$seen = New-Object 'System.Collections.Generic.HashSet[string]' ([System.StringComparer]::OrdinalIgnoreCase)

foreach ($inputPath in $Paths) {
	$resolvedPath = Resolve-AbsolutePath -PathValue $inputPath
	if (-not $resolvedPath) {
		Write-Warning "Path '$inputPath' could not be resolved."
		continue
	}

	if (-not (Test-Path -LiteralPath $resolvedPath)) {
		Write-Warning "Path '$resolvedPath' does not exist."
		continue
	}

	$item = Get-Item -LiteralPath $resolvedPath
	if ($item.PSIsContainer) {
		Get-ChildItem -LiteralPath $item.FullName -Recurse -File | ForEach-Object {
			if (-not $targetExtensions.Contains($_.Extension)) { return }
			if (Test-IsExcluded -FullName $_.FullName -Exclusions $exclusionRoots) { return }
			if ($bypassFiles.Contains($_.FullName)) { return }
			if ($seen.Add($_.FullName)) { $filesToProcess.Add($_) }
		}
	}
	else {
		if ($targetExtensions.Contains($item.Extension) -and -not (Test-IsExcluded -FullName $item.FullName -Exclusions $exclusionRoots)) {
			if ($bypassFiles.Contains($item.FullName)) { continue }
			if ($seen.Add($item.FullName)) { $filesToProcess.Add($item) }
		}
	}
}

if ($filesToProcess.Count -eq 0) {
	Write-Host 'No matching files were found.' -ForegroundColor Yellow
	return
}

$utf8NoBom = New-Object System.Text.UTF8Encoding($false)
$updated = New-Object 'System.Collections.Generic.List[string]'

foreach ($fileInfo in $filesToProcess) {
	try {
		$text = [System.IO.File]::ReadAllText($fileInfo.FullName)
	}
	catch {
		Write-Warning "Failed to read '$($fileInfo.FullName)': $($_.Exception.Message)"
		continue
	}

	$lineEnding = Get-LineEnding -Text $text
	$lines = [System.Text.RegularExpressions.Regex]::Split($text, "\r?\n")
	if ($lines.Count -eq 0) {
		$lines = @('')
	}
	$result = Update-EnableMocksLines -Lines $lines

	if (-not $result.Changed) {
		continue
	}

	$newText = [string]::Join($lineEnding, $result.Lines.ToArray())
	$endsWithNewline = $text.EndsWith("`r`n") -or $text.EndsWith("`n") -or $text.EndsWith("`r")
	if ($endsWithNewline -and ($result.Lines.Count -eq 0 -or $result.Lines[$result.Lines.Count - 1] -ne '')) {
		$newText += $lineEnding
	}

	if ($PSCmdlet.ShouldProcess($fileInfo.FullName, 'Update ENABLE_MOCKS toggles')) {
		try {
			[System.IO.File]::WriteAllText($fileInfo.FullName, $newText, $utf8NoBom)
			$updated.Add($fileInfo.FullName) | Out-Null
			Write-Host "Updated $($fileInfo.FullName)"
		}
		catch {
			Write-Warning "Failed to write '$($fileInfo.FullName)': $($_.Exception.Message)"
		}
	}
	else {
		Write-Host "Would update $($fileInfo.FullName)" -ForegroundColor Yellow
	}
}

if ($updated.Count -eq 0) {
	Write-Host 'No files required changes.' -ForegroundColor Yellow
}
else {
	Write-Host "Updated $($updated.Count) file(s)." -ForegroundColor Green
}