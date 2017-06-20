run:
	java -classpath out rmilernen.Main &
	sleep 5
	java -classpath out rmilernen.client.Client

build:
	find ./src -type f | grep .java | xargs javac -d out
