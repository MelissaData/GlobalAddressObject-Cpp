# Name:    MelissaGlobalAddressObjectWindowsCpp
# Purpose: Use the MelissaUpdater to make the MelissaGlobalAddressObjectWindowsCpp code usable

######################### Parameters ##########################

param(
    $addressLine1 = '""',
    $addressLine2 = '""',
    $addressLine3 = '""',
    $locality = '""',
    $administrativeArea= '""',
    $postalCode = '""',
    $country = '""',
    $dataPath = '',
    $license = '',
    [switch]$quiet = $false
    )

######################### Classes ##########################

class DLLConfig {
  [string] $FileName;
  [string] $ReleaseVersion;
  [string] $OS;
  [string] $Compiler;
  [string] $Architecture;
  [string] $Type;
}

######################### Config ###########################

$RELEASE_VERSION = '2025.Q3'
$ProductName = "GLOBAL_DQ_DATA"

# Uses the location of the .ps1 file 
$CurrentPath = $PSScriptRoot
Set-Location $CurrentPath
$ProjectPath = "$CurrentPath\MelissaGlobalAddressObjectWindowsCpp"

# Configure the path to vcvarsall.bat if needed
$CmdPath = "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat"

$BuildPath = "$ProjectPath\Build"
if (!(Test-Path $BuildPath)) {
  New-Item -Path $ProjectPath -Name 'Build' -ItemType "directory"
}

if ([string]::IsNullOrEmpty($dataPath)) {
  $DataPath = "$ProjectPath\Data" 
}

if (!(Test-Path $DataPath) -and ($DataPath -eq "$ProjectPath\Data")) {
  New-Item -Path $ProjectPath -Name 'Data' -ItemType "directory"
}
elseif (!(Test-Path $DataPath) -and ($DataPath -ne "$ProjectPath\Data")) {
  Write-Host "`nData file path does not exist. Please check that your file path is correct."
  Write-Host "`nAborting program, see above.  Press any button to exit.`n"
  $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown") > $null
  exit
}

$DLLs = @(
  [DLLConfig]@{
    FileName       = "mdAddr.dll";
    ReleaseVersion = $RELEASE_VERSION;
    OS             = "WINDOWS";
    Compiler       = "DLL";
    Architecture   = "64BIT";
    Type           = "BINARY";
  },
  [DLLConfig]@{
    FileName       = "mdGeo.dll";
    ReleaseVersion = $RELEASE_VERSION;
    OS             = "WINDOWS";
    Compiler       = "DLL";
    Architecture   = "64BIT";
    Type           = "BINARY";
  },
  [DLLConfig]@{
    FileName       = "mdGlobalAddr.dll";
    ReleaseVersion = $RELEASE_VERSION;
    OS             = "WINDOWS";
    Compiler       = "DLL";
    Architecture   = "64BIT";
    Type           = "BINARY";
  },
  [DLLConfig]@{
    FileName       = "mdRightFielder.dll";
    ReleaseVersion = $RELEASE_VERSION;
    OS             = "WINDOWS";
    Compiler       = "DLL";
    Architecture   = "64BIT";
    Type           = "BINARY";
  },
  [DLLConfig]@{
    FileName       = "mdEnums.h";
    ReleaseVersion = $RELEASE_VERSION;
    OS             = "ANY";
    Compiler       = "C";
    Architecture   = "ANY";
    Type           = "INTERFACE";  
  },
  [DLLConfig]@{
    FileName       = "mdGlobalAddr.h";
    ReleaseVersion = $RELEASE_VERSION;
    OS             = "ANY";
    Compiler       = "C";
    Architecture   = "ANY";
    Type           = "INTERFACE";  
  },
  [DLLConfig]@{
    FileName       = "mdGlobalAddr.lib";
    ReleaseVersion = $RELEASE_VERSION;
    OS             = "WINDOWS";
    Compiler       = "C";
    Architecture   = "64BIT";
    Type           = "INTERFACE";
  }
)

######################## Functions #########################

function DownloadDataFiles([string] $license) {
  Write-Host "`n=============================== MELISSA UPDATER ============================="
  Write-Host "MELISSA UPDATER IS DOWNLOADING DATA FILE(S)..."

  .\MelissaUpdater\MelissaUpdater.exe manifest -p $ProductName -r $RELEASE_VERSION -l $license -t $DataPath 
  if($? -eq $False ) {
    Write-Host "`nCannot run Melissa Updater. Please check your license string!"
    Exit
  }     

  Write-Host "Melissa Updater finished downloading data file(s)!"
}

