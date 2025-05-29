# Melissa - Global Address Object Windows C++

## Purpose
This code showcases the Melissa Global Address Object using C++.

Please feel free to copy or embed this code to your own project. Happy coding!

For the latest Melissa Global Address Object release notes, please visit: https://releasenotes.melissa.com/on-premise-api/global-address-object/

For further details, please visit: https://docs.melissa.com/on-premise-api/global-address-object/global-address-object-quickstart.html

The console will ask the user for:

- Address Line 1
- Address Line 2
- Address Line 3
- Locality
- Administrative Area
- Postal Code
- Country

And return 

- Melissa Address Key (MAK)
- Company
- Address Line 1
- Address Line 2
- Address Line 3
- Address Line 4
- Address Line 5
- Locality
- Administrative Area
- Postal Code
- Postbox
- Country
- Country ISO 2
- Country ISO 3
- Latitude 
- Longitude
- Formatted Address
- Result Codes

## Tested Environments
- Windows 10 64-bit Microsoft Visual C++ 14.34, Powershell 5.1
- Melissa data files for 2025-Q2
- Nmake 14.34
- Visual Studio 2022 Developer Command Prompt v17.4.2 64-bit

## Required File(s) and Programs

#### Binaries
This is the c++ code of the Melissa Object.

- mdAddr.dll
- mdGeo.dll
- mdGlobalAddr.dll
- mdRightFielder.dll

#### Data File(s)
- Addr.dbf
- Congress.csv
- dph256.dte
- dph256.hsa
- dph256.hsc
- dph256.hsd
- dph256.hsf
- dph256.hsn
- dph256.hsp
- dph256.hsr
- dph256.hst
- dph256.hsu
- dph256.hsv
- dph256.hsx
- dph256.hsy
- dph256.hsz
- ews.txt
- icudt52l.dat
- lcd256
- mdAddr.dat
- mdAddr.lic
- mdAddr.nat
- mdAddr.str
- mdAddrKey.db
- mdAddrKeyCA.db
- mdCanada3.db
- mdCanadaPOC.db
- mdGeoCode.db3
- mdGlobalAddr.ffbb
- mdGlobalAddr.ffhb
- mdGlobalAddr.ffpl
- mdGlobalAddr.ffps
- mdGlobalAddr.ffst
- mdGlobalAddr.sac
- mdLACS256.dat
- mdRBDI.dat
- mdRightFielder.cfg
- mdRightFielder.dat
- mdSteLink256.dat
- mdSuiteFinder.db
- month256.dat

#### Dependencies
- mdEnums.h
- mdGlobalAddr.h
- mdGlobalAddr.lib

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

#### Visual Studio Developer Command Prompt
It is important to note that you must be able to initialize the Visual Studio Developer Command Prompt environment for `x86_x64` in order to test the Melissa Global Address Object. The Visual Studio Developer Command Prompt should already be downloaded if you have Microsoft Visual Studio installed. 

To check if you are able to intialize the Visual Studio Developer Command Prompt for `x86_x64`, you can open the start menu and search for `x86_x64 Cross Tools Command Prompt for VS 2022`. If this program exists, then you may continue to the next steps.

Alternatively, you can check to see if the following filepath exists: `C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat` (with Visual Studio 2022 installed). If the filepath exists, then you may continue to the next steps.

#### Set up Powershell settings
If running Powershell for the first time, you will need to run this command in the Powershell console: `Set-ExecutionPolicy RemoteSigned`.
The console will then prompt you with the following warning shown in the image below. 
 - Enter `'A'`. 
 	- If successful, the console will not output any messages. (You may need to run Powershell as administrator to enforce this setting).
	
 ![alt text](/screenshots/powershell_executionpolicy.png)

#### Download this project
```
git clone https://github.com/MelissaData/GlobalAddressObject-Cpp
cd GlobalAddressObject-Cpp
```

