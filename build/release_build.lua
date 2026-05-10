darwin.add_recipe({
  name = "release",
  description = "Builds the LuaFluidJson module inside a Docker Debian container",
  outs = { "release/luaFluidJson" },
  inputs = { "src/" },
  callback = function()
    prepare()

    local machine = darwin.ship.create_machine("debian:latest")
    machine.provider = "sudo docker"
    machine.add_comptime_command("apt update")
    machine.add_comptime_command("apt install -y gcc")

    machine.start({
      flags = { "--network=host" },
      volumes = { { ".", "/output" } },
      command = "gcc -shared -fpic /output/src/one.c -o /output/release/luaFluidJson/luaFluidJson.so"
    })

    os.execute("cd release && zip -r luaFluidJson.zip luaFluidJson")
  end
})
