for %%f in (*.vert) do (
    glslangValidator -V "%%f" -o "../Compiled/%%f.spv"
)

for %%f in (*.frag) do (
    glslangValidator -V "%%f" -o "../Compiled/%%f.spv"
)

for %%f in (*.comp) do (
    glslangValidator -V "%%f" -o "../Compiled/%%f.spv"
)