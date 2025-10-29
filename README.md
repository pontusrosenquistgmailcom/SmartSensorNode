# Smart Sensor Node
Project for Nordic Tech AB

Kurs 2: uppgift 306

KRAV
Produkt SKA:
Mäta Temperatur (+ tid + id)
Lagra mätvärden lokalt
Skicka data till en molnserver 
Teknik: TCP/HTTP.

Använda funktionspekare (callback)
Använda pekare till pekare

Dokumentation
Easy build med Makefile

Använda GIT (commit often)

den 29 oktober 2025
13:24

Measurement module (dummy)
    Time module  ???

Storage module (cJson write to file OR store in heap list)

HTTP builder (POST)
    Get body text from storage
    Construct HTTP POST message string
    Pass HTTP message to TCPClientSocket
HTTP Parser
    Obtain body text

TCP Client connect to server socket
    Local socket
    Connetc to server
    Send to server 
        While loop to send all data
    Recv from server
        Listen repeatedly to make sure we ge everything
    Close connection
    

Cirka tid: 2 veckor

User input NEW DATA -- store data in local storage
User input CREATE REPORT -- HTTP Builder creates HTTP REQUEST
User input SEND TO SERVER -- TCPClient opens socket to server and writes HTTP REQUEST to socket



SCRUM
PO: Nordic Systems AB
Scrum Master: Pontus R
Developer: Pontus R


Stories:

As user i want to enter new data
As user i want to view stored data
As user i want to connect to server using TCP
As user i want to build a report that can be sent over HTTP
As user i want to send data(report as HTTP request) to server
As user i want to view the server's response to my report

As user i want to view the server response

Sprint plan 2 weeks
    Week 1
        Start by creating a Storage module, where we house some placeholder data
        Next build TCP socket that can read and write data (sending the data in storage)
    Week 2
        Next build HTTP Parser/builder that can assemble a HTTP request
        Next make a simple user input UI to gather new data or opt to build report/send report, view report
    

Input Data

Send Data


Language C (for efficency), sockets using POSIX
We will provide Makefile and instructins on how to build project
We will use GIT to help handle versions