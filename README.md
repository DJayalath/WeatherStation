# WeatherStation
A client-server based weather station using a server with sensors and a client with a display.

Uses an arduino nano (client) and uno (server).
For a very minimal development log see [here](http://dulhanjayalath.com/weather-station)

### Stage 1: Planning

As with all things, it's important to plan in order to be efficient. My idea for this project was to create a server-client system where the weather station would be a server kept outside (since all the sensors would be on the server) and the client would be a display device kept inside. The server would send all its data to the client through a wireless transceiver to be displayed. The following is my estimate for the cost of the project:

    Weather Station (Server)
    Arduino Uno (clone) ~ £5
    Breadboard and acrylic base ~ £2
    Male-to-Male dupont jumper wires ~ £3
    Bosche BMP180 temperature & pressure sensor ~ £4
    Rain sensor ~ £4
    DHT11 temperature & humidity sensor ~ £3
    NRF24L01+ Wireless RF Transceiver ~ £1

    Display Device (Client)
    Arduino Nano (clone) ~ £5
    1602 Serial Backlight LCD Display I2C ~ £4
    NRF24L01+ Wireless RF Transceiver ~ £1
    Push Button ~ £2

Total Cost ~ £34

Of course this could all be purchased for less than half the price from international retailers (e.g. Aliexpress) but I'm impatient when it comes to delivery times.

### Stage 2: Prototyping

Once all the parts arrived I built a prototype on a breadboard to work out how I would wire the final thing. For the time being, I connected the LCD display to the server to directly display sensor readings. I would then move on to attempting to connect the client and server together and using this connection to display data. However, before I could even begin to think about wiring everything up, I had to write the program to control everything. I ended up using the Adafruit sensor and LCD libraries to get sensor inputs and display them. After a worrying amount of debugging, I finally had some results to show for my time:



Next, I separated the client and server. This time I tested the client with the LCD and wireless receiver and checked if it successfully received the sensor data I wanted (temperature, humidity, pressure, and rain/dry status) from the server's transmitter.

### Stage 3: Building, Finalising and Testing

To make the prototype more permanent, I purchased a waterproof PVC electrical enclosure for the weather station. Since the rain sensor must be mounted outside the box, I drilled a few holes for the rain sensor and its wires. I also had to create a hole for the USB serial input as well as a few holes at the bottom of the enclosure to allow heat and air to continuously flow between the external environment and the sensors inside. It's important to keep the difference as small as possible because the point of having a server is to measure the conditions outside and view them with the client indoors.


Next, it was time to make an enclosure for the client. This is the part that would be visible so it's a little more important to get the design right. I had a go at modelling a potential enclosure using FreeCAD:


This model was too wide for my printer... I had to remodel the enclosure to fit the build area of my MP Select Mini V2 and this involved a much less appealing design but at the very least it was printable.


I first printed the lid to see if it would fit the LCD display because the schematic I used to model the area was from a different manufacturer of the same model. Lucky for me it fit rather snugly.


Knowing it will all work, I printed the box (a whopping 10 hour long print for just 99g of PLA) and placed all the electronics in and used self-tapping screws to finish.


The button used is a momentary switch that triggers the display backlight to toggle state. I really don't want bright blue light all over my room when trying to sleep. All in all, I think the project went very well especially considering this was a project of many firsts for me, including:

    Using a microcontroller
    3D modelling using CAD software
    3D Printing

To improve, it would probably be worth making connections permanent in future projects by purchasing some stripboard and soldering connections. At the moment, I'm certain dropping the enclosure would cause some connection or other to come loose and break it. 
