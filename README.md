# Introduction
This is an application for abstract library database written on C++/Qt 
![plot](./screen1.png)
pic.1 *Admin GUI*
# Installation
Load library_db_backup.sql to your PSQL
Change PSQL username, name of your database, password in the constructon of mainwindow.cpp
Run qmake && make 
## Requirements
PSQL version 16.x (or late)
QMake version 3.1 (or late) using Qt version 6.x.x and his basic libs
# Use
## As a customer
Create new account, then login and choose any avaliable books you wish
## As an admin
Login with Admin111 username and same password into account
Handle customers requests
Change the almost all contents of database via GUI
