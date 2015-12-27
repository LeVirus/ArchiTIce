all: Clientjava

sliceJava: interface.ice
	slice2java --output-dir . interface.ice

Clientjava: Client.java biblAudio/*.java
	javac -classpath /usr/share/java/zeroc-ice/ice-3.6.1.jar Client.java biblAudio/*.java

run: Client.java
	java -classpath /usr/share/java/zeroc-ice/ice-3.6.1.jar Client
