copy:
	g++ -fno-elide-constructors copy.cpp -o main

move:
	g++ -fno-elide-constructors move.cpp -o main

copy-elide:
	g++ copy.cpp -o main

move-elide:
	g++ move.cpp -o main

quiz:
	g++ -fno-elide-constructors quiz.cpp -o main

quiz-elide:
	g++ quiz.cpp -o main

clean:
	rm main

%:
	g++ $@.cpp -o main