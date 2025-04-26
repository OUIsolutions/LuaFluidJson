

-- Create a new container machine
local machine = darwin.ship.create_machine("debian:latest")
-- Configure container runtime
machine.provider = "sudo docker"
-- Add build-time commands
machine.add_comptime_command("apt update")
machine.add_comptime_command("apt install -y gcc ")

machine.start({
    flags = {
        "--network=host","-it"
    },
    volumes = {
        { ".", "/teste" }
    },
})
