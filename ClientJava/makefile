all: Clientjava

sliceJava: interface.ice
	slice2java --output-dir . interface.ice

Clientjava: Client.java biblAudio/*.java
	javac -classpath ice-3.6.1.jar Client.java biblAudio/*.java

run: Client.class 
	java -classpath ice-3.6.1.jar Client
