# The following installs the ArcGIS SDK with a per user configuration to "C:\ArcGIS SDK"
# msiexec.exe /i setup.msi ALLUSERS=2 MSIINSTALLPERUSER=1 ACCEPTEULA=YES INSTALLDIR=`"C:\ArcGIS SDK`" /qn | Wait-Process

$installerPath = 'C:\CodeProjects\ArcGIS Runtime SDK Qt 100.15.2\ArcGISRuntimeSDKQt\SetupFiles\setup.msi'
$installDir = 'C:\ArcGIS SDK'

Write-Host "Installing ArcGIS SDK to $installDir. You may need to accept UAC prompts."

# If the above does not work, maybe try the following lines. This will display a UI and UAC prompt since it is doing an admin install
msiexec.exe /i $installerPath ALLUSERS=1 ACCEPTEULA=YES INSTALLDIR=`"$installDir`" /qb | Wait-Process

Write-Host "Patching installed ArcGISRuntime file"

$arcGISRuntimeCMakeFile = "$installDir\Qt100.15.2\sdk\ideintegration\ArcGISRuntime.cmake"
$badString = ' \${CMAKE_OSX_ARCHITECTURES} '
$goodString = ' "${CMAKE_OSX_ARCHITECTURES}" '
((Get-Content -path $arcGISRuntimeCMakeFile) -replace $badString,$goodString) | Set-Content -Path $arcGISRuntimeCMakeFile

Write-Host "Removing ArcGIS SDK. You may need to accept UAC prompts."

# the following will uninstall the SDK
#msiexec.exe /uninstall $installerPath  /qb | Wait-Process
