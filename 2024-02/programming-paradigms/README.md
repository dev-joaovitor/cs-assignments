# Programming Paradigms

This repository is meant to store my code assignments from the college programming paradigms classes.

## Projects

### [1. Taxes](#1-taxes-1)
### [2. Bar](#2-bar-1)
### [3. Athletes](#3-athletes-1)
### [4. Light Bulb](#4-light-bulb-1)
### [5. Tic Tac Toe](#5-tic-tac-toe-1)
---

### 1. Taxes

#### Summary

The purpose of this program is to generate a tax report based on a person monthly income.

#### What should it do?

##### Input/Output
- [x] Read annual salary income
- [x] Read provision of services income
- [x] Read capital gain
- [x] Read educational expenses
- [x] Read medical expenses
- [x] Display the report

##### Tax Report
- [x] Calculate monthly salary income
- [x] Calculate salary tax rate
- [x] Calculate salary tax
- [x] Calculate services provisioning tax
- [x] Calculate capital gain tax
- [x] Calculate gross taxes
- [x] Calculate maximum deductible amount
- [x] Calculate deductible expenses
- [x] Calculate deduction to be applied
- [x] Apply deduction on gross tax

#### How to run?
```sh
cd ./taxes/src
javac Taxes.java
java Taxes
```
#### Java Version
```
java version "1.8.0_401"
Java(TM) SE Runtime Environment (build 1.8.0_401-b10)
Java HotSpot(TM) 64-Bit Server VM (build 25.401-b10, mixed mode)
```
###### [Back to projects](#projects)
---

### 2. Bar

#### Summary
The purpose of this program is to generate a payment report based on customer's consumption at a bar.

#### What should it do?

##### Input/Output
- [x] Read the customer sex
- [x] Read the beers consumed by the customer
- [x] Read the sodas consumed by the customer
- [x] Read the skewers consumed by the customer
- [x] Display the report

##### Payment Report
- [x] If the customer's sex is "male", the ticket will cost R$10.00, if it's "female", it will ost R$8.00  
- [x] Calculate the total consumption adding the beers, sodas and skewers consumed by the customer
- [x] If the consumption is over R$30.00, the couvert is free, else, it's R$4.00
- [x] Sum the total fees

#### How to run?
```sh
cd ./bar/src
javac Bar.java
java Bar
```
#### Java Version
```
java version "1.8.0_401"
Java(TM) SE Runtime Environment (build 1.8.0_401-b10)
Java HotSpot(TM) 64-Bit Server VM (build 25.401-b10, mixed mode)
```
###### [Back to projects](#projects)
---

### 3. Athletes

#### Summary
The purpose of this program is to register athletes and their measurements and generate a general measurements report.

#### What should it do?

##### Input/Output
- [x] Read the amount of athletes that will be registered (should be a positive non-zero integer)
- [x] Read the name of each athlete
- [x] Read the sex of each athlete (should be M for male or F for female)
- [x] Read the height of each athlete (should be a positive non-zero number)
- [x] Read the weight of each athlete (should be a positive non-zero number)
- [x] Display the report

##### Measurements Report
- [x] Calculate the athletes average weight (Men and women)
- [x] Find the highest athlete (Men or women)
- [x] Calculate the percentage of registered men
- [x] Calculate the women average height (If there are no women, display a message)

#### How to run?
```sh
cd ./athletes/src
javac -cp . AthletesProgram.java
java AthletesProgram
```
#### Java Version
```
java version "1.8.0_401"
Java(TM) SE Runtime Environment (build 1.8.0_401-b10)
Java HotSpot(TM) 64-Bit Server VM (build 25.401-b10, mixed mode)
```
###### [Back to projects](#projects)
---

### 4. Light Bulb

#### Summary
The purpose of this program is to register a light bulb and be able to turn it on and off.

#### What should it do?

##### Input/Output
- [x] Read the make
- [x] Read the model
- [x] Read the type (incandescent, fluorescent, led or other)
- [x] Read the color (white, yellow or colorful)
- [x] Read the power in watts (should be a positive non-zero integer)
- [x] Read the price (should be a positive non-zero number)
- [x] Read the warranty time in months (should be a positive non-zero integer)

##### Switch Functionality
- [x] Ask for the user if they wanna toggle the switch or exit the program.

#### How to run?
```sh
cd ./lightbulb/src
javac -cp . LightBulbProgram.java
java LightBulbProgram
```
#### Java Version
```
openjdk 21.0.5 2024-10-15
OpenJDK Runtime Environment (build 21.0.5+11)
OpenJDK 64-Bit Server VM (build 21.0.5+11, mixed mode, sharing)
```
###### [Back to projects](#projects)
---

### 5. Tic tac toe

#### Summary
A simple tic-tac-toe game to practice working with matrices.

#### What should it do?

##### Input/Output
- [x] Menu to start or exit the game.
- [x] Show the current player.
- [x] Show the amount of plays.
- [x] Ask for the board line.
- [x] Ask for the board column.

##### Winning logic
- [x] 3 horizontal plays in sequence.
- [x] 3 vertical plays in sequence.
- [x] 3 diagonal plays in sequence.

#### How to run?
```sh
cd ./tictactoe/src
javac -cp . TicTacToe.java
java TicTacToe
```
#### Java Version
```
openjdk 21.0.5 2024-10-15
OpenJDK Runtime Environment (build 21.0.5+11)
OpenJDK 64-Bit Server VM (build 21.0.5+11, mixed mode, sharing)
```
###### [Back to projects](#projects)
