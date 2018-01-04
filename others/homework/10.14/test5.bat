@echo off
echo abyzABYZ01> compx
echo fgdeFGDE01| %1 > tempa
fc tempa compx
del tempa
del compx