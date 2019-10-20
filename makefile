build:
	gcc -o task1 task1.c -Wall
	gcc -o task2 task2.c -Wall
	gcc -o task3 task3.c -Wall
	gcc -o task4 task4.c -Wall
	gcc -o bonus bonus.c -Wall

run_task1: build
	./task1

run_task2: build
	./task2

run_task3: build
	./task3

run_task4: build
	./task4

run_bonus: build
	./bonus

clean:
	rm -f task1
	rm -f task2
	rm -f task3
	rm -f task4
	rm -f bonus