function DownloadDLLs() {
  Write-Host "MELISSA UPDATER IS DOWNLOADING DLL(S)..."
  $DLLProg = 0
  foreach ($DLL in $DLLs) {
    Write-Progress -Activity "Downloading DLL(S)" -Status "$([math]::round($DLLProg / $DLLs.Count * 100, 2))% Complete:"  -PercentComplete ($DLLProg / $DLLs.Count * 100)

    # Check for quiet mode
    if ($quiet) {
      if ($DLL.FileName -eq "mdAddr.dll" -or $DLL.FileName -eq "mdGeo.dll" -or $DLL.FileName -eq "mdGlobalAddr.dll" -or $DLL.FileName -eq "mdRightFielder.dll")
      {
        .\MelissaUpdater\MelissaUpdater.exe file --filename $DLL.FileName --release_version $DLL.ReleaseVersion --license $LICENSE --os $DLL.OS --compiler $DLL.Compiler --architecture $DLL.Architecture --type $DLL.Type --target_directory $BuildPath > $null
      }
      else
      {
        .\MelissaUpdater\MelissaUpdater.exe file --filename $DLL.FileName --release_version $DLL.ReleaseVersion --license $LICENSE --os $DLL.OS --compiler $DLL.Compiler --architecture $DLL.Architecture --type $DLL.Type --target_directory $ProjectPath > $null
      }
      
      if(($?) -eq $False) {
          Write-Host "`nCannot run Melissa Updater. Please check your license string!"
          Exit
      }
    }
    else {
      if ($DLL.FileName -eq "mdAddr.dll" -or $DLL.FileName -eq "mdGeo.dll" -or $DLL.FileName -eq "mdGlobalAddr.dll" -or $DLL.FileName -eq "mdRightFielder.dll")
      {
        .\MelissaUpdater\MelissaUpdater.exe file --filename $DLL.FileName --release_version $DLL.ReleaseVersion --license $LICENSE --os $DLL.OS --compiler $DLL.Compiler --architecture $DLL.Architecture --type $DLL.Type --target_directory $BuildPath 
      }
      else
      {
        .\MelissaUpdater\MelissaUpdater.exe file --filename $DLL.FileName --release_version $DLL.ReleaseVersion --license $LICENSE --os $DLL.OS --compiler $DLL.Compiler --architecture $DLL.Architecture --type $DLL.Type --target_directory $ProjectPath
      }
      
      if(($?) -eq $False) {
          Write-Host "`nCannot run Melissa Updater. Please check your license string!"
          Exit
      }
    }
    
    Write-Host "Melissa Updater finished downloading " $DLL.FileName "!"
    $DLLProg++
  }
}

function CheckDLLs() {
  Write-Host "`nDouble checking dll(s) were downloaded...`n"
  $FileMissing = $false 
  if (!(Test-Path ("$BuildPath\mdAddr.dll"))) {
    Write-Host "mdAddr.dll not found." 
    $FileMissing = $true
  }
  if (!(Test-Path ("$BuildPath\mdGeo.dll"))) {
    Write-Host "mdGeo.dll not found." 
    $FileMissing = $true
  }
  if (!(Test-Path ("$BuildPath\mdGlobalAddr.dll"))) {
    Write-Host "mdGlobalAddr.dll not found." 
    $FileMissing = $true
  }
  if (!(Test-Path ("$BuildPath\mdRightFielder.dll"))) {
    Write-Host "mdRightFielder.dll not found." 
    $FileMissing = $true
  }
  if ($FileMissing) {
    Write-Host "`nMissing the above data file(s).  Please check that your license string and directory are correct."
    return $false
  }
  else {
    return $true
  }
}

########################## Main ############################

Write-Host "`n======================== Melissa Global Address Object ======================`n                           [ C++ | Windows | 64BIT ]`n"

# Get license (either from parameters or user input)
if ([string]::IsNullOrEmpty($license) ) {
  $License = Read-Host "Please enter your license string"
}

# Check for License from Environment Variables 
if ([string]::IsNullOrEmpty($License) ) {
  $License = $env:MD_LICENSE 
}

if ([string]::IsNullOrEmpty($License)) {
  Write-Host "`nLicense String is invalid!"
  Exit
}

# Get data file path (either from parameters or user input)
if ($DataPath -eq "$ProjectPath\Data") {
  $dataPathInput = Read-Host "Please enter your data files path directory if you have already downloaded the release zip.`nOtherwise, the data files will be downloaded using the Melissa Updater (Enter to skip)"

  if (![string]::IsNullOrEmpty($dataPathInput)) {
    if (!(Test-Path $dataPathInput)) {
      Write-Host "`nData file path does not exist. Please check that your file path is correct."
      Write-Host "`nAborting program, see above.  Press any button to exit.`n"
      $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown") > $null
      exit
    }
    else {
      $DataPath = $dataPathInput
    }
  }
}

# Use Melissa Updater to download data file(s) 
# Download data file(s) 
DownloadDataFiles -license $License # Comment out this line if using own release

# Download dll(s)
DownloadDlls - license $License

# Check if all dll(s) have been downloaded. Exit script if missing
$DllsAreDownloaded = CheckDLLs

if (!$DLLsAreDownloaded) {
	Write-Host "`nAborting program, see above.  Press any button to exit."
  $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
  exit
}

Write-Host "All file(s) have been downloaded/updated!"

# Start program
# Build project
Write-Host "`n================================ BUILD PROJECT =============================="

cmd.exe /C """$CmdPath"" x86_x64 && Powershell -File BuildProgram.ps1" > $null

# Run Project
if ([string]::IsNullOrEmpty($addressLine1) -and [string]::IsNullOrEmpty($addressLine2) -and [string]::IsNullOrEmpty($addressLine3) -and [string]::IsNullOrEmpty($locality) -and [string]::IsNullOrEmpty($administrativeArea) -and [string]::IsNullOrEmpty($postalCode) -and [string]::IsNullOrEmpty($country)){
  & $BuildPath\MelissaGlobalAddressObjectWindowsCpp.exe --license $License --dataPath $DataPath
}
else {
  & $BuildPath\MelissaGlobalAddressObjectWindowsCpp.exe --license $License --dataPath $DataPath --addressLine1 $addressLine1 --addressLine2 $addressLine2 --addressLine3 $addressLine3 --locality $locality --administrativeArea $administrativeArea --postalCode $postalCode --country $country
}
