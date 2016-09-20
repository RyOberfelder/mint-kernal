# mint-kernal

The whole point of this work is a place for me to record the work that I do so that in the case of development everything explodes I have a place to put things.

### Installing Mint

So some of this I had built on old installed programs so it won't be perfect but here it goes.

#### Install Virtualbox

You are going to want some sort of virtualization software. It really does not matter what it is. I use and would recomend Virtual box but only because thats my experience. You will be going in and changing things that could break your computer so you want virtualization so it might only break the virtualization.

#### Download Mint

I went to http://www.osboxes.org/linux-mint/ and got the virtualbox 64bit image

#### Create Box using ming image

When you download it, at least I got a VDI. This actually is going to be pulled in when you are asking for a hard drive in the virutalbox. Make sure to add the vdi at that point. Go through the last little bit of the process then you are good to go.

### Pre Git Set-up

#### login

if you were to go through the osboxes virutal box, your machine will have the default username and password those will be as follows:

Username : osboxes
Password : osboxes.org

#### installing git

note that superuser ability is granted by calling: 

sudo su

once root, call:

apt-get install git

apt-get is your package manager and this will be the process for installing alot of your core functionality.

Lastly set your email in git using:

git config --local user.email "yourEmailHere"
git config --local user.name "your name here"

### Post Git Setup

With any luck this should be very simple. clone down the git repo. Then navigate to the project and type:

make project

This will run a makefile that should make anything that you need.

#### make setup

in the git dir, run:

make setup

will install any packages and anything else needed to run the kernals

### Tutorial information

building and adding modules
http://tldp.org/LDP/lkmpg/2.6/html/lkmpg.html

