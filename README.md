# openmq-wp
Wiring Protocol Notes for Eclipse OpenMQ.

## build

```
mkdir .vs
chdir .vs
..\build-script\build.bat
msbuild openmq-wp.sln -p:Configuration=Release -p:platform=x64
```
# test

```
msbuild RUN_TESTS.vcxproj -p:Configuration=Release -p:platform=x64
```

