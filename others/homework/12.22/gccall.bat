
set str=".exe"
for /R %%s in (.,*) do ( 
gcc %%s -o %%s%str% -g
) 
pause;