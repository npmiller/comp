comp
====
This project is a small interpreter for a functional programming language.
It's only purpose is for me to practice C programming on an interesting project. At the moment, the interpreter is absolutely not stable since there's no real error handling, especially at the parsing phase. However it's basic mechanisms are working and you can write things like :

	> function fact { n:number } (if (= n 1) (return 1) (return (* n (fact (- n 1)))))
	> fact 5
	120
	>

And that's pretty much all you can do, there's not any advanced structures implemented such as lists. And right now, numbers are backed only by ints, so no floats or big numbers.

Anyway, my goal was not to build another working programming language but more to explore the building of one from scratch while improving my C programming skills.
