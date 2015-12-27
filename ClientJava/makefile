all: Clientjava

sliceJava: interface.ice
	slice2java --output-dir . interface.ice

Clientjava: Client.java doss/*.java
	javac -d biblAudio -classpath /usr/share/java/zeroc-ice/ice-3.6.1.jar Client.java biblAudio/*.java

run: clientIce.java
	java -classpath .:Ice.jar clientIce
