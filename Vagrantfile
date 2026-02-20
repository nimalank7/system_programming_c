Vagrant.configure("2") do |config|
  arch=`uname -m`.strip

  if arch == "arm64"
    puts "Detected Apple Silicon (ARM)"
    config.vm.box = "bento/ubuntu-24.04"
    config.vm.box_version = "202510.26.0"
  else
    puts "Detected Intel/AMD (x86_64)"
    config.vm.box = "ubuntu/jammy64"
  end

  # Sync current host directory to /vagrant in the VM
  config.vm.synced_folder ".", "/home/vagrant/shared"

  # Provision the VMs Linux build tools:
  config.vm.provision "shell", inline: <<-SHELL
    apt-get update -y && apt-get install -y build-essential ltrace valgrind clang
  SHELL
end