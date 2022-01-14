$error_ = 0
$this_path = Split-Path -Path $MyInvocation.MyCommand.Definition -Parent
$base = ".."
$released = "$($base)\release"
Set-Location "$($this_path)"
$root = "$($base)\source"
$error_++
Test-Path "$($root)" -PathType Container || Exit $error_
if (-not (Test-Path "$($released)" -PathType Container))
{
  $error_++
  New-Item -Type Directory -Name "$($released)"  || Exit $error_
}
Set-Location "$($root)"
$error_++
MSBuild /property:Configuration=Release /property:Platform=x86 -t:Clean || Exit $error_
$error_++
MSBuild /property:Configuration=Release /property:Platform=x86 -t:Build || Exit $error_
$error_++
Test-Path ".\Release\ctdt.exe" -PathType Leaf || Exit $error_
$error_++
Move-Item -Path ".\Release\ctdt.exe" -Destination "$($released)\ctdt-x86.exe" -Force || Exit $error_
$error_++
MSBuild /property:Configuration=Release /property:Platform=x86 -t:Build || Exit $error_
$error_++
MSBuild /property:Configuration=Release /property:Platform=x64 -t:Clean || Exit $error_
$error_++
Remove-Item -Force -Recurse -Path "$($root)\Release\"  -ErrorAction Stop || Exit $error_
$error_++
Remove-Item -Force -Recurse -Path "$($root)\ctdt\Release\"  -ErrorAction Stop || Exit $error_
$error_++
MSBuild /property:Configuration=Release /property:Platform=x64 -t:Build || Exit $error_
$error_++
Move-Item -Path ".\x64\Release\ctdt.exe" -Destination "$($released)\ctdt-x64.exe" -Force || Exit $error_
$error_++
MSBuild /property:Configuration=Release /property:Platform=x64 -t:Clean || Exit $error_
$error_++
Remove-Item -Force -Recurse -Path "$($root)\x64\"  -ErrorAction Stop || Exit $error_
$error_++
Remove-Item -Force -Recurse -Path "$($root)\ctdt\x64\"  -ErrorAction Stop || Exit $error_
