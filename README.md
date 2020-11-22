# tempgraph
Tempgraph is a flask/arduino project that utilizes 2 arduinos, a receiver and transmitter, and my computer.

One arduino that has a temperature sensor and transmitter on it, and the other arduino has a receiver and is plugged into a computer. The temperatures are logged then sent over the transmitter as encoded data and then the receiver will just do things and send the data to the serial port. A flask web server will then post that data to an sqlalchemy database and my other web server will retrieve that data to display it on a table on the internet.

created: June 15, 2020
