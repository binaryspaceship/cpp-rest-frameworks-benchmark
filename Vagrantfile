# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  config.vm.box = "IngussNeilands/ubuntu-16.04.2-php-7.1-nginx"
  config.vm.synced_folder "samples", "/vagrant"

  config.vm.provision "disable-apt-periodic-updates", type: "shell" do |s|
    s.privileged = true
    s.inline = "echo 'APT::Periodic::Enable \"0\";' > /etc/apt/apt.conf.d/02periodic"
  end
  config.vm.provision :shell, :path => "bootstrap.sh"
end
