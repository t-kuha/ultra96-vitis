# set PRJ_NAME=hello_world

# .elf
setws _application
app create -name hello_world -hw ultra96.xsa -os standalone -proc psu_cortexa53_0 -template {Hello World}
app config -name hello_world -set build-config release
app build -name hello_world

platform generate
