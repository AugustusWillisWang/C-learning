@echo off
echo fgdeFGDE01> compx
echo abyzABYZ01| %1 > tempa
fc tempa compx
del tempa
del compx