#### Set up Melissa Updater
Melissa Updater is a CLI application allowing the user to update their Melissa applications/data.
- Download Melissa Updater here: <https://releases.melissadata.net/Download/Library/WINDOWS/NET/ANY/latest/MelissaUpdater.exe>
- Create a folder within the cloned repo called `MelissaUpdater`.
- Put `MelissaUpdater.exe` in the `MelissaUpdater` folder you've just created.

#### Different ways to get data file(s)
1. Using Melissa Updater
    - It will handle all of the data download/path and dll(s) for you.
    - **Please be aware that this object will require about 100GB of disk space.**
2. If you already have the latest release zip, you can find the data file(s) in there
    - To pass in your own data file path directory, you may either use the '-dataPath' parameter or enter the data file path directly in interactive mode.
    - Comment out this line "DownloadDataFiles -license $License" in the powershell script.
    - This will prevent you from having to redownload all the files.

## Run Powershell Script
Parameters:
- -addressLine1: a test address line 1
- -addressLine2 (optional): a test address line 2
- -addressLine3 (optional): a test address line 3
- -locality: a test locality
- -administrativeArea: a test administrative area
- -postalCode: a test postal code
- -country: a test country
 	
  These are convenient when you want to get results for a specific address in one run instead of testing multiple addresses in interactive mode.

- -dataPath (optional): a data file path directory to test the Global Address Object
- -license (optional): a license string to test the Global Address Object
- -quiet (optional): add to the command if you do not want to get any console output from the Melissa Updater

When you have modified the script to match your data location, let's run the script. There are two modes:
- Interactive 

    The script will prompt the user for an address line 1, address line 2, address line 3, locality, administrative area, postal code, and country, then use the provided inputs to test Global Address Object. For example:
    ```
    .\MelissaGlobalAddressObjectWindowsCpp.ps1
    ```
    For quiet mode:
    ```
    .\MelissaGlobalAddressObjectWindowsCpp.ps1 -quiet
    ```
- Command Line 

    You can pass an address line 1, address line 2, address line 3, locality, administrative area, postal code, country, and a license string into the ```-addressLine1```, ```-addressLine2```, ```-addressLine3```, ```-locality```, ```-administrativeArea```, ```-postalCode```, ```-country```, and ```-license``` parameters respectively to test Global Address Object. For example:
    ```
    .\MelissaGlobalAddressObjectWindowsCpp.ps1 -addressLine1 "US Embassy" -addressLine2 "Via Vittorio Veneto 121" -addressLine3 "00187 Roma RM" -country "Italy" 
    .\MelissaGlobalAddressObjectWindowsCpp.ps1 -addressLine1 "US Embassy" -addressLine2 "Via Vittorio Veneto 121" -addressLine3 "00187 Roma RM" -country "Italy" -license "<your_license_string>"
    ```

    For quiet mode:
    ```
    .\MelissaGlobalAddressObjectWindowsCpp.ps1 -addressLine1 "US Embassy" -addressLine2 "Via Vittorio Veneto 121" -addressLine3 "00187 Roma RM" -country "Italy"  -quiet
    .\MelissaGlobalAddressObjectWindowsCpp.ps1 -addressLine1 "US Embassy" -addressLine2 "Via Vittorio Veneto 121" -addressLine3 "00187 Roma RM" -country "Italy"  -license "<your_license_string>" -quiet
    ```
This is the expected output from a successful setup for interactive mode:

![alt text](/screenshots/output.png)

## Troubleshooting
Troubleshooting for errors found while running your program.

### C# Errors:
| Error      | Description |
| ----------- | ----------- |
| ErrorRequiredFileNotFound      | Program is missing a required file. Please check your Data folder and refer to the list of required files above. If you are unable to obtain all required files through the Melissa Updater, please contact technical support below. |
| ErrorLicenseExpired   | Expired license string. Please contact technical support below. |

## Contact Us
For free technical support, please call us at 800-MELISSA ext. 4 (800-635-4772 ext. 4) or email us at tech@melissa.com.

To purchase this product, contact the Melissa sales department at 800-MELISSA ext. 3 (800-635-4772 ext. 3).
