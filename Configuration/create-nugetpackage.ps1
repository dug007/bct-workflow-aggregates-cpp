param (
    [Parameter(Mandatory=$true)][string]$SolutionDir,
    [Parameter(Mandatory=$true)][string]$TargetDir,
    [Parameter(Mandatory=$true)][string]$NugetSpec,
    [Parameter(Mandatory=$false)][string]$NugetSpec2,
    [Parameter(Mandatory=$false)][string]$NugetSpec3,
    [Parameter(Mandatory=$false)][string]$NugetSpec4
 )

# Environment variables:
# NUGET_BUILD - null if local computer, set to the Jenkins build number if on build computer
# 
function ComputeBuildNumber
{
    [System.DateTime]$nowx = [System.DateTime]::Now
    [System.DateTime]$then = [System.DateTime]::Parse("2018-1-1")
    [System.TimeSpan]$diff = $nowx - $then
    $sec = [System.Math]::Floor($diff.TotalSeconds)
    $build = $sec.ToString("000000000")
    
    return $build
}

    Write-Host "create-nuspec.ps1 inputs:"
    Write-Host $SolutionDir $TargetDir $NugetSpec $NugetSpec2 $NugetSpec3 $NugetSpec4
    #TESTING C:\src-git\2017SandboxGit\Common\DevComm\Trunk\ C:\src-git\2017SandboxGit\Common\DevComm\Trunk\Output\Debug\netcoreapp2.1\ BCT.Common.DevComm Bct.DeviceCommon.ClientTerminal

    if ($null -eq $env:BUILD_BUILDNUMBER)
    {
       $NugetVersionFilename = "SOLUTION_NUSPEC_VERSION.TXT"

       $ConfigDir = $SolutionDir + "Configuration\"
       $NugetPackageOutputDir = "$TargetDir\"

       $StreamBld = [IO.File]::OpenText("${ConfigDir}${NugetVersionFilename}")
       $NugetVersion = $StreamBld.ReadLine().Trim()
       $StreamBld.Close()

       $ComputedBuildNumber = ComputeBuildNumber
       $NugetVersion += "-XDV-" + $ComputedBuildNumber

       Set-Location $TargetDir

       $cmd = $ConfigDir + 'nuget-4.8.1.exe'

       $cmdargs = @("pack", ("$SolutionDir$NugetSpec"+".nuspec"), "-Version", $NugetVersion, "-OutputDirectory", $NugetPackageOutputDir, "-BasePath", ".") 
       Write-Host "Packaging NuGet:"
       Write-Host $cmd $cmdargs
       & $cmd $cmdargs

       $cmdargs = @("delete", ("$NugetSpec"), ("$NugetVersion"), "-noninteractive", "-source", ($env:USERPROFILE+"\.nuget\localsource\"))
       & $cmd $cmdargs
       $cmdargs = @("add", ("$NugetPackageOutputDir$NugetSpec.$NugetVersion"+".nupkg"), "-source", ($env:USERPROFILE+"\.nuget\localsource\"))
       & $cmd $cmdargs

       $cmdargs = @("delete", ("$NugetSpec"), ("$NugetVersion"),  "-noninteractive", "-source", ($env:USERPROFILE+"\.nuget\packages\"))
       & $cmd $cmdargs
       $cmdargs = @("add", ("$NugetPackageOutputDir$NugetSpec.$NugetVersion"+".nupkg"), "-expand", "-source", ($env:USERPROFILE+"\.nuget\packages\"))
       & $cmd $cmdargs
    }

