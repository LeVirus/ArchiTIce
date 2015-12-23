all: Clientjava

sliceJava: interface.ice
	slice2java --output-dir doss interface.ice

Clientjava: main.java doss/biblAudio/*.java
	javac -classpath .:Ice.jar main.java doss/biblAudio/*.java

run: clientIce.java
	java -classpath .:Ice.jar clientIce
